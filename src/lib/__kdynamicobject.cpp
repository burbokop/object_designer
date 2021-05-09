#include "__kdynamicobject.h"

#include <QJsonDocument>
#include <QVariant>

#include <private/qmetaobjectbuilder_p.h>
#include <private/qmetaobject_p.h>


__KDynamicObject::__KDynamicObject(QObject *parent) : QObject(parent)
{

}

QObject *__KDynamicObject::create(QByteArray data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isNull()) {
        QMetaObjectBuilder builder;
        builder.addMetaObject(&__KDynamicObject::staticMetaObject);
        auto variantMap = doc.toVariant().toMap();
        for(auto it = variantMap.begin(); it != variantMap.end(); ++it) {
            auto property = builder.addProperty(it.key().toUtf8(), it.value().toByteArray());
            property.setNotifySignal(builder.addSignal(it.key().toUtf8() + "Changed(" + it.value().toByteArray() + ")"));
            property.setWritable(true);
        }
        auto meta = builder.toMetaObject();

        auto object = qobject_cast<__KDynamicObject*>(meta->newInstance());
        return object;
    }
    return nullptr;
}

void __KDynamicObject::__kdefault_static_metacall(QObject *, QMetaObject::Call _c, int, void **_a) {
    if (_c == QMetaObject::CreateInstance) {
        __KDynamicObject *_r = new __KDynamicObject();
        if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r;
    }
}


int KMetaObjectData::metaCall(QObject *, QMetaObject::Call, int _id, void **) {
    (void)_id;
    return -1;
}

