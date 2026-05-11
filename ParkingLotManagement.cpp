#include <iostream>
#include <string>
using namespace std;

// ---------------- Vehicle Class ----------------
class Vehicle
{
private:
    int vehicleNumber;
    string type;

public:
    Vehicle()
    {
       vehicleNumber = 0;
       type = "";
    }

    Vehicle(int vNo, string t)
    {
        vehicleNumber = vNo;
        type = t;
    }

    int getVehicleNumber()
    {
        return vehicleNumber;
    }

    string getType()
    {
        return type;
    }

    void display()
    {
        cout << "Vehicle No: " << vehicleNumber << ", Type: " << type << endl;
    }
};

// ---------------- Stack (Parking) ----------------
class Stack
{
private:
    class Node
    {
    public:
        Vehicle data;
        Node* next;
        Node(Vehicle v)
        {
            data = v;
            next = NULL;
        }
    };

    Node* top;

public:
    Stack()
    {
        top = NULL;
    }

    void push(Vehicle v)
    {
        Node* newNode = new Node(v);
        newNode->next = top;
        top = newNode;
    }

    void pop()
    {
        if (!top) return;
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    Vehicle Top()
    {
        if (!top) return Vehicle();
        return top->data;
    }

    bool isEmpty()
    {
        return top == NULL;
    }

    int size()
    {
        int count = 0;
        Node* temp = top;
        while (temp)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display()
    {
        if (!top)
        {
            cout << "Parking is empty\n";
            return;
        }
        Node* temp = top;
        while (temp)
        {
            temp->data.display();
            temp = temp->next;
        }
    }

    bool removeVehicle(int vNo)
    {
        Node* temp = top;
        Node* prev = NULL;

        while (temp)
        {
            if (temp->data.getVehicleNumber() == vNo)
            {
                if (!prev) top = temp->next;
                else prev->next = temp->next;
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    Vehicle* search(int vNo)
    {
        Node* temp = top;
        while (temp)
        {
            if (temp->data.getVehicleNumber() == vNo)
                return &temp->data;
            temp = temp->next;
        }
        return NULL;
    }

    void destroy()
    {
        while (!isEmpty()) pop();
    }

    void typeReport()
    {
        int cars = 0, bikes = 0, others = 0;
        Node* temp = top;

        while (temp)
        {
            string t = temp->data.getType();
            if (t == "Car") cars++;
            else if (t == "Bike") bikes++;
            else others++;
            temp = temp->next;
        }

        cout << "Parked Vehicle Type Report:\n";
        cout << "Cars: " << cars << ", Bikes: " << bikes << ", Others: " << others << endl;
    }

};

// ---------------- Queue (Waiting) ----------------
class Queue
{
private:
    class Node
    {
    public:
        Vehicle data;
        Node* next;
        Node(Vehicle v)
        {
            data = v;
            next = NULL;
        }
    };

    Node* front;
    Node* rear;

public:
    Queue()
    {
        front = rear = NULL;
    }

    void enqueue(Vehicle v)
    {
        Node* newNode = new Node(v);
        if (!rear) front = rear = newNode;
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue()
    {
        if (!front) return;
        Node* temp = front;
        front = front->next;
        if (!front) rear = NULL;
        delete temp;
    }

    Vehicle Front()
    {
        if (!front) return Vehicle();
        return front->data;
    }

    bool isEmpty()
    {
        return front == NULL;
    }

    int size()
    {
        int count = 0;
        Node* temp = front;
        while (temp)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display()
    {
        if (!front)
        {
            cout << "Waiting queue is empty\n";
            return;
        }
        Node* temp = front;
        while (temp)
        {
            temp->data.display();
            temp = temp->next;
        }
    }

    bool removeVehicle(int vNo)
    {
        Node* temp = front;
        Node* prev = NULL;

        while (temp)
        {
            if (temp->data.getVehicleNumber() == vNo)
            {
                if (!prev) front = temp->next;
                else prev->next = temp->next;

                if (temp == rear) rear = prev;
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }
        return false;
    }

    Vehicle* search(int vNo)
    {
        Node* temp = front;
        while (temp)
        {
            if (temp->data.getVehicleNumber() == vNo)
                return &temp->data;
            temp = temp->next;
        }
        return NULL;
    }

    void destroy()
    {
        while (!isEmpty()) dequeue();
    }

    void typeReport()
    {
        int cars = 0, bikes = 0, others = 0;
        Node* temp = front;

        while (temp)
        {
            string t = temp->data.getType();
            if (t == "Car") cars++;
            else if (t == "Bike") bikes++;
            else others++;
            temp = temp->next;
        }

        cout << "Waiting Queue Vehicle Type Report:\n";
        cout << "Car: " << cars << ", Bike: " << bikes << ", Others: " << others << endl;
    }
};

// ---------------- ParkingLotManager ----------------
class ParkingLotManager
{
private:
    Stack parking;
    Queue waiting;
    int capacity;

public:
    ParkingLotManager(int cap)
    {
        capacity = cap;
    }

    void enterVehicle()
    {
        int num;
        string type;

        cout << "Enter vehicle number: ";
        cin >> num;
        cout << "Enter vehicle type: ";
        cin >> type;

        if (parking.search(num) || waiting.search(num))
        {
            cout << "Vehicle already exists!\n";
            return;
        }

        Vehicle v(num, type);
        if (parking.size() < capacity)
        {
            parking.push(v);
            cout << "Vehicle parked.\n";
        }
        else
        {
            waiting.enqueue(v);
            cout << "Parking full. Added to waiting queue.\n";
        }
    }

    void exitVehicle()
    {
        if (parking.isEmpty())
        {
            cout << "Parking empty.\n";
            return;
        }

        Vehicle v = parking.Top();
        parking.pop();
        cout << "Vehicle exited:\n";
        v.display();

        if (!waiting.isEmpty())
        {
            Vehicle next = waiting.Front();
            waiting.dequeue();
            parking.push(next);
        }
    }

    void exitSpecificVehicle()
    {
        int num;
        cout << "Enter vehicle number to remove: ";
        cin >> num;

        if (parking.removeVehicle(num))
        {
            cout << "Vehicle removed from parking.\n";
            if (!waiting.isEmpty())
            {
                Vehicle next = waiting.Front();
                waiting.dequeue();
                parking.push(next);
            }
        }
        else if (waiting.removeVehicle(num))
        {
            cout << "Vehicle removed from waiting queue.\n";
        }
        else
        {
            cout << "Vehicle not found.\n";
        }
    }

    void searchVehicle()
    {
        int num;
        cout << "Enter vehicle number to search: ";
        cin >> num;

        Vehicle* v = parking.search(num);
        if (v)
        {
            cout << "Vehicle found in PARKING:\n";
            v->display();
            return;
        }

        v = waiting.search(num);
        if (v)
        {
            cout << "Vehicle found in WAITING QUEUE:\n";
            v->display();
            return;
        }

        cout << "Vehicle not found.\n";
    }

    void vehicleTypeReport()
    {
        parking.typeReport();
        waiting.typeReport();
    }

    void showParking()
    {
        parking.display();
    }
    void showWaiting()
    {
        waiting.display();
    }

    void showTotalVehicles()
    {
        cout << "Parked: " << parking.size()
             << ", Waiting: " << waiting.size() << endl;
    }

    void clearParkingLot()
    {
        parking.destroy();
        waiting.destroy();
        cout << "Parking lot cleared.\n";
    }
};

// ---------------- Main ----------------
int main()
{
    int cap;
    cout << "Enter parking capacity: ";
    cin >> cap;

    ParkingLotManager system(cap);
    int choice;

    do
    {
        cout << "\n===== Parking Lot Menu =====\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Exit Vehicle\n";
        cout << "3. Exit Specific Vehicle\n";
        cout << "4. Show Parked Vehicles\n";
        cout << "5. Show Waiting Queue\n";
        cout << "6. Search Vehicle\n";
        cout << "7. Vehicle Type Report\n";
        cout << "8. Show Total Vehicles\n";
        cout << "9. Clear Parking Lot\n";
        cout << "10. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.enterVehicle();
            break;
        case 2:
            system.exitVehicle();
            break;
        case 3:
            system.exitSpecificVehicle();
            break;
        case 4:
            system.showParking();
            break;
        case 5:
            system.showWaiting();
            break;
        case 6:
            system.searchVehicle();
            break;
        case 7:
            system.vehicleTypeReport();
            break;
        case 8:
            system.showTotalVehicles();
            break;
        case 9:
            system.clearParkingLot();
            break;
        }
    }
    while (choice != 10);

    cout << "Program exited.\n";
    return 0;
}
