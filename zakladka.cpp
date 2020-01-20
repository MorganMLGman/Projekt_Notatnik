#include "zakladka.h"
#include "ui_zakladka.h"

Zakladka::Zakladka(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Zakladka)
{
    ui->setupUi(this);
    czyEdytowana = 0;
    czyZmianaNazwy =0;
}

Zakladka::~Zakladka()
{
    delete ui;
}

void Zakladka::on_textEdit_textChanged()
{
    czyEdytowana =1;
}

bool Zakladka::sprawdzCzyEdytowana(){
    return czyEdytowana;
}

void Zakladka::zostalZapisany(){
    czyEdytowana = 0;
}

const QString & Zakladka::pobierzSciezke(){
    return sciezka;
}

void Zakladka::ustawSciezke(const QString &sciezkaPliku){
    sciezka = sciezkaPliku;
}

QString Zakladka::pobierzTekst(bool rodzaj){
    if(rodzaj == false){
        return ui->textEdit->toPlainText();
    }
    else{
        return ui->textEdit->toHtml();
    }
}

void Zakladka::dodajTekst(QString tekst){
    ui->textEdit->append(tekst);
}

void Zakladka::zmienRozmiarCzcionki(){
    ui->textEdit->selectAll();
    ui->textEdit->setFont(QFontDialog::getFont(nullptr,ui->textEdit->font()));
}
