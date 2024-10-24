#pragma once
#include <string>

class TrenchCoat
{
private:
	std::string size;
	std::string colour;
	float price;
	int quantity;
	std::string photo;

public:
	TrenchCoat();

	TrenchCoat(const std::string& size, const std::string& colour, float price, int quantity, const std::string& photo); // constructor

	TrenchCoat(const TrenchCoat& t); // copy

	TrenchCoat& operator=(const TrenchCoat& t);

	bool operator==(const TrenchCoat& t) const;

	std::string getSize() const { return this->size; }
	std::string getColour() const { return this->colour; }
	float getPrice() const { return this->price; }
	int getQuantity() const { return this->quantity; }
	std::string getPhoto() const { return this->photo; }

	friend std::istream& operator>>(std::istream& is, TrenchCoat& t);
	friend std::ostream& operator<<(std::ostream& os, const TrenchCoat& t);

};