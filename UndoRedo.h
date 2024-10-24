#pragma once
#include <vector>
#include "TrenchCoat.h"

class OperationStack
{
protected:
	int position = -1;
	std::vector<std::vector<TrenchCoat>> stack;

public:
	virtual std::vector<TrenchCoat> execute() = 0;
	void record_activity(std::vector<TrenchCoat> instance);
};


class UndoStack : public OperationStack
{
public:
	std::vector<TrenchCoat> execute() override;
	void increasePos();
};


class RedoStack : public OperationStack
{
public:
	std::vector<TrenchCoat> execute() override;
	void decreasePos();
};