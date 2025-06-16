#include "queue.h"
#include <iostream>
using namespace std;

int main() {
    ArrayQueue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Queue: " << q.toString() << endl;
    cout << "Front: " << q.front() << endl;
    cout << "Back: " << q.back() << endl;

    q.dequeue();
    cout << "After dequeue: " << q.toString() << endl;

    return 0;
}
