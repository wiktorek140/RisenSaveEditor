#ifndef HEADER_H
#define HEADER_H

#include "save/helper.h"

class Header {
public:
    Header(char *argv){
        QFile f(argv);
        f.open(QFile::ReadWrite);

        Signature = f.read(8);
        Version = Helper::toInt(f.read(4));
        Reserved = Helper::toInt(f.read(4));
        InfoOffest = Helper::toInt(f.read(4));
        LayerOffest = Helper::toInt(f.read(4));
        ObjectOffset = Helper::toInt(f.read(4));
        //print();
        f.close();
    }

    Header(QFile &f){

        f.open(QFile::ReadWrite);
        Signature = f.read(8);
        Version = Helper::toInt(f.read(4));
        Reserved = Helper::toInt(f.read(4));
        InfoOffest = Helper::toInt(f.read(4));
        LayerOffest = Helper::toInt(f.read(4));
        ObjectOffset = Helper::toInt(f.read(4));
    }

    QByteArray Signature;
    int Version;
    int Reserved;
    int InfoOffest;
    int LayerOffest;
    int ObjectOffset;

    void print() {
        qDebug()<<Signature;
        qDebug()<<Version;
        qDebug()<<Reserved;
        qDebug()<<InfoOffest;
        qDebug()<<LayerOffest;
        qDebug()<<ObjectOffset;
    }

};

#endif // HEADER_H
