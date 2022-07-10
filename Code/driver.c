#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"codegenerator.c"
int table[NON_TERMINALS][TERMINALS]; // parsing table
int main(int k, char* l[]){
    int symbol_count = 0, inp = 0 , a = 0, b = 0, flag = 0, t = 0, nodes[1] = {0}, ast_node[1] = {0};
    if(k!=3){
        printf("Enter correct format\n");
        return 0;
    }
    
	printf("\nIMPLEMENTED PHASES :\n\t Lexer \n\t Abstract Syntax Tree \n\t Symbol Table \n\t Semantic Analysis \n\t Type Checking \n\t Code Generation \n");
	printf("\n1 : Press 1 for token list \n2 : Press 2 for parsing & generating the Parse Tree \n3 : Press 3 for printing AST \n4 : Press 4 for displaying number of nodes allocated\n5 : Press 5 to print the Symbol Table\n6 : Press 6 for checking the Type and Semantic Verification\n7 : Press 7 for Code Generation\n0 : Exit\n\n");
    FILE *x = fopen("test.txt", "a");
    FILE *y = fopen("temp.txt", "w");
    FILE *semantic = fopen("Error.txt", "w+");
    if(x == NULL){
        printf("ERROR : NO FILE FOUND !\n");
        return 0;
    }
    if(y == NULL){
        printf("ERROR : NO FILE FOUND !\n");
        return 0;
    }
    fprintf(x, "%s", "\n$");
    fclose(x);
    create_symbol_table();
    FILE *q = fopen("text.txt", "r");
    parsetree head = NULL;
    scanf("%d\n", &inp);
    do{
        if(inp == 1){
            rewind(q);
            fseek(q, 0, SEEK_SET);
            q = getstream(q);
            node* Lex = token_generation();
            int i = 1,  j = 0;
             while(strcmp(Lex->tk->value, "$")!=0){
                if(strcmp(Lex->tk->token, "ERROR")==0){
                    j++;
                }
                else{
                    printf("%d. token = %s, value = %s, line = %d\n", i++,Lex->tk->token, Lex->tk->value, Lex->tk->line);
                }
                free(Lex);
                node* Lex = token_generation();
             }
            printf("\nTOTAL TOKENS :- %d\n",i+j);
			printf("VALID :- %d\n",i);
		    printf("INVALID :- %d\n",j);
        }
        if(inp == 2){
            int first[51][11] = {-1}, follow[51][15] = {-1};
            find_first_and_follow(Grammar, first, follow);
            initialise(table);
            make_parse_table(table, Grammar);
            initialise();
            head = parse_source_code("test.txt");
       		count(head, nodes);
       		populate(head,"test.txt");
			printf("\nTREE TRAVERSAL:  PRE ORDER\n");
    		print_tree(head);
            flag = 2;
        }
        if(inp == 3){
            if(head == NULL || flag < 2){
                // if second phase not done yet
                printf("Run Parser before this phase!");
            }
            else{
                ast(head);
                count(head, ast_node);
                printf("\nPREORDER TREE TRAVERSAL\n");
                print_tree(head);
                flag = 3;
            }
        }
        if(inp == 4){
            if(flag < 3){
                // if third phase not done yet
                printf("Construct an Abstract Syntax Tree first!\n");
            }
            else{
                a = nodes[0]*sizeof(struct Parsetree);
                b = ast_node[0]*sizeof(struct Parsetree)/2;
                printf("\nParse tree\t\tNumber of nodes = %d Allocated Memory = %d Bytes\n",nodes[0],nodes[0]*sizeof(struct Parsetree));
			    printf("Abstract Syntax tree\tNumber of nodes = %d Allocated Memory = %d Bytes\n",ast_node[0]/2,ast_node[0]*sizeof(struct Parsetree)/2);
                float ans = ((float)((a - b)*100)/ (float)(a));
                printf("Compression done by : %.3f\n", ans);
            }   
        }
        if(inp == 5){
            if(flag < 3){
                printf("Construct an Abstract Syntax Tree first!\n");
            }
            else{
                if(symbol_count == 0){
                    char scope[100];
                    memset(scope, '\0', sizeof(scope));
                    fill_symbol_table(semantic, head, scope);
                    disp_symbol_table();
                    symbol_count = 1;
                }
                else{
                    printf("Symbol Table has been printed!");
                }
            }
        }
        if(inp == 6){
            if(semantic != NULL){
                fclose(semantic);
                FILE *fp = fopen("Errors.txt", "r");
                fseek(fp, 0, SEEK_SET);
                char c = fgetc(fp);
                while(c!=EOF){
                    printf("%c",c);
                    c = fgetc(fp);
                    t++;
                }
                flag = 6;
                fclose(fp);
                if(t == 0){
                    printf("\n Compilation Successful!");
                }
            }
        }
        if(inp == 7){
            FILE* fp = fopen("ign.txt", "W");
            if(flag < 6 || t != 0){
                // if previous phase has not been completed
                printf("Perform previous phase first!");
            }
            else{
                char scope[100];
                memset(scope, '\0', sizeof(scope));
                code_generator(head, y);
                generate_code(fp, head, y, scope);
            }
            fclose(y);
        }
        printf("\n 1 : Press 1 for token list \n2 : Press 2 for parsing & generating the Parse Tree \n3 : Press 3 for printing AST \n4 : Press 4 for displaying number of nodes allocated\n5 : Press 5 to print the Symbol Table\n6 : Press 6 for checking the Type and Semantic Verification\n7 : Press 7 for Code Generation\n0 : Exit\n\n");
        scanf("%d", &inp);
    }
    while(inp == 1 || inp == 2 || inp == 3 || inp == 4 || inp == 5 || inp == 6 || inp == 7);
    printf("Thanks! Have a nice day!");
    return 0;
}