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
template<typename Object>
Vector<Object>::Vector(int init_size):the_size(init_size),
    the_capacity(init_size+SPACE_CAPACITY)
{
    m_objects = new Object[the_capacity];
}

template<typename Object>
Vector<Object>::~Vector()
{
    delete [] m_objects;
}

/*
copy
 */
template<typename Object>
Vector<Object>::Vector(const Vector& v):the_size(v.the_size),
    the_capacity(v.the_capacity), m_objects(nullptr)
{
    m_objects = new Object[the_capacity];
    for(int k = 0; k<the_size;++k)
    {
        m_objects[k]=v.m_objects[k];
    }
}

template<typename Object>
Vector<Object>&
Vector<Object>::operator=(const Vector& v)
{
    Vector<Object> copy_v = v;
    std::swap(*this, copy_v);
    return *this;
}


/*
move
 */
template<typename Object>
Vector<Object>::Vector(Vector&& v):the_size(v.the_size),
    the_capacity(v.the_capacity), m_objects(v.m_objects)
{
    v.m_objects = nullptr;
    v.the_size = 0;
    v.the_capacity = 0;
}

template<typename Object>
Vector<Object>&
Vector<Object>::operator= (Vector&& v)
{
    std::swap(the_size, v.the_size);
    std::swap(the_capacity, v.the_capacity);
    std::swap(m_objects, v.m_objects);
    
    return *this;
}

template<typename Object>
void Vector<Object>::reserve(int new_capacity)
{
    if(new_capacity < the_size) // needn't reserve
    {
        return;
    }

    Object* new_array = new Object[new_capacity];

    for(int i = 0; i<the_size; ++i)
    {
        new_array[i] = std::move(m_objects[i]);
    }

    the_capacity = new_capacity;
    std::swap(m_objects, new_array);

    delete[] new_array; 
}


template<typename Object>
Object& Vector<Object>::operator[] (int index)
{
    return m_objects[index];
}

template<typename Object>
const Object& Vector<Object>::operator[](int index) const
{
    return m_objects[index];
}

template<typename Object>
void Vector<Object>::pushBack(const Object& x)
{
    if(the_size == the_capacity)
    {
        reserve(2*the_capacity+1);
    }
    m_objects[the_size++] = x;
}

template<typename Object>
void Vector<Object>::pushBack(Object&& x)
{
    if(the_size == the_capacity)
    {
        reserve(2*the_capacity+1);
    }
    m_objects[the_size++] = std::move(x);
}


template<typename Object>
void Vector<Object>::popBack()
{
    --the_size;
}

template<typename Object>
const Object& Vector<Object>::back() const
{
    return m_objects[the_size-1];
}

template<typename Object>
Vector<Object>::iterator Vector<Object>::begin()
{
    return &m_objects[0];
}

template<typename Object>
Vector<Object>::const_iterator Vector<Object>::begin() const
{
    return &m_objects[0];
}

template<typename Object>
Vector<Object>::iterator Vector<Object>::end()
{
    return &m_objects[size()];
}

template<typename Object>
Vector<Object>::const_iterator Vector<Object>::end() const
{
    return &m_objects[size()];
}

#endif
