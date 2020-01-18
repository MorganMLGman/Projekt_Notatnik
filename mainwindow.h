#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include "zakladka.h"
#include "ostrzezenie.h"
#include "pytanietaknie.h"
#include "pytanieodpowiedz.h"
#include "QFileDialog"
#include "QFile"
#include "QFileInfo"
#include "QTabWidget"
#include "QWidget"
#include "QCloseEvent"
#include "QMessageBox"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent * zamknij);

private slots:
    void on_dodajNowy_triggered();

    void on_otworzPlik_triggered();

    void on_zapiszPlik_triggered();

    void on_tabWidget_tabCloseRequested(int index);


private:
    Ui::MainWindow *ui;
    int ileZakladek;
    Zakladka* dodajNowaZakladka(QString nazwa);
    QString pobierzNazwe();
    void zapiszPlik(int indeks);
    void otworzPlik();

};
#endif // MAINWINDOW_H
