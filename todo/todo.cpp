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

int size = 0;
Case::Date currentDate;

void createController(Case* todo);
void updateController(Case* todo);
void deleteController(Case* todo);
void optionController();

short initializeTime(Case::Date time);

short validateDate(Case::Date form);
short validateForm(Case form);

void showTable(Case* arr, short mode = 0);
void viewSingleCase(Case row);

Case inputForm();

void errorMessage(std::string text) {
    std::cout << "\n" + text + "\n";
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

    delete[] tmp;

    return 1;
}

int main()
{
    Case* todo = new Case[::size];
    short action = 0;

    initializeTime(currentDate);

    while (true) {
        //view(todo);

        std::cout << "Menu: 0 - view; 1 - Create; 2 - Update; 3 - Delete; 4 - Search; 5 - Sort by; 6 - Settings; -1 - Exit\n> ";
        std::cin >> action;

        if (action == -1)
            break;

        switch (action)
        {
            case 0: {
                showTable(todo);

                break;
            }
            case 1:
                createController(todo);
                break;
            case 2:
                updateController(todo);
                break;
            case 3:
                break;
            case 4:
                deleteController(todo);
                break;
            case 5:
                break;
            case 6:
                optionController();
                break;
            default: 
                std::cout << "Try again!\n";
                break;
        }

        
    }

    delete[] todo;

    return 0;
}

void createController(Case* todos) {
    Case form = inputForm();

    short validate = validateForm(form);

    if (validate)
    {
        return errorMessage("Incorrect input data");
    }

    resize(todos, 1);
    
    todos[::size - 1] = form;
    
    return showTable(todos, 4);
}

void updateController(Case* todo) {
    int id = 0;
    Case req;

    std::cout << "Update by id: ";
    std::cin >> id;

    if (id < 0 || id >= ::size) {
        return errorMessage("invalid id!");
    }

    req = inputForm();

    todo[id] = req;

    return showTable(todo, 4);
}

void deleteController(Case* todo) {
    int id = 0;
    std::cout << "Delete by id: ";
    std::cin >> id;

    if (id < 0 || id >= ::size) {
        return errorMessage("Invalid id!");
    }

    for (int i = id; i < ::size - 1; i++)
    {
        todo[i] = todo[i + 1];
    }

    return showTable(todo, 4);
}

void optionController() {
    int settings = 0;

    std::cout << "1 - start time; 2 - default view mod\n> ";
    std::cin >> settings;

    switch (settings)
    {
    case 1:
        initializeTime(currentDate);
        break;
    default:
        return errorMessage("Undefined number");
        break;
    }
}

short initializeTime(Case::Date time) {
    short validate;

    std::cout << "Initialize datetime\n";

    do {
        std::cout << "\tHour: ";
        std::cin >> time.hour;

        std::cout << "\tMinutes: ";
        std::cin >> time.minutes;

        std::cout << "\tDay: ";
        std::cin >> time.day;

        std::cout << "\tMonth: ";
        std::cin >> time.month;

        std::cout << "\tYear: ";
        std::cin >> time.year;

        validate =  validateDate(time);

        if (validate)
            std::cout << "Incorrect date!\nTry again!\n";
    } while(validate);

    return 0;
}

short validateDate(Case::Date form)
{
    if (form.hour > 60 || form.hour < 0) {
        return 1;
    }

    if (form.minutes > 60 || form.minutes < 0) {
        return 1;
    }

	if (form.year < 2021 || form.year >= 2100)
        return 1;

    if (form.month < 1 || form.month > 12)
        return 1;

    if (form.day < 1 || form.day > 31)
        return 1;
	
	return 0;
}

short validateForm(Case form) {
    short validate = validateDate(form.deadline);

    if (validate) {
        return 1;
    }

    return 0;
}

Case inputForm() {
    Case res;
    unsigned short day, month, year;
    short error;

    std::cout << "Title: ";
    std::cin >> res.title;

    std::cout << "Description: ";
    std::cin >> res.description;

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

        error = validateDate(res.deadline);

        if (error)
            errorMessage("Try again!");
        else
            break;
    }

    res.created_at = "";
    res.updated_at = "";

    return res;
}

void showTable (Case* arr, short mode) {
    unsigned short timestep = mode;
    
    if (timestep == 0) {
        std::cout << "View on: 1 - today; 2 - this week; 3 - this month; 4 - all;\n> ";
        std::cin >> timestep;
    }

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


