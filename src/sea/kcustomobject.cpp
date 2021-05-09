#include "kcustomobject.h"


KCustomObject::KCustomObject(QObject *parent) : KDynamicObject(parent) {

}

//QObject *KCustomObject::create(const QByteArray &data, QObject *parent) {
//    auto result = new KCustomObject();
//
//    result->addProperty("abc0", "int", 4);
//    result->compleate();
//
//
//    result->setProperty("abc0", 112);
//    qDebug() << "cn" << result->property("abc0");
//
//
//    result->setParent(parent);
//    return result;
//}
