#include "ostrzezenie.h"
#include "ui_ostrzezenie.h"

Ostrzezenie::Ostrzezenie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ostrzezenie)
{
    ui->setupUi(this);
}

Ostrzezenie::~Ostrzezenie()
{
    delete ui;
}

void Ostrzezenie::zmienTekst(QString tekst){
    ui->lineEdit->setText(tekst);
}
