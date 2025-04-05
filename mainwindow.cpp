#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<QPixmap> images;
    reel1 = new Reel;
    reel2 = new Reel;
    reel3 = new Reel;

    QHBoxLayout* layout = new QHBoxLayout(ui->slotsWidget);
    layout->addWidget(reel1);
    layout->addWidget(reel2);
    layout->addWidget(reel3);

    images.emplace_back(QPixmap("/Users/alexey/Casino/icons/apple.png"));
    images.emplace_back(QPixmap("/Users/alexey/Casino/icons/pineapple.png"));
    images.emplace_back(QPixmap("/Users/alexey/Casino/icons/watermelon.png"));
    images.emplace_back(QPixmap("/Users/alexey/Casino/icons/banana.png"));

    reel1->setSlots(images);
    reel2->setSlots(images);
    reel3->setSlots(images);

    startStateMachine();
}

void MainWindow::startStateMachine()
{
    QStateMachine* machine = new QStateMachine();

    QState* waiting = new QState();
    QState* rolling = new QState();
    QState* showWin = new QState();

    waiting->addTransition(ui->startButton, &QPushButton::clicked, rolling);

    rolling->addTransition(ui->stopButton, &QPushButton::clicked, waiting);
    rolling->addTransition(this, &MainWindow::signalOnWaiting, waiting);
    rolling->addTransition(this, &MainWindow::signalOnWin, showWin);

    showWin->addTransition(this, &MainWindow::signalOnWaiting, waiting);

    //connect(reel3, &Reel::spinningStopped, [=](){ emit signalOnWaiting(); });

    connect(reel3, &Reel::spinningFinished, [=]()
    {
        if(reel1->currentOffsetIndex() == reel2->currentOffsetIndex() && reel2->currentOffsetIndex() == reel3->currentOffsetIndex())
            emit signalOnWin();
        else
            emit signalOnWaiting();
    });

    connect(waiting, &QState::entered, [=]()
    {
        reel1->stop_spinning();
        reel2->stop_spinning();
        reel3->stop_spinning();

        ui->statusbar->showMessage("Waiting . . .");
    });

    connect(rolling, &QState::entered, [=]()
    {
        reel1->spin(4000);
        reel2->spin(5000);
        reel3->spin(6000);

        ui->statusbar->showMessage("Rolling . . .");
    });

    connect(showWin, &QState::entered, [=]()
    {
        ui->statusbar->showMessage("WIN");

        int ret = QMessageBox::information(this, "Win!", "U have a great WIN", QMessageBox::Cancel);

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
