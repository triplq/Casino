#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStateMachine* machine = new QStateMachine();

    QTimer *timer = new QTimer();

    QState* waiting = new QState();
    QState* rolling = new QState();
    QState* showWin = new QState();

    waiting->addTransition(ui->startButton, &QPushButton::clicked, rolling);
    rolling->addTransition(timer, &QTimer::timeout, showWin);
    showWin->addTransition(this, &MainWindow::signalOnWaiting, waiting);
    rolling->addTransition(ui->stopButton, &QPushButton::clicked, waiting);

    connect(waiting, &QState::entered, []()
    {
        qDebug() << "We r in a waiting state\n";
    });

    connect(rolling, &QState::entered, [=]()
    {
        qDebug() << "We r in a rolling state wait . . .\n";

        timer->start(5000);
    });

    connect(showWin, &QState::entered, [=]()
    {
        int ret = QMessageBox::information(this, "Win!", "Ur win is 0$ =)", QMessageBox::Cancel);

        qDebug() << "We r showing win\n";

        if(ret == QMessageBox::Cancel)
            emit signalOnWaiting();
    });

    machine->addState(showWin);
    machine->addState(waiting);
    machine->addState(rolling);

    machine->setInitialState(waiting);
    machine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
