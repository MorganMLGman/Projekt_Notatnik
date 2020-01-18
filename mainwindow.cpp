#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zakladka.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ileZakladek =0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dodajNowy_triggered()
{
    qDebug("NOWY");
    dodajNowaZakladka();
}

void MainWindow::on_otworzPlik_triggered()
{
    qDebug("OTWÓRZ");
}

void MainWindow::on_zapiszPlik_triggered()
{
    qDebug("ZAPISZ");
    zapiszPlik(ui->tabWidget->currentIndex());
}

void MainWindow::dodajNowaZakladka(){
    pytanieOdpowiedz podajNazwe;
    podajNazwe.exec();
    QString nazwa = podajNazwe.on_buttonBox_accepted();
    podajNazwe.close();
    ileZakladek++;
    Zakladka *nowa = new Zakladka;
    ui->tabWidget->addTab(nowa, nazwa);
    ui->tabWidget->setCurrentWidget(nowa);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    QWidget *obecny = ui->tabWidget->widget(index);
    Zakladka *obecna = dynamic_cast<Zakladka*>(obecny);
    if(obecna->sprawdzCzyEdytowana() == 1){
        pytanieTakNie czyZamknac;
        czyZamknac.zmienTekst("Plik nie został zapisany. Czy na pewno chcesz zamknąć?");
        if(czyZamknac.exec() == 0){
            return;
        }
    }
    ileZakladek--;
    ui->tabWidget->removeTab(index);
}

void MainWindow::zapiszPlik(int indeks){
    QWidget *obecny = ui->tabWidget->widget(indeks);
    Zakladka *obecna = dynamic_cast<Zakladka*>(obecny);
    QString sciezka = obecna->pobierzSciezke();
    if(sciezka.isEmpty()){
        QString filtry("Plik tekstowy (*.txt);;Plik wykonywalny (*.bat);;Strona HTML (*.html);;Wszystkie pliki (*.*)");
        sciezka = QFileDialog::getSaveFileName(this,"Zapisz plik",QDir::currentPath(),filtry);
    }
    if(sciezka.isEmpty()){
        return;
    }
    obecna->ustawSciezke(sciezka);
    QFile plik(sciezka);
    if(!plik.open(QFile::WriteOnly | QFile::Text)){
        qDebug("Nie można otworzyć pliku do zapisu");
        return;
    }
    QTextStream wyjscie(&plik);
    if(sciezka.contains(".html",Qt::CaseInsensitive) == true){
        wyjscie<< obecna->pobierzTekst(true);
    }
    else{
        wyjscie<< obecna->pobierzTekst(false);
    }
    plik.flush();
    plik.close();
    QFileInfo nazwa(plik);
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), nazwa.fileName());
    obecna->zostalZapisany();
}
