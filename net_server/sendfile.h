#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>

class SendFile : public QObject {
    Q_OBJECT
  public:
    explicit SendFile(QObject *parent = nullptr);
    
    void working(const QString& file_path);
    
  signals:
    
};

#endif  // SENDFILE_H
