# Inheritance

The capability of a class (*Sub Class*) to derive properties and characteristics from another class (*Super Class*) is called Inheritance.

*Why and when to use inheritance*? To reduce the chances of error and data redundancy.

*Implementing inheritance in C++*: For creating a sub-class which is inherited from the base class we have to follow the below syntax. 

```cpp
class subclass_name : access_mode base_class_name
{
  //body of subclass
};
```

*Note*: A derived class doesn’t inherit access to private data members. However, it does inherit a full parent object, which contains any private members which that class declares.


### Modes of Inheritance
- *Public mode*: If we derive a sub class from a public base class, then the public member of the base class will become public in the derived class and protected members of the base class will become protected in derived class.
- *Protected mode*: If we derive a sub class from a Protected base class, then both public member and protected members of the base class will become protected in derived class.
- *Private mode*: If we derive a sub class from a Private base class, then both public member and protected members of the base class will become Private in derived class. 


```cpp
class A
{
public:
    int x;
protected:
    int y;
private:
    int z;
};
 
class B : public A
{
    // x is public
    // y is protected
    // z is not accessible from B
};
 
class C : protected A
{
    // x is protected
    // y is protected
    // z is not accessible from C
};
 
class D : private A    // 'private' is default for classes
{
    // x is private
    // y is private
    // z is not accessible from D
};
```



### Types of Inheritance
1. Single Inheritance: In single inheritance, a class is allowed to inherit from only one class. i.e. one sub class is inherited by one base class only.
   
2. Multiple Inheritance: Multiple Inheritance is a feature of C++ where a class can inherit from more than one classes. i.e one sub class is inherited from more than one base classes.
   ```cpp
    class Vehicle {
    public:
        Vehicle()
        {
        cout << "This is a Vehicle" << endl;
        }
    };
    
    // second base class
    class FourWheeler {
    public:
        FourWheeler()
        {
        cout << "This is a 4 wheeler Vehicle" << endl;
        }
    };
    
    // sub class derived from two base classes
    class Car: public Vehicle, public FourWheeler {
    
    };
   ```

3. Multilevel Inheritance: In this type of inheritance, a derived class is created from another derived class.

    ```cpp
    class Vehicle
    {
    public:
        Vehicle()
        {
        cout << "This is a Vehicle" << endl;
        }
    };
    
    // first sub_class derived from class vehicle
    class fourWheeler: public Vehicle
    {  public:
        fourWheeler()
        {
        cout<<"Objects with 4 wheels are vehicles"<<endl;
        }
    };
    // sub class derived from the derived base class fourWheeler
    class Car: public fourWheeler{
    public:
        Car()
        {
        cout<<"Car has 4 Wheels"<<endl;
        }
    };
    ```

4. Hierarchical Inheritance: In this type of inheritance, more than one sub class is inherited from a single base class. i.e. more than one derived class is created from a single base class.

    ```cpp
    // base class
    class Vehicle
    {
    public:
        Vehicle()
        {
        cout << "This is a Vehicle" << endl;
        }
    };
    
    
    // first sub class
    class Car: public Vehicle
    {
    
    };
    
    // second sub class
    class Bus: public Vehicle
    {
        
    };
    ```

5. Hybrid (Virtual) Inheritance: Hybrid Inheritance is implemented by combining more than one type of inheritance. For example: Combining Hierarchical inheritance and Multiple Inheritance.
    
6.  A special case of hybrid inheritance : Multipath inheritance: 
A derived class with two base classes and these two base classes have one common base class is called multipath inheritance. An ambiguity can arrise in this type of inheritance. 

    ```cpp
    class ClassA {
    public:
        int a;
    };
    
    class ClassB : public ClassA {
    public:
        int b;
    };
    class ClassC : public ClassA {
    public:
        int c;
    };
    
    class ClassD : public ClassB, public ClassC {
    public:
        int d;
    };
    ```
Both ClassB & ClassC inherit ClassA, they both have single copy of ClassA. However ClassD inherit both ClassB & ClassC, therefore ClassD have **two copies of ClassA**, one from ClassB and another from ClassC. 

If we need to access the data member a of ClassA through the object of ClassD, we must specify the path from which a will be accessed, whether it is from ClassB or ClassC, **bco’z compiler can’t differentiate between two copies of ClassA in ClassD**.



#### There are 2 ways to avoid this ambiguity: 
- **Avoiding ambiguity using scope resolution operator:**
  ```cpp
  obj.ClassB::a = 10;        //Statement 3
  obj.ClassC::a = 100; 
  ```

- **Avoiding ambiguity using virtual base class:**

  ```cpp
    class ClassA
     {
            public:
            int a;
     };
 
     class ClassB : virtual public ClassA
     {
            public:
            int b;
     };
     class ClassC : virtual public ClassA
     {
            public:
            int c;
     };
 
     class ClassD : public ClassB, public ClassC
     {
            public:
            int d;
     };
  ```
  


