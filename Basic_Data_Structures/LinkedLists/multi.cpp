#include <iostream>
using namespace std;
struct Course
{
    int courseId;
    struct Student *firstStudent;
    struct Course *next;
} *courseHead = NULL;

struct Student
{
    int id;
    int courseId;
    struct Student *next;
} *studentHead = NULL;

struct Course *findCourseByNumber(int courseId)
{
    struct Course *currentCourse = courseHead;
    while (currentCourse != NULL)
    {
        if (currentCourse->courseId == courseId)
        {
            return currentCourse;
        }
        currentCourse = currentCourse->next;
    }
    return NULL; // Course not found
}

void insertCourse(int courseId)
{
    if (courseHead == NULL)
    {
        struct Course *current = new Course();
        current->next = NULL;
        current->firstStudent = NULL;
        current->courseId = courseId;
        courseHead = current;
    }
    else
    {
        struct Course *current = courseHead;
        struct Course *temp = new Course();
        temp->next = NULL;
        temp->firstStudent = NULL;
        temp->courseId = courseId;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = temp;
    }
}

void insertStudent(int courseId, int studentId)
{
    struct Course *currentCourse = courseHead;
    while (currentCourse != NULL)
    {
        if (currentCourse->courseId == courseId)
        {
            break;
        }
        currentCourse = currentCourse->next;
    }
    if (currentCourse == NULL)
    {
        cout << "Course is not available this semester" << endl;
        return;
    }

    if (currentCourse->firstStudent == NULL)
    {
        struct Student *temp = new Student();
        temp->next = NULL;
        temp->id = studentId;
        temp->courseId = courseId;
        currentCourse->firstStudent = temp;
    }
    else
    {
        struct Student *currentStudent = currentCourse->firstStudent;
        struct Student *temp = new Student();
        temp->next = NULL;
        temp->courseId = courseId;
        temp->id = studentId;
        while (currentStudent->next != NULL)
        {
            currentStudent = currentStudent->next;
        }
        currentStudent->next = temp;
    }
}

void print()
{
    struct Course *currentCourse = courseHead;
    while (currentCourse != NULL)
    {
        cout << "Course No : " << currentCourse->courseId << endl
             << "Students Enrolled In This Course  " << endl;
        struct Student *currentStudent = currentCourse->firstStudent;
        while (currentStudent != NULL)
        {
            cout << "Student Id : " << currentStudent->id << endl;
            currentStudent = currentStudent->next;
        }
        currentCourse = currentCourse->next;
    }
}

void deleteAllStudents(int courseId)
{
    struct Student *tempStudent = new Student();
    struct Course *currentCourse = courseHead;
    while (currentCourse != NULL)
    {
        if (currentCourse->courseId == courseId)
        {
            break;
            ;
        }
        currentCourse = currentCourse->next;
    }
    if (currentCourse == NULL)
    {
        cout << "Course is not available this semester" << endl;
        return;
    }

    while (currentCourse->firstStudent = NULL)
    {
        tempStudent = currentCourse->firstStudent;
        currentCourse->firstStudent = currentCourse->firstStudent->next;
        free(tempStudent);
    }
    cout << "All nodes are deleted successfully.\n";
}

void deleteAStudent(int studentId)
{
    struct Course *currentCourse = courseHead;
    while (currentCourse != NULL)
    {
        struct Student *currentStudent = currentCourse->firstStudent;
        struct Student *prevStudent = NULL;

        while (currentStudent != NULL)
        {
            if (currentStudent->id == studentId)
            {
                if (prevStudent == NULL)
                {
                    // Deleting the first student in the list
                    currentCourse->firstStudent = currentStudent->next;
                }
                else
                {
                    prevStudent->next = currentStudent->next;
                }

                struct Student *temp = currentStudent;
                currentStudent = currentStudent->next;
                free(temp);
            }
            else
            {
                prevStudent = currentStudent;
                currentStudent = currentStudent->next;
            }
        }
        currentCourse = currentCourse->next;
    }
}

void deleteACourse(int courseId)
{
    struct Student *temp = new Student();

    struct Course *currentCourse = courseHead;
    struct Course *prevCourse = NULL;

    while (currentCourse != NULL)
    {
        if (currentCourse->courseId == courseId)
        {
            break;
        }
        prevCourse = currentCourse;
        currentCourse = currentCourse->next;
    }

    if(currentCourse == NULL){
        return;
    }

    while (currentCourse->firstStudent != NULL)
    {
        temp = currentCourse->firstStudent;
        currentCourse->firstStudent = currentCourse->firstStudent->next;
        free(temp);
    }

    currentCourse->firstStudent = NULL;
    cout << "All nodes are deleted successfully.\n";

    if (currentCourse == courseHead)
    {
        struct Course *curr = currentCourse;
        courseHead = currentCourse->next;
        free(curr);
    }
    else
    {
        prevCourse->next = currentCourse->next;
        free(currentCourse);
    }
}

void printStudent(int studentId)
{
    struct Course *currentCourse = courseHead;
    cout << "Student ID : " << studentId << endl;
    cout << "Courses Enrolled : ";
    while (currentCourse != NULL)
    {
        struct Student *currentStudent = currentCourse->firstStudent;
        while (currentStudent != NULL)
        {
            if (currentStudent->id == studentId)
            {
                cout << currentCourse->courseId << " | ";
                break;
            }
            currentStudent = currentStudent->next;
        }
        currentCourse = currentCourse->next;
    }
    cout << endl;
}

int main()
{
    insertCourse(111);
    insertCourse(222);
    insertCourse(333);
    insertCourse(444);
    insertStudent(444, 1);
    insertStudent(444, 2);
    insertStudent(333, 1);
    insertStudent(222, 3);
    insertStudent(111, 4);
    insertStudent(222, 1);
    printStudent(1);
    print();
    deleteAStudent(1);
    print();

    // int input;
    // do
    // {
    //     cout << "1.Insert Course" << endl;
    //     cout << "2.Insert Student" << endl;
    //     cout << "3.Print List" << endl;
    //     cout << "4.Delete All Students" << endl;
    //     cout << "5.Delete A Student From All Courses" << endl;
    //     cout << "6.Delete A Course" << endl;
    //     cout << "7.Print Student Data" << endl;
    //     cout << "8.Exit" << endl;
    //     cout << "Enter Your Choice : " << endl;
    //     cin >> input;
    //     if (input == 1)
    //     {
    //         insertCourse();
    //     }
    //     else if (input == 2)
    //     {
    //         insertStudent();
    //     }
    //     else if (input == 3)
    //     {
    //         print();
    //     }
    //     else if (input == 4)
    //     {
    //         deleteAllStudents();
    //     }
    //     else if (input == 5)
    //     {
    //         deleteAStudent();
    //     }
    //     else if (input == 6)
    //     {
    //         deleteACourse();
    //     }
    //     else if (input == 7)
    //     {
    //         printStudent();
    //     }
    //     else if (input == 8)
    //     {
    //     }
    //     else
    //     {
    //         cout << "Invalid Input" << endl;
    //     }
    // } while (input != 8);

    return 0;
}