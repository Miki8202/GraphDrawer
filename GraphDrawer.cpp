#include "GraphDrawer.h"
#include "wierzcholek.h"
#include "krawedz.h"
#include <QDebug>
#include <ctime>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>


graphics::graphics()
  : QGraphicsScene()
  , nodes()
  , edges()
  , selectedEdge(NULL)
  , selectedNode(NULL)
  , drawmode(NodeDraw)
  , nodeId(0)
  , edgeId(0)
{
  srand (static_cast <unsigned> (time(0)));
}

void graphics::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  if(drawmode == NodeDraw)
    {
     for(Node* node : nodes)
        {
          if(node->contains(event->scenePos()))
            {
              removeNode(node);
              return;
            }
        }
      Node *node = new Node(event->scenePos(),nodeId++);
      nodes.push_back(node);
      addItem(node);
    }
  else
    {
      for(Edge* edge : edges)
        {
          if(edge->contains(event->scenePos()))
            {
              removeEdge(edge);
              return;
            }
        }
    }
}

void graphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  for(Node* node : nodes)
    {
      if(node->contains(event->scenePos()))
        {
          if(drawmode == NodeDraw)
            {
              selectedNode = node;
            }
          else
            {
              Edge *edge = new Edge(node,edgeId++);
              edges.push_back(edge);
              addItem(edge);
              selectedEdge = edge;
            }
        }
    }
}

void graphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

  if(drawmode == NodeDraw && selectedNode != NULL)
    {
      selectedNode->setPos(event->scenePos());
      for (Edge* edge : edges)
        {
          if(edge->getFrom() == selectedNode)
            edge->setStart(selectedNode->scenePos());
          if(edge->getTo() == selectedNode)
            edge->setEnd(selectedNode->scenePos());
        }
      update();
    }
  else if (selectedEdge != NULL)
    {
      selectedEdge->setEnd(event->scenePos());
      update();
    }
}

void graphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  if(drawmode == NodeDraw && selectedNode != NULL)
    {
      selectedNode = NULL;
    }
  else if (selectedEdge != NULL)
    {
      for(Node* node : nodes)
        {
          if(node->contains(event->scenePos()))
            {
              bool cond = false;
              if (selectedEdge->getFrom() == node)
                cond = true;
              else
                {
                  for (neighbor n : node->getAdlist())
                    {
                      if((std::get<1>(n)->getFrom() == selectedEdge->getFrom() &&
                          std::get<1>(n)->getTo() == node)||
                         (std::get<1>(n)->getFrom() == node &&
                          std::get<1>(n)->getTo() == selectedEdge->getFrom()))
                        {
                          cond = true;
                          break;
                        }
                    }
                }
              if(!cond)
                {
                  selectedEdge->setTo(node);
                  node->addNeighbor({selectedEdge->getFrom(),selectedEdge});
                  selectedEdge->getFrom()->addNeighbor({node,selectedEdge});
                  update();
                  selectedEdge = NULL;
                }
              break;
            }
        }
      if(selectedEdge != NULL)
        {
          removeItem(selectedEdge);
          selectedEdge = NULL;
          edges.pop_back();
        }
    }
}

void graphics::removeNode(Node *node)
{
  for(auto i = nodes.begin();i!= nodes.end();++i)
    {
      if(*i == node)
        {
          removeItem(*i);
          std::vector<neighbor> n(std::move((*i)->getAdlist()));
          for (neighbor j : n)
            {
              qDebug() << std::get<1>(j) << std::get<1>(j)->getId();
              removeEdge(std::get<1>(j));

            }
          nodes.erase(i);
          node->removeFromNeighbors();
          delete node;
          return;
        }
    }
}
void graphics::removeEdge(Edge *edge)
{
  for(auto i = edges.begin();i!= edges.end();++i)
    {
      qDebug() << (*i)->getId() << edge->getId();
      if((*i)->getId() == edge->getId())
        {
          removeItem(*i);
          edges.erase(i);
          edge->removeFromNeighbors();
          delete edge;
          return;
        }
    }
}
