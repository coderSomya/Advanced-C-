#include <iostream>
using namespace std;

template <typename T>

class sharedptr
{

private:
    T *res;
    int *counter;

    void incrementcounter()
    {
        if (counter)
        {
            (*counter)++;
        }
    }

    void decrementcounter()
    {
        if (counter)
        {
            (*counter)--;

            if ((*counter) == 0)
            {
                if (res)
                {
                    delete res;
                    delete counter;
                    res = nullptr;
                    counter = nullptr;
                }
            }
        }
    }

public:
    sharedptr(T *pt = nullptr) : res(ptr), counter(new int(1))
    {
        cout << "created\n";
    }

    sharedptr<T>(const sharedptr<T> &ptr)
    {
        res = ptr.res;
        counter = ptr.counter;
        incrementcounter();
    }

    sharedptr<T>(const sharedptr<T> &&ptr)
    {
        res = ptr.res;
        counter = ptr.counter;

        ptr.res = nullptr;
        ptr.counter = nullptr;
    }

    sharedptr<T> operator=(sharedptr<T> &&ptr)
    {
        if (this != &ptr)
        {
            decrementcounter();
            this.res = ptr.res;
            this.counter = ptr.counter;

            ptr.res = nullptr;
            ptr.counter = nullptr;
        }
    }

    sharedptr<T> &operator=(const sharedptr<T> &ptr)
    {
        if (this != &ptr)
        {
            decrementcounter();
            res = ptr.res;
            counter = ptr.counter;
            incrementcounter();
        }

        return *this
    }

    void reset(T *ptr)
    {
        decrementcounter();
        res = ptr.res;
        counter = new int(1);
    }

    int get_count()
    {
        if (counter)
        {
            return (*counter);
        }
        return -1;
    }

    T *operator->()
    {
        return res;
    }

    T &operator*()
    {
        return *res;
    }

    T *get()
    {
        return res;
    }

    ~sharedptr()
    {
        decrementcounter();
    }
};

int main()
{
    sharedptr<int> ptr1;
    sharedptr<int> ptr2(new int(2));

    sharedptr<int> ptr3(ptr1);
    ptr3 = ptr2;
    sharedptr<int> ptr4(std::move(ptr2));

    ptr1.reset(new int(10));
    ptr1.reset(new int(20));

    cout << (*ptr1);
    // ptr1->func();

    ptr1.get();

    ptr1.get_count(); // number of objects pointing to the same resource
}