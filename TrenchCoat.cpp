#include "TrenchCoat.h"
#include <sstream>
#include <vector>

using namespace std;

/// <summary>
/// Default constructor for object of type TrenchCoat
/// </summary>
TrenchCoat::TrenchCoat()
{
	this->size = "";
	this->colour = "";
	this->price = 0;
	this->quantity = 0;
	this->photo = "";
}

/// <summary>
/// Constructor of object of type TrenchCoat, but assigns data given to the object
/// </summary>
/// <param name="size"></param>
/// <param name="colour"></param>
/// <param name="price"></param>
/// <param name="quantity"></param>
/// <param name="photo"></param>
TrenchCoat::TrenchCoat(const string& s, const string& c, float pr, int qt, const string& ph)
{
	this->size = s;
	this->colour = c;
	this->price = pr;
	this->quantity = qt;
	this->photo = ph;
}

/// <summary>
/// Copy function for object of type TrenchCoat
/// </summary>
/// <param name="t"></param>
TrenchCoat::TrenchCoat(const TrenchCoat& t)
{
	this->size = t.size;
	this->colour = t.colour;
	this->price = t.price;
	this->quantity = t.quantity;
	this->photo = t.photo;
}

/// <summary>
/// Function for '=' operator when assigning TrenchCoat objects
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
TrenchCoat& TrenchCoat::operator=(const TrenchCoat& t)
{
	this->size = t.size;
	this->colour = t.colour;
	this->price = t.price;
	this->quantity = t.quantity;
	this->photo = t.photo;
	return *this;
}

/// <summary>
/// Function for verifying equality between objects of type TrenchCoat
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
bool TrenchCoat::operator==(const TrenchCoat& t) const
{
	return this->size == t.size &&
		this->colour == t.colour &&
		this->price == t.price &&
		this->quantity == t.quantity &&
		this->photo == t.photo;
}

/// <summary>
/// Helps to delimit the data given in the file
/// </summary>
/// <param name="str"></param>
/// <param name="delimiter"></param>
/// <returns></returns>
vector<string> tokenize(string str, char delimiter)
{
	vector <string> result;
	stringstream ss(str);
	string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);

	return result;
}

/// <summary>
/// Operator for getting input from a file
/// </summary>
/// <param name="is"></param>
/// <param name="t"></param>
/// <returns></returns>
std::istream& operator>>(std::istream& is, TrenchCoat& t)
{
	string line;
	getline(is, line);

	vector<string> tokens = tokenize(line, ',');
	if (tokens.size() != 5)
		return is;

	t.size = tokens[0];
	t.colour = tokens[1];
	t.price = stof(tokens[2]);
	t.quantity = stoi(tokens[3]);
	t.photo = tokens[4];

	return is;
}

/// <summary>
/// Operator for writing to a file
/// </summary>
/// <param name="os"></param>
/// <param name="t"></param>
/// <returns></returns>
std::ostream& operator<<(std::ostream& os, const TrenchCoat& t)
{
	os << t.size << "," << t.colour << "," << t.price << "," << t.quantity << "," << t.photo << "\n";
	return os;
}
