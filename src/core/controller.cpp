#include <random>

#include "include/controller.h"
#include "include/tile_model.h"

namespace core
{

Position::Position(int row, int column)
    : row(row)
    , column(column)
{
}

bool operator==(const Position& left, const Position& right)
{
    return left.row == right.row && left.column == right.column;
}

struct Controller::Pimpl
{
    Pimpl(Controller* parent);

    void disperseBombs(size_t numberOfBombs);

    bool isBomb(const Position& pos);

    Controller*           m_controller = nullptr;
    std::vector<Position> m_bombs;
    std::unique_ptr<TileModel> m_tileModel;
};

Controller::Controller()
    : m_p(std::make_unique<Pimpl>(this))
{
    m_p->disperseBombs(40);
    m_p->m_tileModel->updateAdjacentBombs();
}

Controller::~Controller() = default;

int Controller::rows() const
{
    return 20;
}

int Controller::columns() const
{
    return 20;
}

int Controller::getRow(int tileNumber) const
{
    return std::floor(tileNumber / columns());
}

int Controller::getColumn(int tileNumber) const
{
    return tileNumber % columns();
}

int Controller::getTileNumber(int row, int column) const
{
    return row * columns() + column;
}

void Controller::loopOverNeighbours(const Position& pos, std::function<void(const Position&)> f)
{
    for (size_t row = std::max(0, pos.row - 1);
         row != std::min(m_p->m_controller->rows(), pos.row + 2);
         ++row)
    {
        for (size_t col = std::max(0, pos.column - 1);
             col != std::min(m_p->m_controller->columns(), pos.column + 2);
             ++col)
        {
            const Position neighbour(row, col);
            if (pos == neighbour)
                continue;

            f(neighbour);
        }
    }
}

QAbstractListModel* Controller::tileModel() const
{
    return m_p->m_tileModel.get();
}

std::vector<Position> Controller::bombs() const
{
    return m_p->m_bombs;
}

void Controller::onTileClicked(int tileNumber)
{
    TileModel& tileModel = *m_p->m_tileModel;

    const Position    pos(getRow(tileNumber), getColumn(tileNumber));
    const QModelIndex index(tileModel.index(tileNumber, 0));

    std::function<void(const Position&)> revealNeighboursEmptyTile =
        [this, &tileModel, &revealNeighboursEmptyTile](const Position& pos)
    {
        const QModelIndex index(tileModel.index(getTileNumber(pos.row, pos.column), 0));

        if (tileModel.getState(index) != State::State::unclicked)
            return;

        tileModel.setState(index, State::State::success);

        if (tileModel.data(index) != 0)
            return;

        loopOverNeighbours(pos, revealNeighboursEmptyTile);
    };

    if (m_p->isBomb(pos))
    {
        tileModel.setState(index, State::State::failure);
        return;
    }

    revealNeighboursEmptyTile(pos);
}

Controller::Pimpl::Pimpl(Controller* parent)
    : m_controller(parent)
    , m_tileModel(std::make_unique<TileModel>(parent))
{
}

void Controller::Pimpl::disperseBombs(size_t numberOfBombs)
{
    std::random_device              device;
    std::mt19937                    engine(device());
    std::uniform_int_distribution<> distRows(0, m_controller->rows() - 1);
    std::uniform_int_distribution<> distColumns(0, m_controller->columns() - 1);

    for (size_t bomb = 0; bomb != numberOfBombs; ++bomb)
        m_bombs.push_back(Position(distRows(device), distColumns(device)));
}

bool Controller::Pimpl::isBomb(const Position& pos)
{
    return std::find(m_bombs.cbegin(), m_bombs.cend(), pos) != m_bombs.cend();
}
}
