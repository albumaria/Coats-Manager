#include "HTMLShoppingCart.h"
#include <fstream>
#include <Windows.h>

/// <summary>
/// HTML Shopping Cart constructor
/// </summary>
HTMLShoppingCart::HTMLShoppingCart()
{
	std::ofstream file("ShoppingCart.html");

	file << "";

	file.close();
}

/// <summary>
/// Saves to file
/// </summary>
void HTMLShoppingCart::saveToFile()
{
	std::ofstream file("ShoppingCart.html");

	file << "<!DOCTYPE html>\n";
	file << "<html>\n";
	file << "<head>\n";
	file << "	<title>Shopping Cart</title>\n";
	file << "</head>\n";
	file << "<body>\n";
	file << "<table border=\"1\">\n";
	file << "	<tr>\n";
	file << "		<td>Size</td>\n";
	file << "		<td>Colour</td>\n";
	file << "		<td>Price</td>\n";
	file << "		<td>Quantity</td>\n";
	file << "		<td>Link</td>\n";
	file << "	</tr>\n";

	for (auto trench : this->returnCart())
	{
		file << "	<tr>\n";
		file << "		<td>" << trench.getSize() << "</td>\n";
		file << "       <td>" << trench.getColour() << "</td>\n";
		file << "       <td>" << trench.getPrice() << "</td>\n";
		file << "       <td>" << trench.getQuantity() << "</td>\n";
		file << "       <td><a href=\"" << trench.getPhoto() << "\">Website</a></td>\n";
		file << "	</tr>\n";
	}

	file << "</table>\n";
	file << "</body>\n";
	file << "</html>\n";

	file.close();
}

/// <summary>
/// Displays the cart
/// </summary>
void HTMLShoppingCart::displayCart()
{
	std::string aux = "D:\\Facultate\\Anul1\\Sem2\\Oop\\Lab\\\Lab9\\\Lab9\\ShoppingCart.html";
	ShellExecuteA(NULL, NULL, "chrome.exe", aux.c_str(), NULL, SW_SHOWMAXIMIZED);
}
