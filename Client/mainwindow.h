#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QListWidgetItem>

#include "chatwindow.h"
#include "structs/client.h"

class QTcpSocket;

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
    void on_pb_Conectar_clicked();
    void on_pb_Desconectar_clicked();
    void on_pb_crearChat_clicked();

    void on_readyRead(Client *c, Peticion p);
    void on_stateChanged(QAbstractSocket::SocketState state);
    void on_lw_Usuarios_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Client *cliente;
    chatWindow *cw;
};

#endif // MAINWINDOW_H
