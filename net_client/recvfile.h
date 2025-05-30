#ifndef RECVFILE_H
#define RECVFILE_H

#include <QObject>
#include <QTcpSocket>

class RecvFile : public QObject {
    Q_OBJECT
  public:
    explicit RecvFile(QObject *parent = nullptr);
    
    void connect_server(const QString& ip, unsigned short port);
    
    void recv_file();
    
  signals:
    void connected();
    
    void connection_error();
    
    void recv_completed();
    
    void message(QByteArray msg);
    
  private:
    QTcpSocket* socket_;
};

#endif  // RECVFILE_H
