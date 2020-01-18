#ifndef PYTANIEODPOWIEDZ_H
#define PYTANIEODPOWIEDZ_H

#include <QDialog>

namespace Ui {
class pytanieOdpowiedz;
}

class pytanieOdpowiedz : public QDialog
{
    Q_OBJECT

public:
    explicit pytanieOdpowiedz(QWidget *parent = nullptr);
    ~pytanieOdpowiedz();
    QString on_buttonBox_accepted();

private slots:

private:
    Ui::pytanieOdpowiedz *ui;
};

#endif // PYTANIEODPOWIEDZ_H
