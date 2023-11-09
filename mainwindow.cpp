#include "circlenode.h"
#include "mainwindow.h"
#include "algscene.h"
#include "ui_mainwindow.h"
#include "view.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centeralWidget = new QWidget;
    centeralWidget->setStyleSheet("QWidget {background-color: red}");
    this->setCentralWidget(centeralWidget);

    m_gridLayout = new QGridLayout();
    centeralWidget->setLayout(m_gridLayout);

    View *view = new View;
    m_gridLayout->addWidget(view, 0, 0);

    m_algScene = new AlgScene;
    m_algScene->setSceneRect(view->rect());
    m_algScene->setBackgroundBrush(QBrush(Qt::gray));

    view->setScene(m_algScene);

}

MainWindow::~MainWindow()
{
}

AlgScene *MainWindow::algScene()
{
    return m_algScene;
}


void MainWindow::on_pushButton_clicked()
{
    static int i = 0;
    m_algScene->compare(i, i+1);
    m_algScene->swap(i, i+1);
    i++;
}

