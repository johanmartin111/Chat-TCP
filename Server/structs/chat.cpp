#include "chat.h"

// CONSTRUCTOR CON ID Y LISTA DE USUARIOS
Chat::Chat(int idChat, QList<Client *> clientes)
{
  this->idChat   = idChat;
  this->clientes = clientes;
  cambiarEstados();
}
// CONSTRUCTOR CON ID Y LISTA DE USUARIOS


//  CAMBIAR ESTADO DE TODOS LOS CLIENTES
void Chat::cambiarEstados(){
  foreach (Client *c, clientes) {
      c->setChatID(this->idChat);
  }
}
//  CAMBIAR ESTADO DE TODOS LOS CLIENTES


//  GETTERs & SETERs
QList<Usuario> Chat::getUsuarios() const
{
    QList<Usuario> usrs;
    foreach (Client *c, clientes) {
        usrs << c->getUsuario();
    }
    return usrs;
}

QStringList Chat::getMensajes() const
{ return mensajes; }

int Chat::getID() const
{  return idChat; }

QList<Client *> Chat::getClientes() const
{ return clientes; }
//  GETTERs & SETERs


//  START CHAT
void Chat::startChat()
{
    foreach (Client *c, clientes) {
        QDataStream ds(c);
        ds << Peticion(NUEVO_CHAT, getUsuarios() , idChat);
        c->flush();
    }
}
//  START CHAT


//  AGREGAR MSJ A LA LISTA DE MSJ
void Chat::addMsj(QString msj)
{ mensajes << msj; }
//  AGREGAR MSJ A LA LISTA DE MSJ


//  MANDA MSJ A TODOS LOS PARTICIPANTES
void Chat::sendMsj(Mensaje msj)
{
    foreach (Client *c, clientes) {
        QDataStream ds(c);
        ds << Peticion(MENSAJE, msj);
        c->flush();
    }
    addMsj(msj.toString());
}
//  MANDA MSJ A TODOS LOS PARTICIPANTES



QDebug operator<<(QDebug qd, const Chat &chat)
{
    qd << "ChatID: " << chat.getID() << "\n";
    qd << "Clientes: \n";
    foreach ( Client *c, chat.getClientes() ) {
        qd << c->getUsuario().getNick()
           << c->getUsuario().getIP()
           << c->getUsuario().getEstado()
           << "\n";
    }
    qd << "Mensajes: " << chat.getMensajes();
    return qd;
}


