#ifndef SEAENVIRONMENT_H
#define SEAENVIRONMENT_H

#include <QObject>

#include <src/sea/vessel.h>
#include <src/utility/kabstractfactory.h>
#include <src/experimental/universalqueue/kuniversalqueue.h>

#define DECLARE_REQUEST_TYPE(TYPE, NAME) \
    class NAME { \
        TYPE m_value; \
    public: \
        NAME() { } \
        NAME(TYPE value) { m_value = value; } \
        TYPE value() const { return m_value; } \
    };

DECLARE_REQUEST_TYPE(QString, SeaCreateRequest)
DECLARE_REQUEST_TYPE(QString, SeaDestroyRequest)

class SeaEnvironment : public QObject {
    Q_OBJECT

    KAbstractFactory<QString, Vessel> vesselFactory;
    KUniversalQueue requestQueue;
    QList<Vessel*> vessels;
public:
    explicit SeaEnvironment(QObject *parent = nullptr);
    template<typename T>
    void registerType() { vesselFactory.registerType<T>(); }
    template<typename T>
    void pushRequest(const T request) { requestQueue.enqueue(request); }
signals:

};

#endif // SEAENVIRONMENT_H
