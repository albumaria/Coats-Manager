#include "Service.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <locale>
#include <iterator>
#include <fstream>
#include <iostream>

using namespace std;



Service::Service()
{
    this->startUpRepository();
    this->undoStack.record_activity(this->returnRepository().all_objects());
    this->redoStack.record_activity(this->returnRepository().all_objects());
}

/// <summary>
/// Returns the repository
/// </summary>
/// <returns></returns>
RepositoryTrenchCoats& Service::returnRepository()
{
    return this->repository;
}


/// <summary>
/// Adds an object to the repository
/// </summary>
/// <param name="t"></param>
/// <returns></returns>
int Service::add_to_repository(TrenchCoat t)
{
    try {
        this->repository.add_object(t);
        this->undoStack.record_activity(this->returnRepository().all_objects());
        this->redoStack.record_activity(this->returnRepository().all_objects());
        this->writeToFile();
    }
    catch (exception& e) {
        return 1;
    }

    return 0;
}

/// <summary>
/// Removes an object from the repository
/// </summary>
/// <param name="price"></param>
/// <param name="colour"></param>
/// <returns></returns>
int Service::remove_from_repository(float price, const std::string& colour)
{
    try {
        this->repository.remove_object(price, colour);
        this->undoStack.record_activity(this->returnRepository().all_objects());
        this->redoStack.record_activity(this->returnRepository().all_objects());
        this->writeToFile();
    }
    catch (exception& e) {
        return 1;
    }

    return 0;
}


/// <summary>
/// Updates an object from the repository
/// </summary>
/// <param name="price"></param>
/// <param name="colour"></param>
/// <param name="t"></param>
/// <returns></returns>
int Service::update_from_repository(float price, const std::string& colour, TrenchCoat t)
{
    try {
        this->repository.update_object(price, colour, t);
        this->undoStack.record_activity(this->returnRepository().all_objects());
        this->redoStack.record_activity(this->returnRepository().all_objects());
        this->writeToFile();
    }
    catch (exception& e) {
        return 1;
    }

    return 0;
}

/// <summary>
/// Filters the repository by size
/// </summary>
/// <param name="size"></param>
/// <returns></returns>
vector<TrenchCoat> Service::filterBySize(std::string& size)
{
    vector<TrenchCoat> filteredCoats;

    if (size.size() == 0)
        return this->repository.all_objects();

    // Get the vector of all objects
    auto allObjects = this->repository.all_objects();

    // Iterate through all objects and add matching ones to filteredCoats
    for (auto& coat : allObjects) {
        if (coat.getSize() == size) {
            filteredCoats.push_back(coat);
        }
    }

    return filteredCoats;
}

/// <summary>
/// Checks if the repository is empty
/// </summary>
/// <param name="repository"></param>
/// <returns></returns>
int Service::check_if_empty(RepositoryTrenchCoats repository)
{
    if (repository.get_size() == 0)
        return 1;

    return 0;
}

/// <summary>
/// Returns the size of the repository
/// </summary>
/// <param name="repository"></param>
/// <returns></returns>
int Service::returnSize(RepositoryTrenchCoats repository)
{
    return repository.get_size();
}

/// <summary>
/// Starts up objects in repository
/// </summary>
void Service::startUpRepository()
{
    ifstream f("TrenchCoats.txt");
    if (!f.is_open())
        return;

    TrenchCoat t{};
    while (f >> t)
    {
        this->repository.add_object(t);
    }

    f.close();
}

/// <summary>
/// Writes the data to a file
/// </summary>
void Service::writeToFile()
{
    ofstream f("TrenchCoats.txt", ios::out);
    if (!f.is_open())
        return;

    for (auto s : this->repository.all_objects())
    {
        f << s;
    }

    f.close();
}


void Service::undo()
{
    std::vector<TrenchCoat> undo_data = this->undoStack.execute();
    this->repository.substitute_repository(undo_data);
    this->redoStack.decreasePos();
    this->writeToFile();
}


void Service::redo()
{
    std::vector<TrenchCoat> redo_data = this->redoStack.execute();
    this->repository.substitute_repository(redo_data);
    this->undoStack.increasePos();
    this->writeToFile();
}
