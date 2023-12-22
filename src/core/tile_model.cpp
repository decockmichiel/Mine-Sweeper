#include "include/controller.h"
#include "include/tile_model.h"

namespace core
{

TileModel::TileModel(Controller* controller)
    : m_controller(controller)
{
    m_data = std::vector<State::State>(controller->rows() * controller->columns(),
                                       State::State::unclicked);
}

int TileModel::rowCount(const QModelIndex& parent) const
{
    return static_cast<int>(m_data.size());
}

QVariant TileModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
    case state:
        return static_cast<int>(m_data[index.row()]);
    }

    return {};
}

QHash<int, QByteArray> TileModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(state, "state");
    return roles;
}

void TileModel::setState(const QModelIndex& index, State::State state)
{
    auto& curState = m_data[index.row()];
    if (curState != state)
    {
        curState = state;
        emit dataChanged(index, index);
    }
}

} // namespace core
