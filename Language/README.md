# Language Specifications :

- The language is implemented using various data structures, is fully functional and robust. 
- It is capable of handling the Integer, Real and Boolean primitive data types. 
- However it cannot generate the code for multiple modules.

### Size of Data Types :
- Integer data type is stored by taking size of 2 bytes
- Real data type is stored by taking size of 4 bytes 
- Boolean data type is stored by taking size of 1 byte

## Keywords :
The key words used in the language are as follows:

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

## Symbols: 
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










