#include "CartModelView.h"

CartModelView::CartModelView(CSVShoppingCart& cart) : cart{cart}
{
}


int CartModelView::rowCount(const QModelIndex& parent) const
{
	return this->cart.returnCart().size();
}


int CartModelView::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant CartModelView::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int row = index.row();
    const int col = index.column();

    TrenchCoat t = this->cart.returnCart()[row];

    if (role == Qt::DisplayRole) {
        switch (col) {
        case 0:
            return QString::fromStdString(t.getSize());
        case 1:
            return QString::fromStdString(t.getColour());
        case 2:
            return QString::number(t.getPrice());
        case 3:
            return QString::number(t.getQuantity());
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QVariant CartModelView::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Size");
            case 1:
                return QString("Colour");
            case 2:
                return QString("Price");
            case 3:
                return QString("Quantity");
            default:
                return QVariant();
            }
        }
    }
    return QVariant();
}

void CartModelView::update()
{
    beginResetModel();
    endResetModel();
}
