#include "client2.h"

#include <QJsonDocument>
#include <QTimer>
#include <src/network/kpackage.h>

Client2::Client2(QObject *parent) : QObject(parent)
{
    local.bind(2361);

    QTimer::singleShot(4000, this, [this](){
        local.write(KPackage("initial", "client2").toJson());
    });

    connect(&local, &KLocalSyncronizer::frameReady, this, [this](QByteArray array) {
        auto package = KPackage::fromJson(array);
        if(package.type() == "text") {
            setText(package.data().toString());
        } else if(package.type() == "initial") {
            setInitialInfo(package.data().toString());
        }
    });

    connect(this, &Client2::textChanged, this, [this](){
        local.write(KPackage("text", text()).toJson());
    });
}
