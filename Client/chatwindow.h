#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include "structs/client.h"
namespace Ui {
class chatWindow;
}

class chatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit chatWindow(Client *client, int chatID, QWidget *parent = 0);
    ~chatWindow();
private slots:
    void on_readyRead(Client*c, Peticion p);
    void on_pb_Enviar_clicked();


private:
    Ui::chatWindow *ui;
    Client *cliente;
};

#endif // CHATWINDOW_H
