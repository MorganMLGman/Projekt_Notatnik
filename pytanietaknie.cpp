#include "pytanietaknie.h"
#include "ui_pytanietaknie.h"

pytanieTakNie::pytanieTakNie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pytanieTakNie)
{
    ui->setupUi(this);
}

pytanieTakNie::~pytanieTakNie()
{
    delete ui;
}


void pytanieTakNie::zmienTekst(QString tekst){
    ui->lineEdit->setText(tekst);
}
void pytanieTakNie::on_buttonBox_accepted()
{

}

void pytanieTakNie::on_buttonBox_rejected()
{

}
