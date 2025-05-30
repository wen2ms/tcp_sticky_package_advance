#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent) : QTcpServer{parent} {}

void MyTcpServer::incomingConnection(qintptr socket_descriptor) {
    emit new_client(socket_descriptor);
}
