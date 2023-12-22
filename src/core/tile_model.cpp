#include "include/controller.h"
#include "include/tile_model.h"

namespace core
{
struct TileModel::Pimpl
{
    Pimpl(TileModel* parent, Controller* controller)
        : m_model(parent)
        , m_controller(controller)
        , m_data(std::vector<TileData>(controller->rows() * controller->columns()))
    {
    }

    std::vector<TileData> m_data;
    TileModel*            m_model = nullptr;
    Controller*           m_controller = nullptr;
};

TileModel::TileModel(Controller* controller)
    : m_p(std::make_unique<Pimpl>(this, controller))
{
}

TileModel::~TileModel() = default;

int TileModel::rowCount(const QModelIndex& parent) const
{
    return static_cast<int>(m_p->m_data.size());
}

QVariant TileModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return static_cast<int>(m_p->m_data[index.row()].adjacentBombs);
    case state:
        return static_cast<int>(m_p->m_data[index.row()].state);
    }

    return {};
}

QHash<int, QByteArray> TileModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(state, "state");
    return roles;
}

State::State TileModel::getState(const QModelIndex& index) const
{
    return static_cast<State::State>(data(index, Roles::state).toInt());
}

void TileModel::setState(const QModelIndex& index, State::State state)
{
    auto& curState = m_p->m_data[index.row()].state;
    if (curState != state)
    {
        curState = state;
        emit dataChanged(index, index);
    }
}

void TileModel::updateAdjacentBombs()
{
    for (const auto& bomb : m_p->m_controller->bombs())
    {
        m_p->m_controller->loopOverNeighbours(
            bomb,
            [this](const Position& neighbour)
            {
                m_p->m_data[m_p->m_controller->getTileNumber(neighbour.row, neighbour.column)]
                    .adjacentBombs++;
            });
    }
}

} // namespace core
