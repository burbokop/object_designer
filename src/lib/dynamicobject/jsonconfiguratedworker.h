#ifndef JSONCONFIGURATEDWORKER_H
#define JSONCONFIGURATEDWORKER_H

#include "formulaparser.h"

#include <src/lib/dynamicobject/kdynamicobject.h>

#include <QElapsedTimer>




class KObjectListener;
class QTimer;
class JsonConfiguratedWorker : public KDynamicObjectWorker {
    KObjectListener *m_listener = nullptr;
    QTimer *m_updateTimer = nullptr;
    KDynamicObject *m_object = nullptr;
    KFormulaParser fromulaParser;
    QElapsedTimer elapsedTimer;
    QElapsedTimer elapsedTimer2;
    void update();
    void propertyChanged(QString objectName, QString property, QVariant value);
    struct Reciept {
        enum Type { Change, Loop };
        QStringList inputPropertyNames;
        QString outputPropertyName;
        std::function<QVariant(const QVariantMap &)> function;
        Type type = Change;
    };

    struct Program {
        QList<Reciept> changeRecieptList;
    } m_program;
    Program compile(const QVariantMap &data, const QStringList &properties);

public:
    JsonConfiguratedWorker();
    static QString replace(QString string, const QVariantMap &values);
    // KDynamicObjectWorker interface
public:
    bool beforeCompleate(KDynamicObject *dynamicObject, const QByteArray &data) override;
    void afterCompleate(KDynamicObject *dynamicObject) override;
};

#endif // JSONCONFIGURATEDWORKER_H
