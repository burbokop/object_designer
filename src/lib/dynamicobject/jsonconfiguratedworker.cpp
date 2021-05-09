#include "jsonconfiguratedworker.h"

#include <QJsonDocument>
#include <QTimer>
#include <src/math/kmath.h>
#include <src/utility/kobjectlistener.h>
#include <QtDebug>
#include <QMetaType>
#include <math.h>

void JsonConfiguratedWorker::update() {
//    qDebug() << m_object->property("resultAngle");
    for(auto reciept : m_program.changeRecieptList) {
        if(reciept.type == Reciept::Loop) {
            QVariantMap values;
            for(auto prop : reciept.inputPropertyNames) {
                values[prop] = m_object->property(prop.toStdString().c_str());
            }
            values["daltaTime"] = elapsedTimer.restart();
            values["elapsedTime"] = elapsedTimer2.elapsed();
            if(values.size() > 0) {
                setPropertyPrivate(reciept.outputPropertyName.toStdString().c_str(), reciept.function(values));
            }
        }
    }
}

void JsonConfiguratedWorker::propertyChanged(QString objectName, QString property, QVariant value) {
    (void)objectName;
    (void)value;
    for(auto reciept : m_program.changeRecieptList) {
        if(reciept.type == Reciept::Change) {
            bool neededReciept = false;
            QVariantMap values;
            for(auto prop : reciept.inputPropertyNames) {
                if(prop == property) neededReciept = true;
                values[prop] = m_object->property(prop.toStdString().c_str());
            }
            if(neededReciept) {
                if(setPropertyPrivate(reciept.outputPropertyName.toStdString().c_str(), reciept.function(values))) {
                    break;
                }
            }
        }
    }
}

JsonConfiguratedWorker::Program JsonConfiguratedWorker::compile(const QVariantMap &data, const QStringList &properties) {
    Program result;

    fromulaParser.addOperation('+', 1, [](auto a, auto b) { return a + b; });
    fromulaParser.addOperation('-', 1, [](auto a, auto b) { return a - b; });
    fromulaParser.addOperation('*', 2, [](auto a, auto b) { return a * b; });
    fromulaParser.addOperation('/', 2, [](auto a, auto b) { return a / b; });
    fromulaParser.addOperation('%', 2, &std::fmod);


    for(auto recieptData : data["reciepts"].toList()) {
        //ChangeReciept r;
        //r.outputPropertyName = "aaa";
        //r.inputPropertyNames = { "a", "b", "c" }
        //result.changeRecieptList.push_back(r);
    }

    for(auto it = data.begin(); it != data.end(); ++it) {
        if(it.key() != "class" && it.key() != "members") {
            auto rule = it.value().toString().split('=');
            if(rule.size() > 1) {
                Reciept testReciept;
                if(it.key().contains("loop")) {
                    testReciept.type = Reciept::Loop;
                }
                testReciept.outputPropertyName = KFormulaParser::removeSpacing(rule[0]);
                QString formula = rule[1];

                for(auto p : properties) {
                    if(formula.contains(p)) {
                        testReciept.inputPropertyNames.push_back(p);
                    }
                }
                formula = KFormulaParser::removeSpacing(formula);
                testReciept.function = [this, formula](auto args) -> QVariant {
                    return fromulaParser.parse(replace(formula, args));
                };
                result.changeRecieptList.push_back(testReciept);
            }
        }
    }
    return result;
}

JsonConfiguratedWorker::JsonConfiguratedWorker() {}

QString JsonConfiguratedWorker::replace(QString string, const QVariantMap &values) {
    for(auto it = values.begin(); it != values.end(); ++it) {
        const auto v = it.value().toDouble();
        if(qFuzzyCompare(v, 0)) {
            string.replace(it.key(), "0");
        } else {
            string.replace(it.key(), QString::fromStdString(std::to_string(v)));
        }
    }
    return string;
}

bool JsonConfiguratedWorker::beforeCompleate(KDynamicObject *dynamicObject, const QByteArray &data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if(!doc.isNull()) {
        auto map = doc.toVariant().toMap();
        auto props = map["members"].toList();
        //dynamicObject->specifyClassName(map["class"].toByteArray());
        QStringList propList;
        for(auto p : props) {
            auto strings = p.toString().split(' ');
            bool readonly = false;
            QString type;
            QString name;
            QVariant value;
            if(strings.size() > 0) {
                if(strings[0] == "readonly") {
                    readonly = true;
                    if(strings.size() > 2) {
                        type = strings[1];
                        name = strings[2];
                        if(strings.size() > 3) {
                            value = strings[3];
                        }
                    }
                } else if(strings.size() > 1) {
                    type = strings[0];
                    name = strings[1];
                    if(strings.size() > 2) {
                        value = strings[2];
                    }
                }
            }
            if(!name.toUtf8().isEmpty()) {
                dynamicObject->addProperty(name.toUtf8(), type.toUtf8(), !readonly, value);
                propList.push_back(name.toUtf8());
            }
            if(map["interval"].isValid()) {
                m_updateTimer = new QTimer(dynamicObject);
                m_updateTimer->start(map["interval"].toDouble());
            }
        }
        m_program = compile(map, propList);
        return true;
    }
    return false;
}

void JsonConfiguratedWorker::afterCompleate(KDynamicObject *dynamicObject) {
    m_listener = new KObjectListener(dynamicObject);
    m_listener->listen(dynamicObject);
    m_object = dynamicObject;
    QObject::connect(m_listener, &KObjectListener::propertyEvent, dynamicObject, [this](auto objectName, auto property, auto value) {
        propertyChanged(objectName, property, value);
    });
    elapsedTimer.start();
    elapsedTimer2.start();
    if(m_updateTimer) {
        QObject::connect(m_updateTimer, &QTimer::timeout, dynamicObject, [this](){ update(); });
    }
}
