#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mytcpserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
  private slots:
    void on_start_clicked();
    
    void on_select_file_clicked();
    
    void on_send_clicked();
    
  private:
    Ui::MainWindow *ui;
    
    MyTcpServer* server_;    
};
#endif  // MAINWINDOW_H
