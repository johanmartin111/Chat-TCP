#ifndef USUARIO_H
#define USUARIO_H

#include <QString>
#include <QHostAddress>
#include <QDataStream>
#include <QNetworkInterface>

typedef enum {
    OCUPADO, DISPONIBLE
} ESTADOS;

class Usuario
{
public:
    explicit Usuario();
    explicit Usuario(QString nick);
    explicit Usuario(QString nick, QString ip);

    void copyUsuario(const Usuario &u);

    friend QDataStream &operator>>(QDataStream &ds, ESTADOS &e);
    friend QDataStream &operator<<(QDataStream &ds, const Usuario &u);
    friend QDataStream &operator>>(QDataStream &ds, Usuario &u);
    bool operator==( const Usuario u) const;
    bool operator!=( const Usuario u) const;

    QString getIP() const;
    void setIP(const QString &IP);

    QString getNick() const;
    void setNick(const QString &value);

    int getChatID() const;
    void setChatID(int value);

    ESTADOS getEstado() const;
    void setDisponible( bool disp = true);

    bool isEmpty();
private:
    QHostAddress IP;
    QString nick;
    int chatID;
    ESTADOS estado;
};


#endif // USUARIO_H
