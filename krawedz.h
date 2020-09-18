#ifndef EDGE_H
#define EDGE_H
#include "wierzcholek.h"
#include <QtGui>
#include <QGraphicsLineItem>

class Node;
class Edge : public QGraphicsLineItem
{
public:
  Edge(Node* from,int id);
  Edge(int id,QString label,QPointF start,QPointF end);

  QRectF boundingRect() const;
  bool contains(const QPointF &pos) const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
  Node* getFrom() const {return from;}
  Node* getTo() const {return to;}
  QString getLabel() const {return label;}
  QPointF getStart() const {return start;}
  QPointF getEnd() const {return end;}
  int getId() const {return id;}
  void setEnd(QPointF pos){end = pos;}
  void setStart(QPointF pos){start = pos;}
  void setTo(Node* node){end = node->pos();to = node;}
  void setFrom(Node* node){start = node->pos();from = node;}
  void removeFromNeighbors();
private:
  QString label;
  Node* from;
  Node* to;
  QPointF start;
  QPointF end;
  int id;
};
#endif // EDGE_H
