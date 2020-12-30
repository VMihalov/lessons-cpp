#include <iostream>
#include <string>

int size = 0;

struct Case {
    struct Deadline {
        short day;
        short month;
        short year;
    };
    std::string title = "";
    std::string description = "";
    int priority = 0;
    Deadline deadline;
    std::string created_at = "";
    std::string updated_at = "";
};

short isValidDate( short day, short month, int year )
{
	if (year < 2021 || year >= 2100)
        return 1;

    if (month < 1 || month > 12)
        return 1;

    if (day < 1 || day > 31)
        return 1;
	
	return 0;
}

Case inputForm() {
    Case res;
    unsigned short day, month, year;
    short error;

    std::cout << "Title: ";
    std::cin >> res.title;

    std::cout << "Description: ";
    std::cin.ignore();
    std::getline(std::cin, res.description);

    std::cout << "Priority: ";
    std::cin >> res.priority;

    std::cout << "Deadline:\n";
    while(true) {
        std::cout << "\tDay: ";
        std::cin >> res.deadline.day;
        std::cout << "\tMonth: ";
        std::cin >> res.deadline.month;
        std::cout << "\tYear: ";
        std::cin >> res.deadline.year;

        error = isValidDate(res.deadline.day, res.deadline.month, res.deadline.year);

        if (error)
            std::cout << "Try again!\n";
        else
            break;
    }

    res.created_at = "";
    res.updated_at = "";

    return res;
}

int create(Case* arr)
{
    Case req = inputForm();

    arr[::size - 1] = req;

    return 1;
}

int updateCase(Case* arr) {
    int id = 0;
    Case req;

    std::cout << "Update by id: ";
    std::cin >> id;

    req = inputForm();

    arr[id] = req;

    return 1;
}

int deleteCase(Case* arr) {
    int id = 0;
    std::cout << "Delete by id: ";
    std::cin >> id;

    if (id < 0 || id >= ::size) {
        return 0;
    }

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

template <typename T>
int resize(T*& arr, int expand)
{
    ::size += expand;
    T* tmp = new T[::size];

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
            << "\t|\t"
            << arr[i].priority
            << "\t|\t"
            << std::to_string(arr[i].deadline.day) + '.' + std::to_string(arr[i].deadline.month) + '.' + std::to_string(arr[i].deadline.year)
            << "\t|\n";
    }
    std::cout << std::endl;
}

int main()
{
    Case* todo = new Case[::size];
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
                int remove = deleteCase(todo);

                if (!remove) {
                    std::cout << "\nId is invalid\n";
                } else {
                    resize(todo, -1);
                }
                
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
