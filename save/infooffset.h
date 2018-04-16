#ifndef INFOOFFSET_H
#define INFOOFFSET_H

#include <save/helper.h>

class InfoOffset {
public:
    InfoOffset(QFile &f);
    void print();

    int Version;               // 00000002
    short NameSize;
    QByteArray NameData;    // Name of the savegame (UTF-16)
    QByteArray unknown0;  //Only 12 length        // 00 00 00 00 00 00 00 00 00 00 00 00
    int reserved;              // (alignment)
    long TimeStamp;             // (struct FILETIME)
    short WorldSize;
    QByteArray WorldData;  // Name of the world (ASCII)

    class Screenshot {
    public:
        int Size;
        class Data {
        public:
            short HeaderVersion;  // 0001
            QByteArray Signature;   // "G3IMG"
            int Version;        // 00000002
            int Width;          // 00000080
            int Height;         // 00000080
            int Depth;          // 00000000
            int CubeMap;        // 00000000 (bool)
            int Levels;         // 00000001
            int Usage;          // 00000000
            int ColorFormat;    // 00000015
            int Pool;           // 00000001
            int ImageSize;      // 00010000
            int unknown;        // 3078C284
            int Reserved;       // 00000000
            QByteArray ImageData;  // (struct RGBQUAD[])
        } data;
    } screenshot;

    class Stats {
    public:
        int Size;  // 0000000C
        class Data {
        public:
            int GameTime;  // in seconds
            int Flags;     // 1 = Minsky?
            int Chapter;   // 1..4
        } data;

    } stats;

    class Objects {
    public:
        class PropertyId {
        public:
            QString Core;  //[16] (struct GUID)
            //QString Core_;
            int Count;
            int DataSize; //need to store it in this same place as property id to easier managing it
        };
        int Count;

        //for(int i=0;i<Count;i++ ) {
        int DataSize;    // 00000000
        //}
        QList<PropertyId> obj;

        } objects;
};

#endif // INFOOFFSET_H
