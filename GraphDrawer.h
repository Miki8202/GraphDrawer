#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class Edge;
class Node;

class graphics : public QGraphicsScene
{
  Q_OBJECT
public:
  graphics();
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *gsme);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *gsme);
  void mousePressEvent(QGraphicsSceneMouseEvent *gsme);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *gsme);
  void removeNode(Node *node);
  void removeEdge(Edge *edge);
public slots:
  void setNodeDrawMode(){drawmode = NodeDraw;}
  void setEdgeDrawMode(){drawmode = EdgeDraw;}
private:
  std::vector<Node*> nodes;
  std::vector<Edge*> edges;
  Edge *selectedEdge;
  Node *selectedNode;
  enum drawmode{NodeDraw,EdgeDraw} drawmode;
  int nodeId;
  int edgeId;
};


#endif // GRAPHICS_H
