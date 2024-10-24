#include "UndoRedo.h"
#include <qexception.h>

void OperationStack::record_activity(std::vector<TrenchCoat> instance)
{
	if (position < stack.size() - 1) {
		stack.erase(stack.begin() + position + 1, stack.end());
	}
	stack.push_back(instance);
	position = stack.size() - 1;
}


std::vector<TrenchCoat> UndoStack::execute()
{
	if (this->position <= 0)
		throw std::exception("No more Undo!");

	this->position--;
	std::vector<TrenchCoat> undo_data = this->stack[this->position];

	return undo_data;
}

void UndoStack::increasePos()
{
	this->position++;
}


std::vector<TrenchCoat> RedoStack::execute()
{
	if (this->position >= this->stack.size() - 1)
		throw std::exception("No more Redo!");

	this->position++;
	std::vector<TrenchCoat> redo_data = this->stack[this->position];

	return redo_data;
}

void RedoStack::decreasePos()
{
	this->position--;
}
