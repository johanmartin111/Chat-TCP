#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "structs/server.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pb_startServer_clicked();
    void on_nuevaPeticion(Peticion p);

private:
    Ui::MainWindow *ui;
    bool iniciado;

    //  SERVER
    Server *servidor;
};

#endif // MAINWINDOW_H
