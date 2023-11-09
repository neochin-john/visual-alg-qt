#include "circlenode.h"

#include <QPainter>
#include <QTextItem>
#include <QGraphicsScene>

CircleNode::CircleNode(QGraphicsItem *parent)
    : QGraphicsObject(parent)
        , m_radius(50)
        , m_text("")
        , m_pen(Qt::black)
        , m_brush(Qt::white)
{

}

void CircleNode::setRadius(qreal radius)
{
    m_radius = radius;
}

qreal CircleNode::radius()
{
    return m_radius;
}

void CircleNode::setText(const QString &text)
{
    m_text = text;
}

QString CircleNode::text()
{
    return m_text;
}

void CircleNode::setPen(const QPen &pen)
{
    m_pen = pen;
}

void CircleNode::setBrush(const QBrush &brush)
{
    m_brush = brush;
}

QRectF CircleNode::boundingRect() const
{
    return QRectF(-m_radius, -m_radius, 2 * m_radius, 2 * m_radius);
}

void CircleNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setPen(m_pen);
    painter->setBrush(m_brush);

    painter->drawEllipse(QPointF(0, 0), m_radius, m_radius);

    QRect rect = painter->fontMetrics().boundingRect(m_text);
    painter->drawText(-rect.center(), m_text);

    painter->restore();
    return;
}
