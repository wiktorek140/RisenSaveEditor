#include "infooffset.h"

InfoOffset::InfoOffset(QFile &f){
    f.open(QFile::ReadOnly);
    //f.pos()
    Version  = Helper::toInt(f.read(4));
    NameSize = Helper::toInt(f.read(2));
    NameData = Helper::toBString(f.read(NameSize));//.replace(0x00,'.');
    unknown0 = f.read(12);
    reserved = Helper::toInt(f.read(4));
    TimeStamp = Helper::toInt(f.read(8));
    WorldSize = Helper::toInt(f.read(2));
    WorldData = f.read(WorldSize);

    screenshot.Size = Helper::toInt(f.read(4));
    screenshot.data.HeaderVersion = Helper::toInt(f.read(2));
    screenshot.data.Signature = f.read(5);
    screenshot.data.Version = Helper::toInt(f.read(4));
    screenshot.data.Width = Helper::toInt(f.read(4));
    screenshot.data.Height = Helper::toInt(f.read(4));
    screenshot.data.Depth = Helper::toInt(f.read(4));
    screenshot.data.CubeMap = Helper::toInt(f.read(4));
    screenshot.data.Levels = Helper::toInt(f.read(4));
    screenshot.data.Usage = Helper::toInt(f.read(4));
    screenshot.data.ColorFormat = Helper::toInt(f.read(4));
    screenshot.data.Pool = Helper::toInt(f.read(4));
    screenshot.data.ImageSize = Helper::toInt(f.read(4));
    screenshot.data.unknown = Helper::toInt(f.read(4));
    screenshot.data.Reserved = Helper::toInt(f.read(4));
    screenshot.data.ImageData = f.read(screenshot.data.ImageSize);

    //f.seek(f.pos()+screenshot.Size);
    stats.Size = Helper::toInt(f.read(4));
    stats.data.GameTime = Helper::toInt(f.read(4));
    stats.data.Flags = Helper::toInt(f.read(4));
    stats.data.Chapter = Helper::toInt(f.read(4));

    qDebug()<<"CurrentPos: "<<f.pos();


    objects.Count = Helper::toInt(f.read(4));
    Objects::PropertyId prop;
    for(int i=0;i<objects.Count;i++){
        prop.Core = Helper::toGUID(f.read(16));
        prop.Count = Helper::toInt(f.read(4));
        prop.DataSize = Helper::toInt(f.read(4));
        objects.obj.append(prop);
    }
}

void InfoOffset::print() {
    qDebug()<<"InfoOffset part";
    qDebug()<<Version;
    qDebug()<<NameSize;
    qDebug()<<NameData;
    qDebug()<<TimeStamp;
    qDebug()<<WorldSize;
    qDebug()<<WorldData;
    qDebug()<<"Stats";
    qDebug()<<stats.data.GameTime;
    qDebug()<<stats.data.Flags;
    qDebug()<<stats.data.Chapter;
    qDebug()<<"Objects";
    qDebug()<<objects.Count;
    for(int i=0;i<objects.Count;i++){
        //qDebug()<<objects.obj.at(i).Core<<" - "<<
        //          objects.obj.at(i).Count<<" - "<<objects.obj.at(i).DataSize;
    }

}
