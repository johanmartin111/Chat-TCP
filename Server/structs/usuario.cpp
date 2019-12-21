#include "usuario.h"

//  CONSTRUCTOR VACIO
Usuario::Usuario()
{
    IP     = QHostAddress::Null;
    nick   = "";
    chatID = -1;
    estado = DISPONIBLE;
}
//  CONSTRUCTOR VACIO


//  CONSTRUCTOR CON NOMBRE
Usuario::Usuario(QString nick )
{
    this->nick   = nick;
    estado = DISPONIBLE;
    chatID = -1;

    QList<QHostAddress> ipsList = QNetworkInterface::allAddresses();
    foreach (QHostAddress ip, ipsList) {
        if (ip != QHostAddress::LocalHost && ip.toIPv4Address()){
            IP = ip;
            break;
        }
    }
    if ( IP.isNull() )
        IP = QHostAddress(QHostAddress::LocalHost);
}
//  CONSTRUCTOR CON NOMBRE


//  CONSTRUCTOR CON NOMBRE Y IP
Usuario::Usuario(QString nick, QString ip)
{
    IP     = ip;
    this->nick   = nick;
    chatID = -1;
    estado = DISPONIBLE;
}
//  CONSTRUCTOR CON NOMBRE Y IP


// COPIA DE OTRO USUARIO
void Usuario::copyUsuario(const Usuario &u)
{
    nick   = u.getNick();
    estado = u.getEstado();
    IP     = u.getIP();
    chatID = u.getChatID() ;
}

// COPIA DE OTRO USUARIO


// OPERATOR << >>
bool Usuario::operator==(const Usuario u) const
{
    return this->IP.toString() == u.getIP() && this->nick == u.getNick();
}

bool Usuario::operator!=(const Usuario u) const
{
    return !(this->IP.toString() == u.getIP() && this->nick == u.getNick());
}

QDataStream &operator>>(QDataStream &ds, ESTADOS &e)
{
    ds >> (quint32&)e;
    return ds;
}

QDataStream &operator<<(QDataStream &ds, const Usuario &u)
{
    return ds << u.IP << u.nick << u.chatID << u.estado;
}

QDataStream &operator>>(QDataStream &ds, Usuario &u)
{
    return ds >> u.IP >> u.nick >> u.chatID >> u.estado;
}
// OPERATOR <</>>


//  SI ESTA VACIO
bool Usuario::isEmpty()
{
  return IP == QHostAddress::Null && nick == "" && chatID == -1 && estado == DISPONIBLE;
}
//  SI ESTA VACIO


//  GETERs & SETERs
ESTADOS Usuario::getEstado() const
{ return estado; }

void Usuario::setDisponible(bool disp)
{
    if (disp)
        estado = DISPONIBLE;
    else
        estado = OCUPADO;
    chatID = -1;
}

QString Usuario::getIP() const
{ return IP.toString(); }

void Usuario::setIP(const QString &IP)
{ this->IP = QHostAddress(IP); }

QString Usuario::getNick() const
{ return nick; }

void Usuario::setNick(const QString &value)
{ nick = value; }

int Usuario::getChatID() const
{ return chatID; }

void Usuario::setChatID(int value)
{
    chatID = value;
    if ( chatID > -1 )
        estado = OCUPADO;
    else
        estado = DISPONIBLE;
}
//  GETERs & SETERs




