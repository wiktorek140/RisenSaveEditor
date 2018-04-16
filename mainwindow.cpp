#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initSave();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initSave() {
    QFile f("QuickSave.save");
    Header h(f);
    h.print();
    f.seek(h.InfoOffest);

    FileSaver::save("zlib.compr",f.read(f.size() - h.InfoOffest));
    //Decompress todo
    QFile z("zlib.ucompr");

    InfoOffset i(z);
    i.print();
    LayerOffset l(z);
    l.print();
    setData(h,i,l);

}

void MainWindow::setData(Header h, InfoOffset io, LayerOffset lo){
    ui->chapter->setText(ui->chapter->text()+": "+Helper::toString(io.stats.data.Chapter));
    ui->flag->setText(ui->flag->text()+": "+Helper::toString(io.stats.data.Flags));
    ui->gameTime->setText(ui->gameTime->text()+": "+Helper::toString(io.stats.data.GameTime));

    ui->name->setText(ui->name->text()+": " + QString(io.NameData));
    ui->time->setText(ui->time->text()+": "+ Helper::toString(io.TimeStamp));

    for(int i=0;i<io.objects.Count;i++)ui->Obiekty->addItem(QString(io.objects.obj.at(i).Core));

    for(int i=0;i<lo.buffer.objId.Count;i++)ui->ObjId->addItem(QString(lo.buffer.objId.propList.at(i).Core));
}

void MainWindow::on_Obiekty_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"Cliced obiekty: "<<item->text();

    ObjectEdit *edit= new ObjectEdit();
    edit->setObjectName(item->text());
    edit->setWindowTitle(item->text());
    edit->show();

}

void MainWindow::on_ObjId_itemClicked(QListWidgetItem *item)
{
    qDebug()<<"Cliced objid: "<<item->text();

    ObjectEdit *edit= new ObjectEdit();
    edit->setObjectName(item->text());
    edit->setWindowTitle(item->text());
    edit->show();
}
