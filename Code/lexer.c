#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

static int linenum = 1;
int state = 0;
static int end = 0;
char buff[3000]; // buffer
FILE *fp1;
static int begin = 0;

// Tokens
char* token_values[] = {"WHILE", "DEFAULT", "BREAK", "CASE", "SWITCH", "IN", "AND", "OR", "FOR", "TRUE", "FALSE", "RETURNS", "TAKES","INPUT","PRINT", "USE","WITH","PARAMETERS", "DECLARE", "MODULE", "DRIVER", "PROGRAM", "GET_VALUE","START", "END","ARRAY","INTEGER", "REAL","BOOLEAN","OF"};

// Keywords
char* keyword_values[] = {"while", "default", "break", "case", "switch","in", "AND", "OR", "for", "true", "false", "return", "takes", "input", "print", "use", "with", "parameters", "declare", "module", "driver", "program","get_value", "start", "end", "array", "integer", "real", "boolean","of"};
typedef char* buffer;

// Inside a token
struct TokenInformation{
    char token[30];
    char value[30];
    int line;
};

typedef struct TokenInformation tokeninformation;

// Abstract syntax tree of Lexer as node including token info
struct Node{
    tokeninformation* tk;
};

typedef struct Node node;

// Head containing Node 
struct head{
    struct Node* headlink;
};
typedef struct head *header;

// Declare Essential Functions
FILE* getstream(FILE *fp);
node* createnode();

// Buffer Flush
void buffer_flush(char* str){
    int k;
    for(k = 0; k < 3000; k++){
        str[k] = '\0';
    }
}

void flush(char* str){
    int k;
    for(k = 0; k < 30; k++){
        str[k] = '\0';
    }
}

// function to make the node of lexer
node* createnode(){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->tk = (tokeninformation*)malloc(sizeof(tokeninformation));
    return new_node;
}

// initialise the head
header head_initialise(){
    header new_head = (header)malloc(sizeof(struct head));
    new_head->headlink = NULL;
    return new_head;
}

// Loading Buffer
FILE* loadbuffer(){
    fseek(fp1, 0, SEEK_CUR);
    fp1 = getstream(fp1);
    buff[2998] = '~';
    return fp1;
}

// Removal of comments 
int remove_comments(char* buff, int forward){
    while(!((buff[forward] == '*') && (buff[forward+1] == '*'))){
        forward++;
        if(buff[forward] == '\n'){
            linenum++;
        }
    }
    return forward;
}

// Removal of newline characters '\n'
int remove_newlines(char*buff, int forward){
    while(buff[forward] == '\r' && buff[forward++] == '\n'){
        linenum++;
        forward++;
    }
    return forward;
}

// Checking for non-terminal keywords
char* check_keywords(char val[]){
    char *c;
    c = (char*)malloc(sizeof(char)*30);
    int k;
    for(k = 0;k<30;k++){
        if(strcmp(val, keyword_values[k]) == 0){
            strcpy(c, token_values[k]);
            return c;
        }
    }
    char output[9] = "NO_VALUE";
    strcpy(c,output);
    return c;
}

// remove comments from test case files
void remove_test_comments(char *testcase){
    FILE*f1 = fopen(testcase , "+r");
    if(f1 == NULL){
        printf("Error");
        return;
    }
    char c;
    while(!feof(f1)){
        c = fgetc(f1);
        if(c == '$'){
            break;
        }
        if(c == '*'){
            if(c == fgetc(f1) == '*'){
                while (!((c = fgetc(f1) == '*') && (c = fgetc(f1) == '*'))){
                    continue;
                }
                c = fgetc(f1);
            }
        }
        fputc(c, stdout);
        }
    fclose(f1);
}


// read data and put into buffer, then return the pointer 
FILE* getstream(FILE* fp){
    int length = 3000, k ;
    buffer_flush(buff);
    if(fp == NULL){
        printf("Invalid\n");
        exit(0);
    }

    //buffer flush
    for(k = 0;k<length;k++){
        buff[k] = '\0';
    }
    
    if(fread(buff,(size_t)length, 1, fp)){
            return fp;
    }

    return NULL;
}

// generation of tokens or lexemes
int total_tokens = 0;
node* token_generation(){
    char c, value[30], token[30];
    int length = 0;
    flush(value);
    flush(token);

    while(1){
        c = buff[end];
        switch (state)
        {
        case 0 :
            if (c == '$')
            {
                node* Lex = createnode();
                strcpy(Lex->tk->token, "END");
                strcpy(Lex->tk->value, "$");
                Lex->tk->line = linenum;
                linenum = 1;
                begin = 0;
                state = 0;
                return Lex;
                break;
            }
            else if(c == '/'){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "DIV");
                strcpy(Lex->tk->value, "/");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            
            else if(c == '+'){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "PLUS");
                strcpy(Lex->tk->value, "+");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c =='-'){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "MINUS");
                strcpy(Lex->tk->value, "-");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c == ';'){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "SEMICOL");
                strcpy(Lex->tk->value, ";");
                Lex->tk->line = linenum;
                total_tokens++;
                length = 0;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c == ','){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "COMMA");
                strcpy(Lex->tk->value, ",");
                Lex->tk->line = linenum;
                total_tokens++;
                length = 0;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c == '['){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "SQBO");
                strcpy(Lex->tk->value, "[");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c == ')'){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "BC");
                strcpy(Lex->tk->value, ")");
                Lex->tk->line = linenum;
                total_tokens++;
                length = 0;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c == '\r'){
                c = buff[++end];
                if(c == '\n'){
                    c = buff[++end];
                }
                linenum++;
                state = 0;
                break;
            }
            else if (c == ' ' || c == '\t')
            {
                c = buff[++end];
                state = 0;
                break;
            }
            else if(c == ']'){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "SQBC");
                strcpy(Lex->tk->value, "]");
                Lex->tk->line = linenum;
                total_tokens++;
                length = 0;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c == '('){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "BO");
                strcpy(Lex->tk->value, "(");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                length = 0;
                state = 0;
                return Lex;
                break;
            }
            else if(c == '*'){
                c = buff[++end];
                state = 1;
                break;
            }
            else if(c == ':'){
                c = buff[++end];
                state = 2;
            }
            else if (c=='=')
            {
                state = 3;
                c = buff[++end];
            }
            else if (c == '<')
            {
                c = buff[++end];
                state = 4;
            }
            else if (c == '>')
            {
                c = buff[++end];
                state = 5;
            }
            else if (c == '!')
            {
                c = buff[++end];
                state = 6;
            }
            else if (isalpha(c))
            {
                value[length] = c;
                length++;
                c = buff[++end];
                state = 8;
            }
            
            else if (isdigit(c))
            {
                value[length] = c;
                length++;
                c = buff[++end];
                state = 9;
            }
            else{
                node* Lex = createnode();
                strcpy(Lex->tk->token, "Error");
                strcpy(Lex->tk->value, "No_Token");
                printf("Error : Unknown Pattern %s at line %d\n", value, length);
                Lex->tk->line = linenum;
                total_tokens++;
                flush(value);
                end++;
                begin = end;
                state = 0;
                return Lex;
            }
            break;
            
    case 1:
            if (c == '*')
            {// ** comment **
                state = 0;
                end = remove_comments(buff, end);
                end += 2;
                begin = end;
                break;
            }
            else{
                node* Lex = createnode();
                strcpy(Lex->tk->token, "MUL");
                strcpy(Lex->tk->value, "*");
                Lex->tk->line = linenum;
                total_tokens++;
                length = 0;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            break;
    case 2:
            if(c == '='){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "ASSIGNOP");
                strcpy(Lex->tk->value, ":=");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else{
                node* Lex = createnode();
                strcpy(Lex->tk->token, "COLON");
                strcpy(Lex->tk->value, ":");
                Lex->tk->line = linenum;
                total_tokens++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            break;
    case 3: if(c == '='){
            node* Lex = createnode();
                strcpy(Lex->tk->token, "EQ");
                strcpy(Lex->tk->value, "==");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else {
                node* Lex = createnode();
                strcpy(Lex->tk->token, "Error");
                strcpy(Lex->tk->value, "=");
                printf("Unidentified token %s at line %d", value, linenum);
                Lex->tk->line = linenum;
                total_tokens++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            break;
    case 4: if(c == '='){
            node* Lex = createnode();
                strcpy(Lex->tk->token, "LE");
                strcpy(Lex->tk->value, "<=");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c == '<'){
                node* Lex = createnode();
                c = buff[++end];
                if(c == '<'){
                    strcpy(Lex->tk->token, "DRIVERDEF");
                    strcpy(Lex->tk->value, "<<<");
                    Lex->tk->line = linenum;
                    total_tokens++;
                    end++;
                    begin = end;
                    state = 0;
                    return Lex;
                break;
                }
                else{
                    strcpy(Lex->tk->token, "DEF");
                strcpy(Lex->tk->value, "<<");
                Lex->tk->line = linenum;
                total_tokens++;
                begin = end;
                state = 0;
                return Lex;
                break;
                }
            }
            else{
                node* Lex = createnode();
                strcpy(Lex->tk->token, "LT");
                strcpy(Lex->tk->value, "<");
                Lex->tk->line = linenum;
                total_tokens++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            break;
    case 5 : 
            if(c == '='){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "GE");
                strcpy(Lex->tk->value, ">");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else if(c == '>'){
                node* Lex = createnode();
                c = buff[++end];
                if(c == '>'){
                    node* Lex = createnode();
                    strcpy(Lex->tk->token, "DRIVERENDDEF");
                    strcpy(Lex->tk->value, ">>>");
                    Lex->tk->line = linenum;
                    total_tokens++;
                    end++;
                    begin = end;
                    state = 0;
                    return Lex;
                    break;
                }
                else{
                    node* Lex = createnode();
                    strcpy(Lex->tk->token, "ENDDEF");
                    strcpy(Lex->tk->value, ">>");
                    Lex->tk->line = linenum;
                    total_tokens++;
                    begin = end;
                    state = 0;
                    return Lex;
                    break;
                }
            }
            else{
                    node* Lex = createnode();
                    strcpy(Lex->tk->token, "GT");
                    strcpy(Lex->tk->value, ">");
                    Lex->tk->line = linenum;
                    total_tokens++;
                    begin = end;
                    state = 0;
                    return Lex;
                    break;
            }
            break;
    case 6:
           if(c == '='){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "NE");
                strcpy(Lex->tk->value, "!=");
                Lex->tk->line = linenum;
                total_tokens++;
                end++;
                begin = end;
                state = 0;
                return Lex;
                break;
           } 
           else{
                node* Lex = createnode();
                strcpy(Lex->tk->token, "ERROR");
                strcpy(Lex->tk->value, "!");
                Lex->tk->line = linenum;
                printf("Unidentified token %s at line %d", value, linenum);
                total_tokens++;
                begin = end;
                state = 0;
                return Lex;
                break;
           }
           break;
    case 7: 
            if(c == '.'){
                node* Lex = createnode();
                strcpy(Lex->tk->token, "RANGEOP");
                strcpy(Lex->tk->value, "..");
                Lex->tk->line = linenum;
                end++;
                total_tokens++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
            else{
                node* Lex = createnode();
                strcpy(Lex->tk->token, "ERROR");
                strcpy(Lex->tk->value, "!");
                Lex->tk->line = linenum;
                printf("Unidentified token %s at line %d", value, linenum);
                total_tokens++;
                begin = end;
                state = 0;
                return Lex;
                break;
            }
    case 8: 
            if(isalnum(c) || (c == '_') && (c != '$')){
                value[length] = c;
                length++;
                c = buff[++end];
                state = 8;
                begin = end;
                break;
            }
            else{
                char *position = check_keywords(value);
                if(strcmp(position , "SORRY")!=0){
                    node * Lex = createnode();
                    strcpy(Lex->tk->token, position);
                    strcpy(Lex->tk->value, value);
                    Lex->tk->line = linenum;
                    total_tokens++;
                    state = 0;
                    length = 0;
                    begin = end;
                    flush(value);
                    return Lex;
                    break;
                }
                else{
                    if(length <=9){
                        node* Lex = createnode();
                        strcpy(Lex->tk->token, "ID");
                        strcpy(Lex->tk->value, value);
                        Lex->tk->line = linenum;
                        total_tokens++;
                        state = 0;
                        length = 0;
                        begin = end;
                        flush(value);
                        return Lex;
                        break;
                    }
                    else{
                        node* Lex = createnode();
                        strcpy(Lex->tk->token, "ERROR");
                        strcpy(Lex->tk->value, "Range_Error");
                        Lex->tk->line = linenum;
                        printf("Error on line %d: Identifier exceeds the length limit", linenum);
                        total_tokens++;
                        state = 0;
                        length = 0;
                        begin = end;
                        flush(value);
                        return Lex;
                        break;
                    }
                }
            }
    case 9 : 
            if (isdigit(c))
            { // numerical values contd
                value[length] = c;
                length++;
                state = 9;
                c = buff[++end];
                begin = end;
                break;
            }
            else if(c == '.' && buff[end+1] != '.'){
                value[length] =c;
                length++;  
                c = buff[++end];
                if(isdigit(c)){
                    // decimal num
                    state = 10;
                    value[length] = c;
                    length++;
                    c = buff[++end];
                    begin = end;
                    break;
                }
                else{ // num..
                    node* Lex = createnode();
                    strcpy(Lex->tk->token , "ERROR");
                    strcpy(Lex ->tk->value, "Num_Error");
                    Lex->tk->line = linenum;
                    total_tokens++;
                    printf("Error : Numerical Error at line %d", linenum);
                    state = 0;
                    length = 0;
                    begin = end;
                    flush(value);
                    return Lex;
                    break;
                }

            }
            else{ // any other case
                node* Lex = createnode();
                strcpy(Lex->tk->token , "NUM");
                    strcpy(Lex ->tk->value, value);
                    Lex->tk->line = linenum;
                    total_tokens++;
                    flush(value);
                    state = 0;
                    length = 0;
                    begin = end;
                    return Lex;
                    break;
            }            
            break;

        case 10:
                // values after point
                if(isdigit(c)){
                    value[length] = c;
                    length++;
                    c = buff[++end];
                    state = 10;
                    break;
                }
                else if(c == 'e' || c == 'E'){
                    // Exponent and mantissa 
                    value[length] = c;
                    length++;
                    c = buff[++end];
                    // Eg : 10E-2 or 10E+2
                    if(c == '-' || c == '+'){
                        value[length] = c;
                        length++;
                        c = buff[++end];
                    }
                    else {//by default '+' ,eg: 10E2
                        value[length] = '+';
                        length++;
                        c = buff[end];
                    }
                    state = 10;
                    break;
                }
                else{

                    // other cases
                    node* Lex = createnode();
                    strcpy(Lex->tk->token, "RNUM");
                    strcpy(Lex->tk->value, value);
                    Lex->tk->line = linenum;
                    total_tokens++;
                    state = 0;
                    length = 0;
                    begin = end;
                    flush(value);
                    return Lex;
                    break;   
                }
                break;
     }
    }
}
