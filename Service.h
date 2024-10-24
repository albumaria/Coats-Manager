#pragma once
#include "UndoRedo.h"
#include "Repository.h"

class Service
{
private:
	UndoStack undoStack;
	RedoStack redoStack;

public:
	Service();

	RepositoryTrenchCoats repository;

	RepositoryTrenchCoats& returnRepository();

	int add_to_repository(TrenchCoat t);

	int remove_from_repository(float price, const std::string& colour);

	int update_from_repository(float price, const std::string& colour, TrenchCoat t);

	std::vector<TrenchCoat> filterBySize(std::string& size);

	int check_if_empty(RepositoryTrenchCoats repository);

	int returnSize(RepositoryTrenchCoats repository);

	void startUpRepository();

	void writeToFile();

	void undo();

	void redo();
};
