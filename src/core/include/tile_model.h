#pragma once
#include <memory>
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

struct TileData
{
    State::State state = State::State::unclicked;
    size_t       adjacentBombs = 0;
};

class TileModel : public QAbstractListModel
{
public:
    TileModel(Controller* controller);
    ~TileModel();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void setState(const QModelIndex& index, State::State state);

    void updateAdjacentBombs();

    enum Roles
    {
        state = Qt::UserRole
    };

private:
    struct Pimpl;
    std::unique_ptr<Pimpl> m_p;
};

} // namespace core
