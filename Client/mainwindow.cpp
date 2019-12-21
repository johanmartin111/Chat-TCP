#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chatwindow.h"

#include <QDebug>
#include <QMessageBox>
#include "structs/peticion.h"

//  CONSTRUCTOR
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sw_vistas->setCurrentIndex(0);
    cw = NULL;
}
//  CONSTRUCTOR


//  DESTRUCTOR
MainWindow::~MainWindow()
{
    delete ui;
    if ( cliente->isOpen() )
        cliente->desconectar();
}
//  DESTRUCTOR


//  BOTON CONEXION
void MainWindow::on_pb_Conectar_clicked()
{
    cliente = new Client(this, ui->le_Nick->text());  //  CREACION USUARIO
    bool conectado = cliente->conectar( ui->le_Server->text(), ui->le_puerto->text().toInt()) ;
    if ( conectado ){
        ui->l_Nick->setText( cliente->getUsuario().getNick() );

        // CONECTAR SEÑAL DEL SOCKET CON SLOT
        connect(cliente, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
                                this, SLOT(on_stateChanged(QAbstractSocket::SocketState)));
        connect(cliente, SIGNAL(readyRead(Client*,Peticion)), this, SLOT(on_readyRead(Client*,Peticion)));
        cliente->send( Peticion(NUEVO_USUARIO, cliente->getUsuario()) );  //  ENVIAR PETICION NUEVO USUARIO
    }else
        return;

    ui->sw_vistas->setCurrentIndex(1);  //  CAMBIAR VISTA
}
//  BOTON CONEXION


//  LECTURA DE PETICION EN SOCKET
void MainWindow::on_readyRead(Client *c, Peticion p)
{
    switch ( p.getCOD() ) {
    case LISTA_USUARIOS:
    {
        ui->lw_Usuarios->clear();
        foreach (Usuario u, p.getUsuarios()) {
            if ( u != cliente->getUsuario() ){
                QListWidgetItem *item = new QListWidgetItem(
                            QString("%1 - %2").arg(u.getNick()).arg(u.getIP()));
                if ( u.getEstado() == DISPONIBLE )
                    item->setTextColor(QColor("green"));
                else
                    item->setTextColor(QColor("red"));
                ui->lw_Usuarios->addItem(item);
            }
        }
        break;
    }
    case NUEVO_CHAT:
    {
        cw = new chatWindow(cliente, p.getChatID(), this);
        cw->show();
        break;
    }
    default:
        break;
    }
}
//  LECTURA DE PETICION EN SOCKET


//  CUANDO EL SOCKET CAMBIA DE ESTADO
void MainWindow::on_stateChanged(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState){
        QMessageBox::information(this, "Se ha desconectado", "Se ha desconectado...");
        on_pb_Desconectar_clicked();
    }
}
//  CUANDO EL SOCKET CAMBIA DE ESTADO


//  DESCONECTAR
void MainWindow::on_pb_Desconectar_clicked()
{
    cliente->desconectar();
    ui->sw_vistas->setCurrentIndex(0);  //  CAMBIAR VISTA
}
//  DESCONECTAR


//  CREAR CHAT
void MainWindow::on_pb_crearChat_clicked()
{
//    QList<Usuario> usrs;
//    usrs << Usuario("Jose") << Usuario("Renzo");
//    Peticion p(CREAR_CHAT, usrs );
//    cliente->envia(p);
}
//  CREAR CHAT


//  Usuario CLick
void MainWindow::on_lw_Usuarios_itemClicked(QListWidgetItem *item)
{
    //  SI EL ITEM SELECCIONADO ES ROJO O VERDE
    if ( item->textColor() == QColor("red") ){
        QMessageBox::critical(this, "Error en crear chat",
                          "No puedes iniciar una nueva sala de chat con un usuario ocupado");
    }else{
        QStringList txt = item->text().split("-", QString::SkipEmptyParts);
        QString nick = txt.at(0).simplified();
        QString ip   = txt.at(1).simplified();
        if ( QMessageBox::question(this, "Creando chat",
                              QString("Desea crear una nueva sala de chat con: \n %1 - %2")
                              .arg(nick).arg(ip)) == QMessageBox::Yes ){
            QList<Usuario> chat_usr;
            chat_usr << cliente->getUsuario() << Usuario(nick, ip);
            cliente->send(Peticion(NUEVO_CHAT, chat_usr));
        }
    }

}
//  Usuario CLick
