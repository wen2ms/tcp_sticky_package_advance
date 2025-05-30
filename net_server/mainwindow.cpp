#include "mainwindow.h"

#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QRandomGenerator>

#include "./ui_mainwindow.h"
#include "sendfile.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    server_ = new MyTcpServer(this);
    
    connect(server_, &MyTcpServer::new_client, this, [=](qintptr socket) {
        QThread* send_file_thread = new QThread;
        
        SendFile* worker = new SendFile(socket);
        
        worker->moveToThread(send_file_thread);
        
        connect(this, &MainWindow::start, worker, &SendFile::working);
        
        connect(worker, &SendFile::send_complete, this, [=]() {
            send_file_thread->quit();
            send_file_thread->wait();
            
            worker->deleteLater();
            send_file_thread->deleteLater();
        });
        
        connect(worker, &SendFile::text, this, [=](QByteArray msg) {
            QVector<QColor> colors = {Qt::red, Qt::green, Qt::black, Qt::blue, Qt::darkRed, Qt::cyan, Qt::magenta};
            
            int index = QRandomGenerator::global()->bounded(colors.size());
            
            ui->message->setTextColor(colors.at(index));
            ui->message->append(msg);
        });
        
        send_file_thread->start();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_start_clicked() {
    unsigned short port = ui->port->text().toUShort();
    
    server_->listen(QHostAddress::Any, port);
}

void MainWindow::on_select_file_clicked() {
    QString path = QFileDialog::getOpenFileName();
    
    if (path.isEmpty()) {
        QMessageBox::warning(this, "Open File", "The file path selected cannot be empty");
        
        return;
    }
    
    ui->path->setText(path);
}

void MainWindow::on_send_clicked() {
    QString path = ui->path->text();
    
    if (path.isEmpty()) {
        QMessageBox::information(this, "Send File", "The file path cannot be empty");
        
        return;
    }
    
    emit start(path);
}
