#include "perfil.h"
#include "ui_perfil.h"

Perfil::Perfil(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Perfil)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);
    QString user =  Cliente::instance()->m_username;

    query.prepare("SELECT * FROM usuario WHERE username= '"+user+"'");
    if(query.exec())
    {
        qDebug() << Cliente::instance()->m_username;
        while(query.next())
        {
            ui->label_2->setText(query.value(1).toString());
            ui->label_4->setText(query.value(3).toString());
        }
    }
}

Perfil::~Perfil()
{
    delete ui;
}

void Perfil::on_pushButton_clicked()
{
    if(ui->comboBox->currentText()=="Filmes em cartaz")
    {
        this->close();
        Cliente janela;
        janela.setModal(true);
        janela.exec();
    }
}

