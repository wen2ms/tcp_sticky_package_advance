#include "sendfile.h"

SendFile::SendFile(qintptr socket, QObject *parent) : QObject{parent}, socket_(socket) {}

void SendFile::working(const QString &file_path) {}
