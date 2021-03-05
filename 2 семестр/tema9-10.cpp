#include <iostream>
#include <string>
#define GRADES 3

struct Student {
    std::string surname = "";
    int grades[GRADES] = { 0 };
};

struct ClassBook {
    private: 
        Student* students = 0;
        int numberOfStudents = 0;

    public:
        ClassBook(int count) {
            numberOfStudents = count;
            students = new Student[numberOfStudents];
        }

        ~ClassBook() {
            delete[] students;
            students = nullptr;
        }

        void insert() {
            for (int i = 0; i < numberOfStudents; i++)
            {
                std::cout << i + 1 << ")\n" << "\tSurname: ";
                std::cin >> students[i].surname;

                for (int j = 0; j < GRADES; j++)
                {
                    std::cout << "\t\t" << j + 1 <<" grade: ";
                    std::cin >> students[i].grades[j];
                }

            }
        }
        
        void render() {
            for (int i = 0; i < numberOfStudents; i++)
            {
                std::cout << i + 1 << ") " << students[i].surname << "\t";
                for (int j = 0; j < GRADES; j++)
                {
                    std::cout << students[i].grades[j] << " ";
                }
                std::cout << std::endl;
            }
            
        }

        void groupByAverageGrade() {
            Student tmp;

            for (int i = 0; i < numberOfStudents; i++)
            {
                for (int j = 0; j < numberOfStudents; j++)
                {
                    if (averageGrade(students[i].grades) > averageGrade(students[j].grades)) {
                        tmp = students[i];
                        students[i] = students[j];
                        students[j] = tmp;
                    }
                }
                
            }
            
        }

        double getQualitativePerformanceIndicator() {
            double numberOfGoodGrades = 0;

            for (int i = 0; i < numberOfStudents; i++)
            {
                for (int j = 0; j < GRADES; j++)
                {
                    if (students[i].grades[j] == 4 || students[i].grades[j] == 5)
                        numberOfGoodGrades += 1;
                }  
            }

            return (numberOfGoodGrades * 10) / numberOfStudents;        
        }

    private:
        double averageGrade(int numbers[GRADES]) {
            double sumOfGrades = 0;

            for (int i = 0; i < GRADES; i++)
            {
                sumOfGrades += numbers[i];
            }
            
            return sumOfGrades / GRADES;
        }

};

int main() {
    ClassBook classbook = ClassBook(10);

    classbook.insert();
    classbook.groupByAverageGrade();
    classbook.render();

    std::cout << "Qualitative Performance Indicator of students: " 
              << classbook.getQualitativePerformanceIndicator()
              << std::endl;

    return 0;
}