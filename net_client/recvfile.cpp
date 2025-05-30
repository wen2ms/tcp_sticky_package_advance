#include "recvfile.h"

#include <QThread>
#include <QDebug>
#include <QtEndian>

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
        // QByteArray recv_data = socket_->readAll();
                
        // emit message(recv_data);
    
        
        while (socket_->bytesAvailable() > 0) {            
            QByteArray head;
            int ret = readn(head, sizeof(int));
            int len = qFromBigEndian(*(int*)(head.data()));
            
            qDebug() << "The length of data:" << len;
            
            QByteArray data;
            
            ret = readn(data, len);
            
            emit message(data);   
        }
        
        socket_->close();
        socket_->deleteLater();
        
        emit recv_completed();
    });
}

int RecvFile::readn(QByteArray &block, int count) {
    int nleft = count;
    
    if (socket_->bytesAvailable() < count) {
        return -1;
    }
    
    while (nleft > 0) {
        block.append(socket_->read(nleft));
        
        nleft = count - block.size();
    }
    
    return count;
}


