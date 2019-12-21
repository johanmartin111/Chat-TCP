#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

#include "structs/usuario.h"
#include "structs/peticion.h"

class Client : public QTcpSocket
{
    Q_OBJECT
public:
    explicit Client(QObject *parent, QString nick = "");
    explicit Client(QTcpSocket *socket);

    bool conectar(QString host, int port);
    void desconectar();
    void send(Peticion p);

    Usuario getUsuario() const;
    void setUsuario(const Usuario &value);
    void setChatID(const int &value);
private:
    Usuario usuario;
signals:
    void readyRead(Client *, Peticion);


private slots:
    void on_readyRead();
};

#endif // CLIENT_H
