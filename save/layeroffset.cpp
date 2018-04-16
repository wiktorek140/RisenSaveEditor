#include <save/layeroffset.h>

LayerOffset::LayerOffset(QFile &f) {

    header.unknown = Helper::toInt(f.read(4));
    header.FilesOffset = Helper::toInt(f.read(4));
    header.EmptyOffset = Helper::toInt(f.read(4));
    header.ObjIdOffset = Helper::toInt(f.read(4));
    qDebug()<<"Buffer Pos: "<<f.pos();
    startBuffer = f.pos();
    header.FilesOffset+=startBuffer;
    header.EmptyOffset+=startBuffer;
    header.ObjIdOffset+=startBuffer;


    buffer.objId.unknown = f.read(1);
    buffer.objId.Count = Helper::toInt(f.read(4));
    Buffer::ObjId::PropertyId prop;
    for(int i=0;i<buffer.objId.Count;i++){
        prop.Core = Helper::toGUID(f.read(16));
        prop.Count = Helper::toInt(f.read(4));
        buffer.objId.propList.append(prop);
    }
    qDebug()<<"Datas Pos: "<<f.pos();
    buffer.initDatas(f, header.EmptyOffset);
}

void LayerOffset::print(){
    qDebug()<<"LayerOffset";
    qDebug()<<"Header";
    qDebug()<<header.unknown;
    qDebug()<<header.FilesOffset;
    qDebug()<<header.EmptyOffset;
    qDebug()<<header.ObjIdOffset;

    qDebug()<<"Buffer";
    qDebug()<<buffer.objId.Count;
    //for(int i=0;i<buffer.objId.Count;i++){
        //qDebug()<<i<<": "<<buffer.objId.propList.at(i).Core<<
        //          " - "<<buffer.objId.propList.at(i).Count;
    //}
}

void LayerOffset::Buffer::initDatas(QFile &f, int EmptyOffset){
    LayerOffset::Buffer::Datas data;
    LayerOffset::Buffer::Datas::BufferData bdata;
    while(f.pos() < EmptyOffset){
        data.BufferSize = Helper::toInt(f.read(4));
        data.ObjectCount = Helper::toInt(f.read(4));

        for(int i=0;i<data.ObjectCount;i++){
            bdata.objectId.Core = Helper::toGUID(f.read(16));
            bdata.objectId.Count = Helper::toInt(f.read(4));
            bdata.parentId.Core = Helper::toGUID(f.read(16));
            bdata.parentId.Count = Helper::toInt(f.read(4));
            bdata.propertyId.UnknownId = Helper::toGUID(f.read(16));
            bdata.propertyId.Count = Helper::toInt(f.read(4));
            bdata.unknown = Helper::toInt(f.read(1));
            bdata.ObjectSize = Helper::toInt(f.read(4));

            bdata.objectData.Reserved = Helper::toInt(f.read(2));
            bdata.objectData.isTrue = Helper::toBool(f.read(1));

            data.bufferData.append(bdata);
        }
        datas.append(data);
    }
}


void LayerOffset::Buffer::Datas::BufferData::clean(){
    //this->objectData.unknown0;
}
