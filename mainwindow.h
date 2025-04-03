#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <QState>
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>
#include <QVector>
#include "reel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QStateMachine *machine;

    QState *waiting;
    QState *rolling;
    QState *showWin;

    void startStateMachine();

    QVector<QPixmap*> images;

 signals:
    void signalOnWaiting();

};
#endif // MAINWINDOW_H
