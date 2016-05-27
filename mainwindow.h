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
    void pinModeToggle(int pin);
    void closeEvent(QCloseEvent *event);
    void setBgColorFromPin(int pin,int lvl);
    void setBgColorFromMode(int gpio, int lvl);
    void timerSetup(int ms);

private slots:

    void on_pushButton_clicked();

    void on_pin_37_clicked();

    void readAllPins();

    void timerCallback();


    void on_pin_32_clicked();
    void on_pin_36_clicked();
    void on_pin_38_clicked();
    void on_pin_40_clicked();
    void on_pin_27_clicked();
    void on_pin_28_clicked();
    void on_pin_11_clicked();
    void on_pin_12_clicked();
    void on_pin_13_clicked();
    void on_pin_15_clicked();
    void on_pin_16_clicked();
    void on_pin_18_clicked();
    void on_pin_22_clicked();
    void on_pin_7_clicked();
    void on_pin_3_clicked();
    void on_pin_5_clicked();
    void on_pin_24_clicked();
    void on_pin_26_clicked();
    void on_pin_19_clicked();
    void on_pin_21_clicked();
    void on_pin_23_clicked();
    void on_pin_8_clicked();
    void on_pin_10_clicked();
    void on_pin_29_clicked();
    void on_pin_31_clicked();
    void on_pin_33_clicked();
    void on_pin_35_clicked();

    void on_pin_mode_7_clicked();

    void on_pin_mode_11_clicked();

    void on_pin_mode_12_clicked();

    void on_pin_mode_13_clicked();

    void on_pin_mode_15_clicked();

    void on_pin_mode_16_clicked();

    void on_pin_mode_18_clicked();

    void on_pin_mode_22_clicked();

    void on_pin_mode_29_clicked();

    void on_pin_mode_31_clicked();

    void on_pin_mode_32_clicked();

    void on_pin_mode_33_clicked();

    void on_pin_mode_35_clicked();

    void on_pin_mode_36_clicked();

    void on_pin_mode_37_clicked();

    void on_pin_mode_38_clicked();

    void on_pin_mode_40_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray pins;
    char gpio_modes[31];
    char gpios[31];
    QTimer *mTimer;
};

#endif // MAINWINDOW_H
