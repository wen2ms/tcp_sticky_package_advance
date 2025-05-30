#include "sendfile.h"

#include <QFile>
#include <QDebug>
#include <QThread>

SendFile::SendFile(qintptr socket, QObject *parent) : QObject{parent}, socket_(socket) {}

void SendFile::working(const QString &file_path) {
    qDebug() << "Server Thread:" << QThread::currentThread();
    
    tcp_ = new QTcpSocket;
    
    tcp_->setSocketDescriptor(socket_);
    
    connect(tcp_, &QTcpSocket::connected, this, &SendFile::connected);
    
    connect(tcp_, &QTcpSocket::disconnected, this, [=]() {
        tcp_->close();
        tcp_->deleteLater();
        
        emit disconnected();
        
        qDebug() << "Client disconnected and destory socket...";
    });
    
    qDebug() << "Filename:" << file_path;
    
    QFile file(file_path);
    
    bool ret = file.open(QFile::ReadOnly);
    
    if (ret) {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            
            tcp_->write(line);
            
            emit text(line);
            
            QThread::msleep(50);
        }
    }
    
}
