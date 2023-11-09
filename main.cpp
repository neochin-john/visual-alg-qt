#include "mainwindow.h"
#include "visuallist.h"

#include <QApplication>
#include <QList>
#include <QDebug>
#include <QThread>
#include "algscene.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QList<int> orgList{3, 2, 67, 43, 56, 22, 12, 9};
    VisualList data(orgList);
    w.algScene()->setData(orgList);
    QObject::connect(&data, &VisualList::s_compare, w.algScene(), &AlgScene::compare);
    QObject::connect(&data, &VisualList::s_swap, w.algScene(), &AlgScene::swap);

    QThread *thd = QThread::create([&](){
        for (int i = 0; i < data.size() - 1; i++)
        {
            for (int j = 0; j < data.size() - i - 1; j++)
            {
                // scene-compare(j, j+1)
                if (data[j] > data[j+1])
                {
                    // scene->swap(j, j+1)
                    data.swap(j, j+1);
                }
            }
        }

        emit w.algScene()->s_complete();
    });

    thd->start();
    QObject::connect(thd, &QThread::finished, thd, &QObject::deleteLater);

    return a.exec();
}
