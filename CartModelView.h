#pragma once
#include <qabstractitemmodel.h>
#include "ShoppingCart.h"
#include "CSVShoppingCart.h"
#include "HTMLShoppingCart.h"


class CartModelView : public QAbstractTableModel
{
private:
	CSVShoppingCart& cart;

public:
	CartModelView(CSVShoppingCart& cart);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void update();
};

