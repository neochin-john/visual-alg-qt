#include <QBuffer>
#include <QDebug>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QThread>
#include <cstdio>

#include "circlenode.h"
#include "algscene.h"

AlgScene::AlgScene(QObject *parent)
        : QGraphicsScene(parent)
        , inAnimation(false)
        , m_defaultPen(Qt::black, 2)
        , m_defaultBrush(Qt::white)
        , m_comparePen(Qt::red, 2)
        , m_compareBrush(Qt::yellow)
{
    connect(this, &AlgScene::s_complete, this, &AlgScene::complete);
}

void AlgScene::setData(const QList<int> &data)
{
    this->clear();
    m_items.clear();
    m_compareItems.clear();

    qreal horizontalMagin = 50;
    qreal circleRectPadding = 5;

    qreal paintWidth = this->sceneRect().width() - horizontalMagin * 2;
    m_circleRectSize = paintWidth / data.size();
    qreal circleRadius = m_circleRectSize / 2 - circleRectPadding;
    qreal y = this->sceneRect().height() / 2;

    for (int i = 0; i < data.size(); i++)
    {
        CircleNode *node = new CircleNode;
        node->setRadius(circleRadius);
        node->moveBy(horizontalMagin + i * m_circleRectSize + m_circleRectSize / 2, y);

        node->setPen(m_defaultPen);
        node->setBrush(m_defaultBrush);
        node->setText(QString::number(data.at(i)));

        this->addItem(node);
        m_items.append(node);
    }

    m_timerId = startTimer(50);
}

void AlgScene::swap(int idx1, int idx2)
{
    if (inAnimation)
    {
        return;
    }

    if (idx1 == idx2)
    {
        qDebug() << "same index, no need to swap";
        return;
    }

    if (idx1 < 0 || idx1 >= m_items.size()
            || idx2 < 0 || idx2 >= m_items.size())
    {
        qDebug() << "bad swap idx";
        return;
    }

    int duration = 500;
    int minIdx = qMin(idx1, idx2);
    int maxIdx = qMax(idx1, idx2);
    CircleNode *leftItem = m_items.at(minIdx);
    CircleNode *rightItem = m_items.at(maxIdx);

    QParallelAnimationGroup *group = new QParallelAnimationGroup();
    QPropertyAnimation *leftItemAni = new QPropertyAnimation(leftItem, "pos");
    leftItemAni->setKeyValues(QPropertyAnimation::KeyValues{
                                  QPropertyAnimation::KeyValue(0, leftItem->pos()),
                                  QPropertyAnimation::KeyValue(0.25, leftItem->pos() + QPointF(0, m_circleRectSize)),
                                  QPropertyAnimation::KeyValue(0.75, rightItem->pos() + QPointF(0, m_circleRectSize)),
                                  QPropertyAnimation::KeyValue(1, rightItem->pos()),
                              });
    leftItemAni->setDuration(duration);
    leftItemAni->setEasingCurve(QEasingCurve::Linear);

    QPropertyAnimation *rightItemAni = new QPropertyAnimation(rightItem, "pos");
    rightItemAni->setKeyValues(QPropertyAnimation::KeyValues{
                                  QPropertyAnimation::KeyValue(0, rightItem->pos()),
                                  QPropertyAnimation::KeyValue(0.25, rightItem->pos() - QPointF(0, m_circleRectSize)),
                                  QPropertyAnimation::KeyValue(0.75, leftItem->pos() - QPointF(0, m_circleRectSize)),
                                  QPropertyAnimation::KeyValue(1, leftItem->pos()),
                              });
    rightItemAni->setDuration(duration);
    rightItemAni->setEasingCurve(QEasingCurve::Linear);

    group->addAnimation(leftItemAni);
    group->addAnimation(rightItemAni);
    connect(group, &QParallelAnimationGroup::finished, this, [=](){
        group->deleteLater();
        this->m_items.swap(minIdx, maxIdx);
        this->inAnimation = false;
    });

    group->start();
    inAnimation = true;
}

void AlgScene::compare(int idx1, int idx2)
{
    if (!m_compareItems.empty())
    {
        foreach (CircleNode *o, m_compareItems)
        {
            o->setPen(m_defaultPen);
            o->setBrush(m_defaultBrush);
            o->update();
        }
    }

    m_compareItems.clear();
    m_items[idx1]->setPen(m_comparePen);
    m_items[idx1]->setBrush(m_compareBrush);
    m_items[idx1]->update();
    m_items[idx2]->setPen(m_comparePen);
    m_items[idx2]->setBrush(m_compareBrush);
    m_items[idx2]->update();
    m_compareItems.append(m_items[idx1]);
    m_compareItems.append(m_items[idx2]);
}

void AlgScene::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    return;

    // write image files
    static int i = 0;
    QPixmap pixmap(this->sceneRect().width(), this->sceneRect().height());
    QPainter painter(&pixmap);
    this->render(&painter);
    QBuffer buffer;
    buffer.open(QBuffer::ReadWrite);
    pixmap.save(QString("../xxx/alg_%1.jpg").arg(i));
    pixmap.save(&buffer, "PNG");

    fwrite(buffer.data().data(), 1, buffer.size(), stdout);
    printf("\n");
    fflush(stdout);
    i++;
}

void AlgScene::complete()
{
    if (!m_compareItems.empty())
    {
        foreach (CircleNode *o, m_compareItems)
        {
            o->setPen(m_defaultPen);
            o->setBrush(m_defaultBrush);
            o->update();
        }
    }

    killTimer(m_timerId);
}
