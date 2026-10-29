//Yee Khang
#include<fstream> //works with file
#include<iostream> //works with input output stream
#include<string> //works with all strings

using namespace std;

class Employee{//class to hold employee objects

    public:
        int employeeId;
        string firstName, lastName, phoneNumber, emailAddress;
        double salary;
Employee() {}
    //parameter constructor
Employee(int id, string fn, string ln, string pn, string ea, double pay):

    employeeId(id), firstName(fn), lastName(ln), phoneNumber(pn),
    emailAddress(ea), salary(pay){}

//prints function
void printEmployee() const{
    cout << employeeId << " " << firstName << " " << lastName << " " << phoneNumber << " "
         << emailAddress << " " << salary << " ";
}

};

class ListElement { //represents a single element
    public:
    ListElement() {} //blank constructor
    Employee emp_var;
    ListElement* next;
};

class MyList { //represents entire list
    public:
    ListElement* head;
    MyList():
        head(nullptr){}

    void deleteList() { //deletes all elements of list
        for (ListElement* curElement = head; curElement != nullptr;) {
            ListElement* deleted = curElement;
            curElement = curElement->next;
            delete deleted;
        }
    }

    void printEmployees() { //prints every employee in list
        for (ListElement* curElement = head; curElement != nullptr; curElement = curElement->next) {
            curElement->emp_var.printEmployee();
            cout << endl;
        }
    }

    ListElement* findPosition(const Employee& e) { //return the element to insert after or null
        if(head != nullptr) {
            ListElement* curElement = head;
            //cout << "starting search " << endl;
            while(curElement != nullptr) {
                
                //cout << e.employeeId << " compared to " << curElement->emp_var.employeeId << endl;
                
                if(curElement->next == nullptr || curElement->next->emp_var.employeeId > e.employeeId) {
                    //cout << "Found position at " << curElement->emp_var.employeeId << endl;
                    return curElement;
                }
                
                curElement = curElement->next;
            }
            return curElement;
        }
        else {
            return nullptr;
        }
    }

    void insertEmployee(const Employee& e) {//this inserts an employee to the list at the appropriate position
        ListElement* newElement = new ListElement; //allocated new memory
        newElement->emp_var = Employee(e.employeeId, e.firstName, e.lastName, e.phoneNumber, e.emailAddress, e.salary);

        if(head != nullptr) {
            ListElement* insertAfter = findPosition(e);
            if(insertAfter != nullptr) {
                ListElement* newNext = insertAfter->next;
                insertAfter->next = newElement;
                newElement->next = newNext;
            }
            else {
                ListElement* firstElement = head;
                head = newElement;
                newElement->next = firstElement;
            }
        }
        else {
            head = newElement;
            newElement->next = nullptr;
        }
    }
};

//inserts employee data from file
void insertEmployee(MyList& employeeList, const Employee& employeeData){
    employeeList.insertEmployee(employeeData);
}

int main(){

    ifstream file("Employee_File.txt"); //opens file

    if(!file){
        cout << "Invalid file" << endl;
        return 1;
    }

    MyList employeeList; //declares the list
    
    int id;
    string fn, ln, pn, ea;
    double pay;

    while (file >> id >> fn >> ln >> pn >> ea >> pay) {
        Employee employeeData(id, fn, ln, pn, ea, pay);
        insertEmployee(employeeList, employeeData);
    }

    file.close(); //close file
    employeeList.printEmployees();
    employeeList.deleteList();
}

