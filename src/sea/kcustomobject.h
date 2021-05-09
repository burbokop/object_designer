#ifndef KCUSTOMOBJECT_H
#define KCUSTOMOBJECT_H

#include <src/lib/dynamicobject/jsonconfiguratedworker.h>



class KCustomObject : public KDynamicObject {
    Q_OBJECT
    K_QML_TYPE(KCustomObject)
public:
    KCustomObject(QObject *parent = nullptr);
    //static QObject *create(const QByteArray &data, QObject *parent = nullptr);
};

#endif // KCUSTOMOBJECT_H
