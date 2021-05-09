#ifndef KDYNAMICOBJECT2_H
#define KDYNAMICOBJECT2_H

#include <klibcore/src/kmacro.h>

#include <QFile>
#include <QObject>
#include <QVariant>


class KDynamicObject;

class KDynamicObjectWorker {
    friend KDynamicObject;
    KDynamicObject *__object;
protected:
    bool setPropertyPrivate(const char *name, const QVariant &value);
public:
    virtual bool beforeCompleate(KDynamicObject *, const QByteArray &) { return true; }
    virtual void afterCompleate(KDynamicObject *) { }
    virtual ~KDynamicObjectWorker() {}
};

/** Can configure meta object in runtime. */
class KDynamicObject : public QObject {
    friend KDynamicObjectWorker;
public:
    QT_WARNING_PUSH
    Q_OBJECT_NO_OVERRIDE_WARNING
    static inline const QMetaObject staticMetaObject = QObject::staticMetaObject;
    virtual const QMetaObject *metaObject() const override;
    virtual void *qt_metacast(const char *) override;
    virtual int qt_metacall(QMetaObject::Call, int, void **) override;
    QT_TR_FUNCTIONS
private:
    Q_OBJECT_NO_ATTRIBUTES_WARNING
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **);
    QT_WARNING_POP
    struct QPrivateSignal {};
    QT_ANNOTATE_CLASS(qt_qobject, "")
    K_QML_TYPE(KDynamicObject)
public:
    explicit KDynamicObject(QObject *parent = nullptr);
    ~KDynamicObject();


    void specifyClassName(const QByteArray &className);

    /** Adds a new property to the object, must be called before ready(). */
    void addProperty(const QByteArray &name, const QByteArray &type, bool writable = true, const QVariant &value = QVariant());

    /** Marks the object as ready and creates the metaObject. */
    void compleate();

    template<typename T>
    bool compleate(const QByteArray &data = QByteArray()) {
        if (m_metaObject != nullptr) {
            error(QString(__PRETTY_FUNCTION__) + " should be called only once.");
            return false;
        }
        m_worker = new T();
        m_worker->__object = this;
        if(m_worker->beforeCompleate(this, data)) {
            compleate();
            m_worker->afterCompleate(this);
            return true;
        }
        return false;
    }

    template<typename T>
    static QObject *create(const QByteArray &data, QObject *parent) {
        auto result = new KDynamicObject(parent);
        if(result->compleate<T>(data)) {
            result->setParent(parent);
            return result;
        }
        error(QString(__PRETTY_FUNCTION__) + " class not resolved.");
        delete result;
        return nullptr;
    }

    template<typename T>
    static QObject *load(const QString &file, QObject *parent) {
        QFile f(file);
        if(f.open(QIODevice::ReadOnly)) {
            return create<T>(f.readAll(), parent);
        }
        error(QString(__PRETTY_FUNCTION__) + " file not opened.");
        return nullptr;
    }

private:
    static void error(QString message);
    struct DynamicProperty {
        QByteArray name;
        QByteArray type;
        int typeId;
        QVariant variant;
        bool writable;
    };

    QByteArray m_className;
    QMetaObject *m_metaObject = nullptr;
    KDynamicObjectWorker *m_worker = nullptr;
    std::vector<DynamicProperty> m_properties;
};
#endif // KDYNAMICOBJECT2_H
