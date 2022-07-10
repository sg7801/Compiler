#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include "lexer.c"
#define STACK_SIZE 50
#define EPLS 109
#define TERMS 110
#define NON_TERMINALS 51
#define TERMINALS 58
#define TOTAL_RULES 94

int stack[STACK_SIZE];
int top = -1;
int parsetable[NON_TERMINALS][TERMINALS]; // LL(1) Parse table
struct Parsetree{
    node *Lex;
    int value, rule, generated, isleaf, isVisited;
    struct Parsetree *child, *left, * right, *parent;
};
typedef struct Parsetree* parsetree;
// Terms we took as tokens in lexer 
static char* terms[110] = { "$","program","moduleDeclarations","otherModules","driverModule","moduleDeclaration","moduleDef","module","input_plist","input_plistprime","ret","output_plist","output_plistprime","dataType","type","range","statements","statement","ioStmt","simpleStmt","declareStmt","condionalStmt","iterativeStmt","var","whichId","assignmentStmt","moduleReuseStmt","whichStmt","lvalueIDStmt","lvalueARRStmt","expression","index","optional","idList","idListprime","arithmeticExpr","oplowprec","term","arithmeticExprprime","ophighprec","factor","termprime","arithmeticOrBooleanExpr","AnyTerm","logicalOp","relationalOp","caseStmts","default","N7","N8","N9","value","INTEGER","REAL","BOOLEAN","OF","ARRAY","START","END","DECLARE","MODULE","DRIVER","PROGRAM","GET_VALUE","PRINT","USE","WITH","PARAMETERS","TRUE","FALSE","TAKES","INPUT","RETURNS","AND","OR","FOR","IN","SWITCH","CASE","BREAK","DEFAULT","WHILE","PLUS","MINUS","MUL","DIV","LT","LE","GE","GT","EQ","NE","DEF","ENDDEF","DRIVERDEF","DRIVERENDDEF","COLON","RANGEOP","SEMICOL","COMMA","ASSIGNOP","SQBO","SQBC","BO","BC","COMMENTMARK","ID","NUM","RNUM","eps"};
int first[51][11] = {{59,92,94,-1},{59,109,-1},{92,109,-1},{94,-1},{59,-1},{57,-1},{92,-1},{106,-1},{99,109,-1},{72,109,-1},{106,-1},{99,109,-1},{52,53,54,56,-1},{52,53,54,-1},{107,-1},{63,64,106,101,65,59,77,75,81,109,-1},{63,64,106,101,65,59,77,75,81,-1},{63,64,-1},{106,101,65,-1},{59,-1},{77,-1},{75,81,-1},{106,107,108,-1},{101,109,-1},{106,-1},{101,65,-1},{100,101,-1},{100,-1},{101,-1},{103,106,107,108,83,-1},{106,107,-1},{101,109,-1},{106,-1},{99,109,-1},{106,107,108,-1},{82,83,-1},{106,107,108,-1},{82,83,109,-1},{84,85,-1},{106,107,108,-1},{84,85,109,-1},{103,106,107,108,-1},{106,107,108,-1},{73,74,-1},{86,87,88,89,90,91,-1},{78,-1},{80,109,-1},{73,74,109,-1},{86,87,88,89,90,91,109,-1},{78,109,-1},{107,68,69,-1}};
int follow[51][15] = {{0,-1},{92,94,-1},{94,0,-1},{92,0,-1},{59,92,94,-1},{92,0,94,-1},{92,94,0,-1},{102,-1},{102,-1},{57,-1},{102,-1},{102,-1},{99,102,98,-1},{99,102,98,-1},{102,104,-1},{58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{104,84,85,82,83,86,87,88,89,90,91,73,74,98,-1},{104,84,85,82,83,86,87,88,89,90,91,73,74,98,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{63,64,106,101,65,59,77,75,81,58,79,-1},{98,-1},{102,-1},{65,-1},{96,98,102,-1},{96,98,102,-1},{104,86,87,88,89,90,91,73,74,98,-1},{106,107,108,-1},{82,83,104,86,87,88,89,90,91,73,74,98,-1},{104,86,87,88,89,90,91,73,74,98,-1},{106,107,108,-1},{84,85,82,83,104,86,87,88,89,90,91,73,74,98,-1},{82,83,104,86,87,88,89,90,91,73,74,98,-1},{104,98,-1},{73,74,104,98,-1},{106,107,108,-1},{106,107,108,-1},{80,58,-1},{58,-1},{104,98,-1},{73,74,104,98,-1},{80,58,-1},{96,-1}};
int Grammar[94][14] = {{1,2,3,4,3,-1},{2,109,-1},{2,5,2,-1},{3,109,-1},{3,7,3,-1},{4,94,61,62,95,6,-1},{5,59,60,106,98,-1},{6,57,16,58,-1},{7,92,60,106,93,70,71,101,8,102,98,10,6,-1},{8,106,96,13,9,-1},{9,109,-1},{9,99,106,96,13,9,-1},{10,109,-1},{10,72,101,11,102,98,-1},{11,106,96,14,12,-1},{12,109,-1},{12,99,106,96,14,12,-1},{13,52,-1},{13,53,-1},{13,54,-1},{13,56,101,15,102,55,14,-1},{14,52,-1},{14,53,-1},{14,54,-1},{15,107,97,107,-1},{16,109,-1},{16,17,16,-1},{17,18,-1},{17,19,-1},{17,20,-1},{17,21,-1},{17,22,-1},{18,63,103,106,104,98,-1},{18,64,103,23,104,98,-1},{19,25,-1},{19,26,-1},{20,59,33,96,13,98,-1},{21,77,103,106,104,57,46,47,58,-1},{22,75,103,106,76,15,104,57,16,58,-1},{22,81,103,42,104,57,16,58,-1},{23,106,24,-1},{23,107,-1},{23,108,-1},{24,101,106,102,-1},{24,109,-1},{25,106,27,-1},{26,32,65,60,106,66,67,33,98,-1},{27,28,-1},{27,29,-1},{28,100,30,98,-1},{29,101,31,102,100,30,98,-1},{30,42,-1},{30,83,103,35,104,-1},{31,106,-1},{31,107,-1},{32,101,33,102,100,-1},{32,109,-1},{33,106,34,-1},{34,109,-1},{34,99,106,34,-1},{35,37,38,-1},{36,82,-1},{36,83,-1},{37,40,41,-1},{38,109,-1},{38,36,37,38,-1},{39,84,-1},{39,85,-1},{40,23,-1},{41,109,-1},{41,39,40,41,-1},{42,103,42,104,-1},{42,43,48,-1},{43,35,49,-1},{44,73,-1},{44,74,-1},{45,86,-1},{45,87,-1},{45,88,-1},{45,89,-1},{45,90,-1},{45,91,-1},{46,78,51,96,16,79,98,50,-1},{47,109,-1},{47,80,96,16,79,98,-1},{48,109,-1},{48,44,43,48,-1},{49,109,-1},{49,45,35,49,-1},{50,109,-1},{50,78,51,96,16,79,98,50,-1},{51,107,-1},{51,68,-1},{51,69,-1}};

char arr[1000][40] = {"0"};
int z = 0;
// check if element y present in array x
int present(int *x, int y){
    int k;
    for(k = 0; x[k] != 0;k++){
        if(x[k] == y){
            return 1;
        }
    }
    return 0;
}

// size of an array with -1 representing end
int size(int *a){
    int k = 0, cnt = 0;
    while(a[k] != -1){
        k++; cnt++;
    }
    return cnt;
}

// find the first term of non terminals
void first_term(int ans[150], int n, int Grammar[][14]){
    int i , j , k ,l;
    if(n > 51){
        ans[0] =  n; // terminal
    }
    // non terminal
    else{
        for(i = 0;i<94;i++){// total grammar rules are 94
            if(Grammar[i][0] == n){
                // E -> abc is stored in Grammar as Eabc in form of numbers
                // hence we match Grammar[i][0] to n (here E in example)

                //if the first element is terminal (here a) then simply put in ans
                if(Grammar[i][1] > 51){ // terminal
                    // check if grammar[i][1] is present in ans
                    if(!present(ans, Grammar[i][1])){
                        ans [j++] = Grammar[i][1];   
                        }
                    }
                }   
                // if first element would have been a non terminal itself eg : E-> Abc stored as EAbc and A -> tc..
                // then we would find the first of A

                else{

                for( k = 1; k<size(Grammar[i]); k++){
                    int flag = 0;
                    int sub_result[150] = {0};
                    first_term(sub_result, Grammar[i][k], Grammar);
                    for(l = 0; sub_result[l]!=0;l++){
                        // if sub result contains epsilon then we need to traverse again 
                        if(sub_result[l] == 109){
                            flag = 1;
                        }
                        else{
                            if(!present(ans, sub_result[l])){
                                ans[j++] = sub_result[l];
                            }
                        }

                        // no epsilon found then break
                        if(flag!=1){
                            break;
                        }
                    }
                }
            }
        }
    }
}

// finding the follow terms 
void follow_term(int ans[1024], int n, int Grammar[][14]){
    int i,j,k,l,m;

    if(n == 1){
        // 1 means "$" or end hence ans[0] = -1 
        ans[0] = -1;
    }
    for(i = 0;i<94;i++){
        for(j = 1;j<size(Grammar[i]); j++){ 
            
            // starting from second element of each grammar rule since we must find the "follow" in RHS expansion
            
            if(Grammar[i][j] == n){
            // if we found the given Non Terminal at ith row and jth col in RHS expansion
            // Eg : E-> Etcd then it is stored as EEtcd, we started from j = 1 hence we skipped the LHS already.
            // amongst the RHS(expansion) we found the E at second place (at j) then we would find first of (tcd)
            // hence k = j+1 starting from "t"

                for(k = j+1; Grammar[i][k] != -1; k++){
                    // starting from j+1 since the first of next element would be found 

                    int flag = 0;
                    int sub_result[1024] = {0};

                    // finding the first of (tcd) 
                    first_term(sub_result, Grammar[i][k], Grammar);
                    
                    for(m = 0; sub_result[m] !=0; m++){
                        // checking for epsilon
                        if(sub_result[m] == 109){
                            flag = 1;
                        }
                        else{
                            if(!present(ans, sub_result[m])){
                                ans[l++]= sub_result[m];
                            }
                        }
                    }
                    // if no epsilon found then we stop else we continue to next term
                        if(!flag){
                            break;
                        }
                    }

                    // if we are at last of grammar RHS and the LHS is not n 
                    // following above eg, if we have to find follow of E, and in T->E, E is at jth location which is already the end 
                    // hence in such cases we find the follow of T 
                    // we store in ans if not already present

                    if(Grammar[i][j] == -1 && Grammar[i][0] != n){
                        int sub_result[1024] = {0};
                        follow_term(sub_result, Grammar[i][0], Grammar);
                        for(m = 0; sub_result[m] != 0; m++){
                            if(!present(ans, sub_result[m])){
                                ans[l++] = sub_result[m];
                            }
                        }
                    }      
                }
            }
        }
    }

// check if epsilon is in the "first" set
int epsilon(int alphabet, int first[][11]){
    int k;
    for(k = 0;k<11;k++){
        if(first[alphabet][k] == EPLS){
            return 1;
        }
    }
    return 0;
}

// stack operations
void push(int a){
    stack[++top] = a;
}
void initialise(){
    int j;
    for(j = 0;j<STACK_SIZE;j++){
        stack[j]  = -1;
    }
}
int pop(){
    int a = stack[top];
    if (top != -1)
    {
        stack[top] = -1;
        top--;
    }
    return a;
}

void stack_print(){
    int i ;
    for(int i = 0; i<= STACK_SIZE;i++){
        if(stack[i] == -1){
            break;
        }
        printf("%s  ", terms[stack[i]]);
    }
}

//searching a value in parsing tree
parsetree search(parsetree root, int a){
    parsetree x;
    if(root == NULL){
        return NULL;
    }
    else if(root->value == a && !root->isVisited){
        return root;
    }
    else if((x = search(root->left, a))!= NULL){
        return x; 
    }
    else if((x = search(root->right, a))!=NULL){
        return x;
    }
    return NULL;
}

// find location of a token
int location(char * token){
    int k ;
    for(k = 0; k < TERMS; k++){
        if(strcmp(token, terms[k]) == 0){
                return k;
        }
    }
    return -1;
}

void parse_table(int ptable[][TERMINALS]){
    // rows of non terminals and cols of terminals (LL1)
    int i, j;
    for(i = 0;i<NON_TERMINALS;i++){
        for(j = 0; j<TERMINALS;j++){
            ptable[i][j] = -1;
        }
    }
}

// inserting a lexeme
void insert_lexeme(parsetree t, node* lex){
    t->Lex = lex;
}

// inserting a node in parsetree
void insert_node(parsetree x, int rule, int Grammar[][14], node* Lex){
    int *Rule = Grammar[rule - 1];
    int i = 1;
    parsetree right, left, a, b;
    x->isVisited = 1;
    x->rule = rule;
    while(Rule[i] != -1){
        // till the end of grammar rule selected is reached
        int j;
        a = (parsetree)malloc(sizeof(struct Parsetree));
        a->Lex = createnode();
        a->generated = 0;
        a->value = Rule[i];
        a->Lex->tk->line = Lex->tk->line;
        
        a->left = NULL;
        a->right = NULL;
        a->child = NULL;
        a->parent = NULL;
        a->isVisited = 0;

        if(Rule[i] > 51){
            a->isleaf = 1;
        }
        else{
            a->isleaf = 0;
        }
        if(x->child == NULL){
            x->child = a;
        }
        else{
            b = x->child;
            while(b->right != NULL){
                right = b->right;
                b = right;
            }
            b->right = a;
            a->left = b;
        }
        i++;
    }
}

// printing the parse tree on screen
void print_tree(parsetree head){
    
    // head is null or epsilon then stop & return 
    if((head == NULL) || (head->value == 109)){
        return;
    }
    //recursive call to child of current node
    print_tree(head->child);

    //dynamic allocation of components of tree
    char* curr_node = (char*) malloc(30*sizeof(char));
    int linenum;
    char* token_val = (char*) malloc(30*sizeof(char));
    char* parent_node = (char*) malloc(30*sizeof(char));
    char* value_number = (char*) malloc(30*sizeof(char));
    char* isleafNode = (char*) malloc(30*sizeof(char));
    char* node_symbol = (char*) malloc(30*sizeof(char));

    strcpy(token_val, terms[head->value]);
    linenum = head->Lex->tk->line;
    if(head->parent == NULL){
        // if head doesnt have parent then its the root
        strcpy(parent_node , "ROOT");
    }
    else{
        strcpy(parent_node, terms[head->parent->value]);
    }
    if(!head->isleaf){
        strcpy(isleafNode,"NO");
    }
    else{
        strcpy(isleafNode, "YES");
    }
    if(head->value>51){
        // if head points to terminal node
        strcpy(curr_node, head->Lex->tk->value);
        strcpy(node_symbol, "~");
    }
    else{
        // head points to non - terminal node
        strcpy(curr_node, "~");
        strcpy(node_symbol, terms[head->value]);
    }
    if((head->value == 107 ) || (head->value == 108)){
        // head value is a NUM or RNUM
        strcpy(value_number, head->Lex->tk->value);
    }
    else{
        strcpy(value_number, "~");
    }
    printf("%s %d %s %s %s %s %s", curr_node, linenum, token_val, parent_node, value_number, isleafNode, node_symbol);
}

void print_parsing_table(int table[][TERMINALS]){
    int i, j;
    for(i =0;i<NON_TERMINALS;i++){
        for(j = 0;j<TERMINALS;j++){
            if(table[i][j] == -1){
                printf("-");
            }
            else{
                printf("%d  ", table[i][j]);
            }
        }
    }
}
 
 // counting the total number of nodes
 void count(parsetree head, int* cnt){
    if(head == NULL){
        return;
    }
    count(head->child, cnt);
    cnt[0]++;
    count(head->right, cnt);
 }

// removing the punctuation 
void remove_punctuation(parsetree head)
{
    if(head == NULL){
        return;
    }
    parsetree right = head->right;
    parsetree child = head->child;
    
// Two consecutive case statements without any other statements in between (fall-through) 
// cause the second case to become the child of the first one. 
// If additional consecutive case statements follow, they nest even further

    switch(head->value){
        case 55: // ARRAY
        case 58: // DECLARE
        case 62: // GET_VALUE
        case 66: // WITH
        case 67: // TRUE
        case 70: // INPUT
        case 71: // RETURNS
        case 92: // DEF(<<)
        case 93: // EDDEF(>>)
        case 94: // DRIVERDEF (<<<)
        case 95: // DRIVERENDDEF(>>>)
        case 96: // COLON (:)
        case 98: // RANGEOP (..)
        case 99: // COMMA (,)
        case 101: // SQBO ([)
        case 102: // SQBC(])
        case 103: // BO (
        case 104: // BC )
        if(head->left == NULL){
            head->parent->child = head->right;
            if(head->right != NULL){
                head->right->left = NULL;
            }
            free(head);
        }
        else{
            head->left->right = head->right;
            if(head->right!=NULL){
                head->right->left = head->left;
            }
            free(head);
        }
        remove_punctuation(child);
        remove_punctuation(right);
    }
}

// create an ast
void ast(parsetree head){

    if(head==NULL)
        return;
// Two consecutive case statements without any other statements in between (fall-through) 
// cause the second case to become the child of the first one. 
// If additional consecutive case statements follow, they nest even further
    
    // C99 standard mandates this type of parsing tree
    
    switch(head->rule){
        // program
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 11:
        case 13:
        case 16:
        case 25:
        case 26:
        case 45:
        case 57:
        case 59:
        case 61:
        case 64:
        case 65:
        case 70:
        case 73:
        case 74:
        case 84:
        case 86:
        case 88:
        case 90: break;
        // io statements
        case 18:
        case 19:
        case 20:
        case 22:
        case 23:
        case 24:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 35:
        case 36:
        case 42:
        case 43:
        case 48: 
        case 49:
        case 52:
        case 54:
        case 55:
        case 62:
        case 63:
        case 67:
        case 68:
        case 69:
        case 75:
        case 76:
        case 77:
        case 78:
        case 79:
        case 80:
        case 81:
        case 82:
        case 92:
        case 93:
        case 94: break;
        // in moduledef
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 12:
        case 14:
        case 15:
        case 17:
        case 21:
        case 27:
        case 33:
        case 34:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 44:
        case 46:
        case 50:
        case 53:
        case 58:
        case 60:
        case 66:
        case 71:
        case 72:
        case 83:
        case 85:
        case 87:
        case 89:
        case 91:break;
    }
    if(head != NULL){
        ast(head->child);
        ast(head->right);
    }
}

void create_ast(parsetree head){
    remove_punctuation(head);
    ast(head);    
}

// printing to file 
void print_to_file(parsetree head){
    
    // head is null or epsilon then stop & return 
    if((head == NULL) || (head->value == 109)){
        return;
    }
    //recursive call to child of current node
    print_to_file(head->child);

    //dynamic allocation of components of tree
    char* curr_node = (char*) malloc(30*sizeof(char));
    int linenum;
    char* token_val = (char*) malloc(30*sizeof(char));
    char* parent_node = (char*) malloc(30*sizeof(char));
    char* value_number = (char*) malloc(30*sizeof(char));
    char* isleafNode = (char*) malloc(30*sizeof(char));
    char* node_symbol = (char*) malloc(30*sizeof(char));

    strcpy(token_val, terms[head->value]);
    linenum = head->Lex->tk->line;
    if(head->parent == NULL){
        // if head doesnt have parent then its the root
        strcpy(parent_node , "ROOT");
    }
    else{
        strcpy(parent_node, terms[head->parent->value]);
    }
    if(!head->isleaf){
        strcpy(isleafNode,"NO");
    }
    else{
        strcpy(isleafNode, "YES");
    }
    if(head->value>51){
        // if head points to terminal node
        strcpy(curr_node, head->Lex->tk->value);
        strcpy(node_symbol, "~");
    }
    else{
        // head points to non - terminal node
        strcpy(curr_node, "~");
        strcpy(node_symbol, terms[head->value]);
    }
    if((head->value == 107 ) || (head->value == 108)){
        // head value is a NUM or RNUM
        strcpy(value_number, head->Lex->tk->value);
    }
    else{
        strcpy(value_number, "~");
    }
    int rule = head->rule;
    fprintf(stdout, "%s %d %s %s %s %s %s %d", curr_node, linenum, token_val, parent_node, value_number, isleafNode, node_symbol, rule);
    free(curr_node);
    free(token_val);
    free(parent_node);
    free(value_number);
    free(isleafNode);
    free(node_symbol);

    //recursive call to right of head
    print_to_file(head->right);
}

// adding lexeme 
void add_lexeme(parsetree head, node* Lex){
    if(head == NULL){
        return;
    }
    add_lexeme(head->child, Lex);
    if(head->isleaf == 1 && head->value != 109){
        strcpy(head->Lex->tk->value, arr[z++]);
    }
    add_lexeme(head->right, Lex);
}

// populating the lexemes
void populate(parsetree head, char* file_name){
    // calling the method in lexer
    node* Lex = token_generation();
    int i = 1, j = 0;
    while (strcmp(Lex->tk->value, "$") != 0)
    {
        strcpy(arr[j++], Lex->tk->value);
        free(Lex);
        node* Lex = token_generation();
    }
    add_lexeme(head, Lex);
}

void find_first_and_follow(int Grammar[][14], int first[][11], int follow[][15]){
    int i, j;
    // first
    
    // for 0 - 51 NON TERMINALS
    // starting from i = 1 as at i = 0 its $
    for(i = 1; i<52; i++){
        int ans[1024] = {0};
        first_term(ans, i, Grammar);
        for(j = 0; ans[j] != 0;j++){ // 0 denotes $
            first[i][j] = ans[j];
        }
        first[i][j] = -1; // to mark the end 
    }

    // follow
    for(i = 1; i<52;i++){
        int ans[1024] = {0};
        follow_term(ans, i, Grammar);
        for(j = 0; ans[j]!=0; j++){ 
            if(ans[j] == -1){ // on encounter of $ we entered -1
                follow[i][j] = 0;
            }
            else{
                follow[i][j] = ans[j];
            }
        }
        follow[i][j] = -1; // marks the end of follow of that element
    }
}

// making & filling values in parsing table using the first, follow & Grammar 

void make_parse_table(int table[][TERMINALS], int Grammar[][14]){
    int flag, rule, right, firstterm, head, term, left_head, a, alpha, foll;
    table[0][43] = 1; table[25][14] = 47;


    // traversing grammar
    for(rule = 0; rule< TOTAL_RULES; rule++){
        flag = 0;
        left_head = Grammar[rule][0]; // LHS of grammar rule
        head = left_head-1; // index of head for table filling 
        for(right = 1; right < 14; right++){
            alpha = Grammar[rule][right];
            if(alpha == -1){
                break; // end of rule expansion
            }

            if(alpha == EPLS){ // epsilon 
                flag = 1;
                break;
            }
            // filling table value 
            if(alpha > NON_TERMINALS){ // alpha is a terminal
                table[head][alpha-NON_TERMINALS] = rule + 1;
                break;
            }
            // if alpha is a non terminal we find the first of that non terminal to fill table as per LL1
            for(firstterm = 0;firstterm < sizeof(first[alpha-1]); firstterm++){
                term = first[alpha-1][firstterm]; // each individual first term of alpha
                if(term != 109 && term > NON_TERMINALS){
                    // not epsilon and a terminal character then directly fill that term in table
                    table[head][term - NON_TERMINALS] = rule+1;
                }
            }
            if(!epsilon(alpha, first)){
                // does not contain epsilon in first set
                break;
            }
            else if(epsilon(alpha, first) && Grammar[rule][right+1] == -1){
                // if epsilon is present in first of alphabet and we have reached the end of RHS of rule 
                // then flag = 1
                flag =1 ;
                break;
            }
            else{} 

        }

        // we calculate the follow of the LHS of the rule if flag == 1
        if(flag == 1){
            for(foll = 0; foll < sizeof( follow[head] ); foll++){
                a = follow[head][foll];
                if(a == -1){
                    break;
                    // end of follow terms for given rule
                }
                if(a == 0){ // if a is $
                    table[head][a] = rule+1;
                }
                else{ // if a is a terminal
                    table[head][a - NON_TERMINALS] = rule+1;
                }
            }
        }
    }
}

// Parsing the source code
parsetree parse_source_code(char* file){
    
    // defining the parsetreee structure
    parsetree head;
    head = (parsetree)malloc(sizeof(struct Parsetree));
    head->Lex = createnode();
    strcpy(head->Lex->tk->token, "PROGRAM");
    strcpy(head->Lex->tk->value, "program");
    head->Lex->tk->line = 1;
    head->value = 1;
    head->child = NULL;
    head->left = NULL;
    head->right = NULL;
    head->isleaf = 0;
    head->isVisited = 0;
    head->parent = NULL;

    FILE *fp = fopen(file, "r");
    rewind(fp);
    fseek(fp, 0, SEEK_SET);
    fp = getstream(fp);
    push(0);
    push(1);

    node* Lex = token_generation();
    int p = 0, cnt = 0;
    printf("Token = %s, Value = %s, Line = %d\n", Lex->tk->token, Lex->tk->value, Lex->tk->line);
    while(strcmp(Lex->tk->value, "$") != 0){// till we reach end of stack
        char * token = Lex->tk->value;
        printf("Token being parsed is %s", token);
        // in case of comments
        if(strcmp(token, "COMMENTMARK") == 0){
            Lex = token_generation();
            token = Lex->tk->token;
            if(stack[top] == 0 || stack[top] == 3){
                break;
            }
        }
        if(stack[top] > NON_TERMINALS){
            // in case of terminal on the top of stack
            if(stack[top] == location(token)){
                // if the token is equivalent to terminal character at top of stack
                // then they get cancelled 
                // we pop the terminal character from stack
                pop();
                cnt++;
                Lex = token_generation();
                token = Lex->tk->token;
                stack_print();
            }
            else{
                printf("Error : Token & Lexeme do not match here.");
                exit(0) ;
            }
        }
        else{
            // in case of non-terminal character
            // find the rule from the parsing table 
            int rule = parsetable[stack[top] - 1][(location(token) - NON_TERMINALS)];
            if(rule == -1){
                printf("Error : The token does not match");
                Lex = token_generation();
                token = Lex->tk->token;
                while((rule = parsetable[stack[top] -1][location(token) - NON_TERMINALS]) == -1){
                    Lex = token_generation();
                    token = Lex->tk->token;
                }
            }
            else{
                if(head->child == NULL){
                    // if the child of the head is null then populate the parse tree
                    insert_node(head, rule, Grammar, Lex);
                }
                else{
                    // else search for the child where to insert the new node
                    parsetree x = search(head, stack[top]);
                    insert_node(x, rule, Grammar, Lex);
                }
                int right;
                pop();
                // we expand the rule and push in stack the RHS
                for(right = size(Grammar[rule-1])-1 ; right > 0 ; right--){
                    int alpha = Grammar[rule - 1][right];
                    if(alpha != EPLS){
                        push(alpha);
                    }
                    stack_print();
                }
            }
        }
        
    }
    if(stack[top] == 3){
            pop();
        }
        if(stack[top] == 0){
            // if $ is left only
            // successful parsing
            pop();
            printf("Successful Parsing");
        }
        printf("Count\n", cnt);
        return head;
}

// printing the parse tree
void parse_tree_print(parsetree head){
    printf("%s %s %s %s %s %s %s %s", "curr_node", "lineno", "token", "value", "parent", "isleaf", "Node_Symbol", "rule");
    print_to_file(head);
}