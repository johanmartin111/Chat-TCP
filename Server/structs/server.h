#ifndef SERVER_H
#define SERVER_H


#include <QTcpServer>         //  SERVIDOR TCP
#include <QTcpSocket>         //  SOCKET TCP
#include <QHostAddress>       //  DIRECCIONES IP
#include <QNetworkInterface>  //  INTERFAZ DE RED (TARGETA DE RED)
#include <QDataStream>        //  FLUJO DE DATOS POR STREAM (SOCKET)
#include <QList>              //  MANEJO DE LISTA S

#include <QDebug>

#include "client.h"
#include "peticion.h"
#include "mensaje.h"
#include "chat.h"

class Server : public QTcpServer
{
    Q_OBJECT
  public:
    Server(QObject *parent = 0);  //  CONSTRUCTOR
    bool start(int puerto = 0);   //  INICIAR SERVIDOR

    void broadcast(Peticion p);  // MANDA PETICION A TODOS
    void send(Peticion p, Client *C);  // MANDA PETICION A CLIENTE
    void send(Peticion p, QList<Client *> clientes);

    Client *search(Usuario u);  // BUSCA UN CLIENTE
    int indexOf(Usuario u);  //  BUSCA UN CLIENTE

    QString getIp() const;
    void setIp(const QString &value);
    int getPuerto() const;
    void setPuerto(int value);
    QList<Client *> getClientes() const;

    QList<Usuario> getUsuarios();
    QList<Chat *> getChats() const;
private:
    QString ip;
    int puerto;
    QList<Client *> clientes;
    QList<Chat *> chats;
signals:
    void nuevaPeticion(Peticion);
private slots:
    void on_newConnection();                   //  EN NUEVAS CONEXIONES
    void on_readyRead(Client *C, Peticion p);  //  CUANDO ESTA LISTO PARA LECTURA
};

#endif // SERVER_H
