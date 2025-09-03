//ACM_TASK.cpp
//Design a simple class called Dealership, 
//That has two functions : buyCar(Car a) and sellCar(Car a).
//buyCar(Car a) : Adds the car to the list of cars already in the dealership.
//sellCar(Car a) : Removes the car from the list of cars already in the dealership.

#include <iostream>
#include <cassert>

class Car {
private:
    int val;
    Car* next;
public:
    friend class Dealership;
    Car(int val) : val(val), next(nullptr) {}
};
class Dealership {
private:
    Car* cars_l;
public:
    // these two in case someone tryes to call default copy constryctor or assinment operator from Dealership
    Dealership(const Dealership&) = delete;
    Dealership& operator=(const Dealership&) = delete;

    Dealership(): cars_l(nullptr) { }
    ~Dealership() {
        Car* temp = cars_l;
        while (temp != nullptr) {
            Car* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
    // i would rather pass data here and then construct an object
    // But due to task constraints i pass Car, even though i temporarely takes more memory
    void buyCar(Car car);
    // Here i would also search by data
    void sellCar(Car car);
    void display() const;
    // test functions:
    bool contains(int val) const;
    int size() const;
};

void Dealership::buyCar(Car car) {
    Car* newcar = new Car(car.val);

    if (cars_l == nullptr) {
        cars_l = newcar;
    }
    else {
        Car* temp = cars_l;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newcar;
    }
}
void Dealership::sellCar(Car car) {
    if (cars_l == nullptr) return;

    // if head is the node to delete
    if (cars_l->val == car.val) {
        Car* toDelete = cars_l;
        // if there is only one node, it will be assigned to nullptr
        cars_l = cars_l->next;
        delete toDelete;
        return;
    }
    Car* temp = cars_l;
    while (temp->next != nullptr &&
        temp->next->val != car.val) {

        temp = temp->next;
    }
    // if not found, nothing happens
    // if found, will join previous and next elements in respect to deleted node
    // Will also work for last element
    if (temp->next != nullptr) {
        Car* toDelete = temp->next;
        temp->next = temp->next->next;
        delete toDelete;
    }
}
void Dealership::display() const {
    Car* temp = cars_l;
    while (temp) {
        std::cout << temp->val << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}
bool Dealership::contains(int val) const {
    Car* temp = cars_l;
    while (temp) {
        if (temp->val == val) return true;
        temp = temp->next;
    }
    return false;
}
int Dealership::size() const {
    int count = 0;
    Car* temp = cars_l;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

int main()
{
    Dealership d;

    d.buyCar(Car(10));
    d.buyCar(Car(20));
    d.buyCar(Car(30));
    assert(d.size() == 3);
    assert(d.contains(10));
    assert(d.contains(20));
    assert(d.contains(30));
    assert(!d.contains(40));
    d.display();

    d.sellCar(Car(20));
    assert(d.size() == 2);
    assert(!d.contains(20));
    d.display();

    d.sellCar(Car(10));
    assert(d.size() == 1);
    assert(!d.contains(10));
    d.display();

    d.sellCar(Car(40)); // not in list
    assert(d.size() == 1);
    d.display();

    d.sellCar(Car(30));
    assert(d.size() == 0);
    assert(!d.contains(30));
    d.display();

    return 0;
}
