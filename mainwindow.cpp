#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<QPixmap> images;
    reel1 = new Reel(this);
    reel2 = new Reel(this);
    reel3 = new Reel(this);

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
    machine = new QStateMachine(this);

    waiting = new QState(machine);
    rolling = new QState(machine);
    showWin = new QState(machine);

    machine->setInitialState(waiting);

    waiting->addTransition(ui->startButton, &QPushButton::clicked, rolling);

    rolling->addTransition(ui->stopButton, &QPushButton::clicked, waiting);
    rolling->addTransition(this, &MainWindow::signalOnWaiting, waiting);
    rolling->addTransition(this, &MainWindow::signalOnWin, showWin);

    showWin->addTransition(this, &MainWindow::signalOnWaiting, waiting);

    auto checkWin = [=]()
    {
        if(reel1->currentOffsetIndex() == reel2->currentOffsetIndex() && reel2->currentOffsetIndex() == reel3->currentOffsetIndex())
            emit signalOnWin();

        else
            emit signalOnWaiting();
    };

    connect(reel3, &Reel::spinningFinished, checkWin);

    connect(waiting, &QState::entered, [=]()
    {
        ui->statusbar->showMessage("Waiting . . .");
        reel1->stop_spinning();
        reel2->stop_spinning();
        reel3->stop_spinning();
    });

    connect(rolling, &QState::entered, [=]()
    {
        ui->statusbar->showMessage("Rolling . . .");
        reel1->spin(4000);
        reel2->spin(5000);
        reel3->spin(6000);
    });

    connect(showWin, &QState::entered, [=]()
    {
        ui->statusbar->showMessage("WIN");


        QMessageBox* msgBox = new QMessageBox(QMessageBox::Information, tr("Win!"), tr("U have a great WIN"), QMessageBox::Cancel, this);
        msgBox->show();

        connect(msgBox, &QMessageBox::buttonClicked, [=]()
        {
            reel1->stop_spinning();
            reel2->stop_spinning();
            reel3->stop_spinning();

            emit signalOnWaiting();
            msgBox->deleteLater();
        });
    });

    machine->start();
}


MainWindow::~MainWindow()
{
    delete ui;
}
