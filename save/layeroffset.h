#ifndef LAYEROFFSET_H
#define LAYEROFFSET_H
#include "save/helper.h"

class LayerOffset {
public:
    LayerOffset(QFile &f);
    void print();

    int startBuffer;
    class Header {
    public:
        int unknown;      // 00000001
        int FilesOffset;  // offset incremented of start pos of buffer
        int EmptyOffset;  // offset
        int ObjIdOffset;
    } header;


    class Buffer {
    public:
        void initDatas(QFile &f, int EmptyOffset);
        class ObjId {
        public:
            QByteArray unknown;  // 01
            int Count;
            class PropertyId {
            public:
                QString Core;  //[16] (struct GUID)
                int Count;     // 00000000
            };

            QList<PropertyId> propList;
        } objId;

        class Datas { // [File.Count] {
        public:
            int BufferSize;
            int ObjectCount;
            class BufferData {
            public:
                void clean();
                //for( ObjectCount ) {
                class ObjectId {
                public:
                    QString Core;  // (struct GUID)
                    int Count;     // 00000000
                } objectId;

                class ParentId {
                public:
                    QString Core;  // (struct GUID)
                    int Count;     // 00000000
                } parentId;

                class PropertyId {            // Template/Class/Type?
                public:
                    QString UnknownId;  // (struct GUID)
                    int Count;          // 00000000
                } propertyId;

                int unknown;  // 01
                int ObjectSize;
                class ObjectData {
                public:
                    short Reserved;  // 00D6
                    bool isTrue ; //znak (bool)
                    //if( isTrue ) {
                    float unknown0[4][4];  // World matrix? (struct D3DMATRIX)
                    float unknown1[4][4];  // Local matrix? (struct D3DMATRIX)
                    float unknown2[3];
                    float unknown3[3];
                    float unknown4[3];
                    float unknown5[3];
                    float unknown6[3];
                    float unknown7[3];
                    float unknown8[8];
                    // }
                    int PropertyCount; //1 byte
                    //for( PropertyCount ) {
                    class Property {
                    public:
                        short Type;
                        int Index;
                        int Size;
                        QByteArray Data;//[Size]  //TODO: Document property types/data.
                    };
                    QList<Property> property;
                } objectData;  
            };
            QList<BufferData> bufferData;
        };

        QList<Datas> datas;

    } buffer;
};

#endif // LAYEROFFSET_H
