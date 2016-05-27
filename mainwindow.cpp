#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QTcpSocket>
#include <QByteArray>
#include <QCloseEvent>
#include <QTimer>

#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    socket->write("X\n");
    event->accept();

}

void MainWindow::connectTCP()
{
//    QByteArray data;

    socket = new QTcpSocket(this);
    socket->connectToHost("pizero.local",3344);
//    if(socket->waitForConnected()){
//       socket->write(data);
//    }
    connect(socket,&QIODevice::readyRead, this,&MainWindow::readAllPins);
//    connect(socket,&QIODevice::bytesWritten,this, &MainWindow::)

}

void MainWindow::sendGetAll(){
    qDebug() << "sending Y";
    socket->write("Y\n");
}

void MainWindow::timerSetup(int ms){
    mTimer = new QTimer(this);
    mTimer->setTimerType(Qt::PreciseTimer);
    connect(mTimer,SIGNAL(timeout()), this, SLOT(&MainWindow::timerCallback()));
    qDebug() << "starting timer";
    mTimer->start(ms);
}

void MainWindow::timerCallback(){
    qDebug() << "timer callback";
    socket->write("Y\n");
    socket->waitForBytesWritten();
}

void MainWindow::readAllPins(){

//    qDebug() << socket->bytesAvailable() << "available in readAllPins()";
    if(socket->bytesAvailable() < 64)
        return;

    char bytesRemaining = 64;
    char bytes_pre,bytes_post;

    while(bytesRemaining > 0){
        bytes_pre = pins.size();
        pins.append(socket->read(bytesRemaining));
        bytes_post = pins.size();

        bytesRemaining -= (bytes_post-bytes_pre);
//        qDebug() << QByteArray::number(bytesRemaining) << "remaining";
//        qDebug() << pins.size() << "pins.size";
    }
//    qDebug() << pins.size() << "pins.size";

    for(int i = 0;i<=31;i++){
        gpios[i] = pins[(2*i)+1];
        gpio_modes[i] = pins[2*i];
        setBgColorFromPin(i,gpios[i]);
        setBgColorFromMode(i,gpio_modes[i]);
    }
    pins.clear();


}


void MainWindow::setBgColorFromPin(int gpio, int lvl)
{
    switch (gpio) {
    case 0:
        if(lvl == 1)
            ui->pin_11->setStyleSheet("background-color:green");
        else ui->pin_11->setStyleSheet("background-color:white");
        break;
    case 1:
        if(lvl == 1)
            ui->pin_12->setStyleSheet("background-color:green");
        else ui->pin_12->setStyleSheet("background-color:white");
        break;
    case 2:
        if(lvl == 1)
            ui->pin_13->setStyleSheet("background-color:green");
        else ui->pin_13->setStyleSheet("background-color:white");
        break;
    case 3:
        if(lvl == 1)
            ui->pin_15->setStyleSheet("background-color:green");
        else ui->pin_15->setStyleSheet("background-color:white");
        break;
    case 4:
        if(lvl == 1)
            ui->pin_16->setStyleSheet("background-color:green");
        else ui->pin_16->setStyleSheet("background-color:white");
        break;
    case 5:
        if(lvl == 1)
            ui->pin_18->setStyleSheet("background-color:green");
        else ui->pin_18->setStyleSheet("background-color:white");
        break;
    case 6:
        if(lvl == 1)
            ui->pin_22->setStyleSheet("background-color:green");
        else ui->pin_22->setStyleSheet("background-color:white");
        break;
    case 7:
        if(lvl == 1)
            ui->pin_7->setStyleSheet("background-color:green");
        else ui->pin_7->setStyleSheet("background-color:white");
        break;
    case 8:
        if(lvl == 1)
            ui->pin_3->setStyleSheet("background-color:green");
        else ui->pin_3->setStyleSheet("background-color:white");
        break;
    case 9:
        if(lvl == 1)
            ui->pin_5->setStyleSheet("background-color:green");
        else ui->pin_5->setStyleSheet("background-color:white");
        break;
    case 10:
        if(lvl == 1)
            ui->pin_24->setStyleSheet("background-color:green");
        else ui->pin_24->setStyleSheet("background-color:white");
        break;
    case 11:
        if(lvl == 1)
            ui->pin_26->setStyleSheet("background-color:green");
        else ui->pin_26->setStyleSheet("background-color:white");
        break;
    case 12:
        if(lvl == 1)
            ui->pin_19->setStyleSheet("background-color:green");
        else ui->pin_19->setStyleSheet("background-color:white");
        break;
    case 13:
        if(lvl == 1)
            ui->pin_21->setStyleSheet("background-color:green");
        else ui->pin_21->setStyleSheet("background-color:white");
        break;
    case 14:
        if(lvl == 1)
            ui->pin_23->setStyleSheet("background-color:green");
        else ui->pin_23->setStyleSheet("background-color:white");
        break;
    case 15:
        if(lvl == 1)
            ui->pin_8->setStyleSheet("background-color:green");
        else ui->pin_8->setStyleSheet("background-color:white");
        break;
    case 16:
        if(lvl == 1)
            ui->pin_10->setStyleSheet("background-color:green");
        else ui->pin_10->setStyleSheet("background-color:white");
        break;
        // no wiringpi gpio pins between 16 and 21!
    case 21:
        if(lvl == 1)
            ui->pin_29->setStyleSheet("background-color:green");
        else ui->pin_29->setStyleSheet("background-color:white");
        break;
    case 22:
        if(lvl == 1)
            ui->pin_31->setStyleSheet("background-color:green");
        else ui->pin_31->setStyleSheet("background-color:white");
        break;
    case 23:
        if(lvl == 1)
            ui->pin_33->setStyleSheet("background-color:green");
        else ui->pin_33->setStyleSheet("background-color:white");
        break;
    case 24:
        if(lvl == 1)
            ui->pin_35->setStyleSheet("background-color:green");
        else ui->pin_35->setStyleSheet("background-color:white");
        break;
    case 25:
        if(lvl == 1)
            ui->pin_37->setStyleSheet("background-color:green");
        else ui->pin_37->setStyleSheet("background-color:white");
        break;
    case 26:
        if(lvl == 1)
            ui->pin_32->setStyleSheet("background-color:green");
        else ui->pin_32->setStyleSheet("background-color:white");
        break;
    case 27:
        if(lvl == 1)
            ui->pin_36->setStyleSheet("background-color:green");
        else ui->pin_36->setStyleSheet("background-color:white");
        break;
    case 28:
        if(lvl == 1)
            ui->pin_38->setStyleSheet("background-color:green");
        else ui->pin_38->setStyleSheet("background-color:white");
        break;
    case 29:
        if(lvl == 1)
            ui->pin_40->setStyleSheet("background-color:green");
        else ui->pin_40->setStyleSheet("background-color:white");
        break;
    case 30:
        if(lvl == 1)
            ui->pin_27->setStyleSheet("background-color:green");
        else ui->pin_27->setStyleSheet("background-color:white");
        break;
    default:
        break;
    }
}



void MainWindow::setBgColorFromMode(int gpio, int lvl)
{
    switch (gpio) {
    case 0:
        if(lvl == 1)
            ui->pin_mode_11->setStyleSheet("background-color:blue");
        else ui->pin_mode_11->setStyleSheet("background-color:white");
        break;
    case 1:
        if(lvl == 1)
            ui->pin_mode_12->setStyleSheet("background-color:blue");
        else ui->pin_mode_12->setStyleSheet("background-color:white");
        break;
    case 2:
        if(lvl == 1)
            ui->pin_mode_13->setStyleSheet("background-color:blue");
        else ui->pin_mode_13->setStyleSheet("background-color:white");
        break;
    case 3:
        if(lvl == 1)
            ui->pin_mode_15->setStyleSheet("background-color:blue");
        else ui->pin_mode_15->setStyleSheet("background-color:white");
        break;
    case 4:
        if(lvl == 1)
            ui->pin_mode_16->setStyleSheet("background-color:blue");
        else ui->pin_mode_16->setStyleSheet("background-color:white");
        break;
    case 5:
        if(lvl == 1)
            ui->pin_mode_18->setStyleSheet("background-color:blue");
        else ui->pin_mode_18->setStyleSheet("background-color:white");
        break;
    case 6:
        if(lvl == 1)
            ui->pin_mode_22->setStyleSheet("background-color:blue");
        else ui->pin_mode_22->setStyleSheet("background-color:white");
        break;
    case 7:
        if(lvl == 1)
            ui->pin_mode_7->setStyleSheet("background-color:blue");
        else ui->pin_mode_7->setStyleSheet("background-color:white");
        break;
    case 21:
        if(lvl == 1)
            ui->pin_mode_29->setStyleSheet("background-color:blue");
        else ui->pin_mode_29->setStyleSheet("background-color:white");
        break;
    case 22:
        if(lvl == 1)
            ui->pin_mode_31->setStyleSheet("background-color:blue");
        else ui->pin_mode_31->setStyleSheet("background-color:white");
        break;
    case 23:
        if(lvl == 1)
            ui->pin_mode_33->setStyleSheet("background-color:blue");
        else ui->pin_mode_33->setStyleSheet("background-color:white");
        break;
    case 24:
        if(lvl == 1)
            ui->pin_mode_35->setStyleSheet("background-color:blue");
        else ui->pin_mode_35->setStyleSheet("background-color:white");
        break;
    case 25:
        if(lvl == 1)
            ui->pin_mode_37->setStyleSheet("background-color:blue");
        else ui->pin_mode_37->setStyleSheet("background-color:white");
        break;
    case 26:
        if(lvl == 1)
            ui->pin_mode_32->setStyleSheet("background-color:blue");
        else ui->pin_mode_32->setStyleSheet("background-color:white");
        break;
    case 27:
        if(lvl == 1)
            ui->pin_mode_36->setStyleSheet("background-color:blue");
        else ui->pin_mode_36->setStyleSheet("background-color:white");
        break;
    case 28:
        if(lvl == 1)
            ui->pin_mode_38->setStyleSheet("background-color:blue");
        else ui->pin_mode_38->setStyleSheet("background-color:white");
        break;
    case 29:
        if(lvl == 1)
            ui->pin_mode_40->setStyleSheet("background-color:blue");
        else ui->pin_mode_40->setStyleSheet("background-color:white");
        break;
    default:
        break;
    }
}


void MainWindow::writeTCPData()
{

}

void MainWindow::pinToggle(int pin)
{
    QByteArray msg;
    msg.append("B");
    msg.append(pin+0x30);
    if(gpios[pin]) msg.append("0\n");
    if(!gpios[pin]) msg.append("1\n");
    socket->write(msg);
}

void MainWindow::pinModeToggle(int pin)
{

    QByteArray msg;
    msg.append("A");
    msg.append(pin+0x30);
    if(gpio_modes[pin]) msg.append("1\n");
    if(!gpio_modes[pin]) msg.append("0\n");
    socket->write(msg);

}

void MainWindow::on_pushButton_clicked()
{
    sendGetAll();
}

void MainWindow::on_pin_11_clicked()
{
    pinToggle(0);
    sendGetAll();
}

void MainWindow::on_pin_12_clicked()
{
    pinToggle(1);
    sendGetAll();
}

void MainWindow::on_pin_13_clicked()
{
    pinToggle(2);
    sendGetAll();
}

void MainWindow::on_pin_15_clicked()
{
    pinToggle(3);
    sendGetAll();
}

void MainWindow::on_pin_16_clicked()
{
    pinToggle(4);
    sendGetAll();
}

void MainWindow::on_pin_18_clicked()
{
    pinToggle(5);
    sendGetAll();
}

void MainWindow::on_pin_22_clicked()
{
    pinToggle(6);
    sendGetAll();
}

void MainWindow::on_pin_7_clicked()
{
    pinToggle(7);
    sendGetAll();
}

void MainWindow::on_pin_3_clicked()
{
    pinToggle(8);
    sendGetAll();
}

void MainWindow::on_pin_5_clicked()
{
    pinToggle(9);
    sendGetAll();
}

void MainWindow::on_pin_24_clicked()
{
    pinToggle(10);
    sendGetAll();
}

void MainWindow::on_pin_26_clicked()
{
    pinToggle(11);
    sendGetAll();
}

void MainWindow::on_pin_19_clicked()
{
    pinToggle(12);
    sendGetAll();
}

void MainWindow::on_pin_21_clicked()
{
    pinToggle(13);
    sendGetAll();
}

void MainWindow::on_pin_23_clicked()
{
    pinToggle(14);
    sendGetAll();
}

void MainWindow::on_pin_8_clicked()
{
    pinToggle(15);
    sendGetAll();
}

void MainWindow::on_pin_10_clicked()
{
    pinToggle(16);
    sendGetAll();
}

void MainWindow::on_pin_29_clicked()
{
    pinToggle(21);
    sendGetAll();
}

void MainWindow::on_pin_31_clicked()
{
    pinToggle(22);
    sendGetAll();
}

void MainWindow::on_pin_33_clicked()
{
    pinToggle(23);
    sendGetAll();
}

void MainWindow::on_pin_35_clicked()
{
    pinToggle(24);
    sendGetAll();
}

void MainWindow::on_pin_37_clicked()
{
    pinToggle(25);
    qDebug() << "sendGetAll from pin37 clicked";
    sendGetAll();
}

void MainWindow::on_pin_32_clicked()
{
    pinToggle(26);
    sendGetAll();
}

void MainWindow::on_pin_36_clicked()
{
    pinToggle(27);
    sendGetAll();
}

void MainWindow::on_pin_38_clicked()
{
    pinToggle(28);
    sendGetAll();
}

void MainWindow::on_pin_40_clicked()
{
    pinToggle(29);
    sendGetAll();
}

void MainWindow::on_pin_27_clicked()
{
    pinToggle(30);
    sendGetAll();
}

void MainWindow::on_pin_28_clicked()
{
    pinToggle(31);
    sendGetAll();
}

void MainWindow::on_pin_mode_7_clicked()
{
    pinModeToggle(7);
}

void MainWindow::on_pin_mode_11_clicked()
{
    pinModeToggle(0);
}

void MainWindow::on_pin_mode_12_clicked()
{
    pinModeToggle(1);
}

void MainWindow::on_pin_mode_13_clicked()
{
    pinModeToggle(2);
}

void MainWindow::on_pin_mode_15_clicked()
{
    pinModeToggle(3);
}

void MainWindow::on_pin_mode_16_clicked()
{
    pinModeToggle(4);
}

void MainWindow::on_pin_mode_18_clicked()
{
    pinModeToggle(5);
}

void MainWindow::on_pin_mode_22_clicked()
{
    pinModeToggle(6);
}

void MainWindow::on_pin_mode_29_clicked()
{
    pinModeToggle(21);
}

void MainWindow::on_pin_mode_31_clicked()
{
    pinModeToggle(22);
}

void MainWindow::on_pin_mode_32_clicked()
{
    pinModeToggle(26);
}

void MainWindow::on_pin_mode_33_clicked()
{
    pinModeToggle(23);
}

void MainWindow::on_pin_mode_35_clicked()
{
    pinModeToggle(24);
}

void MainWindow::on_pin_mode_36_clicked()
{
    pinModeToggle(27);
}

void MainWindow::on_pin_mode_37_clicked()
{
    pinModeToggle(25);
}

void MainWindow::on_pin_mode_38_clicked()
{
    pinModeToggle(28);
}

void MainWindow::on_pin_mode_40_clicked()
{
    pinModeToggle(29);
}
