#include "Repository.h"
#include <cstring>
#include <sstream>

/// <summary>
/// Adds an object to the repository
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
int RepositoryTrenchCoats::add_object(TrenchCoat t)
{
	auto it = std::find(this->Repository.cbegin(), this->Repository.cend(), t);
	if (it != Repository.end())
		throw std::exception("Cannot add item that already exists!");

	Repository.push_back(t);
	return 0;
}

/// <summary>
/// Removes an object from the repository by given price and colour
/// </summary>
/// <param name="price"></param>
/// <param name="colour"></param>
/// <returns></returns>
int RepositoryTrenchCoats::remove_object(float price, const std::string& colour)
{
	auto it = std::find_if(this->Repository.begin(), this->Repository.end(), [&](TrenchCoat& coat) {
		return coat.getPrice() == price && coat.getColour() == colour; });

	if (it != this->Repository.end()) {
		this->Repository.erase(it);
		return 0;
	}

	throw std::exception("Cannot delete item that doesn't exist!");
}

/// <summary>
/// Updates an object identified by price and colour with another object t
/// </summary>
/// <param name="price"></param>
/// <param name="colour"></param>
/// <param name="t"></param>
/// <returns></returns>
int RepositoryTrenchCoats::update_object(float price, const std::string& colour, TrenchCoat t)
{
	auto it = std::find_if(Repository.begin(), Repository.end(), [&](TrenchCoat& coat) {
		return coat.getColour() == colour && coat.getPrice() == price;
		});

	if (it != Repository.end()) {
		*it = t; // Update the found object
		return 0; // Object updated successfully
	}

	throw std::exception("Cannot update item that doesn't exist!");
}

/// <summary>
/// Returns the vector of trench coats
/// </summary>
/// <returns></returns>
std::vector<TrenchCoat> RepositoryTrenchCoats::all_objects()
{
	return this->Repository;
}

/// <summary>
/// Returns the size of the vector of the repository
/// </summary>
/// <returns></returns>
int RepositoryTrenchCoats::get_size()
{
	return this->Repository.size();
}

/// <summary>
/// Operator []
/// </summary>
/// <param name="pos"></param>
/// <returns></returns>
TrenchCoat& RepositoryTrenchCoats::operator[](int pos)
{
	return this->Repository[pos];
}

/// <summary>
/// Changes the repository to the one given by the undo/redo stacks
/// </summary>
/// <param name="data"></param>
void RepositoryTrenchCoats::substitute_repository(std::vector<TrenchCoat> data)
{
	this->Repository = std::move(data);
}
