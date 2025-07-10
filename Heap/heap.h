#pragma once
#include <string>
#include <cmath>
using namespace std;

class Heap
{
private:
    int *data = nullptr;
    int current_size = 0;
    int max_size = 0;

    int parent_idx(int idx) const
    {
        return ((idx - 1) / 2);
    }
    int left_child_idx(int idx) const
    {
        return 2 * idx + 1;
    }
    int right_child_idx(int idx) const
    {
        return 2 * idx + 2;
    }
    void compare_with_parent(int idx)
    {
        if (data[idx] > data[parent_idx(idx)])
        {
            swap(data[idx], data[parent_idx(idx)]);
            compare_with_parent(parent_idx(idx));
        }
    }
    void compare_with_child(int idx)
    {
        int left = left_child_idx(idx);
        int right = right_child_idx(idx);
        int large = idx;
        if (left < current_size && data[left] > data[large])
        {
            large = left;
        }
        if (right < current_size && data[right] > data[large])
        {
            large = right;
        }
        if (large != idx)
        {
            swap(data[idx], data[large]);
            compare_with_child(large);
        }
        else
        {
            return;
        }
    }

public:
    Heap(int max_size)
    {
        this->max_size = max_size;
        data = new int[max_size];
    }
    Heap(const vector<int> &numbers)
    {
        max_size = numbers.size();
        data = new int[max_size];
    }
    ~Heap()
    {
        delete[] data;
    }

    int size() const
    {
        return current_size;
    }

    void insert(int value)
    {
        if (current_size >= max_size)
        {
            cout << "heap is already full" << endl;
            return;
        }
        data[current_size] = value;
        current_size++;
        if (current_size > 1)
        {
            compare_with_parent(current_size - 1);
        }
    }

    int getMax() const
    {
        if (current_size == 0)
        {
            throw runtime_error("Heap is empty");
        }
        return data[0];
    }

    void deleteKey()
    {
        if (current_size == 0)
        {
            throw runtime_error("Heap is empty");
        }
        int item = data[0];
        data[0] = data[current_size - 1];
        current_size--;
        if (current_size > 1)
        {
            compare_with_child(0);
        }
    }
};

void heapsort(vector<int> &v)
{
    int originsize = v.size();
    Heap h(originsize);
    // int *soretedata = new int[originsize];
    for (int i = 0; i < originsize; i++)
    {
        h.insert(v[i]);
    }
    v.clear();
    for (int i = 0; i < originsize; i++)
    {
        v.push_back(h.getMax());
        h.deleteKey();
    }
}