#ifndef PROPERTYINTERSECTOR_H
#define PROPERTYINTERSECTOR_H

#include <QObject>

class PropertyIntersector : public QObject {
    Q_OBJECT
public:
    explicit PropertyIntersector(QObject *parent = nullptr);

public slots:
    void changeProperty(const QString &obj, const QString &prop, const QVariant &value);
    void appendMeta(const QByteArray &data);
    void changeMeta(const QByteArray &data);

signals:
    void propertyChanged(const QString &obj, const QString &prop, const QVariant &value);
    void metaAppended(const QByteArray &data);

};

#endif // PROPERTYINTERSECTOR_H
