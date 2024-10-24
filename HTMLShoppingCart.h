#pragma once
#include "ShoppingCart.h"

class HTMLShoppingCart : public ShoppingCart
{
public:
	HTMLShoppingCart();
	void saveToFile() override;
	void displayCart() override;
};

