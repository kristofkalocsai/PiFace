#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTextStream>

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
    void readAllPins();
    void pinToggle(int pin);
    void closeEvent(QCloseEvent *event);
    void setBgColorFromPin(int pin,int lvl);

private slots:

    void on_pushButton_clicked();

    void on_pin_37_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray pins;
    char gpios[31];
    QTextStream out();

};

#endif // MAINWINDOW_H
