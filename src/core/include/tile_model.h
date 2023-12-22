#pragma once
#include <vector>

#include <QAbstractListModel>
#include <QQmlEngine>

namespace State
{
Q_NAMESPACE
QML_ELEMENT

enum class State
{
    unclicked = 0,
    success,
    failure,
    potential
};
Q_ENUM_NS(State)

} // namespace State

namespace core
{

class Controller;

class TileModel : public QAbstractListModel
{
public:
    TileModel(Controller* controller);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setState(const QModelIndex& index, State::State state);

    enum Roles
    {
        state = Qt::UserRole
    };

private:
    std::vector<State::State> m_data;
    Controller*               m_controller = nullptr;
};

} // namespace core
