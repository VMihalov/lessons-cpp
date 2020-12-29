#include <iostream>
#include <string>

int size = 7;

struct Case {
    std::string title = "";
    std::string description = "";
    std::string deadline = "";
    int priority = 0;
    std::string created_at = "";
    std::string updated_at = "";
};

int create(Case* arr)
{
    Case req;

    std::cout << "Title: ";
    std::cin >> req.title;

    std::cout << "Description: ";
    std::cin.ignore();
    std::getline(std::cin, req.description);

    std::cout << "Priority: ";
    std::cin >> req.priority;

    std::cout << "Deadline: ";
    std::cin >> req.deadline;

    req.created_at = "";
    req.updated_at = "";

    arr[::size - 1] = req;

    return 1;
}

int updateCase(Case* arr) {
    int id = 0;
    Case req;

    std::cout << "Update by id: ";
    std::cin >> id;

    std::cout << "Title: ";
    std::cin >> req.title;

    std::cout << "Description: ";
    std::cin >> req.description;

    std::cout << "Priority: ";
    std::cin >> req.priority;

    std::cout << "Deadline: ";
    std::cin >> req.deadline;

    req.updated_at = "";

    arr[id] = req;

    return 1;
}

int deleteCase(Case* arr) {
    int id = 0;
    std::cout << "Delete by id: ";
    std::cin >> id;

    for (int i = id; i < ::size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }

    return 1;
}

int searchCase(Case* arr) {
    int type;
    std::string value, by;
    std::cout << "Search by: 1 - name; 2 - priority; 3 - description; 4 - deadline;\n> ";
    std::cin >> type;

    std::cout << "Insert: ";
    std::cin.ignore();
    std::getline(std::cin, value);

    for (int i = 0; i < ::size; i++)
    {
        if (arr[i].title == value || arr[i].description == value) {
            std::cout << std::endl << "| "
                << i
                << " |\t"
                << arr[i].title
                << "\t|\t"
                << arr[i].description
                << "\t|\n" << std::endl;
        }
    }

    return 1;
}

int resize(Case*& arr, int expand)
{
    ::size += expand;
    Case* tmp = new Case[::size];

    int length = expand > 0 ? ::size - expand : (::size + expand) + 1;

    for (int i = 0; i < length; i++) {
        tmp[i] = arr[i];
    }

    delete[] arr;
    arr = tmp;

    return 1;
}

void view(Case* arr) {
    for (int i = 0; i < ::size; i++)
    {
        std::cout << "| "
            << i
            << " |\t"
            << arr[i].title
            << "\t|\t"
            << arr[i].description
            << "\t|\n";
    }
    std::cout << std::endl;
}

int main()
{
    Case* todo = new Case[::size];
    for (int i = 0; i < ::size; i++)
    {
        todo[i].title = "Hello" + std::to_string(i);
        todo[i].description = i;
    }
    int action = 0;
    
    while (true) {
        //view(todo);

        std::cout << "Set action: 0 - view; 1 - Create; 2 - Update; 3 - Delete; 4 - Search; 5 - Sort by; -1 - Exit\n> ";
        std::cin >> action;

        if (action == -1)
            break;

        switch (action)
        {
            case 0:
                view(todo);
                break;
            case 1: {
                resize(todo, 1);
                create(todo);
                break;
            }
            case 2:
                updateCase(todo);
                break;
            case 3: {
                deleteCase(todo);
                resize(todo, -1);
                break;
            }
            case 4:
                searchCase(todo);
                break;
            default:
                std::cout << "Try again!\n";
                break;
        }

        
    }

    delete[] todo;

    return 0;
}
