#include "Validator.h"
#include "TrenchCoat.h"
#include <algorithm>

int Validator::validateTrench(TrenchCoat t)
{
	if (t.getPrice() <= -1)
		throw ValidationException("Invalid price!");

	if (t.getQuantity() <= -1)
		throw ValidationException("Invalid quantity!");

	if(t.getColour().length() == 0)
		throw ValidationException("Input a colour!");

	if (t.getPhoto().length() == 0)
		throw ValidationException("Input a link!");

	if (t.getSize().length() == 0)
		throw ValidationException("Input a size!");

	if (t.getSize() == "XS")
		return 0;

	if (t.getSize() == "S")
		return 0;

	if (t.getSize() == "M")
		return 0;

	if (t.getSize() == "L")
		return 0;

	if (t.getSize() == "XL")
		return 0;

	if (t.getSize() == "XXL")
		return 0;

	throw ValidationException("Invalid size!");
}


int Validator::validateSize(std::string size)
{
	if (size.size() == 0)
		return 0;

	if (size == "XS")
		return 0;

	if (size == "S")
		return 0;

	if (size == "M")
		return 0;

	if (size == "L")
		return 0;

	if (size == "XL")
		return 0;

	if (size == "XXL")
		return 0;

	throw ValidationException("Invalid size!");
}


int Validator::validateStringData(std::string price, std::string quantity)
{
	if (price.length() == 0)
		throw ValidationException("Input a price!");

	if (quantity.length() == 0)
		throw ValidationException("Input a quantity");

	if (!std::all_of(price.begin(), price.end(), ::isdigit))
		throw ValidationException("Invalid price!");

	if (!std::all_of(quantity.begin(), quantity.end(), ::isdigit))
		throw ValidationException("Invalid quantity!");

	return 0;
}
