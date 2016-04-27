#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qextserialport.h>
#include <qextserialenumerator.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QextSerialPort * port = new QextSerialPort();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    bool success;
    bool time_to_exit;
    QTimer* tmrTimer;
    QTimer *heartbeatTimer;
    QTimer* tmr_serial_timeout;

    void main_slot();
    void read_messages();

    int _refresh_serial();
    int connect_serial();

    void heartbeat();

    void on_PortRefresh_released();
    void on_sendButton_released();
    void on_portBox_currentIndexChanged(const QString &arg1);
    void on_connectButton_released();
    void on_pushButton_released();

    void on_parachuteButton_released();

    void on_setServoButton_released();


    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
