#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    
    server_ = new MyTcpServer(this);
    
    connect(server_, &MyTcpServer::new_client, this, [=]() {
        
    });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_start_clicked() {
    unsigned short port = ui->port->text().toUShort();
    
    server_->listen(QHostAddress::Any, port);
}

void MainWindow::on_select_file_clicked() {}

void MainWindow::on_send_clicked() {
    
}
