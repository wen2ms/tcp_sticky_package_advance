#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    
  signals:
    void start_connect(const QString& ip, unsigned short port);
    
  private slots:
    void on_connect_clicked();
    
  private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
