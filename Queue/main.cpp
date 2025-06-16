#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;

/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;

void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}

int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}

int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called" ;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
    //freopen("test_input_1.txt", "r", stdin); // Test Case 1
    freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // cout << "File redirection done." << endl;
    // Initialize the random generator with a fixed seed
    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);
    int timestamp[10001] = {0};

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;

    bool merged = false;
    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        int type;
        cin >> type;

        cout << "Operation " << i << " (";

        switch (type)
        {
        case 1:
        {
            /// int randqueue = randomQueue();
            int id, ts;
            cin >> id >> ts;
            cout << "Arrival " << id << " " << ts << "): " ;

            timestamp[id] = ts;
            if (merged)
            {
                //cout << "Enqueueing to Q: " << id << endl;
                Q->enqueue(id);
                //cout<< endl;
            }
            else
            {
                if (Q1->empty() && Q2->empty() && Q->empty())
                {
                    //cout << "Enqueueing to Q1 or Q2: " << id << endl;
                    int choice = randomQueue();

                    if (choice == 1)
                        Q1->enqueue(id);
                    else
                        Q2->enqueue(id);
                    //cout << endl;
                }

                else if (Q1->empty())
                    Q1->enqueue(id);

                else if (Q2->empty())
                    Q2->enqueue(id);
                else
                {
                    int id1 = Q1->back();
                    int id2 = Q2->back();

                    if (timestamp[id1] < timestamp[id2])
                        Q1->enqueue(id);
                    else
                        Q2->enqueue(id);
                }
            }
            cout << endl;
        }
        break;
        case 2:
        {
            int id, ts;
            cin >> id >> ts;
            cout << "Leave " << id << " " << ts << "): " << endl;

            if (!Q->empty())
            {
                int sz = Q->size();
                for (int j = 0; j < sz; j++)
                {
                    int front = Q->dequeue();
                    if (front != id)
                        Q->enqueue(front);
                }
            }
            else
            {
                int sz1 = Q1->size();
                for (int j = 0; j < sz1; j++)
                {
                    int front = Q1->dequeue();
                    if (front != id)
                        Q1->enqueue(front);
                }

                int sz2 = Q2->size();
                for (int j = 0; j < sz2; j++)
                {
                    int front = Q2->dequeue();
                    if (front != id)
                        Q2->enqueue(front);
                }
            }
        }
        break;
        case 3:
        {
            cout << "Merge): " << endl;
            merged = true;
            while (!Q1->empty() || !Q2->empty())
            {
                if (Q1->empty())
                {
                    Q->enqueue(Q2->dequeue());
                }
                else if (Q2->empty())
                {
                    Q->enqueue(Q1->dequeue());
                }
                else
                {
                    int id1 = Q1->front();
                    int id2 = Q2->front();

                    if (timestamp[id1] < timestamp[id2])
                    {
                        Q->enqueue(Q1->dequeue());
                    }
                    else
                    {
                        Q->enqueue(Q2->dequeue());
                    }
                }
            }
        }
        break;

        case 4:
        {
            cout << "Split): " << endl;
            merged = false;
            if (!Q->empty())
            {
                int sz = Q->size();
                for (int i = 0; i < sz; i++)
                {
                    int id = Q->dequeue();
                    if (i % 2 == 0)
                        Q1->enqueue(id);
                    else
                        Q2->enqueue(id);
                }
            }
        }
        break;
        case 5:
        {
            cout << "Departure): " ;
            ;

            if (!Q->empty())
            {
                Q->dequeue();
            }
            else
            {
                if (!Q1->empty() && !Q2->empty())
                {
                    int choice = randomQueue();
                    if (choice == 1)
                        Q1->dequeue();
                    else
                        Q2->dequeue();
                }
                else if (!Q2->empty())
                    Q2->dequeue();
                else if (!Q1->empty())
                    Q1->dequeue();
            }
            cout <<endl;
        }
        break;
        default:
            break;
        }
        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
        cout << "Q1: " << Q1->toString() << endl;
        cout << "Q2: " << Q2->toString() << endl;
        cout << "Q : " << Q->toString() << endl;
    }
    delete Q;
    delete Q1;
    delete Q2;

    return 0;
}