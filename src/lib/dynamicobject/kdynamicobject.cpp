#include "kdynamicobject.h"

#include <private/qmetaobjectbuilder_p.h>
#include <cstring>
#include <QLoggingCategory>
#include <QJsonDocument>

Q_LOGGING_CATEGORY(loggingCategory, KType<KDynamicObject>().operator const char *());


KDynamicObject::KDynamicObject(QObject *parent)
    : QObject(parent)
    , m_metaObject(nullptr) {
}

KDynamicObject::~KDynamicObject() {
    free(m_metaObject);
    delete m_worker;
}

void KDynamicObject::addProperty(const QByteArray &name, const QByteArray &type, bool writable, const QVariant &value) {
    if (m_metaObject != nullptr) {
        error(QString(__PRETTY_FUNCTION__) + ": Can't add property after calling compleate()");
        return;
    }

    m_properties.emplace_back(DynamicProperty{ name, type, QMetaType::type(type), value, writable });
}

void KDynamicObject::error(QString message) {
    qCWarning(loggingCategory) << message;
    qDebug() << message;
}

void KDynamicObject::compleate() {
    if (m_metaObject != nullptr) {
        error(QString(__PRETTY_FUNCTION__) + " should be called only once.");
        return;
    }

    if(m_className.isEmpty())
        m_className = KType<KDynamicObject>().typeName().toUtf8();

    QMetaObjectBuilder builder;
    builder.setClassName(m_className);
    builder.setSuperClass(&QObject::staticMetaObject);

    for (const auto &dynamicProperty: m_properties) {
        auto property = builder.addProperty(dynamicProperty.name, dynamicProperty.type);
        property.setWritable(dynamicProperty.writable);
        auto signal = builder.addSignal(dynamicProperty.name + "Changed(" + dynamicProperty.type + ")");
        property.setNotifySignal(signal);
    }

    m_metaObject = builder.toMetaObject();
}

void KDynamicObject::specifyClassName(const QByteArray &className) {
    if (m_metaObject != nullptr) {
        error(QString(__PRETTY_FUNCTION__) + ": Can't specify class name after calling compleate()");
        return;
    }
    m_className = className;
}

const QMetaObject* KDynamicObject::metaObject() const {
    return m_metaObject;
}

int KDynamicObject::qt_metacall(QMetaObject::Call call, int id, void **argv) {
    const int realId = id - m_metaObject->propertyOffset();
    if (realId < 0) {
        return QObject::qt_metacall(call, id, argv);
    }

    if (call == QMetaObject::ReadProperty) {
        const auto &property = m_properties.at(static_cast<size_t>(realId));
        QMetaType::construct(property.typeId, argv[0], property.variant.data());
    }
    else if (call == QMetaObject::WriteProperty) {
        auto &property = m_properties.at(static_cast<size_t>(realId));
        property.variant = QVariant(property.typeId, argv[0]);
        *reinterpret_cast<int*>(argv[2]) = 1;  // setProperty return value
        QMetaObject::activate(this, m_metaObject, realId, nullptr);
    }
    else {
        // not handled
    }

    return -1;
}


void* KDynamicObject::qt_metacast(const char *name) {
    if (strcmp(name, m_metaObject->className()) == 0) {
        return this;
    } else {
        return QObject::qt_metacast(name);
    }
}


bool KDynamicObjectWorker::setPropertyPrivate(const char *name, const QVariant &value) {
    if(__object && __object->m_metaObject) {
        size_t index = __object->m_metaObject->indexOfProperty(name) - __object->m_metaObject->propertyOffset();
        if(index < __object->m_properties.size()) {
            if(__object->m_properties[index].variant != value) {
                __object->m_properties[index].variant = value;
                QMetaObject::activate(__object, __object->m_metaObject, index, nullptr);
            }
            return true;
        }
    }
    return false;
}
