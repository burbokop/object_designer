#include "appcore.h"
#include "client1.h"
#include "client2.h"

#include <src/network/kpackage.h>

#include <QQuickItem>
#include <QTimer>
#include <math.h>

#include <src/sea/acousticantenna.h>
#include <QMetaType>
#include <src/lib/__kdynamicobject.h>
#include <src/lib/dynamicobject/formulaparser.h>
#include <src/lib/dynamicobject/jsonconfiguratedworker.h>
#include <src/lib/dynamicobject/kvaluesubstitute.h>

AppCore::AppCore(QObject *parent) : QObject(parent) {

    {
        moduleHandler()->registerModules<
                Client1,
                AcousticAntenna
        >("debug");
    } {
        moduleHandler()->registerModule<
                Client1
        >("client1");
    } {
        moduleHandler()->registerModules<
                AcousticAntenna
        >("antena");
    }

    localSyncronizer.bind(4444);


    setAvailableClasses(kAvailableClasses());

    connect(&localSyncronizer, &KLocalSyncronizer::frameReady, this, [this](QByteArray array) {        
        auto package = KPackage::fromJson(array);
        if(package.type() == "propertyChanged") {
            auto data = package.data().toMap();
            auto object = data["object"].toString();
            auto property = data["property"].toString();
            auto value = data["value"].toString();
            linker()->changeProperty(object, property, value);
        }
    });

    connect(linker()->listener(), &KObjectListener::propertyEvent, this, [this](QString objectName, QString property, QVariant value){
        QVariantMap data;
        data["object"] = objectName;
        data["property"] = property;
        data["value"] = value;
        localSyncronizer.write(KPackage("propertyChanged", data).toJson());
        linker()->changeProperty(objectName, property, value);
    });

    connect(moduleHandler(), &KModuleHandler::objectInstantiated, linker(), &KDynamicObjectLinker::addObject);

    QTimer::singleShot(500, this, [this](){
        moduleHandler()->setMode("debug");
    });
}

double AppCore::parseFormula(const QString &formula) {
    KFormulaParser parser;
    parser.addOperation('+', 1, [](auto a, auto b) { return a + b; });
    parser.addOperation('-', 1, [](auto a, auto b) { return a - b; });
    parser.addOperation('*', 2, [](auto a, auto b) { return a * b; });
    parser.addOperation('/', 2, [](auto a, auto b) { return a / b; });
    parser.addOperation('%', 2, &std::fmod);
    return parser.parse(KFormulaParser::removeSpacing(formula));
}

QString AppCore::substitute(QString string) {
    return KValueSubstitutor::substitute(string, { { "aa", 1 }, { "bb", 2 } });
}

QObject *AppCore::newInstance(QString typeName, QString property, QObject *parent) {
    auto instance = kNewInstance(typeName, parent);
    //auto instance = kInstantinate(typeName);
    if(instance && parent) {
        qDebug() << "add:" << instance << "to" << parent << "as" << property;
        qDebug() << parent->setProperty(property.toStdString().c_str(), QVariant::fromValue<QObject*>(instance));
    }
    return instance;
}

QStringList AppCore::propertiesToString(const QMetaObject *meta) {
    QStringList result;
    for(auto i = 0, c = meta->propertyCount(); i < c; ++i) {
        auto prop = meta->property(i);
        result << ((prop.isWritable() ? QString("") : "readonly ") + prop.typeName() + " " + prop.name() + " " + prop.notifySignal().name());
    }
    return result;
}
