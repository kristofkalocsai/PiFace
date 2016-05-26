#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTextStream>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectTCP();
    void readTCPData();
    void writeTCPData();
    void sendGetAll();
    void pinToggle(int pin);
    void closeEvent(QCloseEvent *event);
    void setBgColorFromPin(int pin,int lvl);
    void timerSetup(int ms);

private slots:

    void on_pushButton_clicked();

    void on_pin_37_clicked();

    void readAllPins();

    void timerCallback();


private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray pins;
    char gpios[31];
    QTimer *mTimer;
};

#endif // MAINWINDOW_H
