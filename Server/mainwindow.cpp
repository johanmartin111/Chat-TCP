#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

//  CONSTRUCTOR
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    iniciado = false;
}
//  CONSTRUCTOR


//  DESTRUCTOR
MainWindow::~MainWindow()
{ delete ui; }
//  DESTRUCTOR


// INICIAR//DETENER SERVIDOR
void MainWindow::on_pb_startServer_clicked()
{
    //  SI NO SE HA INICIADO
    if ( !iniciado ){
        //  NUEVA INSTANCIA DEL SERVIDOR
        servidor = new Server(this);
        connect(servidor, SIGNAL(nuevaPeticion(Peticion)), this, SLOT(on_nuevaPeticion(Peticion)));

        if ( !servidor->start() ){
            QMessageBox::critical(this, "Error en el Servidor",
                                  "No se pudo iniciar el servidor:"+
                                  servidor->errorString());
            return;
        }

        ui->l_serverIP->setText( servidor->getIp() );
        ui->l_serverPort->setText( QString::number(servidor->getPuerto()) );
        ui->te_Debuger->appendHtml("<font color='green'>Servidor inicio correctamente ... </font>");

        iniciado = true;
        ui->pb_startServer->setText("Detener");
    } else {
        iniciado = false;
        ui->pb_startServer->setText("Iniciar");
        ui->l_serverIP->clear();
        ui->l_serverPort->clear();
        if ( servidor->isListening() ){
            servidor->close();
            delete servidor;
            ui->lw_usersConnected->clear();
            ui->lw_chats->clear();
            ui->te_Debuger->clear();
        }
    }
}


void MainWindow::on_nuevaPeticion(Peticion p)
{
    //  COLOR A LAS PETICIONES
    QString msj = p.toString();
    switch ( p.getCOD() ) {
    case NUEVO_USUARIO:
        msj = QString("%1 %2 %3")
                .arg("<font color=''>")
                .arg(msj)
                .arg("</font>");
        break;
    case DESCONECTAR_USUARIO:
        msj = QString("%1 %2 %3")
                .arg("<font color='red'>")
                .arg(msj)
                .arg("</font>");
        break;
    case NUEVO_CHAT:
        msj = QString("%1 %2 %3")
                .arg("<font color=''>")
                .arg(msj)
                .arg("</font>");
        break;
    default:
        break;
    }
    //  COLOR A LAS PETICIONES
    ui->te_Debuger->appendHtml( msj );

    //  ACTUALIZAR TODOS LOS CLIENTES EN LA LISTA
    ui->lw_usersConnected->clear();
    foreach (Client *c, servidor->getClientes()) {
        QListWidgetItem *item = new QListWidgetItem(
                    QString("%1 - %2").arg(c->getUsuario().getNick()).arg(c->getUsuario().getIP()) );
        if ( c->getUsuario().getEstado() == DISPONIBLE )
            item->setTextColor(QColor("green"));
        else
            item->setTextColor(QColor("red"));
        ui->lw_usersConnected->addItem(item);
    }
    //  ACTUALIZAR TODOS LOS CLIENTES EN LA LISTA


    //  ACTUALIZAR LISTA DE CHATS
    ui->lw_chats->clear();
    foreach (Chat *ch, servidor->getChats()) {
        QString txt;
        foreach (Usuario usr, ch->getUsuarios()) {
            txt.append( QString("%1 [%2] | ").arg(usr.getNick()).arg(usr.getIP()) );
        }
        txt.remove(txt.size()-3, 3);
        QListWidgetItem *item = new QListWidgetItem(txt);
        ui->lw_chats->addItem(item);
    }
    //  ACTUALIZAR LISTA DE CHATS
}
