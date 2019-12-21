#ifndef CHAT_H
#define CHAT_H

#include <QList>
#include <QStringList>
#include "usuario.h"
#include "client.h"

class Usuario;
class Chat
{
public:
    explicit Chat(int idChat, QList<Client *> clientes);
    friend QDebug operator<<(QDebug qd, const Chat &chat);

    QList<Usuario> getUsuarios() const;
    QStringList getMensajes() const;
    QList<Client *> getClientes() const;

    void startChat();
    void addMsj(QString msj);
    void sendMsj(Mensaje msj);

    void cambiarEstados();
    int getID() const;    
private:
    int idChat;
    QList<Client *> clientes;
    QStringList mensajes;
};


#endif // CHAT_H
