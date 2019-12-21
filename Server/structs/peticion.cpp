#include "peticion.h"

//  CONSTRUCTOR  VACIO
Peticion::Peticion(){
  this->COD = VACIO;
  chatID = -1;
}
//  CONSTRUCTOR  VACIO

//  CONSTRUCTOR CODIGO Y UN USUARIO (NUEVO USUARIO)
Peticion::Peticion(PETICIONES COD, Usuario user)
{
  this->COD = COD;
  usuarios << user;
  chatID = -1;
}
//  CONSTRUCTOR CODIGO Y UN USUARIO (NUEVO USUARIO)


//  CONSTRUCTOR CODIGO Y LISTA DE USUARIO (LISTA USUARIOS)
Peticion::Peticion(PETICIONES COD, QList<Usuario> users, int chatID)
{
  this->COD = COD;
  usuarios << users;
  this->chatID = chatID;
}
//  CONSTRUCTOR CODIGO Y LISTA DE USUARIO (LISTA USUARIOS


//  CONSTRUCTOR CODIGO Y MENSAJE

Peticion::Peticion(PETICIONES COD, Mensaje msj)
{
    this->COD = COD;
    this->msj = msj;
    chatID = -1;
}
//  CONSTRUCTOR CODIGO Y MENSAJE


//  PETICION TO STRING
QString Peticion::toString()
{
  switch (COD) {
    //  CASO QUE LA PETICION SEA NUEVO USUARIO
    case NUEVO_USUARIO:
      return QString("Nuevo usuario: %1 - %2")
          .arg(getEmisor().getIP())
          .arg(getEmisor().getNick());
      break;
  case DESCONECTAR_USUARIO:
      return QString("Usuario desconectado: %1 - %2")
          .arg(getEmisor().getIP())
          .arg(getEmisor().getNick());
      break;
  case LISTA_USUARIOS:
  {
      QString msj = "Lista de usuarios:";
      foreach (Usuario u, getUsuarios()) {
          msj.append( QString(" %1 - %2").arg(u.getNick()).arg(u.getIP()));
      }
      return msj;
      break;
  }
  case NUEVO_CHAT:{
      QString msj = QString("Nueva sala de chat creada:");
      for (int i = 0; i < getUsuarios().size(); i++){
          Usuario u = getUsuarios().at(i);
          msj.append(QString("<br> &nbsp;&nbsp;&nbsp; %1 - %2").arg(u.getNick()).arg(u.getIP()));
      }
      return msj;
      break;
  }
  case MENSAJE:
      return msj.toString();
      break;
    default:
      return "";
      break;
  }
}
//  PETICION TO STRING



//  OPERATORs << >>
QDataStream &operator>>(QDataStream &ds, PETICIONES &p)
{
  ds >> (quint32&)p;
  return ds;
}

QDataStream &operator<<(QDataStream &ds, const Peticion &p)
{
  return ds << p.COD << p.usuarios << p.chatID << p.msj;
}

QDataStream &operator>>(QDataStream &ds, Peticion &p)
{
  return ds >> p.COD >> p.usuarios >> p.chatID >> p.msj;
}
//  OPERATORs << >>


//  SETERs & GETERs

Usuario Peticion::getEmisor()
{ return usuarios.at(0); }

PETICIONES Peticion::getCOD() const
{ return COD; }

QList<Usuario> Peticion::getUsuarios() const
{ return usuarios; }

Mensaje Peticion::getMsj() const
{ return msj; }
int Peticion::getChatID() const
{ return chatID; }


//  SETERs & GETERs

