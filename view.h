#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
public:
    View(QWidget *parent = nullptr);
    View(QGraphicsScene *scene, QWidget *parent = nullptr);
};

#endif // VIEW_H
