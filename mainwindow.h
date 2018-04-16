#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QFile>
#include <QDebug>
#include "save/header.h"
#include "save/filesaver.h"
#include "save/infooffset.h"
#include "save/layeroffset.h"
#include "objectedit.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initSave();
    void setData(Header h, InfoOffset io, LayerOffset lo);


private slots:
    void on_Obiekty_itemClicked(QListWidgetItem *item);

    void on_ObjId_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
