#include "pytanieodpowiedz.h"
#include "ui_pytanieodpowiedz.h"

pytanieOdpowiedz::pytanieOdpowiedz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pytanieOdpowiedz)
{
    ui->setupUi(this);
}

pytanieOdpowiedz::~pytanieOdpowiedz()
{
    delete ui;
}

QString pytanieOdpowiedz::on_buttonBox_accepted()
{
   return ui->lineEdit->text();
}
