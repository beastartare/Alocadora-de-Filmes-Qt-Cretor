#include "aluguel.h"
#include "ui_aluguel.h"
#include <QDebug>

Aluguel::Aluguel(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Aluguel)
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

Aluguel::~Aluguel()
{
    delete ui;
}

void Aluguel::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    Global::instance()->m_data = item->text();

    this->close();
    Ingresso janela;
    janela.setModal(true);
    janela.exec();
}

