 # Grammar
 The grammar consists of 94 rules constructed from 51 non-terminals including $ and 58 terminals.
 ```
 The Rules Should be written with format :
    [<NONTERMINAL>] --> list of [<NONTERMINAL> | TERMINAL ] 
 ```
\<program> --> \<moduleDeclarations>\<otherModules>\<driverModule>\<otherModules>
 <br>\<moduleDeclarations> --> \<moduleDeclaration>\<moduleDeclarations>
 <br>\<moduleDeclarations> --> ε
 <br>\<moduleDeclaration> --> DRIVER MODULE ID SEMICOL
 <br>\<otherModules> --> \<module>\<otherModules>
 <br>\<otherModules> --> ε
 <br>\<driverModule> --> DRIVERDEF DRIVER PROGRAM DRIVERENDDEF 
 <br>\<moduleDef> --> END \<statements> DECLARE
 <br>\<module> --> DEF MODULE ID ENDDEF TAKES INPUT SQBO \<input_plist> SQBC SEMICOL \<ret>\<moduleDef>
 <br>\<ret> --> RETURNS SQBO \<output_plist> SQBC SEMICOL
 <br>\<ret> --> ε
 <br>\<input_plist> --> ID COLON \<dataType>\<input_plistprime>
 <br>\<input_plistprime> --> COMMA ID COLON \<dataType>\<input_plistprime>
 <br>\<input_plistprime> --> ε
 <br>\<output_plist> --> ID COLON \<type>\<type>
 <br>\<output_plistprime> --> ε
 <br>\<input_plistprime> --> COMMA ID COLON \<dataType>\<output_plistprime>
 <br>\<range> --> \<NUM> RANGEOP \<NUM>
 <br>\<statements> --> <statement>\<statements>
 <br>\<statements> --> ε
 <br>\<statement> --> \<ioStmt>
 <br>\<statement> --> \<simpleStmt>
 <br>\<statement> --> \<declareStmt>
 <br>\<statement> --> \<conditionalStmt>
 <br>\<statement> --> \<iterative>
 <br>\<simpleStmt> --> \<assignmentStmt>
 <br>\<simpleStmt> --> \<moduleReuseStmt>
 <br>\<ioStmt> --> GET_VALUE BO ID BC SEMICOL
 <br>\<ioStmt> --> PRINT BO \<var> BC SEMICOL
 <br>\<declareStmt> --> DECLARE \<idList> COLON \<dataType> SEMICOL
 <br>\<conditionalStmt> --> MODULE \<idList> COLON dataType arithmeticExprprime \<term> \<caseStmt> DEFAULT DECLARE
 <br>\<dataType> --> ARRAY SQBO \<range_arrays> SQBC OF \<type>
 <br>\<dataType> --> INTEGER
 <br>\<dataType> --> REAL
 <br>\<dataType> --> BOOLEAN
 <br>\<type> --> INTEGER
 <br>\<type> --> REAL
 <br>\<type> --> BOOLEAN
 <br>\<iterativeStmt> --> FOR BO ID IN \<range> BC SWITCH \<statements> END
 <br>\<iterativeStmt> --> WHILE BO \<arithOrBoolExpr> BC START \<statements> END
 <br>\<var> --> NUM
 <br>\<var> --> RNUM
 <br>\<whichId> --> SQBO ID SQBC
 <br>\<whichId> --> ε
 <br>\<assignmentStmt> --> ID \<whichStmt>
 <br>\<moduleReuseStmt> --> \<optional> USE MODULE ID WITH PARAMETERS \<idList> SEMICOL
 <br>\<whichStmt> --> \<lvalueIDStmt>
 <br>\<whichStmt> --> \<lvalueARRStmt>
 <br>\<lvalueIDStmt> --> ASSIGNOP \<expression> SEMICOL
 <br>\<lvalueARRStmt> --> SQBO \<Index> SQBC ASSIGNOP \<expression> SEMICOL
 <br>\<expression> --> \<arithOrBoolExpr>
 <br>\<expression> --> MUL BO \<arithmeticExpr> BC
 <br>\<Index> --> NUM
 <br>\<Index> --> ID
 <br>\<optional> --> SQBO \<idList> SQBC ASSIGNOP
 <br>\<optional> --> ε
 <br>\<idList> --> ID \<N3> 
 <br>\<idListprime> --> COMMA ID \<idListprime>
 <br>\<arithmeticExpr> --> \<term>\<arithmeticExprprime>
 <br>\<opLowerprec> -->MINUS 
 <br>\<opLowerprec> --> MUL
 <br>\<term> --> \<factor> \<termprime>
 <br>\<arithmeticExpreprime> --> ε
 <br>\<arithmeticExpreprime> --> \<oplowerprec> \<term> \<arithmeticExpreprime>
 <br>\<ophighprec> --> MUL
 <br>\<ophighprec> --> DIV
 <br>\<factor> --> \<var>
 <br>\<termprime> --> ε
 <br>\<arithmeticBooleanExpr> --> BO \<arithmeticBooleanExpr> BC
 <br>\<arithmeticBooleanExpr> --> \<AnyTerm>\<N7>
 <br>\<termprime> --> \<ophighprec> \<factor> \<termprime>
 <br>\<AnyTerm> --> \<arithmeticExpr> \<N8>
 <br>\<logicalOp> --> AND
 <br>\<logicalOp> --> OR
 <br>\<relationalOp> --> LT
 <br>\<relationalOp> --> LE
 <br>\<relationalOp> --> GT
 <br>\<relationalOp> --> GE
 <br>\<relationalOp> --> EQ
 <br>\<relationalOp> --> NE
 <br>\<caseStmts> --> CASE \<value> COLON \<statements> BREAK SEMICOL \<N9>
 <br>\<default> --> DEFAULT COLON \<statements> BREAK SEMICOL
 <br>\<default> --> ε
 <br>\<N9> --> ε
 <br>\<N9> --> \<logicalop> \<anyTerm> \<N9> 
 <br>\<N8> --> \<relationalOp> \<arithmeticExpr> \<N8>
 <br>\<N8> --> ε
 <br>\<N7> --> NUM
 <br>\<N7> --> TRUE
 <br>\<N7> --> FALSE
