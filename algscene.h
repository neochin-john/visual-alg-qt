#ifndef ALGSCENE_H
#define ALGSCENE_H

#include <QGraphicsScene>
#include <QList>

class CircleNode;
class QGraphicsObject;
class AlgScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit AlgScene(QObject *parent = nullptr);

    void setData(const QList<int> &data);

    void swap(int idx1, int idx2);
    void compare(int idx1, int idx2);



signals:
    void s_complete();

protected:
    void timerEvent(QTimerEvent *event) override;

private:
    void complete();

private:
    QList<CircleNode *> m_items;
    QList<CircleNode *> m_compareItems;
    bool inAnimation;
    qreal m_circleRectSize;

    QPen m_defaultPen;
    QBrush m_defaultBrush;
    QPen m_comparePen;
    QBrush m_compareBrush;

    int m_timerId;
};

#endif // ALGSCENE_H
