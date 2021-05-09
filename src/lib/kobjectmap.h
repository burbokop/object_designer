#ifndef KOBJECTMAP_H
#define KOBJECTMAP_H

#include <klibcore/src/kmacro.h>

class KObjectMap : public QObject {
    Q_OBJECT
    K_QML_TYPE(KObjectMap)

    QMap<QObject*, QObject*> m_data;
public:
    explicit KObjectMap(QObject *parent = nullptr);
    QMap<QObject *, QObject *> data() const;

signals:


public slots:
    void insert(QObject *key, QObject *value);
    QObject *value(QObject *key);
};

#endif // KOBJECTMAP_H
