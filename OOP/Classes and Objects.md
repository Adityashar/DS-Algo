# Classes and Objects

### Class
It is a user-defined data type, which holds its own data members and member functions, which can be accessed and used by creating an instance of that class.

Data members are the data variables and member functions are the functions used to manipulate these variables and together these data members and member functions defines the properties and behavior of the objects in a Class.


#### Example:
Consider the Class of Cars. There may be many cars with different names and brand but all of them will share some common properties like all of them will have 4 wheels, Speed Limit, Mileage range etc. So here, Car is the class and wheels, speed limits, mileage are their properties.



### Object
An Object is an instance of a Class. When a class is defined, no memory is allocated but when it is instantiated memory is allocated.

*Accessing data members and member functions*: The data members and member functions of class can be accessed using the dot(‘.’) operator with the object. 


#### Member Functions
There are 2 ways to define a member function:

- Inside class definition
- Outside class definition

```cpp
#include <bits/stdc++.h>
using namespace std;
class Geeks
{
    public:
    string geekname;
    int id;
     
    // printname is not defined inside class definition
    void printname();
     
    // printid is defined inside class definition
    void printid()
    {
        cout << "Geek id is: " << id;
    }
};
 
// Definition of printname using scope resolution operator ::
void Geeks::printname()
{
    cout << "Geekname is: " << geekname;
}
int main() {
     
    Geeks obj1;
    obj1.geekname = "xyz";
    obj1.id=15;
     
    // call printname()
    obj1.printname();
    cout << endl;
     
    // call printid()
    obj1.printid();
    return 0;
}
```


#### Constructors
- Constructors are special class members which are called by the compiler every time an object of that class is instantiated. 
- Constructors have the same name as the class and may be defined inside or outside the class definition.

There are 3 types of constructors: Default constructors, Parameterized constructors, Copy constructors.

```cpp
#include <bits/stdc++.h>
using namespace std;
class Geeks
{
    public:
    int id;
     
    //Default Constructor
    Geeks()
    {
        cout << "Default Constructor called" << endl;
        id=-1;
    }
     
    //Parameterized Constructor
    Geeks(int x)
    {
        cout << "Parameterized Constructor called" << endl;
        id=x;
    }
};
int main() {
     
    // obj1 will call Default Constructor
    Geeks obj1;
    cout << "Geek id is: " <<obj1.id << endl;
     
    // obj1 will call Parameterized Constructor
    Geeks obj2(21);
    cout << "Geek id is: " <<obj2.id << endl;
    return 0;
}
```


#### Destructors
Destructor is another special member function that is called by the compiler when the scope of the object ends.

```cpp
#include <bits/stdc++.h>
using namespace std;
class Geeks
{
    public:
    int id;
     
    //Definition for Destructor
    ~Geeks()
    {
        cout << "Destructor called for id: " << id <<endl;
    }
};
 
int main()
  {
    Geeks obj1;
    obj1.id=7;
    int i = 0;
    while ( i < 5 )
    {
        Geeks obj2;
        obj2.id=i;
        i++;       
    } // Scope for obj2 ends here
 
    return 0;
  }
```

