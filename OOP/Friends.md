### Access Specifiers
Access Specifiers controls how the data specified inside a class can be accessed by class objects and functions. It implements data hiding in OOP.

- Public
    All the class members declared under the public specifier will be available to everyone. The data members and member functions declared as public can be accessed by other classes through *inheritence* and member functions too. The public members of a class can be accessed from anywhere in the program using the direct member access operator (.) with the object of that class.

- Private
    The class members declared as private can be accessed only by the member functions inside the class. They are not allowed to be accessed directly by any object or function outside the class. Only the member functions or the *friend functions* are allowed to access the private data members of a class. 

- Protected
    Protected access modifier is similar to private access modifier in the sense that it can’t be accessed outside of it’s class unless with the help of *friend class*, the difference is that the class members declared as Protected can be accessed by any subclass(*derived class*) of that class as well. 

### Friend Class 
A friend class can access private and protected members of the other class where it has been declared as a friend. For example, a LinkedList class may be allowed to access private members of Node. 

```cpp
class Node {
private:
    int key;
    Node* next;
    /* Other members of Node Class */
 
    // Now class  LinkedList can
    // access private members of Node
    friend class LinkedList;
};
```

### Friend Function
A friend function can be given a special grant to access private and protected members. A friend function can be: 

- A member of another class 
- A global function 

```cpp
class Node {
private:
    int key;
    Node* next;
 
    /* Other members of Node Class */
    friend int LinkedList::search();
    // Only search() of linkedList
    // can access internal members
};
```

##### Following are some important points about friend functions and classes: 

- Friends should be used only for limited purpose. too many functions or external classes are declared as friends of a class with protected or private data, it *lessens the value of encapsulation* of separate classes in object-oriented programming.
- Friendship is *not* *mutual*. If class A is a friend of B, then B doesn’t become a friend of A automatically.
- Friendship is *not* *inherited* 
- The concept of friends is not there in *Java*.

```cpp
#include <iostream>
 
class B;
 
class A {
public:
    void showB(B&);
};
 
class B {
private:
    int b;
 
public:
    B() { b = 0; }
    friend void A::showB(B& x); // Friend function
};
 
void A::showB(B& x)
{
    // Since showB() is friend of B, it can
    // access private members of B
    std::cout << "B::b = " << x.b;
}
 
int main()
{
    A a;
    B x;
    a.showB(x);
    return 0;
}

```

*Can we access private data members of a class without using a member or a friend function?*

Yes, through pointers.

```cpp
#include <bits/stdc++.h>
using namespace std;
  
class A {
private:
    int x;
    int y;
};
  
int main()
{
    A a;
    int* p = (int*)&a;
    *p = 3;
    p++;
    *p = 9;
    p--;
    cout << endl
         << "x = " << *p;
    p++;
    cout << endl
         << "y = " << *p;
}
```

In the above program, a is an object of class A. The address of the object is assigned to integer pointer p by applying typecasting. The pointer p points to private member x. Integer value is assigned to *p, that is, x. Address of object a is increased and by accessing the memory, location value 9 is assigned to y.

The idea of making private members is to avoid accidental changes. The above change to data is not accidental. It’s an intentionally written code to fool the compiler.