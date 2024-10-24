#pragma once
#include "ShoppingCart.h"

class CSVShoppingCart : public ShoppingCart
{
public:
	CSVShoppingCart();
	void saveToFile() override;
	void displayCart() override;
};

