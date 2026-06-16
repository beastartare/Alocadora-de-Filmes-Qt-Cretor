#include "ingresso.h"
#include "ui_ingresso.h"

Ingresso::Ingresso(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Ingresso)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);

    QString titulo = Global::instance()->m_titulo;
    QString data = Global::instance()->m_data;

    if(query.exec("SELECT * FROM cadeiras_disponíveis WHERE filme = '"+titulo+"' AND data='"+data+"'"))
    {
        while(query.next())
        {
            ui->listWidget->addItem(query.value(2).toString());
        }
    }
}
Ingresso::~Ingresso()
{
    delete ui;
}
QString Ing::ToString()
{
    stringstream sst;

    sst  << "\nvalor: " <<  m_valor << "\nnº cadeira: " << m_cadeira;

    string s = sst.str();

    QString aux = "\nfilme: " + m_filme + "\nsessão:" + m_data + QString::fromStdString(s);
    return aux;
}
QString IngressoPadrao::ToString()
{
    return "Ingresso padrão." + Ing::ToString();
}
QString IngressoVip::ToString()
{
    return "Ingresso vip." + Ing::ToString(); + "\nBenefício: " + m_beneficio;
}
void Ingresso::on_pushButton_clicked()
{
    IngressoPadrao *ing = new IngressoPadrao(Global::instance()->last_item.toInt(), Global::instance()->m_titulo,Global::instance()->m_data);
    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);

    QString usuario = Cliente::instance()->m_username;

    if(query.exec("SELECT * FROM usuario WHERE username='"+usuario+"'"))
    {
        while(query.next())
        {
            if(query.exec("UPDATE usuario SET ingresso='"+ing->ToString()+"' WHERE username='"+usuario+"'"))
            {

            }

        }
        query.prepare("DELETE FROM cadeiras_disponíveis WHERE filme='"+Global::instance()->m_titulo+"'AND data='"+Global::instance()->m_data+"' AND cadeira= :cad");
        QString str = Global::instance()->last_item;
        if(str=="")
        {
            ui->label->setText("Campo obrigatório");
            return;
        }
        bool ok;
        int num = str.toInt(&ok);
        if(!query.exec("DELETE FROM cadeiras_disponíveis WHERE filme='"+Global::instance()->m_titulo+"'AND data='"+Global::instance()->m_data+"' AND cadeira= ?"))
        {
            qDebug() << "Erro ao deletar:" << query.lastError();
            return;
        }
    }
    delete ing;
}

void Ingresso::on_pushButton_2_clicked()
{
    IngressoVip *ing = new IngressoVip(Global::instance()->last_item.toInt(),Global::instance()->m_titulo,Global::instance()->m_data);
    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);

    QString usuario = Cliente::instance()->m_username;
     qDebug() << Cliente::instance()->m_username;

    if(query.exec("SELECT * FROM usuario WHERE username='"+usuario+"'"))
    {
         qDebug() << "entroou if";
        while(query.next())
        {
             if(query.exec("UPDATE usuario SET ingresso='"+ing->ToString()+"' WHERE username='"+usuario+"'"))
            {

            }
             qDebug() << "achou usuario";
        }
        query.prepare("DELETE FROM cadeiras_disponíveis WHERE filme='"+Global::instance()->m_titulo+"'AND data='"+Global::instance()->m_data+"' AND cadeira= :cad");
        QString str = Global::instance()->last_item;
        if(str=="")
        {
            ui->label->setText("Campo obrigatório");
            return;
        }
        bool ok;
        int num = str.toInt(&ok);
        query.bindValue(":cad",num);
        if(!query.exec())
        {
            qDebug() << "Erro ao deletar:" << query.lastError();
            return;
        }
    }
    delete ing;
}

void Ingresso::on_listWidget_itemClicked(QListWidgetItem *item)
{
    qDebug() << "entrou";
    Global::instance()->last_item = item->text();
    qDebug() << Global::instance()->last_item;
}

