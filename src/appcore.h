#ifndef APPCORE_H
#define APPCORE_H

#include <QObject>
#include <klibcore/src/kmacro.h>
#include <klibcore/src/memcontrol/kmodulehandler.h>
#include <src/lib/kdynamicobjectlinker.h>
#include <src/lib/mousespy.h>
#include <src/network/klocalsyncronizer.h>
#include <src/lib/dynamicobject/jsonconfiguratedworker.h>

class AppCore : public QObject {
    Q_OBJECT
    K_QML_TYPE(AppCore)

    K_READONLY_PROPERTY(KModuleHandler*, moduleHandler, moduleHandler, setModuleHandler, moduleHandlerChanged, new KModuleHandler(this))
    K_CONST_PROPERTY(KDynamicObjectLinker*, linker, new KDynamicObjectLinker(this))
    K_READONLY_PROPERTY(QStringList, availableClasses, availableClasses, setAvailableClasses, availableClassesChanged, kAvailableClasses())

    KLocalSyncronizer localSyncronizer;

public:
    explicit AppCore(QObject *parent = nullptr);

signals:


public slots:
    QString objType(QObject* object){
        return object->metaObject()->className();
    }
    double parseFormula(const QString &formula);
    QString substitute(QString string);
    QObject *newInstance(QString typeName, QString property, QObject* parent);
    QStringList propertiesToString(const QMetaObject *meta);
};

#endif // APPCORE_H
