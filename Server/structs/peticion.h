#ifndef PETICION_H
#define PETICION_H

#include "usuario.h"
#include "mensaje.h"

typedef enum {
    VACIO, NUEVO_USUARIO, DESCONECTAR_USUARIO,
    LISTA_USUARIOS, NUEVO_CHAT, MENSAJE
}PETICIONES;

class Peticion
{
public:
    explicit Peticion();
    explicit Peticion(PETICIONES COD, Usuario user);           //  NUEVO USUARIO/DESCONECTAR USUARIO
    explicit Peticion(PETICIONES COD,
                      QList<Usuario> users, int chatID = -1);  //  LISTA USUARIO / nuevo chat
    explicit Peticion(PETICIONES COD, Mensaje msj);           //  MENSAJE

    friend QDataStream &operator<<(QDataStream &ds, const Peticion &p);
    friend QDataStream &operator>>(QDataStream &ds, Peticion &p);
    friend QDataStream &operator>>(QDataStream &ds, PETICIONES &p);

    QString toString();

    Usuario        getEmisor();
    PETICIONES     getCOD() const;
    QList<Usuario> getUsuarios() const;
    Mensaje        getMsj() const;
    int            getChatID() const;

private:
    PETICIONES COD;
    QList<Usuario> usuarios;
    int chatID;
    Mensaje msj;
};


#endif // PETICION_H
