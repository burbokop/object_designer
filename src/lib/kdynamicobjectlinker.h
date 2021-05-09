#ifndef KDYNAMICOBJECTLINKER_H
#define KDYNAMICOBJECTLINKER_H



#include <QObject>
#include <QUuid>
#include <klibcore/src/kmacro.h>
#include <src/utility/kobjectlistener.h>
#include <src/utility/kvaluesaver.h>

class KConnection : public QObject {
    Q_OBJECT
    K_QML_TYPE(KConnection)
    K_AUTO_PROPERTY(QString, sender, sender, setSender, senderChanged, QString())
    K_AUTO_PROPERTY(QString, senderLabel, senderLabel, setSenderLabel, senderLabelChanged, QString())
    K_AUTO_PROPERTY(QString, senderProperty, senderProperty, setSenderProperty, senderPropertyChanged, QString())
    K_AUTO_PROPERTY(QString, reciever, reciever, setReciever, recieverChanged, QString())
    K_AUTO_PROPERTY(QString, recieverLabel, recieverLabel, setRecieverLabel, recieverLabelChanged, QString())
    K_AUTO_PROPERTY(QString, recieverProperty, recieverProperty, setRecieverProperty, recieverPropertyChanged, QString())
    K_AUTO_PROPERTY(bool, active, active, setActive, activeChanged, true)
public:
    KConnection(QObject *parent = nullptr) : QObject(parent) {}
    KConnection(QString sender, QString senderLabel, QString senderProperty, QString reciever, QString recieverLabel, QString recieverProperty, QObject *parent = nullptr) : QObject(parent) {
        setSender(sender);
        setSenderProperty(senderProperty);
        setReciever(reciever);
        setRecieverProperty(recieverProperty);
        setSenderLabel(senderLabel);
        setRecieverLabel(recieverLabel);
    }
    KConnection(const QVariant &data, QObject *parent = nullptr) : QObject(parent) {
        auto map = data.toMap();
        setSender(map["sender"].toString());
        setSenderProperty(map["senderProperty"].toString());
        setReciever(map["reciever"].toString());
        setRecieverProperty(map["recieverProperty"].toString());
        setSenderLabel(map["senderLabel"].toString());
        setRecieverLabel(map["recieverLabel"].toString());
    }
    QVariant serialize() {
        QVariantMap result;
        result["sender"] = sender();
        result["senderProperty"] = senderProperty();
        result["reciever"] = reciever();
        result["recieverProperty"] = recieverProperty();
        result["senderLabel"] = senderLabel();
        result["recieverLabel"] = recieverLabel();
        return result;
    }

signals:
    void dataTransferred();
    void dataBlocked();
};



class KDynamicObjectLinker : public QObject {
    Q_OBJECT
    K_QML_TYPE(KDynamicObjectLinker)

    KObjectListener *m_listener = new KObjectListener(this);
    QList<KConnection*> m_connections;
    K_LIST_PROPERTY(KConnection, connections, m_connections)
    QList<QObject*> m_objects;
    K_READONLY_LIST_PROPERTY(QObject, objects, m_objects)
    void __addObject(QObject *object, QString name);
public:
    static QString objectTree(QObject *object);
    explicit KDynamicObjectLinker(QObject *parent = nullptr);

    void changeProperty(QString object, QString property, QVariant value);

    KObjectListener *listener() const;

private slots:
signals:
    void activeChanged();
    void objectAdded(QObject *object);

public slots:
    inline void addObject(QObject *object) { __addObject(object, QString()); }
    void addConnection(KConnection *conn);
    void addConnection(QString sender, QString senderProperty, QString reciever, QString recieverProperty);
    void removeConnection(KConnection *conn);
    QObject *objectOfName(const QString &name);
};

#endif // KDYNAMICOBJECTLINKER_H
