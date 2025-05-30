#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>

class MyTcpServer : public QTcpServer {
    Q_OBJECT
  public:
    explicit MyTcpServer(QObject *parent = nullptr);
    
  protected:
    void incomingConnection(qintptr socket_descriptor) override;
    
  signals:
    void new_client(qintptr socket);
};

#endif  // MYTCPSERVER_H
