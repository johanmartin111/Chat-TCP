#include "chatwindow.h"
#include "ui_chatwindow.h"

chatWindow::chatWindow(Client *client, int chatID, QWidget *parent) : QDialog(parent),
    ui(new Ui::chatWindow)
{
    ui->setupUi(this);
    this->cliente = client;
    connect( cliente, SIGNAL(readyRead(Client*,Peticion)), SLOT(on_readyRead(Client*,Peticion)) );
}

chatWindow::~chatWindow()
{
    delete ui;
}

void chatWindow::on_readyRead(Client *c, Peticion p)
{
    if (p.getCOD() == MENSAJE){
        ui->pte_chaLog->clear();
        ui->pte_chaLog->appendHtml( p.getMsj().toString() );
    }
}

void chatWindow::on_pb_Enviar_clicked()
{
    Mensaje msj = Mensaje( cliente->getUsuario(), ui->pte_chater->toPlainText());
    cliente->send( Peticion(MENSAJE, msj) );
    ui->pte_chater->clear();
}
