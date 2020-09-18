#ifndef NODE_H
#define NODE_H

#include <QtGui>
#include <QGraphicsEllipseItem>

#define RADIUS 10
class Node;
class Edge;
typedef std::pair<Node*,Edge*> neighbor;

class Node : public QGraphicsEllipseItem
{
public:
  Node(QPointF pos,int id);
  Node(int id, QString label, QPointF pos);

  QRectF boundingRect() const;
  bool contains(const QPointF &pos) const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
  void addNeighbor(std::pair<Node*,Edge*> neigh){adlist.push_back(neigh);}

  int getId() const {return id;}
  std::vector<neighbor>& getAdlist() {return adlist;}
  QString getLabel() const {return label;}
  void getNodeInfo() const;
  void setLabel(QString label) {label = label;}
  void removeNeighbor(Node *node);
  void removeFromNeighbors();
private:
  int id;
  std::vector<neighbor> adlist;
  QString label;
};
#endif // NODE_H
