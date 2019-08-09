#ifndef __VECTOR__H
#define __VECTOR__H

#include <algorithm>
#include <utility>

template<typename Object>
class Vector
{
public:
    explicit Vector(int init_size=0);
    Vector(const Vector& v);
    Vector& operator= (const Vector& v);

    Vector(Vector && v);
    Vector& operator= (Vector && v);

    ~Vector();

    void resize(int new_size);
    void reserve(int new_capacity);

    Object & operator[](int index);
    const Object& operator[](int index) const;

    inline bool empty() const { return 0 == size()}
    inline int size() const { return the_size; }
    inline int capacity() const { return the_capacity; }

    void pushBack(const Object& x);
    void pushBack(Object && x);

    void popBack();

    const Object& back() const;

    using iterator = Object *;
    using const_iterator = const Object *;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    static const int SPACE_CAPACITY = 16;

private:
    int the_size;
    int the_capacity;
    Object* m_objects;

};


#endif