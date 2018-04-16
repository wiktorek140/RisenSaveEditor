#ifndef HELPER_H
#define HELPER_H
#include <QDebug>
#include <QFile>
#include <sstream>
#include <iomanip>

class Helper {
public:
    static QByteArray so(QByteArray b) {
        //qDebug()<<b;
        QByteArray out;
        if(b.size()==2) {
            //qDebug()<<"Found correct";
            for(int i=b.size()-1;i>=0;i--)
                out.append(b[i]);
        }
        if(b.size()==4) {
            //qDebug()<<"Found correct";
            for(int i=b.size()-1;i>=0;i--)
                out.append(b[i]);
        }
        if(b.size()==8) {
            //qDebug()<<"Found correct";
            for(int i=b.size()-1;i>=0;i--)
                out.append(b[i]);
        }
        return out;
    }

    static int toInt(QByteArray b, bool debug = false) {
        if(debug) qDebug()<<b.toHex();
        if(b.size() == 1) return b.toInt(0,16);
        if(b.size() % 2 != 0) return b.toHex().toInt(0,16);
        return so(b).toHex().toInt(0,16);
    }

    static bool toBool(QByteArray b, bool debug = false) {
        if(debug) qDebug()<<b.toHex();
        if(b.at(0) == 1) return true;
        if(b.at(0) == 0) return false;

        qDebug()<<"To nie bool";
        return false;
    }

    //static QByteArray toGUID(QByteArray b) {
    //    return b;
    //}

    static QString toGUID(QByteArray b) {
        QString out;
        for(int i=3;i>=0;i--){out.append(Helper::toHexString(b.at(i)));}
        out.append('-');

        for(int i=5;i>=4;i--){out.append(Helper::toHexString(b.at(i)));}
        out.append('-');

        for(int i=7;i>=6;i--){out.append(Helper::toHexString(b.at(i)));}
        out.append('-');

        for(int i=9;i>=8;i--){out.append(Helper::toHexString(b.at(i)));}
        out.append('-');

        for(int i=15;i>=10;i--){out.append(Helper::toHexString(b.at(i)));}

        return out;
    }

   static QString toString(long liczba, bool hex=false) {
        // Zmiana int na QString w celu numeracji pytań
        std::stringstream ss;
        if(!hex) ss << liczba;
        else ss<<std::hex<<liczba;
        std::string s;
        ss>>s;
        //const char* out = s.c_str();
        return *new QString(s.c_str());
    }

   static QString toHexString(unsigned char liczba) {
        // Zmiana int na QString w celu numeracji pytań

        std::stringstream ss;
        if(liczba<16) {ss<<"0"; ss<<std::setw(1)<<std::hex<<(int)liczba;}
        else ss<<std::setw(2)<<std::hex<<(int)liczba;
        std::string s;
        ss>>s;
        //const char* out = s.c_str();
        return *new QString(s.c_str());
    }

   static QByteArray toBString(QByteArray b) {
       //QByteArray t;
       for(int i=0;i<b.size();i++){
           if(b.at(i) == 0x0){//t.append(NameData.at(i));
            b.remove(i,1);
            i--;
           }
       }
       return b;
   }

};

class FileSaver {
public:
    static void save(QString filename, QByteArray b){
        QFile f(filename);
        //f.seek(h.InfoOffest);

        f.open(QFile::ReadWrite);
        f.write(b);
        f.close();
    }
};

#endif // HELPER_H
