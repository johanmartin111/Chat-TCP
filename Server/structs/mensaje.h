#ifndef MENSAJE_H
#define MENSAJE_H

#include <QString>
#include <QDateTime>
#include <QDataStream>
#include "usuario.h"

class Mensaje
{
public:
    explicit Mensaje(QString msj = "");
    explicit Mensaje(Usuario u, QString msj);
    explicit Mensaje(Usuario emisor, int chatDestino, QString texto);

    friend QDataStream &operator<<(QDataStream &ds, const Mensaje &m);
    friend QDataStream &operator>>(QDataStream &ds, Mensaje &m);

    QString toString();

    Usuario getEmisor() const;
    void setEmisor(Usuario value);

    int getChatReceptor() const;
    void setChatReceptor(int value);

    QString getFecha_hora() const;
    void setFecha_hora(const QDateTime &value);

    QString getTexto() const;
    void setTexto(const QString &value);

    bool isEmpty();
private:
    Usuario emisor;
    int chatReceptor;
    QString fecha_hora;
    QString texto;
};

#endif // MENSAJE_H
