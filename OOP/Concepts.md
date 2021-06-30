# OOP

## Languages

- Machine Language
- Assembly Language
- Structured Programming Language
- Procedural Programming Language
- Object Oriented Programming

### Machine Language

Low level programming language represented with the help of binary format, hexadecimal and octadecimal.

Fast Execution since no translation is needed and the data is already in the machine readable format, but difficult to understand and is hardware dependent.

### Assembly Language

Assembly language is machine-dependent, but the mnemonics used to represent instructions in it are not directly understandable by machine and are architecture dependent.

Error debugging and fixing is possible in assembly language.

#### - Compilers
  
  It translates the source code of a high level language into a machine readable object code which is executed when error free.

  High memory requirements and large amount of time is needed to analyse the whole source code though much lower execution time.

#### - Assemblers
  
  It translates the assembly code into machine code. It is the first interface between the machines and the humans. 

#### - Interpreters
  
  Statement-wise translation of the source code into machine code, done by the language processor, and execution just before moving to the next line.
  
  Immediate termination at the line where the error occured, and no intermediary formation i.e the object code.
  
  Simplified debugging with lower memory needs though is slightly vulnerable when it comes to security.


### Structured Programming

The program is divided into functions and modules to make the code more readable and understandable, giving more importance to functions than data. It focuses on the development of large software applications. PASCAL and C.

### Procedural Programming Approach

Top down approach where the program is divided into functions that perform specific tasks. The data is global and all the functions can access global data. Hence, the data is not secure.

Program control and flow is achieved through function calls and goto statements. Medium sized applications. Eg FOTRAN and COBOL. 

Such programming constructs are over-generalised and do not correlate with real-time applications

### Object Oriented Programming

OOP aims to implement real-world entities like inheritance, hiding, polymorphism etc in programming. 

The main aim of OOP is to bind together the data and the functions that operate on them so that no other part of the code can access this data except that function.

#### Some important points to know about OOP:

- OOP treats data as a critical element.
- Emphasis is on data rather than procedure.
- Decomposition of the problem into simpler modules.
- Doesn’t allow data to freely flow in the entire system, ie localized control flow.
- Data is protected from external functions.

#### Disadvantages of OOP –

- With OOP, classes sometimes tend be over-generalised.
- The relations among classes become superficial at times.
- The OOP design is tricky and requires appropriate knowledge. Also, one needs to do proper planning and design for OOP programming.
- To program with OOP, the programmer needs proper skills such as that of design, programming and thinking in terms of objects and classes etc.

#### Class
These are user-defined datatypes which holds its own data members and member functions which define the properties and behaviour of the objects in a class.

Objects are identifiable entities with some property or characteristic used to define an instance of a class. Each object takes up space in the memory and has a reference similar to a structure in C.



#### Encapsulation
This is the wrapping up of data and information into a single unit or the binding togerther of data and functions in OOP.

Consider a real-life example of encapsulation, in a company, there are different sections. In encapsulation, the data of the sales section and the employees that can manipulate them are wrapped under a single name “sales section”.

Encapsulation also leads to data abstraction or hiding. As using encapsulation also hides the data.



#### Abstraction
Abstraction means displaying only essential information and hiding the details such as implementation.

Consider a real-life example of a man driving a car. The man only knows that pressing the accelerators will increase the speed of the car or applying brakes will stop the car but he does not know about the inner mechanism of the car or the implementation of accelerator, brakes etc in the car. 

- Abstraction using Classes through "Access Specifiers"
- Abstraction using Header Files



#### Data Hiding
Data hiding is a software development technique specifically used in object-oriented programming (OOP) to hide internal object details (data members). Data hiding ensures exclusive data access to class members and protects object integrity by preventing unintended or intended changes.



#### Polymorphism
It is the ability of representing the same data in multiple forms. An operation may exhibit different behaviours in different instances. The behaviour depends upon the types of data used in the operation.

- Operator Overloading: The process of making an operator to exhibit different behaviours in different instances is known as operator overloading.
- Function Overloading: Function overloading is using a single function name to perform different types of tasks. 



#### Inheritance
The capability of a class to derive properties and characteristics from another class is called Inheritance.

- Sub Class
- Super Class

Inheritance supports the concept of *“reusability”*, i.e. when we want to create a new class and there is already a class that includes some of the code that we want, we can derive our new class from the existing class.



#### Dynamic Binding
In dynamic binding, the code to be executed on a function call is decided at runtime. Eg. Virtual Functions and Virtual classes support this.



#### Message Passing
Objects communicate with one another by sending and receiving information to each other. A message for an object is a request for execution of a procedure and therefore will invoke a function in the receiving object that generates the desired results.

Message passing involves specifying the name of the object, the name of the function and the information to be sent.



#### The basic thing which are the essential feature of an object oriented programming are Inheritance, Polymorphism and Encapsulation. 

##### Here are the reasons C++ is called partial or semi Object Oriented Language:

1. *Main function is outside the class* : C++ supports object-oriented programming, but OO is not intrinsic to the language. You can write a valid, well-coded, excellently-styled C++ program without using an object even once.
In C++, main function is mandatory, which executes first but it resides outside the class and from there we create objects. So, here creation of class becomes optional and we can write code without using class.
While in JAVA, main function is executed first and it reside in the class which is mandatory. So, we can’t do anything without making Class. 

2. *Concept of Global variable* : In C++, we can declare a variable globally, which can be accessible from anywhere and hence, it does not provides complete privacy to the data as no one can be restricted to access and modify those data and so, it provides encapsulation partially whereas In JAVA, we can declare variable inside class only and we can provide access specifier to it.

3. *Availability of Friend function*: Friend Class A friend class can access private and protected members of other class in which it is declared as friend. It is sometimes useful to allow a particular class to access private members of other class.