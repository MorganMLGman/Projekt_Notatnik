#ifndef ZAKLADKA_H
#define ZAKLADKA_H

#include <QWidget>
#include "QFontDialog"

namespace Ui {
class Zakladka;
}

class Zakladka : public QWidget
{
    Q_OBJECT

public:
    explicit Zakladka(QWidget *parent = nullptr);
    ~Zakladka();
    bool sprawdzCzyEdytowana();
    bool sprawdzCzyZmienionaNazwa();
    void zostalZapisany();
    const QString &pobierzSciezke();
    void ustawSciezke(const QString &sciezkaPliku);
    QString pobierzTekst(bool rodzaj);
    void dodajTekst(QString tekst);
    void zmienRozmiarCzcionki();

private slots:
    void on_textEdit_textChanged();

private:
    Ui::Zakladka *ui;
    bool czyEdytowana;
    bool czyZmianaNazwy;
    QString sciezka;
};

#endif // ZAKLADKA_H
