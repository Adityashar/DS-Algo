# Virtual Functions

- A member function which is declared in the base class as *virtual* and redefined in a derived class.
- Virtual functions allow us to create a list of base class pointers and call methods of any of the derived classes without even knowing kind of derived class object. 

### Rules for Virtual Functions

1. Virtual functions cannot be static.
2. A virtual function can be a friend function of another class.
3. Virtual functions should be accessed using pointer or reference of base class type to achieve run time polymorphism.
4. The prototype of virtual functions should be the same in the base as well as derived class.
5. They are always defined in the base class and overridden in a derived class. It is not mandatory for the derived class to override (or re-define the virtual function), in that case, the base class version of the function is used.
6. A class may have virtual destructor but it cannot have a virtual constructor.

```cpp
class base {
public:
    virtual void print()
    {
        cout << "print base class" << endl;
    }
 
    void show()
    {
        cout << "show base class" << endl;
    }
};
 
class derived : public base {
public:
    void print()
    {
        cout << "print derived class" << endl;
    }
 
    void show()
    {
        cout << "show derived class" << endl;
    }
};
 
int main()
{
    base* bptr;
    derived d;
    bptr = &d;
 
    // virtual function, binded at runtime
    bptr->print();
 
    // Non-virtual function, binded at compile time
    bptr->show();
}

```

#### **Explanation:**
Runtime polymorphism is achieved only through a pointer (or reference) of base class type. Also, a base class pointer can point to the objects of base class as well as to the objects of derived class. In above code, base class pointer ‘bptr’ contains the address of object ‘d’ of derived class.

Late binding(Runtime) is done in accordance with the content of pointer (i.e. location pointed to by pointer) and Early binding(Compile time) is done according to the type of pointer, since print() function is declared with virtual keyword so it will be bound at run-time (output is print derived class as pointer is pointing to object of derived class ) and show() is non-virtual so it will be bound during compile time(output is show base class as pointer is of base type ).


#### **Working of virtual functions**(concept of VTABLE and VPTR)
If a class contains a virtual function then compiler itself does two things: 
 
If object of that class is created then a virtual pointer(VPTR) is inserted as a data member of the class to point to VTABLE of that class. For each new object created, a new virtual pointer is inserted as a data member of that class.

Irrespective of object is created or not, a static array of function pointer called VTABLE where each cell contains the address of each virtual function contained in that class.
