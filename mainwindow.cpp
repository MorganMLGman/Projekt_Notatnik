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
    dodajNowaZakladka(pobierzNazwe());
}

void MainWindow::on_otworzPlik_triggered()
{
    qDebug("OTWÓRZ");
    otworzPlik();
}

void MainWindow::on_zapiszPlik_triggered()
{
    qDebug("ZAPISZ");
    if(ileZakladek <=0){
        return;
    }
    zapiszPlik(ui->tabWidget->currentIndex());
}

Zakladka* MainWindow::dodajNowaZakladka(QString nazwa){
    ileZakladek++;
    Zakladka *nowa = new Zakladka;
    ui->tabWidget->addTab(nowa, nazwa);
    ui->tabWidget->setCurrentWidget(nowa);
    return nowa;
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

void MainWindow::otworzPlik(){
    QString filtry("Plik tekstowy (*.txt);;Plik wykonywalny (*.bat);;Strona HTML (*.html);;Wszystkie pliki (*.*)");
    QString sciezka = QFileDialog::getOpenFileName(this,"Otwórz plik", QDir::currentPath(),filtry);
    QFile plik(sciezka);

    if(!plik.open(QIODevice::ReadOnly|QFile::Text)){
        qDebug("Błąd podczas otwierania pliku");
        return;
    }
    QFileInfo nazwa(plik);
    Zakladka *nowa = dodajNowaZakladka(nazwa.fileName());
    QTextStream wejscie(&plik);
    nowa->dodajTekst(wejscie.readAll());
    nowa->zostalZapisany();
    plik.close();
}

QString MainWindow::pobierzNazwe(){
    pytanieOdpowiedz podajNazwe;
    podajNazwe.exec();
    QString nazwa = podajNazwe.on_buttonBox_accepted();
    podajNazwe.close();
    return nazwa;
}

void MainWindow::closeEvent(QCloseEvent * zamknij){
    bool czyWszystkoZapisane = true;
    for(int i = 0; i<ileZakladek;i++){
        QWidget *nowy = ui->tabWidget->widget(i);
        Zakladka *nowa = dynamic_cast<Zakladka*>(nowy);
        if(nowa->sprawdzCzyEdytowana()==1){
            czyWszystkoZapisane = false;
        }
    }
    if(czyWszystkoZapisane == false){
        QMessageBox::StandardButton odpowiedz = QMessageBox::question(this, "Wyjście", "Masz niezapisane pliki, zapisać?",QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
        if(odpowiedz == QMessageBox::No){
            zamknij->accept();
        }
        else if(odpowiedz == QMessageBox::Cancel){
            zamknij->ignore();
        }
        else{
            for(int i =0; i<ileZakladek; i++){
                QWidget *nowy = ui->tabWidget->widget(i);
                Zakladka *nowa = dynamic_cast<Zakladka*>(nowy);
                if(nowa->sprawdzCzyEdytowana()==1){
                    ui->tabWidget->setCurrentIndex(i);
                    zapiszPlik(i);
                }
            }
            zamknij->accept();
        }
    }
    else {
        zamknij->accept();
    }

}


void MainWindow::on_zmienCzcionke_triggered()
{
    if(ileZakladek>0){
        QWidget *nowy = ui->tabWidget->currentWidget();
        Zakladka *nowa = dynamic_cast<Zakladka*>(nowy);
        nowa->zmienRozmiarCzcionki();
    }
}

void MainWindow::on_actionCiemny_triggered()
{
    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        return;
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
}

void MainWindow::on_actionSrebrny_triggered()
{
    QFile f(":darkstyle/darkstyle.qss");
    if (!f.exists())
    {
        qDebug("BŁĄD");
        return;
    }
    else
    {
        qDebug("POWODZENIE");
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
}

void MainWindow::on_actionDomy_lny_triggered()
{
    qApp->setStyle(QApplication::style());
    qApp->setStyleSheet(nullptr);
}

void MainWindow::on_actionOpinia_triggered()
{
    info informacja;
    informacja.exec();
}

void MainWindow::on_actionWyj_cie_triggered()
{
    close();
}
