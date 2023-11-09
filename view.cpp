#include "view.h"

View::View(QWidget *parent) : QGraphicsView(parent)
{
    this->setFixedSize(800, 600);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

View::View(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene, parent)
{

}
