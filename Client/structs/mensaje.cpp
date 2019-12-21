#include "mensaje.h"

//  CONSTRUCTOR VACIO
Mensaje::Mensaje(QString msj)
{
    chatReceptor = -1;
    fecha_hora   = "";
    texto        = msj;
    if (!msj.isEmpty())
        fecha_hora = QDateTime::currentDateTime().toString("ddd d MMM yyyy h:ma");
}

Mensaje::Mensaje(Usuario u, QString msj)
{
    chatReceptor = -1;
    this->emisor = u;
    fecha_hora   = QDateTime::currentDateTime().toString("ddd d MMM yyyy h:ma");
    texto        = msj;
}
//  CONSTRUCTOR VACIO


//  CONSTRUCTOR CON EMISOR Y RECEPTOR
Mensaje::Mensaje(Usuario emisor, int chatDestino, QString texto)
{
    this->emisor = emisor;
    fecha_hora   = QDateTime::currentDateTime().toString("ddd d MMM yyyy h:ma");
    this->texto  = texto;
    chatReceptor = chatDestino;
}
//  CONSTRUCTOR CON EMISOR Y RECEPTOR


//  SOBRECARGA DE OPERADORES << >>
QDataStream &operator<<(QDataStream &ds, const Mensaje &m)
{
    return ds << m.emisor << m.chatReceptor << m.fecha_hora << m.texto;
}

QDataStream &operator>>(QDataStream &ds, Mensaje &m)
{
   return ds >> m.emisor >> m.chatReceptor >> m.fecha_hora >> m.texto;
}
//  SOBRECARGA DE OPERADORES << >>


//  MENSAJE TO STRING
QString Mensaje::toString()
{
    return QString("[%1] %2: %3")
            .arg(fecha_hora)
            .arg(emisor.getNick())
            .arg(texto);
}
//  MENSAJE TO STRING


// SI ESTA VACIO
bool Mensaje::isEmpty()
{
  return emisor.isEmpty() && chatReceptor == -1 && fecha_hora == "" && texto == "";
}
// SI ESTA VACIO


//  GETs & SETERs
int Mensaje::getChatReceptor() const
{ return chatReceptor; }

void Mensaje::setChatReceptor(int value)
{ chatReceptor = value; }

QString Mensaje::getFecha_hora() const
{ return fecha_hora; }

void Mensaje::setFecha_hora(const QDateTime &value)
{ fecha_hora = value.toString("ddd d MMM yyyy h:ma"); }

QString Mensaje::getTexto() const
{ return texto; }

void Mensaje::setTexto(const QString &value)
{ texto = value; }

Usuario Mensaje::getEmisor() const
{ return emisor; }

void Mensaje::setEmisor(Usuario value)
{ emisor = value; }
//  GETs & SETERs



