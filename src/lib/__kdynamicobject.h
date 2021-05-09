#ifndef __KDYNAMICOBJECT_H
#define __KDYNAMICOBJECT_H

#include <klibcore/src/kmacro.h>

#include <private/qobject_p.h>

#define Q_OBJECT_WITHOUT_META_OBJECT \
public: \
    QT_WARNING_PUSH \
    Q_OBJECT_NO_OVERRIDE_WARNING \
    static inline const QMetaObject staticMetaObject = QObject::staticMetaObject; \
    virtual void *qt_metacast(const char *); \
    virtual int qt_metacall(QMetaObject::Call, int, void **); \
    QT_TR_FUNCTIONS \
private: \
    Q_OBJECT_NO_ATTRIBUTES_WARNING \
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
    QT_WARNING_POP \
    struct QPrivateSignal {}; \
    QT_ANNOTATE_CLASS(qt_qobject, "")




class KMetaObjectData : public QAbstractDynamicMetaObject {

    QMetaObject *m_metaObject = nullptr;
    // QDynamicMetaObjectData interface
public:
    KMetaObjectData(QMetaObject *metaObject) { m_metaObject = metaObject; }

    int metaCall(QObject *, QMetaObject::Call, int _id, void **) override;
};

class __KDynamicObject : public QObject {
    Q_OBJECT
    K_QML_TYPE(__KDynamicObject)
    QMetaObject *m_metaObject = nullptr;
    //void setMetaObject(QMetaObject *metaObject);
public:
    Q_INVOKABLE explicit __KDynamicObject(QObject *parent = nullptr);

    //virtual const QMetaObject *metaObject() const;


    static QObject *create(QByteArray data);
    static void __kdefault_static_metacall(QObject*, QMetaObject::Call _c, int, void **_a);

signals:

};

//Q_DECLARE_METATYPE(KDynamicObject)

#endif // __KDYNAMICOBJECT_H
