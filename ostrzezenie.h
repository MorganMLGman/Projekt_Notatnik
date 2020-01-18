#ifndef OSTRZEZENIE_H
#define OSTRZEZENIE_H

#include <QDialog>

namespace Ui {
class Ostrzezenie;
}

class Ostrzezenie : public QDialog
{
    Q_OBJECT

public:
    explicit Ostrzezenie(QWidget *parent = nullptr);
    ~Ostrzezenie();
    void zmienTekst(QString tekst);

private:
    Ui::Ostrzezenie *ui;
};

#endif // OSTRZEZENIE_H
