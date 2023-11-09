#ifndef CIRCLENODE_H
#define CIRCLENODE_H

#include <QGraphicsObject>
#include <QPen>
#include <QBrush>

class CircleNode : public QGraphicsObject
{
public:
    CircleNode(QGraphicsItem *parent = nullptr);

public:
    void setRadius(qreal radius);
    qreal radius();
    void setText(const QString &text);
    QString text();

    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    qreal m_radius;
    QString m_text;
    QPen m_pen;
    QBrush m_brush;
};

#endif // CIRCLENODE_H
