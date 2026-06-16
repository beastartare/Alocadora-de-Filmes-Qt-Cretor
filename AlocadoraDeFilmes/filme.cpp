#include "filme.h"
#include "ui_filme.h"

Filme::Filme(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Filme)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);

    QString titulo = Global::instance()->m_titulo;


    if(query.exec("SELECT * FROM cadastrar_filmes WHERE filme='"+titulo+"'"))
    {
        while(query.next())
        {
            ui->label->setText(query.value(0).toString());
            QString imagePath = query.value(2).toString();

            QPixmap pix(imagePath);

            if (!pix.isNull()) {
                QPixmap resizedPixmap = pix.scaled(138, 204, Qt::KeepAspectRatio);  // Redimensiona para 400x300, mantendo a proporção

                ui->label_2->setPixmap(pix);
                ui->label_2->setPixmap(resizedPixmap);

            }
            ui->listWidget->addItem(query.value(1).toString());
        }
    }
}

Filme::~Filme()
{
    delete ui;
}

void Filme::on_pushButton_clicked()
{
    QSqlDatabase db = QSqlDatabase::database("bancodedados");

    QSqlQuery query(db);
    query.prepare("DELETE FROM cadastrar_filmes WHERE filme='"+Global::instance()->m_titulo+"'AND data='"+Global::instance()->m_data+"'");
    if(!query.exec())
    {
        ui->label_4->setText("Erro ao remover sessão");
        return;
    }
    ui->label_4->setText("Sessão removida com sucesso");
    /*if(!query.exec("UPDATE usuario SET ingresso='""' WHERE ='"+Cliente::instance()->m_username+"'"))
    {
        qDebug() << "erro ao remover ingresso";
    }*/
}


void Filme::on_listWidget_itemClicked(QListWidgetItem *item)
{
    Global::instance()->m_data = item->text();
}

