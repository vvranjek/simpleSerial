#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTimer"
#include "qextserialenumerator.h"
#include "iostream"
#include "fstream"
#include <sys/time.h>
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_PortRefresh_released();

    tmrTimer = new QTimer(this);
    connect(tmrTimer,  SIGNAL(timeout()),this,SLOT(main_slot()));
    tmrTimer->start(30);
    heartbeatTimer = new QTimer(this);
    connect(heartbeatTimer,  SIGNAL(timeout()),this,SLOT(heartbeat()));
    heartbeatTimer->start(1000);

    QStringList _baud_rates;
    _baud_rates << "4800" << "9600" << "19200" << "38400" << "57600" << "115200" << "230400";
    ui->baudBox->addItems(_baud_rates);
    ui->baudBox->setCurrentIndex(ui->baudBox->findText("115200"));

    _refresh_serial();
    connect_serial();

}

void MainWindow::main_slot()
{
    ui->serialIn->append(port->readAll());

}

void MainWindow::on_PortRefresh_released()
{
    _refresh_serial();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_portBox_currentIndexChanged(const QString &arg1)
{
    // _refresh_serial();
}


int MainWindow::_refresh_serial(){
    ui->portBox->clear();
    // Serch for serial ports and put them in portBox
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts()){
        if(info.portName.contains("ACM") || info.portName.contains("USB")) {
            ui->portBox->addItem(info.portName);
            ui->portBox->setCurrentIndex(ui->portBox->findText(info.portName));
        }
    }
}

int MainWindow::connect_serial(){

    port->close();

    port->setBaudRate(ui->baudBox->currentText().toInt());
    port->setPortName(ui->portBox->currentText());

    if (!port->open(QIODevice::ReadWrite)){
        printf("Connected to %s", ui->portBox->currentText().toStdString());
        return 0;
    }
    else {
        return 1;
    }
}

void MainWindow::on_connectButton_released() {
    if (!ui->connectButton->isChecked()){
        port->close();
    }
    else {
        connect_serial();
    }
}
