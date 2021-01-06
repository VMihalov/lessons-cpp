#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <windows.h>
#include <chrono>
#include <ctime>
#include <iomanip>

struct Date;
struct Case;
struct Filter;
struct Find;

struct Date {
    short minutes = 0;
    short hour = 0;
    short day = 1;
    short month = 1;
    int year = 2021;
};

struct Case {
    std::string title = "";
    std::string description = "";
    int priority = 0;
    Date deadline;
    std::string created_at = "";
    std::string updated_at = "";
};

struct Filter
{
    Case* arr;
    int size;
};

struct Find
{
    Case* result;
    int size;
};

int size = 5;
Date currentDate;

//Controllers
void createController(Case*& todo);
void updateController(Case* todo);
void deleteController(Case*& todo);
void findController(Case*& todo);
void optionController();

// Validate
short validateForm(Case form);

// Show table
void render(Case*& todo, int size, short choice = -1, short sort = -1);

// Working with table
Case inputForm(Case temp = {});
Case* resize(Case* arr, int count = ::size, short length = 1);

//Filters
Filter filterForDay(Case* parent, Date date, int parentSize);
Filter filterForWeek(Case* parent, Date date, int parentSize);
Filter filterForMonth(Case* parent, Date date, int parentSize);

//Search
Find findByTitle(Case* arr, int size, std::string title);
Find findByPriority(Case* arr, int size, int priority);
Find findByDescription(Case* arr, int size, std::string description);
Find findByDate(Case* arr, int size, Date date);

//Sort
Case* sortByPriority(Case* arr, int size);
Case* sortByDate(Case* arr, int size);

//Time
void initializeTime(Date& date);
Date getCurrentTime();
Date inputDate();
short validateDate(Date form);

void errorMessage(std::string text) {
    std::cout << "\n" + text + "\n";
}

int main()
{
    Case* todo = new Case[::size];
    short action = 0;

    todo[0].title = "hello";
    todo[0].description = "how are you?";
    todo[0].priority = 4;
    todo[0].deadline = { 0, 0, 13, 2, 2021 };
    todo[1].title = "lorem";
    todo[1].description = "dolor sit amet";
    todo[1].priority = 1;
    todo[1].deadline = { 0, 0, 10, 1, 2021 };
    todo[2].title = "yes";
    todo[2].description = "yeees";
    todo[2].priority = 2;
    todo[2].deadline = { 0, 0, 5, 6, 2021 };
    todo[3].title = "cat";
    todo[3].description = "dog dog dog cat cat cat pig";
    todo[3].priority = 7;
    todo[3].deadline = { 0, 0, 1, 1, 2021 };
    todo[4].title = "football";
    todo[4].description = "basketball maybe???";
    todo[4].priority = 5;
    todo[4].deadline = { 0, 0, 29, 3, 2021 };

    initializeTime(currentDate);

    system("cls");

    while (true) {
        std::cout << "Menu: 0 - view; 1 - Create; 2 - Update; 3 - Delete; 4 - Find; 5 - Sort by; 6 - Settings; -1 - Exit\n> ";
        std::cin >> action;

        if (action == -1)
            break;

        switch (action)
        {
        case 0:
            render(todo, ::size);
            break;
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
            findController(todo);
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

    render(todos, ::size);
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

    system("cls");

    render(todo, ::size, 4, 0);

    std::cout << "\nSelect the id written above to delete: ";
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

void findController(Case*& todo)
{
    short choice = 0;
    Date date;
    int priority = 0;
    Find result;
    std::string text;

    std::cout << "Find by: 1 - title; 2 - description; 3 - priority; 4 - deadline\n> ";

    std::cin >> choice;

    switch (choice)
    {
        case 1:
        {
            std::cout << "Title: ";
            std::cin >> text;

            result = findByTitle(todo, ::size, text);
            break;
        }
        case 2:
        {
            std::cout << "Description: ";
            std::cin >> text;

            result = findByDescription(todo, ::size, text);
            break;
        }
        case 3:
        {
            std::cout << "Priority: ";
            std::cin >> priority;

            result = findByPriority(todo, ::size, priority);
            break;
        }
        case 4:
        {
            std::cout << "Date:\n";
            date = inputDate();

            result = findByDate(todo, ::size, date);
            break;
        }
        default:
            std::cout << "Incorrect value!\n";
            break;
    }

    render(result.result, result.size, 0);
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

void render(Case*& todo, int size, short choice, short sort) {
    if (choice == -1) {
        std::cout << "Show on 1 - day, 2 - week, 3 - month, 4 - all\n";

        std::cin >> choice;
    }

    if (sort == -1) {
        std::cout << "Sort by: 1 - priority; 2 - date; 0 - without sort\n> ";

        std::cin >> sort;
    }

    Filter response;

    switch (choice)
    {
        case 1:
            response = filterForDay(todo, currentDate, size);
            break;
        case 2:
            response = filterForWeek(todo, currentDate, size);
            break;
        case 3:
            response = filterForMonth(todo, currentDate, size);
            break;
        case 4:
            response = { todo, size };
            break;
        default:
            break;
    }

    switch (sort)
    {
        case 0:
            break;
        case 1:
            response.arr = sortByPriority(response.arr, response.size);
            break;
        case 2:
            response.arr = sortByDate(response.arr, response.size);
            break;
    }

    system("cls");

    std::cout << std::setw(3) << std::left << "№" << std::setw(10) << "Title" << std::setw(30) << "Description" << std::setw(10) << "Priority" << std::setw(10) << "Deadline" << std::endl;

    for (int i = 0; i < response.size; i++)
    {
        std::cout << std::setw(3) << std::left << i + 1 << std::setw(10) << response.arr[i].title << std::setw(30) << response.arr[i].description << std::setw(10) << response.arr[i].priority << std::setw(10) << std::to_string(response.arr[i].deadline.hour) + ":" + std::to_string(response.arr[i].deadline.minutes) + " " + std::to_string(response.arr[i].deadline.day) + "." + std::to_string(response.arr[i].deadline.month) + "." + std::to_string(response.arr[i].deadline.year) << std::endl;
    }

}

void initializeTime(Date& date) {
    bool isCorrect = true;
    bool validate = false;
    
    date = getCurrentTime();

    std::cout << "Is time correct? " + std::to_string(date.hour) + ":" + std::to_string(date.minutes) + " " + std::to_string(date.day) + "." + std::to_string(date.month) + "." + std::to_string(date.year) + "\n";
    std::cout << "1 - yes; 0 - no\n> ";

    std::cin >> isCorrect;

    if (!isCorrect)
    {
        std::cout << "Initialize datetime\n";

        do
        {
            date = inputDate();

            validate = validateDate(date);

            if (validate)
                std::cout << "Incorrect date!\nTry again!\n";
        } while (validate);
    }
}

Date inputDate()
{
    Date result;

    std::cout << "\tHour: ";
    std::cin >> result.hour;

    std::cout << "\tMinutes: ";
    std::cin >> result.minutes;

    std::cout << "\tDay: ";
    std::cin >> result.day;

    std::cout << "\tMonth: ";
    std::cin >> result.month;

    std::cout << "\tYear: ";
    std::cin >> result.year;
    
    return result;
}

Date getCurrentTime()
{
    Date result;
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    result.minutes = now->tm_min;
    result.hour = now->tm_hour;
    result.day = now->tm_mday;
    result.month = (now->tm_mon + 1);
    result.year = (now->tm_year + 1900);

    return result;
}

short validateDate(Date form)
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

Filter filterForDay(Case* parent, Date date, int parentSize)
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

Filter filterForWeek(Case* parent, Date date, int parentSize)
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

Filter filterForMonth(Case* parent, Date date, int parentSize)
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

Find findByTitle(Case* arr, int size, std::string title)
{
    Find result;
    int tmpSize = 0;
    Case* tmp = new Case[tmpSize];

    for (int i = 0; i < size; i++)
    {
        if (arr[i].title == title)
        {
            tmp = resize(tmp, tmpSize);

            tmp[tmpSize] = arr[i];

            tmpSize++;
        }
    }

    result.result = tmp;
    result.size = tmpSize;

    return result;
}

Find findByPriority(Case* arr, int size, int priority)
{
    Find result;
    int tmpSize = 0;
    Case* tmp = new Case[tmpSize];

    for (int i = 0; i < size; i++)
    {
        if (arr[i].priority == priority)
        {
            tmp = resize(tmp, tmpSize);

            tmp[tmpSize] = arr[i];

            tmpSize++;
        }
    }

    result.result = tmp;
    result.size = tmpSize;

    return result;
}

Find findByDescription(Case* arr, int size, std::string description)
{
    Find result;
    int tmpSize = 0;
    Case* tmp = new Case[tmpSize];

    for (int i = 0; i < size; i++)
    {
        if (arr[i].description == description)
        {
            tmp = resize(tmp, tmpSize);

            tmp[tmpSize] = arr[i];

            tmpSize++;
        }
    }

    result.result = tmp;
    result.size = tmpSize;

    return result;
}

Find findByDate(Case* arr, int size, Date date)
{
    Find result;
    int tmpSize = 0;
    Case* tmp = new Case[tmpSize];

    for (int i = 0; i < size; i++)
    {
        if (arr[i].deadline.day == date.day && arr[i].deadline.month == date.month && arr[i].deadline.year == date.year)
        {
            tmp = resize(tmp, tmpSize);

            tmp[tmpSize] = arr[i];

            tmpSize++;
        }
    }

    result.result = tmp;
    result.size = tmpSize;

    return result;
}

Case* sortByPriority(Case* arr, int size)
{
    Case tempCase;
    Case* tmp = new Case[size];

    for (int i = 0; i < size; i++)
    {
        tmp[i] = arr[i];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tmp[i].priority < tmp[j].priority)
            {
                tempCase = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = tempCase;
            }
        }
    }

    return tmp;
}

Case* sortByDate(Case* arr, int size)
{
    Case tempCase;
    Case* tmp = new Case[size];

    for (int i = 0; i < size; i++)
    {
        tmp[i] = arr[i];
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tmp[i].deadline.year < tmp[j].deadline.year)
            {
                tempCase = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = tempCase;
            }
            else if (tmp[i].deadline.year == tmp[j].deadline.year && tmp[i].deadline.month < tmp[j].deadline.month)
            {
                tempCase = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = tempCase;
            }
            else if (tmp[i].deadline.year == tmp[j].deadline.year && tmp[i].deadline.month == tmp[j].deadline.month && tmp[i].deadline.day < tmp[j].deadline.day)
            {
                tempCase = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = tempCase;
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        std::cout << tmp[i].title << " -> " << tmp[i].deadline.day << std::endl;
    }

    return tmp;
}
