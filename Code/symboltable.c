#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include"parser.c"
#define SIZE 20
#define HASHSIZE 20
#define Assert assert(0)
int func_num = 0;
char arr1[100][100];
int offset = 0, offseter = 0, sequence = 1;

struct function_node{
    char name[30], input[100], output[100];
    struct function_node* next;
};
typedef struct function_node fnode;
typedef struct function_node *fnext;

struct token_node{
    char name[30], type[15], scope[15], ifnumericalvalue[10];
    int width, offset;
    struct token_node* next;
};

struct function_hash_table{
    fnode* table[20];
};
struct function_hash_table * functable;

typedef struct token_node pnode;
typedef struct token_node *pnext;

// making hash of all hash tables 
// hence a table of type struct of hash table inside the structure of hash of hash tables
struct hash_of_hash_table{
    struct hash_table *function_table[HASHSIZE];
};
struct hash_of_hash_table *ht;

struct hash_table{
    pnode *table[SIZE];
};

// making the table for new hash tables
struct hash_table* create_table(){
    struct hash_table *node = (struct hash_table*)malloc(sizeof(struct hash_table));
    return node;
};

// making a hash [key -> value]
// return the sum of all keys fitted into the SIZE range 
int hash(char* key){
    int value = 0, i =0;
    for(i=0;i<strlen(key);i++)
    {
        value += (int)key[i];
    }
    return (value % SIZE);
}

// making dynamically new nodes for tokens
struct token_node* create_node(char* key, char* type, char* function_name, char* ifnumericalvalue){
    struct token_node *node = (struct token_node*)malloc(sizeof(struct token_node));
    strcpy(node->name , key);
    strcpy(node->ifnumericalvalue, ifnumericalvalue);
    strcpy(node->scope, function_name);
    strcpy(node->type, type);
    node->width = 0; node->offset = 0;
    node->next = NULL;
    return node;
}

// making the function node
struct function_node* create_function_node(char *lexeme , char* input, char* output){
    struct function_node* node = (struct function_node*)malloc(sizeof(struct function_node));
    strcpy(node->name, lexeme);
    strcpy(node->input, input);
    strcpy(node->output, output);
    return node;
}

int hash_insert_function(char *key, char *input, char* output){
    int h = hash(key);
    // new function node is created
    struct function_node* iterator = create_function_node(key,input, output);
    if(iterator == NULL){
        return 0;
    }
    // got till the last table
    while(functable->table[h]->next != NULL){
        h++;
    }
    // new function node will be pointed by last table's next ptr
    functable->table[h]->next = iterator;
    // values of key will be copied
    strcpy(arr1[func_num++],key);
    return h;
}

// to get the hash value of any given function
int func_hash_value(char* function_name){
    int h = hash(function_name);
    while(functable->table[h]->next != NULL){
        if(strcmp(functable->table[h]->next->name, function_name) == 0){
            return h;
        }
        h++;
    }
    return -1;
}

// check if the function is present in function table
int check_func_present(char* func_name){
    int i , j = 1;
    fnode* iterator;
    for(i = 0; i<SIZE; i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name, func_name) == 0){
                return 1;
            }
        }
    }
    return 0;
}

// return the pointer to any function
fnode* ret_func_ptr(char* func_name){
    int i, j = 1;
    for(i = 0 ;i<SIZE;i++){
        if((functable->table[i]->next != NULL) && (int)(functable->table[i]->next->name)<10000000010){
            if(strcmp(functable->table[i]->name, func_name) == 0){
                return functable->table[i]->next;
            }
        }
    }
    return NULL;
}


// to know the type of the function
void function_input_type(char* function_name){
    int i, j = 1;
    char input_type[1000] = {'\0'};
    for(i = 0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name, function_name) == 0){
                strcpy(input_type, functable->table[i]->next->input);
                printf("Input parameter of module %s are  :  ", functable->table[i]->next->name);
                char* token;
                token = strtok(functable->table[i]->next->input, ";"); // break the input string into tokens
                while(token!=NULL){
                    printf("%d %s\n", j++, token);
                    token = strtok(NULL, ";"); // this tells that continue tokenizing the  previosuly mentioned value and stop when we hit "NULL"

                }

            }
        }
    }
}

char input_type[1000] = {'\0'};

// to return the type of function input
char* ret_function_input_type(char* function_name){
    int i, j = 1;    
    for(i = 0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name, function_name) == 0){
                strcpy(input_type, functable->table[i]->next->input);
            }
        }
    }
    return input_type;
}

// know the output type of the function
void function_output_type(char* function_name){
    int i, j = 1;
    char output_type[1000] = {'\0'};
    for(i = 0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name, function_name) == 0){
                strcpy(output_type, functable->table[i]->next->output);
                printf("Output parameter of module %s are  :  ", functable->table[i]->next->name);
                char* token;
                token = strtok(functable->table[i]->next->output, ";"); // break the output string into tokens
                while(token!=NULL){
                    printf("%d %s\n", j++, token);
                    token = strtok(NULL, ";"); // this tells that continue tokenizing the  previosuly mentioned value and stop when we hit "NULL"

                }

            }
        }
    }
}


char output_type[1000] = {'\0'};

// return the output type of the function
char* ret_function_output_type(char* function_name){
    int i, j = 1;
    for(i = 0;i<SIZE;i++){
        if(functable->table[i]->next != NULL && ((int)(functable->table[i]->next->name) < 100000000)){
            if(strcmp(functable->table[i]->next->name, function_name) == 0){
                strcpy(output_type, functable->table[i]->next->output);
            }
        }
    }
    return output_type;
}

// insert the hash into token symbol table
int hash_insert(char * key, char* type, char* func_name, char* numerical_val){
    int h = hash(key);
    int j = func_hash_value(func_name);
    struct token_node* iterator = create_node(key, type, func_name, numerical_val);
    if(iterator == NULL){
        return 0;
    }
    while(ht -> function_table[j] ->table[h] -> next != NULL){
        h++;
    }
    // next ptr of last hash table points to iterator
    ht->function_table[j]->table[h]->next = iterator;

    // identifying the size of the type to be inserted
    int sz = 0;
    if(strcmp(ht->function_table[j]->table[h]->next->type, "INTEGER") == 0){
        sz = 2;
    }
    if(strcmp(ht->function_table[j]->table[h]->next->type, "REAL") == 0){
        sz = 4;
    }
    if(strcmp(ht->function_table[j]->table[h]->next->type, "STRING") == 0){
        sz = strlen(ht->function_table[j]->table[h]->next->name);
    }
    if(strcmp(ht->function_table[j]->table[h]->next->type, "BOOLEAN") == 0){
        sz = 1;
    }
    if(strncmp(ht->function_table[j]->table[h]->next->type, "ARRAY", 5) == 0){
        char type[50];
        int range = 0;
        memset(type, '\0', sizeof(type));
        strcpy(type, ht->function_table[j]->table[h]->next->type);
        char* token = NULL;
        // tokenize type till "(" is hit
        token = strtok(type, "(");
        if(token != NULL){
            token = strtok(NULL, ","); // continue tokenizing the previously passed string 
            if(strcmp(token, "INTEGER") == 0){
                sz = 2;
            }
            if(strcmp(token, "REAL") == 0){
                sz = 4;
            }
            if(strcmp(token, "BOOLEAN") == 0){
                sz = 1;
            }
            token = strtok(token, ")");
            if(token !=NULL){
                range = atoi(token);
            }
        }
        sz = sz* range;
    }
    // width aka size
    ht->function_table[j]->table[h]->next->width = sz;
    ht->function_table[j]->table[h]->next->offset = offset;
    offset+=sz;
    return 1;
}

// get offset value 
int offset_val(char* key, char* func_name){
    int h = hash(key);
    int val = func_hash_value(func_name);
    while(ht->function_table[val]->table[h]->next != NULL){
        if(strcmp(key, ht->function_table[val]->table[h]->next->name) == 0){
            return ht->function_table[val]->table[h]->next->offset;
        }
        h++;
    }
    return -1;
}

// get direct pointer 
pnode* get_direct_ptr(char* key, char* func_name){
    int val = func_hash_value(func_name);
    int h = hash(key);
    while(ht->function_table[val]->table[h]->next!=NULL){
        if(strcmp(key, ht->function_table[val]->table[h]->next->name) == 0){
            return ht->function_table[val]->table[h]->next;
        }
        h++;
    }
    return NULL;
}

// check if a symbol is present in the symbol table
int check_symbol(char* key, char* func_name){
    int h = hash(key);
    int val = func_hash_value(func_name);
    if(ht->function_table[val]->table[h] == NULL){
        return 0;
    }
    while(ht->function_table[val]->table[h]->next != NULL){
        if(strcmp(key, ht->function_table[val]->table[h]->next->name) == 0){
            return 1;
        }
        h++;
    }
    return 0;
}

// display the hash tables 
void disp(char* func_name){
    int i, j = func_hash_value(func_name);
    for(i = 0;i<SIZE;i++){
        pnode* iterator = ht->function_table[j]->table[i]->next;
        if(iterator != NULL && strcmp(iterator->name, "")!=0){
            // if the iterator points to non null value
            if(strncmp(ht->function_table[j]->table[i]->next->type, "AY", 5) == 0){
                printf("%d %s %s %s %d %d", sequence++, ht->function_table[j]->table[i]->next->name, "AY", ht->function_table[j]->table[i]->next->scope,ht->function_table[j]->table[i]->next->width, offseter);
            }
            else{
                printf("%d %s %s %s %d %d", sequence++, ht->function_table[j]->table[i]->next->name, ht->function_table[j]->table[i]->next->type, ht->function_table[j]->table[i]->next->scope, ht->function_table[j]->table[i]->next->width, offseter);
            }
            offseter += ht->function_table[j]->table[i]->next->width;
        }
    }
}

// return the type of hash function
char* type_value(char* key, char* func_name){
    int val = func_hash_value(func_name);
    int h = hash(key);
    while(ht->function_table[val]->table[h]->next != NULL){
        if(strcmp(key, ht->function_table[val]->table[h]->next->name) == 0){
            return ht->function_table[val]->table[h]->next->type;
        }
        h++;
    }
    return NULL;
}

// display the symbol table
void disp_symbol_table(){
    int i;
    printf("%s       %s        %s        %s         %s        %s","Number", "Identifier", "Type", "Scope", "WIdth", " Offset");
    for(i = 0;i<func_num;i++){
        disp_symbol_table(arr1[i]); // display symbol table arr1[100][100]
    }
}

// automation of offset
void automate_offset(char* func_name){
    int val = func_hash_value(func_name);
    int h = hash(func_name);
    int offset = 0, i= 0;
    for(i=0;i<SIZE;i++){
        pnode* iterator = ht->function_table[val]->table[h]->next;
        if(iterator != NULL && strcmp(iterator->name, "")!=0){
            if(strcmp(ht->function_table[val]->table[h]->next->type, "INTEGER") == 0){
                offset+=4;
            }
            if(strcmp(ht->function_table[val]->table[h]->next->type, "REAL") == 0){
                offset+=8;
            }
            if(strcmp(ht->function_table[val]->table[h]->next->type, "STRING") == 0){
                offset+=strlen(ht->function_table[val]->table[h]->next->name);
            }
            if(strcmp(ht->function_table[val]->table[h]->next->type, "ARRAY") == 0){
                offset+=0;
            }
            ht->function_table[val]->table[h]->next->offset = offset;        
            }
    }
}

// checking the type 
int Typechecker(FILE* fp, parsetree head, char* scope){
    int type_left, type_right, i ,error = 0;
    switch(head->value){
        case 100:{// 100 denotes a comma
            type_left = Typechecker(fp, head->parent->parent->parent->child, scope);
            type_right = Typechecker(fp, head->right, scope);
            //if the left side of expression is not equal to right side of expression
            if(type_right == -2 || type_left == -2){
                return -2;
            }
            else{
                if(type_right != type_left){
                    printf("Error : Type of left expression is not equal to type of right expression");
                    return -2;
                }
                else{
                    return type_right;
                }
            }

        }
        break;
        case 106: // 106 denotes a Comment mark
        {
            if(!check_symbol(head->Lex->tk->value, scope)){
                return -2;
            }
            else{
                char type[25] = {'\0'};
                strcpy(type,  type_value(head->Lex->tk->value, scope));
                char* token = NULL;
                token = strtok(type_value(head->Lex->tk->value, scope), "(");
                if(token != NULL)
                {
                    token = strtok(NULL,",");
                    if(token!=NULL){
                        strcpy(type, token);
                    }
                }
                if(strcmp(type, "INTEGER") == 0){
                    return 0;
                }
                if(strcmp(type, "REAL") == 0){
                    return 1;
                }
                if(strcmp(type, "BOOLEAN") == 0){
                    return -1;
                }
            }
        }
        break;
        case 68: // TRUE 
        case 69 : // FALSE
                return -1;
        case 107 : //ID
                return 0;
        case 108 : // NUM
                return 1;
        case 84: // Multiplication
        case 85: // Division
                if(head->parent->parent->parent->value == 41){
                    // if it is a factor
                    if((type_left = Typechecker(fp, head->parent->parent->parent->child->right, scope))==-2){
                        return -2;
                    }
                    if((type_right = Typechecker(fp, head->parent->right, scope))==-2){
                        return -2;
                    }
                }
                if(head->parent->parent->parent->value == 37){
                        //if it is an operand of lower precedence
                        if((type_left = Typechecker(fp, head->parent->parent->parent->child, scope)) == -2){
                            return -2;
                        }
                        if((type_right = Typechecker(fp, head->parent->right, scope))==-2){
                            return -2;
                        }
                    }
                    if(type_left != type_right){
                        fprintf(fp,"Error : Types of Left and Right terms do not match!");
                        return -2;
                    }
                    if(type_left == -1){
                        // if left side is a bool term
                        fprintf(fp,"Error : Boolean expression cannot be divided or multiplied!");
                        return -2;
                    }
                    return type_left;
                    break;
        
        case 82 : //PLUS
        case 83 : //MINUS
                if(head->value == 83 && head->parent->value == 30){
                    // head value denotes minus and parent is some expression
                    return Typechecker(fp, head->right, scope);
                }
                if(head->parent->parent->parent->value == 38){
                    // 38 denotes a term
                    if((type_left = Typechecker(fp, head->parent->parent->parent->child->right, scope))==-2){
                        return -2;
                    }
                    if((type_right = Typechecker(fp, head->parent->right, scope)) == -2){
                        return -2;
                    }
                }

                if(head->parent->parent->parent->value == 35){
                    // 35 denotes idListPrime
                    if((type_left = Typechecker(fp, head->parent->parent->parent->child, scope)) == -2){
                        return -2;
                    }
                    if((type_right = Typechecker(fp, head->parent->right,scope)) == -2){
                        return -2;
                    }
                }
                // if in any of the above case left & right types do not match then :
                if(type_left != type_right){
                    fprintf(fp, "Files do not match!\n");
                    return -2;
                }
                if(type_left == -1){
                    // if the left expression is of type bool
                    fprintf(fp, "Error : We cannot add or subtract boolean expressions!");
                    return -2;
                }
                return type_left;
                break;
        case 86: // Less than (<)
        case 87: // Less than equal to (<=)
        case 88: // Equality check (==)
        case 89: // Greater than equal to (>=)
        case 90: // Greater than (>)
        case 91: // Equality (=)
                if(head->parent->parent->parent->value == 43){
                    // arithmetic or bool expression
                    if((type_left = Typechecker(fp, head->parent->parent->parent->child,scope))==-2){
                        return -2;
                    }
                    if((type_right = Typechecker(fp, head->parent->right, scope)) == -2){
                        return -2;
                    }
                }
                if(head->parent->parent->parent->value == 49){
                    // 49 denotes N9
                    if((type_left = Typechecker(fp, head->parent->parent->parent->child->right,scope))==-2){
                        return -2;
                    }
                    if((type_right = Typechecker(fp, head->parent->right, scope)) == -2){
                        return -2;
                    }

                }
                //if the left and right term are neither an Integer nor a real number
                if((type_left != 0 && type_left != 1)|| (type_right != 0 && type_right!=1)){
                    return -2;
                }
                // left and right expressions have different data types
                if(type_left != type_right){
                    return -2;
                }
                return -1;
                break;
        case 73: // AND
        case 74: // OR
                if(head->parent->parent->value == 42){
                    // termprime
                    if((type_left = Typechecker(fp, head->parent->parent->parent->child, scope)) == -1){
                        // if left not bool type
                        return -2;
                    }
                    if((type_right = Typechecker(fp, head->parent->right, scope))== -1){
                        // if right not bool type
                        return -2;
                    }
                }
                // 48 : default
                if(head->parent->parent->parent->value == 48){
                    if((type_left = Typechecker(fp, head->parent->parent->parent->child->right, scope))!= -1){
                        return -2;
                    }
                    if((type_right = Typechecker(fp, head->parent->right, scope))!= -1){
                        return -2;
                    }
                }
                return -1;
                break;
        default:{
            parsetree child = head->child;
            while(child!= NULL && child->value !=109){
                // till child is neither null nor its value is epsilon
                if(child->value == 24){
                    // value of child is var
                }
                else if((type_left = Typechecker(fp, child,scope))==-2){
                    // if typedef return -2 then its an error
                    error = 1;
                }
                if(type_left == -1 && child->value == 45){
                    return -1;
                    // if the type of left term is bool & value of child is logical operator
                    // then we return -1 dentoing boolean
                }
                child = child->right; 
            }
            if(error == 1){
                return -2;
            }
            //if error is not there return the type of left expression
            return type_left;
        }
    }
    return 1;
}
// creating the symbol table
void create_symbol_table(){
    functable = (struct function_hash_table*)malloc(sizeof(struct function_hash_table*));
    int i ,j;
    char *t, *input = "", *output = "";
    for(i = 0;i<SIZE;i++){
        // creating the function table nodes
        functable->table[i] = create_function_node(t, input, output);
    }
    // creating the func tables and nodes within it 
    ht = (struct hash_of_hash_table*)malloc(sizeof(struct hash_of_hash_table));
    for(j = 0;j < HASHSIZE;j ++){
        ht->function_table[j] = create_table();
        for(i=0;i<SIZE;i++){
            char* key = "", *function_name = "", *type = "", *if_numerical = "";
            ht->function_table[j]->table[i] = create_node(key, type, function_name, if_numerical);
        }
    }
}

// populating the definition of the function
void func_definition(FILE *fp, parsetree head, char* function_name){
    if(head == NULL){
        return ;
    }
    // recursive call to func_definition for child of head
    func_definition(fp, head->child, function_name);
    if((strcmp(head->Lex->tk->value, function_name) == 0)&& head->parent->value == 7){
        // if value of token of lexeme of head has same value as function name
        // and parent value is also 7 , module 
        parsetree iplist = head->right; // right of head into input list
        char itype[1000] = {'\0'}, otype[1000] = {'\0'};
        switch(iplist->child->right->rule){
            // if the rule number 18 in Grammar then input type is INTEGER
            // 13 - > 52
            case 18:  strcat(itype, "INTEGER");
            break;
            // 13 - > 53
            case 19 : strcat(itype, "REAL");
            break;
            // 13 - > 54
            case 20 : strcat(itype, "BOOLEAN");
            break;
            // 13 - > 56, 101, 15, 102, 55, 14, 21 
            case 21 : { // if it is an array
                parsetree range = iplist->child->right->child->right;
                // convert value ascii to integer
                int x = atoi(range->child->Lex->tk->value), y = atoi(range->child->right->right->Lex->tk->value);
                int ans = x - y + 1; 
                char sz[3], type[100] = {'\0'};

                switch(range->right->rule){
                    // if the rule to right is :
                    // 14 -> 52 , i.e. integer
                    case 22: strcat(itype,"ARRAY[INTEGER, ");
                    strcat(itype, sz);
                    strcat(itype, "]");
                    // ARRAY[TYPE, SIZE]

                    break;

                    // rule 14->53, i.e. REAL
                    case 23 : strcat(itype, "ARRAY[REAL, ");
                    strcat(itype, sz);
                    strcat(itype, "]");
                    break;

                    // rule number 24 : 14->54 , i.e. BOOLEAN
                    case 24 : strcat(itype, "ARRAY[BOOLEAN, ");
                    strcat(itype, sz);
                    strcat(itype, "]");
                    break;
                }
            }
            break;
        }
        parsetree iplist_prime = iplist->child->right->right;
        while(iplist_prime->rule != 11){
            // till the rule is not equal to  9 -> 109 (epsilon)
            switch (iplist_prime->child->right->rule)
            {
            // 13 -> 52
            case 18 : strcat(itype,"; INTEGER");
            break;
            // 13 -> 53
            case 19 : strcat(itype, "; REAL");
            break;
            // 13 -> 54
            case 20 : strcat(itype, "; BOOLEAN");
            break;
            // array : 13 - > 56, 101, 15, 102, 55, 14, 21 
            case 21 : 
            {
                parsetree range = iplist_prime->child->right->child->right;
                char sz[3], type[100] = {'\0'};
                
                switch(range->right->rule){
                // if the rule to right is :
                // 14 -> 52 , i.e. integer
                    case 22 : strcat(itype, "; ARRAY(INTEGER, ");
                    strcat(itype, sz);
                    strcat(itype, ")"); 
                    break;
                    // rule 14->53, i.e. REAL
                    case 23 : strcat(itype, "; ARRAY(REAL, ");
                    strcat(itype, sz);
                    strcat(itype, ")");
                    break;
                     // rule number 24 : 14->54 , i.e. BOOLEAN
                    case 24 : strcat(itype, "ARRAY[BOOLEAN, ");
                    strcat(itype, sz);
                    strcat(itype, "]");
                    break;
                }
            }
            break;
            }
        iplist_prime = iplist_prime->child->right->right;
        }

        // output calc
        if(head->right->right->rule != 13){
            // till return is not equal to epsilon , i.e. 10->109
            parsetree oplist = head->right->right->child->right;
            switch (oplist->child->right->rule)
            {
            case 22 : strcat(otype, "INTEGER");
                break;
            case 23 : strcat(otype, "REAL");
            break;
            case 24: strcat(otype, "BOOLEAN");
            break;
            }
            parsetree oplist_prime = oplist->child->right->right;
            while(oplist_prime->rule != 16){
                // 12 -> 109 , i.e. till the output_plist_prime is not epsilon(109)
                switch(oplist_prime->child->right->rule){
    
                    case 22 : strcat(otype, "; INTEGER");
                    break;

                    case 23: strcat(otype, "; REAL");
                    break;

                    case 24 : strcat(otype, "; BOOLEAN");
                    break;
                }
            oplist_prime = oplist_prime->child->right->right;
            }
        }

        hash_insert_function(head->Lex->tk->value, itype, otype);
        return;
    }
func_definition(fp, head->right, function_name);
}

// populating the symbol table
// final step in the symbol table creation

void fill_symbol_table(FILE *fp, parsetree head, char* scope){
    if(head == NULL){
        return;
    }
    if(head->value == 4){
        // driver module
        hash_insert_function("driver", "", "");
        strcpy(scope,"driver");
    }

    fill_symbol_table(fp, head->child, scope);
    if(head->value == 106){
        // an ID
        if(head->parent->value == 5){
            //module declaration
            
            // re declaration case
            if(check_func_present(head->Lex->tk->value)){
                fprintf(fp, "ERROR : Re - declaration of pre-defined function!");
            }
            
            else{
                parsetree root = head;
                while(root->value != 1){ // till it reaches the program
                    root = root->parent;
                }                
                func_definition(fp, root, head->Lex->tk->value);
            }
        }
        if(head->parent->value == 7){
            // module
            if(!check_func_present(head->Lex->tk->value)){
                func_definition(fp, head, head->Lex->tk->value);
            }
        }

        // module with different scope
        if(head->parent->value == 7){
            strcpy(scope, head->Lex->tk->value);
        }

        // 33 denotes idlist and 20 denotes declarative statements
        if(head->parent->value == 33 && head->parent->parent->value == 20){
            if(check_symbol(head->Lex->tk->value, scope)){
                fprintf(fp, "ERROR : Re - declaration of pre-defined function!");
            }
            switch(head->parent->right->rule){
                 // 13 -> 52
                case 18: hash_insert(head->Lex->tk->value, "INTEGER", scope , "~");
                break;
                // 13 -> 53
                case 19 : hash_insert(head->Lex->tk->value, "REAL", scope, "~");
                break;
                // 13 -> 54
                case 20 : hash_insert(head->Lex->tk->value, "BOOLEAN", scope, "~");
                break;
                // array : 13 - > 56, 101, 15, 102, 55, 14, 21 
                case 21 : {
                    parsetree range = head->parent->right->child->right;
                    char sz[3], type[100] = {'\0'};
                    switch (range->right->rule)
                    {
                    case 22 : strcat(type, "ARRAY(INTEGER, ");
                    strcat(type,sz);
                    strcat(type, ")");
                    break;
                    case 23: strcat(type, "ARRAY(REAL, ");
                    strcat(type, sz);
                    strcat(type, ")");
                    hash_insert(head->Lex->tk->value, type, scope,"~");
                    break;
                    }
                }
                break;
            }
        }
        if(head->parent->value == 34){
            // 34 --> idListprime
            parsetree temphead = head;
            while(temphead->parent->value != 33){
                temphead=temphead->parent;
            }
            // value is idlist and declare statements
            if(temphead->parent->value == 33 && temphead->parent->parent->value == 20){
                switch(temphead->parent->right->value){
                    case 18 : hash_insert(head->Lex->tk->value, "INTEGER", scope, "~") ;
                    break;
                    case 19 : hash_insert(head->Lex->tk->value,"REAL",scope,"~");
                    break;
                    case 20 : hash_insert(head->Lex->tk->value, "BOOLEAN", scope, "~");
                    break;
                    case 21 :
                    {
                        parsetree range = temphead->parent->right->child->right;
                        char sz[3], type[100] = {'\0'};
                        switch(range->right->rule){
                            case 22 : strcat(type, "ARRAY(INTEGER, ");
                                        strcat(type, sz);
                                        strcat(type, ")");
                                        hash_insert(head->Lex->tk->value, type, scope,"~");
                            break;
                            case 23 : strcat(type, "ARRAY(REAL, ");
                            strcat(type, sz);
                            strcat(type, ")");
                            hash_insert(head->Lex->tk->value, type, scope, "~");
                            break;

                            case 24 : strcat(type, "ARRAY(BOOLEAN, ");
                            strcat(type, sz);
                            strcat(type, ")");
                            hash_insert(head->Lex->tk->value, type, scope, "~");
                            break; 
                        }
                    }
                    break;
                }
            }
        }
        
        // input parameters
        
        if(head->parent->value == 8 || head->parent->value == 9){
            // if the value is input_plist or input_plistprime
            switch(head->right->rule){
                    case 18 : hash_insert(head->Lex->tk->value, "INTEGER", scope, "~") ;
                    break;
                    case 19 : hash_insert(head->Lex->tk->value,"REAL",scope,"~");
                    break;
                    case 20 : hash_insert(head->Lex->tk->value, "BOOLEAN", scope, "~");
                    break;
                    case 21 :
                    {
                        parsetree range = head->right->child->right;
                        char sz[3], type[100] = {"\0"};
                        switch(range->right->rule){
                            case 22 : strcat(type, "ARRAY(INTEGER, ");
                                        strcat(type, sz);
                                        strcat(type, ")");
                                        hash_insert(head->Lex->tk->value, type, scope,"~");
                            break;
                            case 23 : strcat(type, "ARRAY(REAL, ");
                            strcat(type, sz);
                            strcat(type, ")");
                            hash_insert(head->Lex->tk->value, type, scope, "~");
                            break;

                            case 24 : strcat(type, "ARRAY(BOOLEAN, ");
                            strcat(type, sz);
                            strcat(type, ")");
                            hash_insert(head->Lex->tk->value, type, scope, "~");
                            break; 
                        }
            }
            break;
        }
    }
    
    // output parameters
    if(head->parent->value == 11 || head->parent->value == 12){
        // output_plist or output_plistprime

        switch(head->right->value){
            case 22 : hash_insert(head->Lex->tk->value, "INTEGER", scope, "~");
            break;

            case 23 : hash_insert(head->Lex->tk->value, "REAL", scope, "~");
            break;

            case 24: hash_insert(head->Lex->tk->value, "BOOLEAN", scope, "~");
            break;
        }
    }

    if(head->parent->value != 7 && head->parent->value != 5 && head->parent->value != 26 && !check_symbol(head->Lex->tk->value, scope)){
        // if not module or module declaration or module reuse statement then error
        fprintf(fp, "ERROR : Undeclared Identifier!");
    }

    // module reuse
    if(head->parent->value == 26){
        if(!check_func_present(head->Lex->tk->value)){
            fprintf(fp, "Error : Function definition missing!");
        }
        else{
            char itype[1000] = {"\0"}, otype[1000] = {"\0"};
            if(head->parent->child->rule == 56){
                //START
                parsetree olist = head->parent->child->child;
                strcat(otype, type_value(olist->child->Lex->tk->value, scope));
                parsetree olist_prime = olist->child->right;

                while(olist_prime->rule!=59){
                    // 34 -> 109 , till the rule is not epsilon
                    strcat(otype, "; ");
                    strcat(otype, type_value(olist_prime->child->Lex->tk->value, scope));
                    olist_prime = olist_prime->child->right;
                }
            }
            parsetree ilist = head->right;
            strcat(itype, type_value(ilist->child->Lex->tk->value, scope));
            parsetree ilistprime = ilist->child->right;
            while(ilistprime->rule!=59){
                // not epsilon
                strcat(itype, "; ");
                strcat(itype, type_value(ilistprime->child->Lex->tk->value,scope));
                ilistprime = ilistprime->child->right;
            }
            if(strcmp(itype,  ret_function_input_type(head->Lex->tk->value))!=0){
                fprintf(fp, "ERROR : Input type mismatch");
            }
            if(strcmp(otype, ret_function_output_type(head->Lex->tk->value))!=0){
                fprintf(fp, "ERROR : Output type mismatch");
            }

        }
    }
    // checking the index of array is an integer
    if(head->parent->value == 24){
        //whichID
        if(strcmp(type_value(head->Lex->tk->value, scope), "INTEGER")!= 0 ){
            fprintf(fp, "ERROR : Index should be an integer.");
        }
        if(head->parent->rule == 41 && head->right->rule==44){
            // rule 41 : 23 -> 106, 24
            // rule 44 : 24 -> 101, 106, 102
            char *tok = NULL;
            tok = strtok(type_value(head->Lex->tk->value, scope), "(");
            if(tok == NULL){fprintf(fp, "ERROR : Indexing not done on array!");}
            if(strcmp(tok, "ARRAY")!=0){fprintf(fp, "Indexing not done on array!");}

        }
    }
    }
    if(head->value == 21){
        // conditional statement
        int t2, e = 0, t1 = Typechecker(fp, head->child->right, scope);
        parsetree case_statement = head->child->right->right->right;
        if(t1 == 1){
            // real values
            fprintf(fp, "Real type cannot be in switch statement!");
        }

        else{if(t1 == -1 && case_statement->right->rule == 84){
            // if the type is boolean with default val
            fprintf(fp, "Identifier of Boolean type cannot have default statement!");
        }
        if(t1 == 0 && case_statement->right->rule != 85){
            //integer without default statement 
            fprintf(fp, "Missing default statement!");
        }
        while(case_statement->child->value !=109){
            // till the case statements reach epsilon
            t2 = Typechecker(fp, case_statement->child->right->child, scope);
            if(t1 == t2){
                case_statement=case_statement->child->right->right->right->right;
            }
            else{
                e = 1;//error
                break;
            }
        }
        }
        if(e){
            fprintf(fp, "ERROR : Different type of switch statement found!");
        }
    }
    if(head->value == 22 && head->rule == 39){
        // if the value of head is iterative statement
        // for loop
        int t = Typechecker(fp, head->child->right,scope);
        if(t){
            fprintf(fp, "ERROR : Identifier must be of type INTEGER");
        }
    }
    if(head->value == 22 && head->rule == 40){
        // while loop
        int t = Typechecker(fp, head->child->right, scope);
        if(t!=-1){
            fprintf(fp, "ERROR : While loop expression isn't BOOL.");
        }
    }
        fill_symbol_table(fp, head->right,scope);
    }
