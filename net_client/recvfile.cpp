#include "recvfile.h"

#include <QThread>
#include <QDebug>

RecvFile::RecvFile(QObject *parent) : QObject{parent} {}

void RecvFile::connect_server(const QString &ip, unsigned short port) {
    qDebug() << "Client connect thread:"  << QThread::currentThread();
    
    socket_ = new QTcpSocket;
    
    socket_->connectToHost(QHostAddress(ip), port);
    
    connect(socket_, &QTcpSocket::connected, this, &RecvFile::connected);

    connect(socket_, &QTcpSocket::errorOccurred, this, [=](QAbstractSocket::SocketError error) {
        qDebug() << "Connection error:" << socket_->errorString();
        emit connection_error();
    });

    connect(socket_, &QTcpSocket::readyRead, this, [=]() {
        QByteArray recv_data = socket_->readAll();
        
        emit message(recv_data);
        
        socket_->close();
        socket_->deleteLater();
        
        emit recv_completed();
    });
}
