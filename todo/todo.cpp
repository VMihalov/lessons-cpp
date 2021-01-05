#include <iostream>
#include <string>
#include <windows.h>

struct Case {
    struct Date {
        short minutes = 0;
        short hour = 0;
        short day = 1;
        short month = 1;
        int year = 2021;
    };
    std::string title = "";
    std::string description = "";
    int priority = 0;
    Date deadline = {0, 0, 1, 1, 2021};
    std::string created_at = "";
    std::string updated_at = "";
};

struct Filter
{
    Case* arr;
    int size;
};

int size = 0;
Case::Date currentDate;

//Controllers
void createController(Case*& todo);
void updateController(Case* todo);
void deleteController(Case*& todo);
void optionController();

//Initialize
short initializeTime(Case::Date& time);

// Validate
short validateDate(Case::Date form);
short validateForm(Case form);

// Show table
void render(Case*& todo, short choice = 0);

// Working with table
Case inputForm(Case temp = {});
Case* resize(Case* arr, int count = ::size, short length = 1);

//Filters
Filter filterForDay(Case* parent, Case::Date date, int parentSize);
Filter filterForWeek(Case* parent, Case::Date date, int parentSize);
Filter filterForMonth(Case* parent, Case::Date date, int parentSize);

void errorMessage(std::string text) {
    std::cout << "\n" + text + "\n";
}

int main()
{
    Case* todo = new Case[::size];
    short action = 0;

    initializeTime(currentDate);

    system("cls");

    while (true) {
        std::cout << "Menu: 0 - view; 1 - Create; 2 - Update; 3 - Delete; 4 - Search; 5 - Sort by; 6 - Settings; -1 - Exit\n> ";
        std::cin >> action;

        if (action == -1)
            break;

        switch (action)
        {
        case 0: {
            render(todo);
            break;
        }
        case 1:
            createController(todo);
            break;
        case 2:
            updateController(todo);
            break;
        case 3:
            deleteController(todo);
            break;
        case 4:
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

void createController(Case*& todos) {
    Case form = inputForm();

    short validate = validateForm(form);

    if (validate)
    {
        return errorMessage("Incorrect input data");
    }

    todos = resize(todos);

    todos[::size] = form;

    ::size++;

    render(todos);
}

void updateController(Case* todo) {
    int id = 0;
    Case req;

    std::cout << "Update by id: ";
    std::cin >> id;

    id--;

    if (id < 0 || id >= ::size) {
        return errorMessage("invalid id!");
    }

    req = todo[id];

    req = inputForm(req);

    todo[id] = req;

}

void deleteController(Case*& todo) {
    int id = 0;
    std::cout << "Delete by id: ";
    std::cin >> id;

    id--;

    if (id < 0 || id >= ::size) {
        return errorMessage("Invalid id!");
    }

    for (int i = id; i < ::size - 1; i++)
    {
        todo[i] = todo[i + 1];
    }

    todo = resize(todo, ::size, -1);

    ::size--;
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

void render(Case*& todo, short choice) {    
    if (choice == 0) {
        std::cout << "Show on 1 - day, 2 - week, 3 - month, 4 - all\n";

        std::cin >> choice;
    }

    Filter response;

    switch (choice)
    {
        case 1:
            response = filterForDay(todo, currentDate, ::size);
            break;
        case 2:
            response = filterForWeek(todo, currentDate, ::size);
            break;
        case 3:
            response = filterForMonth(todo, currentDate, ::size);
            break;
        case 4:
            response = { todo, ::size };
            break;
        default:
            break;
    }

    system("cls");

    std::cout << "№  " << "Title\t" << "Description\t" << "Priority\t" << "Deadline\t" << std::endl;
    std::cout << "==================================================================" << std::endl;

    for (int i = 0; i < response.size; i++)
    {
        std::cout << i + 1 << "  " << response.arr[i].title << '\t' << response.arr[i].description << '\t' << response.arr[i].priority << '\t' << std::to_string(response.arr[i].deadline.hour) + ":" + std::to_string(response.arr[i].deadline.minutes) + " " + std::to_string(response.arr[i].deadline.day) + "." + std::to_string(response.arr[i].deadline.month) + "." + std::to_string(response.arr[i].deadline.year) << std::endl;
    }

}

short initializeTime(Case::Date& time) {
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

        validate = validateDate(time);

        if (validate)
            std::cout << "Incorrect date!\nTry again!\n";
    } while (validate);

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

Case* resize(Case* arr, int count, short length)
{
    if (count == 0)
    {
        arr = new Case[count + 1];
    }
    else
    {
        int expand = length > 0 ? count : count + length;

        Case* tempObj = new Case[count + length];
        
        for (int i = 0; i < expand; i++)
        {
            tempObj[i] = arr[i];
        }

        delete[] arr;

        arr = tempObj;
    }

    return arr;
}

Case inputForm(Case temp) {
    Case res = temp;
    short error;

    std::cout << "Title: (=" + temp.title + ") : ";
    //std::cin.ignore();
    //std::getline(std::cin, res.title);
    std::cin >> res.title;

    std::cout << "Description: (=" + temp.description + ") : ";
    //std::cin.ignore();
    //std::getline(std::cin, res.description);
    std::cin >> res.description;

    std::cout << "Priority: (=" + std::to_string(temp.priority) + ") : ";
    std::cin >> res.priority;

    std::cout << "Deadline:\n";
    while (true) {
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

Filter filterForDay(Case* parent, Case::Date date, int parentSize)
{
    Filter result;
    int childSize = 0;
    Case* child = new Case[childSize];

    for (int i = 0; i < parentSize; i++)
    {
        if (parent[i].deadline.day == date.day && parent[i].deadline.month == date.month && parent[i].deadline.year == date.year)
        {
            child = resize(child, childSize);

            child[childSize] = parent[i];

            childSize++;
        }
    }

    result.arr = child;
    result.size = childSize;

    return result;
}

Filter filterForWeek(Case* parent, Case::Date date, int parentSize)
{
    Filter result;
    int childSize = 0;
    Case* child = new Case[childSize];

    int day = 0;
    bool nextMonth = false;

    if (date.day + 7 <= 30)
    {
        day = date.day + 7;
        nextMonth = true;
    }
    else
    {
        day = (date.day + 7) % 10;
    }

    for (int i = 0; i < parentSize; i++)
    {
        if (parent[i].deadline.year == date.year)
        {
            if (!nextMonth)
            {
                if (parent[i].deadline.day <= day)
                {
                    child = resize(child, childSize);

                    child[childSize] = parent[i];

                    childSize++;
                }
            }
            else
            {
                if (parent[i].deadline.day <= day && parent[i].deadline.month == date.month + 1)
                {
                    child = resize(child, childSize);

                    child[childSize] = parent[i];

                    childSize++;
                }
            }
        }
    }

    result.arr = child;
    result.size = childSize;

    return result;
}

Filter filterForMonth(Case* parent, Case::Date date, int parentSize)
{
    Filter result;
    int childSize = 0;
    Case* child = new Case[childSize]; 

    for (int i = 0; i < parentSize; i++)
    {
        if (parent[i].deadline.year == date.year)
        {
            
        }
    }

    result.arr = child;
    result.size = childSize;

    return result;
}
