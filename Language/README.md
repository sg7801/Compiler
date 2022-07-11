# Language Specifications :
The language contains 94 Grammar rules which are constructued from 51 non-terminal (including "$") and 58 Terminal characters.

## Lexical Structure :

### Keywords :
- An identifier is defined as the sequence of underscore, letters or digits with atmost length 8 characters. They are represented as ID & are separated from keywords through white space.
- The language is case-sensitive. 
- The token WHILE is not same as keyword while.

The list of reserved key words used in the language are as follows:

- while <br>
- default <br>
- break <br>
- case <br>
- switch <br>
- in<br>
- AND<br>
- OR<br>
- for <br>
- true<br>
- false<br>
- return<br>
- takes<br>
- input<br>
- print<br>
- use<br>
- with<br>
- parameters
- declare<br>
- module<br>
- driver<br>
- program<br>
- get_value<br>
- start<br>
- end<br>
- array<br>
- integer<br>
-  real<br>
- boolean<br>
- of

### Comments : 
- The comments in the language start with ** and end with **. 
- Tokens are separated by using blank spaces or tabs or new line characters. 
- Keywords and identifiers are separated by tokens or white spaces.

### Numerical Values :
- Integer : Sequence of digits tokenised as NUM.
- Floating Point Numbers : Sequence of digits followed by decimal point. The datatype is real & tokenised as RNUM. They are represented in the exponent and mantissa form. Notation of exponent can be in uppercase or lowercase with/without signs. They cannot start with decimal,hence .12E2 would be invalid.

### Operators :
- Arithmetic operators are +, -, /, * with their conventional meanings respectively. 
- Relational operators are <, >, <=, >=, ==, != have their conventional meaning respectively.
- Logical Operators are AND and OR in uppercase. They have their conventional meaning respectively.
- Assignment Operator := is tokenised as ASSIGNOP.
- Special Characters like .. represent the range operator that represents the range of an array. Example : arr[1..3]

### Symbols: 
-	AND
- OR
-	NOT
-	true
-	false
- (
- ..
- )
- {
- }
- [
- ]
- ;
- :
- _
- .
- '
- ,
- =
- ==
-	!=
- \>
-	\>=
-	\<
-	\<=
-	\+
-	\-
-	\*
-	\/
-	%
-	**
-	~
-	^
-	|
-	&
-	\>>
-	\>>>
-	\<<

## Features :
- The language is implemented using various data structures, is fully functional and robust. 
- Functions can return multiple values. It also might happen that function do not return any value.
- It cannot generate the code for multiple modules.

### Data Types :
- It is capable of handling the Integer, Real and Boolean primitive data types. 
- Boolean type can have true or false.
- Single dimentional array where index range is represented by range operator ..

### Size of Data Types :
- Integer data type is stored by taking size of 2 bytes
- Real data type is stored by taking size of 4 bytes 
- Boolean data type is stored by taking size of 1 byte

### Expressions :
- Expressions are either arithmetic or boolean type.
- Precedence of similar operations is same like that or plus/minus. Paranthesis have highest precedence. 
- True and false are not same as 1 and 0.
- Relational operators can be used to combine sub-expressions and form the final expression.

### Statements :
- It supports the simple, input/output statements , declarative statements, conditional & iterative statements.
- Simple statements have left and right side values/identifiers that should have same data type. The right side's value is assigned to left side's identifier or element.
```Syntax :  <left_hand_value> := <right_hand_expression>;```
- Input statements : Read value from the keyboard and store in variable
```get_value({identifier})```
- Output statements : These write the variables on the console.
```print({identifier})```
- Declarative statements can appear anywhere in the program. They can be used anywhere in their scope. Multiple declarations are not supported. An identifier must be declared before its use in program.
  ```Syntax : declare {identifier_list} : primitive_data_type;```
- Conditional Statements supported by the language are switch statements. Real type cannot form switch statements. Boolean type switch statements can have TRUE or FALSE values. Any number of case statements can be there, separated by break statement & must be followed by default statement. The type of all switch statements must be same else error is generated
  Syntax:
```
switch({identifier})
start
      case {value} : <statements S1>;
                   break;
      case {value} : <statements S2>;
                   break;
      default : <statements S3>; 
                  break;
end
```
- **Iterative statements** :
- For Loop : The statement must not re-declare the variable in the scope.
```
for({identifier} in {low_range}..{high_range})
start
            <statements>
end
```
  - While Loop :
```
while({boolean expression})
start
            <statements>
end
```

### Functions :

- The functions can either return a value or not return value. 
  - For functions returning values the syntax is : ```[return_list] := {function_name}{parameter_list};```
  - For functions not returning values the syntax is : ```{function_name} {parameter_list};```
- Functions can also return multiple values. 
- The type and the parameters of any function must be equal to those used while calling it.
- Parameters returned by it must have some value assigned to them.
- Function is a modular implementation allowing parameter passing by value for all types of variables. They only pass the parameters by reference for arrays.

Syntax :
```
<<module {function_name}>>
takes input [{input_parameter_list}];
returns [{return_parameter_list}];
start
            <function body>
end
```
- Function declaration refers to the declaration of prototype.
- Function call must follow the declaration or definition of the function.
Syntax : ```declare module {function_name};```

## Semantic and Type Checking :
Several rules are followed while checking the type and the semantics of the language :

### Semantic Rules :
- Identifiers cannot have multiple declarations within same scope. However, if declared globally then they can be re-declared anywhere else in new scope.
- Identifiers have to be declared in the same scope or parent's scope to be used.
- Overloading procedures is not supported.
- Recurisve calls to procedures are not supported.
- Left and right sides of assignment statements must have same data types.
- Number of prameters and their types must be same in function definition and function call must be same.

### Type Checking :
- Data type of a variable during declaration is taken as the final type of that variable.
- The type of any identifier or any expression is computed with the help of traversal of the generated Abstract Syntax Tree.
- In case of any expression of syntax : **\<Expression> OPERATOR \<Expression>** :
  - The result is of type Integer if both expressions are of type Integer and the operator is an arithmetic operator.
  - The result is of type Boolean if both expressions are of type Integer and the operator is a relational operator.
  - The result is of type Real if both expressions are of type Real and the operator is an arithmetic operator.
  
**Errors are generated and printed on the console if any of the above fails.**

## Semantic Checking in Code :
- **Undeclared Variables** - When the lookup in the symbol table is not found.
- **Multiple Declarations** - While creating the symbol table, we check if the symbol is found in lookup.
- **Overloading Modules** - While creating the symbol table if the entry to that module is found then module is overloaded.
- **Type & number of input/output parameters** - Each input/output parameter us looked up in the symbol table.
- **Function calls** - The number & types of input/output parameters are checked from symbol table.
- **Conditional Statements** : The assignment of the loop iterating variable is checked by traversing each statement of the loop. We traverse each case node & check if they are according to the rules.
  - While statements : For a while loop, the conditon expression must evaluate to boolean type.
  - For statements : In a for loop, the identifier must be of type INTEGER.
  - Switch statements : The conditional expression cannot be real.
- **Static Type Checking** - The size of arrays are stored in "sz" variables.
- **Recursion** - We traverse the Abstract Sytax Tree till any module is reached. Recursion is performed on child and right sibling of the head till leaf or null node is reached.
- **Arrays** : Array variables, their types and other related information is compared as per the rules.
- **Scope of variables** : Each identifier has an entry in symbol table and a pointer points to its table. Their scope is stored in symbol table entry corresponding to that table and checked from there.
- **Offset Handling** :
  - Nested Scope : Global variables are initialised with value 0. The offset variable is incremented by traversing statements as per the width of variables.
  - Formal Parameters : While traversing the list of parameters, each parameter offset is assigned as current value of global offset incremented accordingly.

## Data Structures : 
- Abstract Syntax Tree : 
The node contains the following -
  - Value variable to store the value of the tokens.
  - Rule variable to store the grammar rule number used.
  - isleaf variable that tells if the current node is a leaf node.
  - isVisited variable that tells if the current node has been visited.
  - Child pointer to the first child of this node.
  - Pointer to the parent of the node.
  - Pointer to the right and left siblings.
  - Pointer to the parent of the node.
  - generated variable to tell if the node has been generated.

- Symbol Table Structure :
The symbol table is implemented in form of a tree of symbol tables that further contain function tables. Each node contains :
- A hash table in which all symbol table entries (of same scope) are hashed.
- A hash of hash tables by including the function tables within hash tables.
- The function nodes have the lexeme, input and output as parameters.
- The hash table has a table that has next pointer, width and offset. Along with them, name, type and scope fields are provided. ifnumericalvalue variable determines if the variable is numerical variable or not.
- The function node contains a table that has same attributes as that of hash table.










