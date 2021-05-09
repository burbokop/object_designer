#ifndef KPROPERTYVIEW_H
#define KPROPERTYVIEW_H

#include <QQuickPaintedItem>
#include <klibcore/src/kmacro.h>

class KPropertyView : public QQuickItem {
    Q_OBJECT
    K_QML_TYPE(KPropertyView)
    K_AUTO_PROPERTY(QObject*, modelObject, modelObject, setModelObject, modelObjectChanged, nullptr)
    K_AUTO_PROPERTY(QQmlComponent*, delegate, delegate, setDelegate, delegateChanged, nullptr)

    QMap<QString, QObject*> delegateMap;
public:
    KPropertyView(QQuickItem *parent = nullptr);

signals:


public slots:
    QObject *record(QString propertyName);
};

#endif // KPROPERTYVIEW_H
