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

int size = 0;
Date currentDate;

//Controllers
void createController(Case*& todo);
void updateController(Case* todo);
void deleteController(Case*& todo);
void findController(Case*& todo);
void optionController();

// Validate
short validateForm(Case form);
short validateDate(Date form);

// Show table
void render(Case*& todo, int size, bool setInterval = true, bool setSort = true);

// Working with table
Case inputForm(Case temp = {});
Case* resize(Case* arr, int count, short length = 1);

//Filters
Filter filterForDay(Case* parent, Date date, int parentSize);
Filter filterForWeek(Case* parent, Date date, int parentSize);
Filter filterForMonth(Case* parent, Date date, int parentSize);

//Search
Find findByTitle(Case* arr, int size, std::string title);
Find findByPriority(Case* arr, int size, int priority);
Find findByDescription(Case* arr, int size, std::string description);
Find findByDate(Case* arr, int size, Date date);

//Update
int updateTitle(Case* arr, int id, std::string title);
int updateDescription(Case* arr, int id, std::string description);
int updatePriority(Case* arr, int id, int priority);
int updateDate(Case* arr, int id, Date date);

//Sort
Case* sortByPriority(Case* arr, int size);
Case* sortByDate(Case* arr, int size);

//Time
void initializeTime(Date& date);
Date getCurrentTime();
Date inputDate();

void errorMessage(std::string text) {
    std::cout << "\n" + text + "\n\n";
}

int main()
{
    Case* todo = new Case[::size];
    short action = 0;

    initializeTime(currentDate);


    std::cin.get();
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
    try
    {
        Case form = inputForm();

        short validate = validateForm(form);

        if (validate)
        {
            throw "Invalid validate";
        }

        todos = resize(todos, ::size);

        todos[::size] = form;

        ::size++;

        render(todos, ::size, false, false);
    }
    catch (const char* exception)
    {
        std::cin.clear();
        std::cin.ignore();

        std::cerr << "\nError: " << exception << '\n';
    }
}

void updateController(Case* todo) {
    try
    {
        int row = 0;
        int id = 0;
        Case req;

        render(todo, ::size, false, false);

        std::cout << "Select the id: ";
        std::cin >> id;

        id--;

        if (id < 0 || id >= ::size)
            throw "Invalid id";

        std::cout << "\nSelect the field: 0 - all, 1 - title, 2 - description, 3 - priority, 4 - date\n> ";
        std::cin >> row;

        std::cin.ignore();

        switch (row)
        {
        case 0: {
            req = todo[id];

            req = inputForm(req);

            todo[id] = req;

            break;
        }
        case 1: {
            std::cout << "Insert new title: ";
            std::getline(std::cin, req.title);

            updateTitle(todo, id, req.title);

            break;
        }
        case 2: {
            std::cout << "Insert new description: ";
            std::getline(std::cin, req.description);

            updateDescription(todo, id, req.description);

            break;
        }
        case 3: {
            std::cout << "Insert new priority: ";
            std::cin >> req.priority;

            updatePriority(todo, id, req.priority);

            break;
        }
        case 4: {
            req.deadline = inputDate();

            updateDate(todo, id, req.deadline);

            break;
        }
        default:
            throw "Invalid row";
            break;
        }
    }
    catch (const char* exception)
    {
        std::cin.clear();
        std::cin.ignore();

        std::cerr << "\nError: " << exception << '\n';
    }
}

void deleteController(Case*& todo) {
    try
    {
        int id = 0;

        system("cls");

        render(todo, ::size, false, false);

        std::cout << "\nSelect the id written above to delete: ";
        std::cin >> id;

        id--;

        if (id < 0 || id >= ::size) {
            throw "Invalid id";
        }

        for (int i = id; i < ::size - 1; i++)
        {
            todo[i] = todo[i + 1];
        }

        todo = resize(todo, ::size, -1);

        ::size--;
    }
    catch (const char* exception)
    {
        std::cin.clear();
        std::cin.ignore();

        std::cerr << "\nError: " << exception << '\n';
    }
}

void findController(Case*& todo)
{
    try
    {
        short choice = 0;
        Date date;
        int priority = 0;
        Find result;
        std::string text;

        std::cout << "Find by: 1 - title; 2 - description; 3 - priority; 4 - deadline\n> ";

        std::cin >> choice;

        std::cin.ignore();

        switch (choice)
        {
        case 1:
        {
            std::cout << "Title: ";
            std::getline(std::cin, text);

            result = findByTitle(todo, ::size, text);
            break;
        }
        case 2:
        {
            std::cout << "Description: ";
            std::getline(std::cin, text);

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
            throw "Incorrect number";
            break;
        }

        render(result.result, result.size, 0);
    }
    catch (const char* exception)
    {
        std::cin.clear();
        std::cin.ignore();

        std::cerr << "\nError: " << exception << '\n';
    }
}

void optionController() {
    try
    {
        int settings = 0;

        std::cout << "1 - default time;\n> ";
        std::cin >> settings;

        switch (settings)
        {
        case 1:
            initializeTime(currentDate);
            break;
        default:
            throw "Incorrect number";
            break;
        }
    }
    catch (const char* exception)
    {
        std::cin.clear();
        std::cin.ignore();

        std::cerr << "\nError: " << exception << '\n';
    }
}

void render(Case*& todo, int size, bool setInterval, bool setSort) {
    unsigned short interval = 0, sort = 0;

    if (setInterval) {
        std::cout << "Show on 0 - all, 1 - day, 2 - week, 3 - month\n";

        std::cin >> interval;
    }

    if (setSort) {
        std::cout << "Sort by: 0 - without sort, 1 - priority; 2 - date;\n> ";

        std::cin >> sort;
    }

    Filter response;

    switch (interval)
    {
        case 0:
            response = { todo, size };
            break;
        case 1:
            response = filterForDay(todo, currentDate, size);
            break;
        case 2:
            response = filterForWeek(todo, currentDate, size);
            break;
        case 3:
            response = filterForMonth(todo, currentDate, size);
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

    std::cin.ignore();

    std::cout << "Title: (=" + temp.title + ") : ";
    std::getline(std::cin, res.title);

    std::cout << "Description: (=" + temp.description + ") : ";
    std::getline(std::cin, res.description);

    std::cout << "Priority: (=" + std::to_string(temp.priority) + ") : ";
    std::cin >> res.priority;

    std::cout << "Deadline:\n";
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
        throw "Invalid date";

    res.created_at = "";
    res.updated_at = "";

    while (!std::cin.good())
    {
        throw "Incorrectly entered data";
    }

    return res;
}

Filter filterForDay(Case* parent, Date date, int parentSize)
{
    Date deadline = date;
    Filter result;
    int childSize = 0;
    Case* child = new Case[childSize];

    int year[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    year[1] = (date.year % 10) % 4 == 0 ? 29 : 28;

    if (deadline.day + 1 <= year[deadline.month - 1])
    {
        deadline.day++;
    }
    else if (deadline.day + 1 > year[deadline.month - 1] && deadline.month != 12)
    {
        deadline.day = (deadline.day + 1) - year[deadline.month - 1];
        deadline.month++;
    }
    else
    {
        deadline.day = 1;
        deadline.month = 1;
        deadline.year++;
    }

    for (int i = 0; i < parentSize; i++)
    {
        if (parent[i].deadline.year >= date.year && parent[i].deadline.month >= date.month && parent[i].deadline.day >= date.day)
        {
            if (parent[i].deadline.year <= deadline.year)
            {
                if (parent[i].deadline.month <= deadline.month)
                {
                    if (parent[i].deadline.day <= deadline.day)
                    {
                        child = resize(child, childSize);

                        child[childSize] = parent[i];

                        childSize++;
                    }
                }
            }
        }
    }

    result.arr = child;
    result.size = childSize;

    return result;
}

Filter filterForWeek(Case* parent, Date date, int parentSize)
{
    Date deadline = date;
    Filter result;
    int childSize = 0;
    Case* child = new Case[childSize];

    int year[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    year[1] = (date.year % 10) % 4 == 0 ? 29 : 28;

    if (deadline.day + 7 <= year[deadline.month - 1])
    {
        deadline.day += 7;
    }
    else if (deadline.day + 7 > year[deadline.month - 1] && deadline.month != 12)
    {
        deadline.day = (deadline.day + 7) - year[deadline.month - 1];
        deadline.month++;
    }
    else
    {
        deadline.day = 7;
        deadline.month = 1;
        deadline.year++;
    }

    for (int i = 0; i < parentSize; i++)
    {
        if (parent[i].deadline.year >= date.year)
        {
            if ( (parent[i].deadline.month >= date.month && parent[i].deadline.day >= date.day) || (parent[i].deadline.month > date.month && parent[i].deadline.day <= date.day))
            {
                if (parent[i].deadline.year <= deadline.year)
                {
                    if (parent[i].deadline.month <= deadline.month)
                    {
                        if (parent[i].deadline.day <= deadline.day)
                        {
                            child = resize(child, childSize);

                            child[childSize] = parent[i];

                            childSize++;
                        }
                    }
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
    Date deadline = date;
    Filter result;
    int childSize = 0;
    Case* child = new Case[childSize];

    int nextMonth = 0;
    int year[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    year[1] = (date.year % 10) % 4 == 0 ? 29 : 28;

    nextMonth = date.month < 12 ? year[date.month] : year[0];

    if (deadline.day + nextMonth <= year[deadline.month - 1])
    {
        deadline.day += nextMonth;
    }
    else if (deadline.day + nextMonth > year[deadline.month - 1] && deadline.month != 12)
    {
        deadline.day = (deadline.day + nextMonth) - year[deadline.month - 1];
        deadline.month++;
    }
    else
    {
        deadline.day = (deadline.day + nextMonth) - year[deadline.month - 1];
        deadline.month = 1;
        deadline.year++;
    }

    for (int i = 0; i < parentSize; i++)
    {
        if (parent[i].deadline.year >= date.year)
        {
            if ((parent[i].deadline.month >= date.month && parent[i].deadline.day >= date.day) || (parent[i].deadline.month > date.month && parent[i].deadline.day <= date.day))
            {
                if (parent[i].deadline.year <= deadline.year)
                {
                    if (parent[i].deadline.month <= deadline.month)
                    {
                        if (parent[i].deadline.day <= deadline.day)
                        {
                            child = resize(child, childSize);

                            child[childSize] = parent[i];

                            childSize++;
                        }
                    }
                }
            }
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
            if (tmp[i].deadline.year > tmp[j].deadline.year)
            {
                tempCase = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = tempCase;
            }
            else if (tmp[i].deadline.year == tmp[j].deadline.year && tmp[i].deadline.month > tmp[j].deadline.month)
            {
                tempCase = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = tempCase;
            }
            else if (tmp[i].deadline.year == tmp[j].deadline.year && tmp[i].deadline.month == tmp[j].deadline.month && tmp[i].deadline.day > tmp[j].deadline.day)
            {
                tempCase = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = tempCase;
            }
            else if (tmp[i].deadline.year == tmp[j].deadline.year && tmp[i].deadline.month == tmp[j].deadline.month && tmp[i].deadline.day == tmp[j].deadline.day)
            {
                if (tmp[i].deadline.hour > tmp[j].deadline.hour)
                {
                        tempCase = tmp[i];
                        tmp[i] = tmp[j];
                        tmp[j] = tempCase;
                }
                else if (tmp[i].deadline.hour == tmp[j].deadline.hour && tmp[i].deadline.minutes > tmp[j].deadline.minutes)
                {
                    tempCase = tmp[i];
                    tmp[i] = tmp[j];
                    tmp[j] = tempCase;
                }
            }
        }
    }

    return tmp;
}

int updateTitle(Case* arr, int id, std::string title)
{
    arr[id].title = title;

    return 0;
}

int updateDescription(Case* arr, int id, std::string description)
{
    arr[id].description = description;

    return 0;
}

int updatePriority(Case* arr, int id, int priority)
{
    arr[id].priority = priority;

    return 0;
}

int updateDate(Case* arr, int id, Date date)
{
    arr[id].deadline = date;

    return 0;
}
