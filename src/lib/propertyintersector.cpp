#include "propertyintersector.h"

PropertyIntersector::PropertyIntersector(QObject *parent) : QObject(parent)
{

}

void PropertyIntersector::changeProperty(const QString &obj, const QString &prop, const QVariant &value) {
    emit propertyChanged(obj, prop, value);
}

void PropertyIntersector::appendMeta(const QByteArray &data) {
    (void)data;
}

void PropertyIntersector::changeMeta(const QByteArray &data) {
    (void)data;
    //emit metaChanged(data);
}
