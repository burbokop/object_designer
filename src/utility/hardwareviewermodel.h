#ifndef HARDWAREVIEWERMODEL_H
#define HARDWAREVIEWERMODEL_H

#include <QAbstractListModel>
#include <klibcore/src/kmacro.h>

class HardwareViewerModel : public QAbstractListModel
{
    Q_OBJECT
    K_QML_TYPE(HardwareViewerModel)

public:
    HardwareViewerModel();
    HardwareViewerModel(QStringList roles);

public slots:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant getValue(int row, QString role);
    int getRoleIndex(QString role);

    QHash<int, QByteArray> roleNames() const override;
    QStringList getRoleNames();
    void addRole(QString);
    void addRoles(QStringList);
    int size();

    //QML
    void push_back(const QVariantList &varList);
    void push_front(const QVariantList &varList);
    void insert(int pos, const QVariantList &varList);
    bool setLineData(const QVariantList &varList, int row = 0);

    //C++
    void push_back(const QMap<QString, QVariant> &varList);
    void push_front(const QMap<QString, QVariant> &varList);
    void insert(int pos, const QMap<QString, QVariant> &varList);
    bool setLineData(const QMap<QString, QVariant> &varlist, int row = 0);


    bool removeAt(int pos);
    bool removeOne(const QVariant &value, const QString &role);
    void removeAll(const QVariant &value, const QString &role);
    bool removeFrom(int pos);
    bool clear();

    /*
     * return true if contains element in specific role
     * if role = "" -> check contains in all roles
     */
    bool contains(QVariant element, QString role = "");

    /*
     * return count of the same elements
     */
    int count(QVariant element, QString role = "");
    /*
     * return -1 if on same element, else
     * return row which contains element
     */
    int indexOf(QVariant element, QString role = "");



private:
    QHash<int, QByteArray> m_roles;
    QStringList m_names;
    QVector<QMap<int, QVariant>> m_data;

private:
    QMap<int, QVariant> generateMap(const QVariantList &varList);
    QMap<int, QVariant> generateMap(const QMap<QString, QVariant> &map);
};

#endif // HARDWAREVIEWERMODEL_H
