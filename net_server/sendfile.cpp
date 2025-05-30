#include "sendfile.h"

#include <QDebug>
#include <QFile>
#include <QThread>
#include <QtEndian>

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
            
            int size = line.size();
            
            int len = qToBigEndian(size);
            
            QByteArray data(reinterpret_cast<char*>(&len), 4);
            
            data.append(line);
            
            tcp_->write(data);
            
            emit text(line);
            
            QThread::msleep(50);
        }
    }
    
    file.close();
}
