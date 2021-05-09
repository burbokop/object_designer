#include "hardwareviewermodel.h"
#include <QList>

#include <QDebug>

HardwareViewerModel::HardwareViewerModel(){}

HardwareViewerModel::HardwareViewerModel(QStringList roles)
{
    m_names = roles;

    for (int i = 0; i < roles.length(); i++)
    {
        m_roles.insert(i + Qt::UserRole, roles[i].toUtf8());
    }
}

int HardwareViewerModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.size();
}

QVariant HardwareViewerModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_data.size())
        return QVariant();
    if(role < Qt::UserRole)
        return QVariant();

    return m_data[index.row()][role];
}

QVariant HardwareViewerModel::getValue(int row, QString role)
{
    if(row < 0 || row >= m_data.size())
        return QString("");

    QVariant a = m_data[row][getRoleIndex(role)];
    return a.isValid() ? a : "";
}

int HardwareViewerModel::getRoleIndex(QString role)
{
    return m_roles.key(role.toUtf8());
}

QHash<int, QByteArray> HardwareViewerModel::roleNames() const
{
    return m_roles;
}

QStringList HardwareViewerModel::getRoleNames()
{
    return m_names;
}

void HardwareViewerModel::addRole(QString role)
{
    if (!m_names.contains(role))
    {
        m_names.append(role);
        m_roles.insert(Qt::UserRole + m_roles.size(), role.toUtf8());
    }
}

void HardwareViewerModel::addRoles(QStringList rolesList)
{
    for (int i = 0; i < rolesList.length(); i++)
    {
        addRole(rolesList[i]);
    }
}

int HardwareViewerModel::size()
{
    return m_data.size();
}

void HardwareViewerModel::push_back(const QVariantList &varList)
{
    int pos = m_data.count();
    beginInsertRows(QModelIndex(), pos, pos);
    auto map = generateMap(varList);
    m_data.push_back(map);
    endInsertRows();
}

void HardwareViewerModel::push_front(const QVariantList &varList)
{
    int pos = 0;
    beginInsertRows(QModelIndex(), pos, pos);
    auto map = generateMap(varList);
    m_data.push_front(map);
    endInsertRows();
}

void HardwareViewerModel::insert(int pos, const QVariantList &varList)
{
    if (pos >= m_data.length())
    {
        push_back(varList);
    }
    else if (pos < 0)
    {
        push_front(varList);
    }
    else
    {
        beginInsertRows(QModelIndex(), pos, pos);
        m_data.insert(pos, generateMap(varList));
        endInsertRows();
    }
}

void HardwareViewerModel::push_back(const QMap<QString, QVariant> &varList)
{
    int pos = m_data.count();
    beginInsertRows(QModelIndex(), pos, pos);
    auto map = generateMap(varList);
    m_data.push_back(map);
    endInsertRows();
}

void HardwareViewerModel::push_front(const QMap<QString, QVariant> &varList)
{
    int pos = 0;
    beginInsertRows(QModelIndex(), pos, pos);
    auto map = generateMap(varList);
    m_data.push_front(map);
    endInsertRows();
}

void HardwareViewerModel::insert(int pos, const QMap<QString, QVariant> &varList)
{
    if (pos >= m_data.length())
    {
        push_back(varList);
    }
    else if (pos < 0)
    {
        push_front(varList);
    }
    else
    {
        beginInsertRows(QModelIndex(), pos, pos);
        m_data.insert(pos, generateMap(varList));
        endInsertRows();
    }
}

bool HardwareViewerModel::setLineData(const QMap<QString, QVariant> &varList, int row)
{
    if (m_data.length() - 1 < row)
    {
        push_back(varList);
        return true;
    }

    auto map = generateMap(varList);
    QMapIterator iter(map);

    while(iter.hasNext())
    {
        auto elem = iter.next();
        m_data[row][elem.key()] = elem.value();
    }
    return true;
}

bool HardwareViewerModel::removeAt(int pos)
{
    if (pos >= m_data.length() || pos < 0) return false;
    beginRemoveRows(QModelIndex(), pos, pos);

    m_data.remove(pos);

    endRemoveRows();
    return true;
}

bool HardwareViewerModel::removeOne(const QVariant &value, const QString &role)
{
    for (int i = m_data.size() - 1; i >= 0; i--)
    {
        if (getValue(i, role) == value)
        {
            return removeAt(i);
        }
    }
    return false;
}

void HardwareViewerModel::removeAll(const QVariant &value, const QString &role)
{
    for (int i = m_data.size() - 1; i >= 0; i--)
    {
        if (getValue(i, role) == value)
        {
            removeAt(i);
        }
    }
}

bool HardwareViewerModel::removeFrom(int pos)
{
    if (m_data.length() - 1 < pos)
    {
        return false;
    }

    for (int i = m_data.length() - 1; i >= pos; i--)
    {
        removeAt(i);
    }
    return true;
}

bool HardwareViewerModel::clear()
{
    beginResetModel();

    m_data.clear();

    endResetModel();
    return true;
}

bool HardwareViewerModel::contains(QVariant element, QString role)
{
    for (int i = 0; i < size(); i++)
    {
        if (role == "")
        {
            for (auto r : m_names)
            {
                if (element == getValue(i, r)) return true;
            }
        }
        else
        {
            if (element == getValue(i, role)) return true;
        }
    }
    return false;
}

int HardwareViewerModel::count(QVariant element, QString role)
{
    int count = 0;
    for (int i = 0; i < size(); i++)
    {
        if (role == "")
        {
            for (auto r : m_names)
            {
                if (getValue(i, r) == element) count++;
            }
        }
        else
        {
            if (getValue(i, role) == element) count++;
        }

    }
    return count;
}

int HardwareViewerModel::indexOf(QVariant element, QString role)
{
    for (int i = 0; i < size(); i++)
    {
        if (role == "")
        {
            for (auto r : m_names)
            {
                if (getValue(i, r) == element) return i;
            }
        }
        else
        {
            if (getValue(i, role) == element) return i;
        }

    }
    return -1;
}

QMap<int, QVariant> HardwareViewerModel::generateMap(const QVariantList &varList)
{
    QMap<int, QVariant> map;
    for (int i = 0; i < varList.length(); i++)
    {
        QVariantMap value = varList[i].toMap();
        int pos = 0;

        for (auto r : m_roles)
        {
            if(!value.isEmpty()) {
                if (r == value.keys().first())
                {
                    pos = m_roles.key(r);
                    break;
                }
            }
        }

        if (pos != 0 && !value.isEmpty())
        {            
            map.insert(pos, value.values().first());
        }

    }
    return map;
}

QMap<int, QVariant> HardwareViewerModel::generateMap(const QMap<QString, QVariant> &map)
{
    QMapIterator<QString, QVariant> iter(map);
    int pos = 0;

    QMap<int, QVariant> resultMap;

    while (iter.hasNext())
    {
        pos = 0;
        auto item = iter.next();

        for (auto r : m_roles)
        {
            if (r.toStdString() == item.key().toStdString())
            {
                pos = m_roles.key(r);
                break;
            }
        }

        if (pos != 0)
        {
            resultMap.insert(pos, item.value());
        }
    }
    return resultMap;
}


bool HardwareViewerModel::setLineData(const QVariantList &varList, int row)
{
    if (m_data.size() - 1 < row)
    {
        push_back(varList);
        return true;
    }

    auto map = generateMap(varList);
    QMapIterator iter(map);

    while(iter.hasNext())
    {
        auto elem = iter.next();
        m_data[row][elem.key()] = elem.value();
    }

    return true;
}
