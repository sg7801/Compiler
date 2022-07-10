#include<stdio.h>
#include<stdlib.h>
#include"symboltable.c"
int i = 0, r = 0, j = 0, output_cnt = 0, for_num = 0, rel_num = 0, while_num = 0, curr_state = 0;
// function to declare variables
void var_declare(parsetree head, FILE *fp){
    char* function_name = "driver";
    j = func_hash_value(function_name);
    for(i=0;i<SIZE;i++){
        pnode* iterator = ht->function_table[j]->table[i]->next;
        if((iterator!=NULL) && (strcmp(iterator->name,"")!=0)){
            char *x = "ARRAY";
            if(strncmp(iterator->type, x, 5)!=0){
                // if the iterator type is ARRAY
                fprintf(fp, iterator->name);
            }
            else{
                // if not array
                char* type = iterator->type; // iterator's type stored in type
                char* t = NULL; // token is null 
                t = strtok(iterator->type, "(");
                if(t!=NULL){
                    // till the token is not null
                    t = strtok(NULL, ",");
                    t = strtok(NULL, ")");
                    if(t!=NULL){
                        strcpy(type, t);
                    }
                }
            }
        }
    }
}

// codegenerator function
void code_generator(parsetree head, FILE*fp){
    var_declare(head, fp);
}

// generating the code expressions
void code_ex(FILE* fp1, parsetree head, FILE*fp, char* scope){
    int x = 0, y = 0, z = 0 ;
    if((head == NULL) || (head->value == 109)){
        // if the head is null or epsilon then return 
        return ;
    }
    code_ex(fp1, head->child, fp, scope);
    switch(head->value){

        case 73 : // if the value is OR
        if(head->parent->parent->parent->value == 42){
            // if the value is arithmetic expression
            // recursive calls for children and right child of head
            code_ex(fp1, head->parent->parent->parent->child, fp, scope);
            code_ex(fp1, head->parent->right, fp, scope);
        }
        if(head->parent->parent->parent->value == 48){
            // if the N9
            code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
            code_ex(fp1, head->parent->right, fp, scope);
        }
        return ;
        case 74: // FOR Loop
        if(head->parent->parent->parent->value == 42){
            // if the value is arithmetic boolean expression

            //recursive calls to children and right of head
            code_ex(fp1, head->parent->parent->parent->child, fp, scope);
            code_ex(fp1, head->parent->right, fp, scope);
        }
        if(head->parent->parent->value == 48){
            // if the value is N9
            //recursive calls to children and right of head
            code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
            code_ex(fp1, head->parent->right, fp, scope);
        }
        return;

        case 82: // MINUS 
        if(!curr_state){
            //if the curr_state is 0
            if(head->parent->parent->parent->value == 38){
                // if the value of the parent arithmetic_expression_prime
                curr_state = 1;
                // recursive call for children
                code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
                // recursive call for the right of parent
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt=0;
            }
                // if the value is an arithmetic expression
                if(head->parent->parent->parent->value == 35){
                    curr_state = 1;
                    // recursive call to children
                    code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                    // recursive call to right of parent
                    code_ex(fp1, head->parent->right, fp, scope);
                    curr_state = 0;
                    output_cnt= 0;
                }
        } 
        return;

        case 83: // if the value is MULTIPLICATION
        if(head->value == 83 && head->parent->value == 30){
            // if the value of head is MULTIPLICATION and parent is an expression
            //recursive call to right
            code_ex(fp1, head->right, fp, scope);
            return;
        }
        else{
            if(!curr_state){
                if(head->parent->parent->parent->value == 38){
                    // if the value is arithmetic expresssion and curr_state is 0
                    curr_state = 1;
                    code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
                    code_ex(fp1,head->parent->right, fp, scope);
                    curr_state = 0 ;
                    output_cnt = 0;
                }
                if(head->parent->parent->parent->value == 35){
                    // if it is an arithmetic expression
                    curr_state = 1;
                    code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                    code_ex(fp1, head->parent->right, fp, scope);
                    curr_state = 0;
                    output_cnt = 0;
                }
            }
            return;
        }

        case 84 : // if the value is DIV
        if(!curr_state){
            // if the curr_state is 0
            if(head->parent->parent->parent->value == 41){
                // if the value is termprime
                curr_state = 1;
                // recursive call to child
                code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
                // recursive call to right
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            // if the value is a term 
            if(head->parent->parent->parent->value == 37){
                curr_state = 1;
                // recursive call to the children
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                // recursive call to the right of head
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
        } 
        return;

        case 85:// if the value is Less than (<)
        if(!curr_state){
            // if the curr_state is 0
            if(head->parent->parent->parent->value = 41){
                // if the value is termprime
                curr_state = 1;
                // recursive call to children
                code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
                // recursive call to the right of head
                code_ex(fp, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            if(head->parent->parent->parent->value == 37){
                // if the value is a term
                curr_state = 1;
                // recurisve call for children
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                //recusive call for the right of head
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0; output_cnt = 0;
            }
        }
        return ;

        case 86: // Less than equal to (<=)
        if(!curr_state){
            // if curr_state is 0
            assert(0);
            if(head->parent->parent->parent->value == 43){
                // if the value is anyterm
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            if(head->parent->parent->parent->value == 49){
                // if the value is N8
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            rel_num++;
        }
        return;
        
        case 87:
        // Equal to (==)
        if(curr_state == 0){
            if(head->parent->parent->parent->value == 43){
                // if the value is anyterm
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            if(head->parent->parent->parent->value == 49){
                // if the value is N8
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            rel_num++;
        }
        return;

        case 88 : // greater than equal to (>=)
        if(curr_state == 0){
            if(head->parent->parent->parent->value == 43){
                // if the value is any term
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            if(head->parent->parent->parent->value == 49){
                // if the value is N8
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
        }
        return;

        case 89 : // if the value is greater than (>)
        if(curr_state == 0){
            if(head->parent->parent->parent->value == 43){
                // if the value is anyterm
                curr_state = 1;
                code_ex(fp1,head->parent->parent->parent->child, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            if(head->parent->parent->parent->value == 49){
                // if the value is N8
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            rel_num++;
        }
        return;
        
        case 90: // if the value is equality (=)
        if(curr_state == 0){
            if(head->parent->parent->parent->value == 43){
                // if the value is anyterm
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            if(head->parent->parent->parent->value == 49){
                // if the value is N8
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child->right, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0; 
            }
            rel_num++;
        }
        return;

        case 91 : // if the value is not equal to (!=)
        if(curr_state == 0){
            if(head->parent->parent->parent->value == 43){
                // anyterm
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            if(head->parent->parent->parent->value == 49){
                curr_state = 1;
                code_ex(fp1, head->parent->parent->parent->child, fp, scope);
                code_ex(fp1, head->parent->right, fp, scope);
                curr_state = 0;
                output_cnt = 0;
            }
            rel_num++;
        }
        return;

        case 106 : // if head refers to ID 
        if(head->parent->parent->parent->value == 37){
            // if the value is a term
            if((Typechecker(fp1, head, scope)) == 0 && head->parent->parent->right->rule == 70 && head->parent->parent->parent->right->rule==65 && curr_state==0){
                // if the pointer points to INTEGER and rule is termprime -> epsilon and arithmetic_expression_prime -> epsilon
                // & curr_state of expression is 0
                return;
            }

        }
        if(Typechecker(fp1, head, scope) == 0 && curr_state == 1){
            // if the Typechecker return 0, i.e. INTEGER and curr_state is 1
            output_cnt++;
            if(output_cnt<=2){
                return;
            }
        }
        else{}
        break;

        case 107 : // if value refers to NUM 
        if(head->parent->parent->parent->value == 37 && curr_state ==0){
            //if its a term && curr_state of expression is 0
            if(head->parent->parent->right->rule == 70 && head->parent->parent->parent->right->rule == 65){
                // if termprime -> epsilon or arithmetic expression -> epsilon
                fprintf(fp, "%s", head->Lex->tk->value);
                return;  
            }
        }
        if(curr_state == 1){
            // if expression's curr_state is 1 , i.e. comment or multiplication
            output_cnt++;
            if(output_cnt <= 2){
                return;
            }
        }
        break;

        default : break;
    }
    // recursive call to right of the head
    code_ex(fp1, head->right, fp, scope);
} 

// function to generate the code curr_statements
void generate_code(FILE *fp1, parsetree head, FILE* fp, char* scope){
    if(head == NULL){ // if the head is null then return
        return ;
    }
    if(head->value == 4){ // value is drivermodule 
        strcpy(scope, "driver");
    }
    if(head->value == 106 && head->parent->value == 7){
        // if the value of head is ID and parent value is module
        strcpy(scope, head->Lex->tk->value);
    }   
    switch(head->value){
        case 22 : // if the value is an iterative curr_statement
         if(head->generated!=1){
            // if the head is not generated
            if(head->rule == 40){
                // if the rule is 22(iterative curr_statement) -> 81, 103, 42, 104, 57, 16, 58
                curr_state = 0;
                code_ex(fp1, head->child->right, fp, scope);
                generate_code(fp1, head->child->right->right->right, fp, scope);
                while_num++;
            }
            if(head->rule == 39){
                // if the rule is 22 -> 75, 103, 106, 76, 15, 104, 57, 16, 58
                curr_state = 0;
                parsetree x = head->child->right;
                int s = atoi(x->right->right->child->Lex->tk->value);
                int e = atoi(x->right->right->child->right->right->Lex->tk->value);
                generate_code(fp1,head->child->right->right->right->right, fp, scope);
                for_num++;
            }
         } 
         head->generated = 1;
         break;

         case 18 : if(head->generated!=1){
            if(head->child->value == 63){
                //if the value is PRINT
                fprintf(fp, "PUSH\n %s",head->child->right->Lex->tk->value);
                }
                else{
                    if(!(head->child->right->rule == 41 && head->child->right->child->right->rule == 44)){
                        // rules for right of child are 23->106, 24 for variable
                        // or 24 -> 101, 106, 102 for a whichID
                        if(head->child->right->rule == 41){
                            fprintf(fp, "\nPUSH %s ", head->child->right->child->Lex->tk->value);
                        }
                        else{
                            fprintf(fp, "PUSH %s", head->child->right->child->Lex->tk->value );
                        }
                    }
                }
         }
         head->generated = 1;
         break; 
    }
    generate_code(fp1, head->child, fp, scope);
    switch(head->value){
        case 4 : strcpy(scope, "driver");
        // if the value is drivermodule
        break;
        case 100 : // if the value is ASSIGNOP
        if(head->generated != 1){
            if(head->parent->value == 28){
                // if the value is LValueIDStmt
                parsetree identifier = head->parent->parent->parent->child;
                int type = Typechecker(fp1, identifier, scope);
                if(!type){
                    code_ex(fp1, head->right, fp, scope);
                }
                head->generated = 1;
            }
        }
        break;
        case 106 : // if the value is ID
        if(head->parent->value == 7){
            // if the value is module
            strcpy(scope, head->Lex->tk->value);
        }
        break;
    }
    generate_code(fp1, head->right, fp, scope);
}

