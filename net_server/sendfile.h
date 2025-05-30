#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>

class SendFile : public QObject {
    Q_OBJECT
  public:
    explicit SendFile(qintptr socket, QObject *parent = nullptr);
    
    void working(const QString& file_path);
    
  signals:
    void send_complete();
    void text(QByteArray msg);
    
  private:
    qintptr socket_; 
};

#endif  // SENDFILE_H
