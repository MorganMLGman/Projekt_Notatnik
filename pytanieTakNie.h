#ifndef PYTANIETAKNIE_H
#define PYTANIETAKNIE_H

#include <QDialog>

namespace Ui {
class pytanieTakNie;
}

class pytanieTakNie : public QDialog
{
    Q_OBJECT

public:
    explicit pytanieTakNie(QWidget *parent = nullptr);
    ~pytanieTakNie();
    void zmienTekst(QString tekst);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::pytanieTakNie *ui;
};

#endif // PYTANIETAKNIE_H
