#pragma once
#include "TrenchCoat.h"
#include <vector>
#include <string>
#include <fstream>

class ShoppingCart
{
private:
	std::vector<TrenchCoat> coats;
	int total;

public:
	int add_to_cart(TrenchCoat t);

	int returnTotal();

	std::vector<TrenchCoat> returnCart();

	virtual void saveToFile() = 0;

	virtual void displayCart() = 0;
};

