#include "mainwindow.h"

#include <QThread.h>
#include <QMessageBox>
#include <QRandomGenerator>

#include "./ui_mainwindow.h"
#include "recvfile.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    setWindowTitle("Client");
    
    qDebug() << "Main Thread:" << QThread::currentThread();
    
    ui->ip->setText("127.0.0.1");
    ui->port->setText("9999");
    
    QThread* recv_file_thread = new QThread;
    
    RecvFile* worker = new RecvFile;
    
    worker->moveToThread(recv_file_thread);
    
    connect(this, &MainWindow::start_connect, worker, &RecvFile::connect_server);
    
    connect(worker, &RecvFile::message, this, [=](QByteArray msg) {
        QVector<QColor> colors = {Qt::red, Qt::green, Qt::black, Qt::blue, Qt::darkRed, Qt::cyan, Qt::magenta};
        
        int index = QRandomGenerator::global()->bounded(colors.size());
        
        ui->message->setTextColor(colors.at(index));
        ui->message->append(msg); 
    });
    
    connect(worker, &RecvFile::connected, this, [=]() {
        QMessageBox::information(this, "Connected Server", "Successfully connected to the server");
    });
    
    connect(worker, &RecvFile::connection_error, this, [=]() {
        QMessageBox::warning(this, "Not Connected Server", "Connection error");
    });
    
    connect(worker, &RecvFile::recv_completed, this, [=]() {
        qDebug() << "Destory recv_file_thread...";
        
        recv_file_thread->quit();
        recv_file_thread->wait();
        recv_file_thread->deleteLater();
        
        worker->deleteLater();
    });
    
    recv_file_thread->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_connect_clicked() {
    QString ip = ui->ip->text();
    unsigned short port = ui->port->text().toUShort();
    
    emit start_connect(ip, port);
}
