#include "CSVShoppingCart.h"
#include <Windows.h>

/// <summary>
/// CSVShoppingCart constructor
/// </summary>
CSVShoppingCart::CSVShoppingCart()
{
	std::ofstream file("ShoppingCart.csv");
	file << "";

	file.close();
}

/// <summary>
/// Saves to file
/// </summary>
void CSVShoppingCart::saveToFile()
{
	std::ofstream file("ShoppingCart.csv");
	for (auto coat : this->returnCart())
	{
		file << coat;
	}

	file.close();
}

/// <summary>
/// Displays the cart
/// </summary>
void CSVShoppingCart::displayCart()
{
	std::string aux = "ShoppingCart.csv";

	ShellExecuteA(NULL, NULL, "excel.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}
