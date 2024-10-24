#pragma once
#include <vector>
#include "TrenchCoat.h"
#include <string>
#include <exception>

class RepositoryTrenchCoats
{
private:
	std::vector<TrenchCoat> Repository;

public:

	int add_object(TrenchCoat t);

	int remove_object(float price, const std::string& colour);

	int update_object(float price, const std::string& colour, TrenchCoat t);

	std::vector<TrenchCoat> all_objects();

	int get_size();

	TrenchCoat& operator[](int pos);

	void substitute_repository(std::vector<TrenchCoat> data);
};