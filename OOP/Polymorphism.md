# Polymorphism

It is the ability of representing the same data in more than one forms. . A real-life example of polymorphism, a person at the same time can have different characteristics. Like a man at the same time is a father, a husband, an employee.


### Types of Polymorphism:
- #### **Compile-time**
    This type of polymorphism is achieved by function overloading or operator overloading.

    1. *Function Overloading*
       When there are multiple functions with same name but different parameters then these functions are said to be overloaded. Functions can be overloaded by change in number of arguments or/and change in type of arguments.

       ```cpp
       class Geeks
        {
            public:
            
            // function with 1 int parameter
            void func(int x)
            {
                cout << "value of x is " << x << endl;
            }
            
            // function with same name but 1 double parameter
            void func(double x)
            {
                cout << "value of x is " << x << endl;
            }
            
            // function with same name and 2 int parameters
            void func(int x, int y)
            {
                cout << "value of x and y is " << x << ", " << y << endl;
            }
        };
       ``` 

        *Functions that cannot be overloaded in C++*

        1. Function declarations that differ only in the return type.
        
        2. Member function declarations with the same name and the name parameter-type-list cannot be overloaded if any of them is a static member function declaration.

        3. Parameter declarations that differ only in the presence or absence of const and/or volatile are equivalent. That is, the const and volatile type-specifiers for each parameter type are ignored when determining which function is being declared, defined, or called.

        Only the const and volatile type-specifiers at the outermost level of the parameter type specification are ignored in this fashion; const and volatile type-specifiers buried within a parameter type specification are significant and can be used to distinguish overloaded function declarations. 
        
        *In particular, for any type T,*
        
        “pointer to T,” “pointer to const T,” and “pointer to volatile T” are considered distinct parameter types, as are “reference to T,” “reference to const T,” and “reference to volatile T.” 


        4. ```cpp
            int fun(int *ptr);
            int fun(int ptr[]); // redeclaration of fun(int *ptr)
           ```
        
        5. Two parameter declarations that differ only in their default arguments are equivalent.



    2. *Operator Overloading*
       
       C++ also provide option to overload operators. For example, we can make the operator (‘+’) for string class to concatenate two strings.

       ```cpp
        class Complex {
        private:
            int real, imag;
        public:
            Complex(int r = 0, int i =0)  {real = r;   imag = i;}
            
            // This is automatically called when '+' is used with
            // between two Complex objects
            Complex operator + (Complex const &obj) {
                Complex res;
                res.real = real + obj.real;
                res.imag = imag + obj.imag;
                return res;
            }
            void print() { cout << real << " + i" << imag << endl; }
            friend Complex operator + (Complex const &, Complex const &);
        };
        
        Complex operator + (Complex const &c1, Complex const &c2) {
            return Complex(c1.real + c2.real, c1.imag + c2.imag);
        }

        int main() {
            Complex c1(10, 5), c2(2, 4);
            Complex c3 = c1 + c2; // An example call to "operator+"
            c3.print();
        }
       ```

       *What is the difference between operator functions and normal functions?*
       The only differences are, name of an operator function is always operator keyword followed by symbol of operator and operator functions are called when the corresponding operator is used.


       *Can we overload all operators?*       
        Almost all operators can be overloaded except few- '.', '::', '?:', 'sizeof';

       *Important points about operator overloading*
       1)  For operator overloading to work, at least one of the operands must be a user defined class object.
       2)  Assignment Operator: Compiler automatically creates a default assignment operator with every class.
       3)  Conversion Operator: We can also write conversion operators that can be used to convert one type to another type. 


- #### **Run-time**
    This type of polymorphism is achieved by Function Overriding.

    **Function overriding** on the other hand occurs when a derived class has a definition for one of the member functions of the base class. That base function is said to be overridden.

    ```cpp

    class base
    {
    public:
        virtual void print ()
        { cout<< "print base class" <<endl; }
    
        void show ()
        { cout<< "show base class" <<endl; }
    };
    
    class derived:public base
    {
    public:
        void print () //print () is already virtual function in derived class, we could also declared as virtual void print () explicitly
        { cout<< "print derived class" <<endl; }
    
        void show ()
        { cout<< "show derived class" <<endl; }
    };
    
    //main function
    int main() 
    {
        base *bptr;
        derived d;

        // base pointer referenced to dervied class object
        bptr = &d;
        
        //virtual function, binded at runtime (Runtime polymorphism)
        bptr->print(); 
        // print derived class

        // Non-virtual function, binded at compile time
        bptr->show(); 
        // show base class

        return 0;
    } 

    ```
