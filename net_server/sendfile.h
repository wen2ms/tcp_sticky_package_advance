#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>

class SendFile : public QObject {
    Q_OBJECT
  public:
    explicit SendFile(qintptr socket, QObject *parent = nullptr);
    
    void working(const QString& file_path);
    
  signals:
    void connected();
    void disconnected();
    void text(QByteArray msg);
    
  private:
    qintptr socket_;
    QTcpSocket* tcp_;    
};

#endif  // SENDFILE_H
