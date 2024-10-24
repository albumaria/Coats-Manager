#include "ShoppingCart.h"

/// <summary>
/// Adds a trench coat to the shopping cart
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
int ShoppingCart::add_to_cart(TrenchCoat t)
{
	this->coats.push_back(t);
	this->total += t.getPrice();
	return 0;
}

/// <summary>
/// Returns the shopping cart's total
/// </summary>
/// <returns></returns>
int ShoppingCart::returnTotal()
{
	return this->total;
}

/// <summary>
/// Returns the cart
/// </summary>
/// <returns></returns>
std::vector<TrenchCoat> ShoppingCart::returnCart()
{
	return this->coats;
}

