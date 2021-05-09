#include "kdynamicobjectlinker.h"

#include <QCoreApplication>
#include <QFile>
#include <QTimer>

#include <klibcore/src/kadditional.h>

#include <src/utility/ktype.h>

#include <src/network/kpackage.h>

QString KDynamicObjectLinker::objectTree(QObject *object) {
    if(!object)
        return QString();

    QString result = objectTree(object->parent());
    result += ".";
    result += object->metaObject()->className();
    return result;
}

KDynamicObjectLinker::KDynamicObjectLinker(QObject *parent) : QObject(parent) {
    QFile input(KAdditional::absolutePath(KType<KDynamicObjectLinker>()));
    if(input.open(QIODevice::ReadOnly)) {
        auto p = KPackage::fromBinary(input.readAll());
        auto list = p.data().toList();
        for(auto l : list) {
            addConnection(new KConnection(l, this));
        }
        connectionsChanged(connections());
    }

    connect(QCoreApplication::instance(), &QCoreApplication::aboutToQuit, this, [this]() {
        QFile output(KAdditional::absolutePath(KType<KDynamicObjectLinker>()));
        output.open(QIODevice::WriteOnly);
        QVariantList list;
        for(auto c : m_connections) {
            list.push_back(c->serialize());
        }
        output.write(KPackage(KType<KDynamicObjectLinker>(), list).toBinary());
    });
}

KObjectListener *KDynamicObjectLinker::listener() const
{
    return m_listener;
}



void KDynamicObjectLinker::__addObject(QObject *object, QString name) {
    if(!object)
        return;

    if(m_objects.contains(object))
        return;

    if(object->objectName().isEmpty()) {
        if(name.isEmpty()) {
            object->setObjectName(object->metaObject()->className());
        } else {
            object->setObjectName(name);
        }        
    }

    m_listener->listen(object);

    m_objects.push_back(object);
    objectsChanged(objects());
    objectAdded(object);
    connect(object, &QObject::destroyed, this, [object, this](){ m_objects.removeOne(object); objectsChanged(objects()); });

    for(auto i = 0, count = object->metaObject()->propertyCount(); i < count; ++i) {
        if(auto cc = object->metaObject()->property(i).read(object).value<QObject*>())
            __addObject(cc, object->objectName() + "." + object->metaObject()->property(i).name());
    };
}

void KDynamicObjectLinker::changeProperty(QString object, QString property, QVariant value) {
    for(auto connection : m_connections) {
        if(connection->sender() == object && connection->senderProperty() == property) {
            if(connection && connection->active()) {
                for(auto o : m_objects) {
                    if(o && o->objectName() == connection->reciever()) {
                        auto meta = o->metaObject();
                        for(auto i = 0, count = meta->propertyCount(); i < count; ++i) {
                            QString str = meta->property(i).name();
                            if(str == connection->recieverProperty()) {
                                if(meta->property(i).isWritable()) {
                                    meta->property(i).write(o, value);
                                    emit connection->dataTransferred();
                                } else {
                                    emit connection->dataBlocked();
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

void KDynamicObjectLinker::addConnection(KConnection *conn) {
    connect(conn, &KConnection::activeChanged, this, [this](bool){
        activeChanged();
    });

    m_connections.push_back(conn);
    connectionsChanged(connections());
    conn->setParent(this);
}

void KDynamicObjectLinker::addConnection(QString sender, QString senderProperty, QString reciever, QString recieverProperty) {
    auto c = new KConnection(sender, "", senderProperty, reciever, "", recieverProperty, this);
    addConnection(c);
    //connectionAdded(c);
}

void KDynamicObjectLinker::removeConnection(KConnection *conn) {
    QMetaObject::invokeMethod(this, [this, conn]() {
        m_connections.removeOne(conn);
        conn->deleteLater();
        connectionsChanged(connections());
        //connectionRemoved(conn);
    });
}

QObject *KDynamicObjectLinker::objectOfName(const QString &name) {
    for(auto o : m_objects) {
        if(o && o->objectName() == name) {
            return o;
        }
    }
    return nullptr;
}
