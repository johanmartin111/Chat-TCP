#include "server.h"

//  CONSTRUCTOR VACIO
Server::Server(QObject *parent) : QTcpServer(parent)
{ }
//  CONSTRUCTOR VACIO


//  INICIAR SERVIDOR
bool Server::start( int puerto )
{
    //  SI SE INICIO CORRECTAMENTE
    if( this->listen(QHostAddress::Any, puerto) ){

        //  SEÑAL EMITIDA POR EL SERVIDOR NUEVA CONEXION
        connect(this, SIGNAL(newConnection()), SLOT(on_newConnection()));

        // OBTENER IPv4 DE LA TARJETA DE RED
        foreach ( const QHostAddress &ip, QNetworkInterface::allAddresses() ) {
            if (ip.toIPv4Address() && ip != QHostAddress::LocalHost){
                this->ip = ip.toString(); break;
            }
        }
        if ( this->ip.isEmpty() )
            this->ip = QHostAddress(QHostAddress::LocalHost).toString();

        //  PUERTO EN QUE SE INICIO EL SERVIDOR
        this->puerto = this->serverPort();
        return true;
    }
    return false;
}
//  INICIAR SERVIDOR


//  ENVIAR UN MENSAJE A TODOS LOS USUARIOS
void Server::broadcast(Peticion p)
{
    foreach (Client *c, clientes) {
        this->send(p, c);
    }
}
//  ENVIAR UN MENSAJE A TODOS LOS USUARIOS


//  ENVIA PETICION A CLIENTE
void Server::send(Peticion p, Client *C)
{
    QDataStream ds(C);
    ds << p;
    C->flush();
}

void Server::send(Peticion p, QList<Client *> clientes)
{
    foreach (Client *c, clientes) {
        this->send(p, c);
    }
}
//  ENVIA PETICION A CLIENTE


//  BUSCA UN CLIENTE ESPECIFICO EN LA LISTA
Client *Server::search(Usuario u)
{
    foreach (Client *c, clientes) {
        if ( (c->getUsuario().getNick() == u.getNick()) &&
             (c->getUsuario().getIP()   == u.getIP()))
            return c;
    }
    return NULL;
}

int Server::indexOf(Usuario u)
{
    for (int i = 0; i < clientes.size(); i++){
        if ( clientes.at(i)->getUsuario().getNick() == u.getNick() &&
             clientes.at(i)->getUsuario().getIP()   == u.getIP())
            return i;
    }
    return -1;
}
//  BUSCA UN CLIENTE ESPECIFICO EN LA LISTA


//  EN NUEVAS CONEXIONES
void Server::on_newConnection()
{
    //  SE CREA UN NUEVO CLIENTE CAPTURANDO EL SOCKET QUE INTENTA CONECTARSE
    Client *new_cliente = new Client( this->nextPendingConnection() );

    //  SE CONECTA SEÑAL EMITIDA CON SLOT
    connect(new_cliente, SIGNAL(readyRead(Client *, Peticion)), this, SLOT(on_readyRead(Client *, Peticion)));

    //  SE AGREGA CLIENTE A LA LISTA DE CLIENTES
    clientes.append( new_cliente );
}
//  EN NUEVAS CONEXIONES


//  SLOT PARA MENSAJES ENTRANTES
void Server::on_readyRead(Client *C, Peticion p){
    qDebug() << p.getCOD();

    switch ( p.getCOD() ) {
    case NUEVO_USUARIO:
        C->setUsuario( p.getEmisor() );
        break;
    case DESCONECTAR_USUARIO:
        clientes.removeAt( indexOf(p.getEmisor()) );
        break;
    case NUEVO_CHAT:{
        QList<Client *> chat_clients;
        Client *cl;
        foreach (Usuario u, p.getUsuarios()) {
            cl = search(u);
            if ( cl ){
                chat_clients << cl;
            }
        }
        Chat ch = Chat(chats.size(), chat_clients);
        chats << ch;
        ch.startChat();
        broadcast(Peticion(MENSAJE, Mensaje(Usuario("Servidor"), "sala de chat creada ...")));
        break;
    }
    case MENSAJE:
    {
        Mensaje msj = Mensaje(Usuario(p.getEmisor()), p.getMsj().toString());
        broadcast(Peticion(MENSAJE, msj));
        break;
    }
    default:
        break;
    }

    broadcast(Peticion(LISTA_USUARIOS, getUsuarios()));

    //  SE EMITE SEÑAL DEL SERVIDOR AL RECIBIR NUEVA PETICION
    emit nuevaPeticion( p );
}
//  SLOT PARA MENSAJES ENTRANTES


//  SETERs & GETERs
int Server::getPuerto() const
{ return puerto; }

void Server::setPuerto(int value)
{ puerto = value; }

QList<Usuario> Server::getUsuarios()
{
    QList<Usuario> cs;
    foreach (Client *c, clientes) {
        cs.append(c->getUsuario());
    }
    return cs;
}

QList<Chat> Server::getChats() const
{ return chats; }

QList<Client *> Server::getClientes() const
{ return clientes; }

QString Server::getIp() const
{ return ip; }

void Server::setIp(const QString &value)
{ ip = value; }
//  SETERs & GETERs

