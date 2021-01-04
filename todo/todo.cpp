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
    std::string title = "test";
    std::string description = "test";
    int priority = 0;
    Date deadline = {0, 0, 1, 1, 2021};
    std::string created_at = "";
    std::string updated_at = "";
};

int size = 0;
Case::Date currentDate;

void createController(Case*& todo);
void updateController(Case* todo);
void deleteController(Case* todo);
void optionController();

short initializeTime(Case::Date time);

short validateDate(Case::Date form);
short validateForm(Case form);

void render(Case*& todo, short choice = 0);
void showTable(Case* arr, short mode = 0);
void viewSingleCase(Case row);

Case inputForm();
Case* resize(Case* arr);
void showData(Case* Obj);

void errorMessage(std::string text) {
    std::cout << "\n" + text + "\n";
}

int main()
{
    Case* todo = 0;
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
        case 2: {
            //updateController(todo);
            int id = 0;
            Case req;

            std::cout << "Update by id: ";
            std::cin >> id;

            id--;

            if (id < 0 || id >= ::size) {
                errorMessage("invalid id!");
            } else {
                req = inputForm();

                todo[id] = req;
            }

            break;
        }
        case 3: {
            int id = 0;
            std::cout << "Delete by id: ";
            std::cin >> id;

            if (id < 0 || id >= ::size) {
                errorMessage("Invalid id!");
            }

            for (int i = id; i < ::size - 1; i++)
            {
                todo[i] = todo[i + 1];
            }

            break;
        }
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

    showData(todos);
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

}

void deleteController(Case* todo) {
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

    /*
    int tmpSize = 0;
    Case* tmp = new Case[tmpSize];

    
    for (int i = 0; i < ::size; i++)
    {
        if (todo[i].deadline.day == currentDate.day && todo[i].deadline.month == currentDate.month && todo[i].deadline.year == currentDate.year) {
            tmp[tmpSize] = todo[i];

            resize(tmp);

            tmpSize++;
        }
    }
    */

    system("cls");

    std::cout << ::size << std::endl;
    std::cout << "№  " << "Title\t" << "Description\t" << "Priority\t" << std::endl;
    std::cout << "========================================" << std::endl;

    for (int i = 0; i < ::size; i++)
    {
        if (choice == 4) {
            std::cout << i + 1 << "  " << todo[i].title << '\t' << todo[i].description << '\t' << todo[i].priority << std::endl;
        }
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

void showData(Case* Obj)
{
    system("cls");
    std::cout << ::size << std::endl;
    std::cout << "№  " << "Title\t" << "Description\t" << "Priority\t" << std::endl;
    std::cout << "========================================" << std::endl;
    for (int i = 0; i < ::size; i++)
    {
        std::cout << i + 1 << "  " << Obj[i].title << '\t' << Obj[i].description << '\t' << Obj[i].priority << std::endl;
    }
}


Case* resize(Case* Obj)
{
    if (::size == 0)
    {
        Obj = new Case[::size + 1];
    }
    else
    {
        Case* tempObj = new Case[::size + 1];
        
        for (int i = 0; i < ::size; i++)
        {
            tempObj[i] = Obj[i];
        }

        delete[] Obj;

        Obj = tempObj;
    }

    return Obj;
}

Case inputForm() {
    Case res;
    short error;

    std::cout << "Title: ";
    std::cin.ignore();
    std::getline(std::cin, res.title);

    std::cout << "Description: ";
    std::cin.ignore();
    std::getline(std::cin, res.description);

    std::cout << "Priority: ";
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
