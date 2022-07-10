# Compiler

A compiler for a toy programming language **"Lin"** that follows LL(1) parsing approach. All specifications of the language & grammar are mentioned in [Language folder](https://github.com/sg7801/Compiler/tree/main/Language). 
<br>
 
 ## Modules
 Multiple Modules have been implemented for all the phases of compiler : 
 ### Lexical Analysis :
 The compiler takes the input as string of characters and produces the stream of tokens. This phase is implemented in **lexer.c** module.
### Syntax Analysis :
This phase takes the stream of tokens and produces a abstract syntax tree. This phase is implemented in **parser.c** module.
### Type - Checking :
This phase takes the abstract syntax tree and generates a symbol table. It primarily performs the semantic analysis along with type checking. This phase is implemented in **symboltable.c** module.
### Code Generation :
This phase takes syntax tree & symbol table, generates the assembly code in .asm file. This phase is implemented in **codegenerator.c** module.

## Input : 
The compiler can take input in the text format (.txt files).
## Output :
As an output the assembly code in .asm file will be generated for provided input code. A **gcc** has been used to assemble and link to an executable.

## Execution :
Run ```make``` command to compile the compiler. Then, to execute it, run ```.\compiler testcase.txt outputfile```
