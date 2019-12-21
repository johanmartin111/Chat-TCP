#include "client.h"

//  CONSTRUCTOR
Client::Client(QObject *parent, QString nick) : QTcpSocket(parent)
{
    usuario = Usuario(nick);
    //  CONECTA LA SEÑAL DEL SOCKET CON EL SLOT LISTO PARA LEER
    connect(this, SIGNAL(readyRead()), SLOT(on_readyRead()));
}
//  CONSTRUCTOR


//  CONSTRUCTOR COPIANDO UN QTCPSOCKET
Client::Client(QTcpSocket *socket): QTcpSocket(socket->parent())
{
    setSocketDescriptor( socket->socketDescriptor() );
    usuario = Usuario();

    //  CONECTA LA SEÑAL DEL SOCKET CON EL SLOT LISTO PARA LEER
    connect(this, SIGNAL(readyRead()), SLOT(on_readyRead()));
}
//  CONSTRUCTOR COPIANDO UN QTCPSOCKET


//  CONECTAR CLIENTE A SERVIDOR
bool Client::conectar(QString host, int port)
{
    connectToHost(host, port);
    return waitForConnected();
}
//  CONECTAR CLIENTE A SERVIDOR


//  DESCONECTAR SOCKET
void Client::desconectar()
{
    send(Peticion(DESCONECTAR_USUARIO, usuario));
    close();
}
//  DESCONECTAR SOCKET


//  ENVIAR PETICION POR SOCKET
void Client::send(Peticion p)
{
    QDataStream ds(this);
    ds << p;
    this->flush();
}
//  ENVIAR PETICION POR SOCKET


//  GETTERs & SETERs
Usuario Client::getUsuario() const
{ return usuario; }

void Client::setUsuario(const Usuario &value)
{ usuario = value; }

void Client::setChatID(const int &value)
{ usuario.setChatID(value); }
//  GETTERs & SETERs


//  EMITE LA SEÑAL LISTO PARA LEER CON EL PUNTERO DE LA CLASE Y LA PETICION
void Client::on_readyRead(){
    Peticion p;
    QDataStream ds(this);
    ds >> p;
    emit readyRead(this, p);
}
//  EMITE LA SEÑAL LISTO PARA LEER CON EL PUNTERO DE LA CLASE Y LA PETICION


