#include "kpropertyview.h"

#include <QQmlContext>


KPropertyView::KPropertyView(QQuickItem *parent) : QQuickItem(parent) {
    connect(this, &KPropertyView::modelObjectChanged, this, [this](){
        for(auto o : delegateMap)
            o->deleteLater();

        delegateMap.clear();

        if(!modelObject())
            return;

        for(auto i = 0, count = modelObject()->metaObject()->propertyCount(); i < count; ++i) {
            QQmlContext *deledateContext = new QQmlContext(qmlContext(this), this);

            if(auto obj = qobject_cast<QQuickItem*>(delegate()->create(deledateContext))) {
                auto property = modelObject()->metaObject()->property(i);

                obj->setParentItem(this);
                deledateContext->setContextProperty("modelData", property.name());
                deledateContext->setContextProperty("writableProperty", property.isWritable());

                delegateMap[property.name()] = obj;
                obj->setY(i * 20);
            }

        };
    });
}

QObject *KPropertyView::record(QString propertyName) {
    return delegateMap[propertyName];
}

