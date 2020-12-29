#include <iostream>
#include <string>
#include <ctime>

int size = 0;

struct Case {
    std::string name = "hello";
    std::string description = "";
    std::string deadline = "";
    int priority = 0;
    std::string created_at = "";
    std::string updated_at = "";
};

int create(Case* arr)
{
    Case req;

    time_t now = time(0);
    char* dt = ctime(&now);

    std::cout << "Title: ";
    std::cin >> req.name;

    std::cout << "Description: ";
    std::cin >> req.description;

    std::cout << "Priority: ";
    std::cin >> req.priority;

    std::cout << "Deadline: ";
    std::cin >> req.deadline;

    req.created_at = dt;
    req.updated_at = dt;

    std::cout << "current size:" << ::size << std::endl;
    arr[::size - 1] = req;

    return 1;
}

int resize(Case* arr, int expand) {
    ::size += expand;

    arr = new Case[::size];

    return 1;
}

int main()
{
    Case* todo = new Case[::size];

    create(todo);

    delete[] todo;

    return 0;
}