#include <iostream>
#include <string>

struct Case {
    struct Date {
        short minutes;
        short hour;
        short day;
        short month;
        short year;
    };
    std::string title = "";
    std::string description = "";
    int priority = 0;
    Date deadline;
    std::string created_at = "";
    std::string updated_at = "";
};

int size = 4;
Case::Date currentDate;

short isValidDate(short minutes, short hour, short day, short month, int year)
{
	if (year < currentDate.year || year >= 2100)
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
        std::cout << "\tHour: ";
        std::cin >> res.deadline.hour;
        std::cout << "\tMinutes: ";
        std::cin >> res.deadline.minutes;
        std::cout << "\tDay: ";
        std::cin >> res.deadline.day;
        std::cout << "\tMonth: ";
        std::cin >> res.deadline.month;
        std::cout << "\tYear: ";
        std::cin >> res.deadline.year;

        error = isValidDate(res.deadline.minutes, res.deadline.hour, res.deadline.day, res.deadline.month, res.deadline.year);

        if (error)
            std::cout << "Try again!\n";
        else
            break;
    }

    res.created_at = "";
    res.updated_at = "";

    return res;
}

void viewSingleCase(Case row) {
    std::cout << " |\t"
            << row.title
            << "\t|\t"
            << row.description
            << "\t|\t"
            << row.priority
            << "\t|\t"
            << std::to_string(row.deadline.hour) + ':' + std::to_string(row.deadline.minutes) + ' ' + std::to_string(row.deadline.day) + '.' + std::to_string(row.deadline.month) + '.' + std::to_string(row.deadline.year)
            << "\t|\n";
}

void sortBy(Case* arr) {
    Case* sortArray = new Case[::size];
    Case tmp;
    sortArray = arr;

    for (int i = 0; i < ::size; i++)
    {
        for (int j = 0; j < ::size; j++)
        {
            if (sortArray[i].priority < sortArray[j].priority) {
                tmp = sortArray[i];
                sortArray[i] = sortArray[j];
                sortArray[j] = tmp;    
            }
        }
        
    }
    
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

    if (id < 0 || id >= ::size) {
        return 0;
    }

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

int view(Case* arr) {
    unsigned short timestep = 1;
    int width;
    std::cout << "View on: 1 - today; 2 - this week; 3 - this month; 4 - all;\n> ";
    std::cin >> timestep;

    for (int i = 0; i < ::size; i++)
    {
        if (timestep == 1)
        {
            if (arr[i].deadline.day == currentDate.day && arr[i].deadline.month == currentDate.month && arr[i].deadline.year == currentDate.year) {
                std::cout << "| " << i;
                viewSingleCase(arr[i]);
            }
        }

        // if (timestep == 2) {
        //     if (arr[i].deadline.day <= currentDate.day + 7) {
        //         std::cout << "| " << i;
        //         viewSingleCase(arr[i]);
        //     }
        // }

        if (timestep == 4)
        {
            std::cout << "| " << i;
            viewSingleCase(arr[i]);
        }
        
    }
    

    std::cout << std::endl;

    return 1;
}

int main()
{
    Case* todo = new Case[::size];
    short action = 0;

    std::cout << "Initialize datetime\n\tHour: ";
    std::cin >> currentDate.hour;

    std::cout << "\tMinutes: ";
    std::cin >> currentDate.minutes;

    std::cout << "\tDay: ";
    std::cin >> currentDate.day;

    std::cout << "\tMonth: ";
    std::cin >> currentDate.month;

    std::cout << "\tYear: ";
    std::cin >> currentDate.year;

    while (true) {
        //view(todo);

        std::cout << "Menu: 0 - view; 1 - Create; 2 - Update; 3 - Delete; 4 - Search; 5 - Sort by; -1 - Exit\n> ";
        std::cin >> action;

        if (action == -1)
            break;

        switch (action)
        {
            case 0: {
                view(todo);

                break;
            }
            case 1: {
                resize(todo, 1);
                create(todo);
                break;
            }
            case 2: {
                int update = updateCase(todo);

                if (!update) {
                    std::cout << "\nId is invalid\n";
                }
                
                break;
            }
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
            case 5:
                sortBy(todo);
                break;
            default: 
                std::cout << "Try again!\n";
                break;
        }

        
    }

    delete[] todo;

    return 0;
}
