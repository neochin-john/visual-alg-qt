#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGridLayout;
class AlgScene;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    AlgScene *algScene();
private slots:
    void on_pushButton_clicked();

private:
    AlgScene *m_algScene;

    QGridLayout *m_gridLayout;
};
#endif // MAINWINDOW_H
