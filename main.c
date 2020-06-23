#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void main()
{
    FILE *file;
    file = fopen("code.psi.txt","r");

    FILE *tokens;
    tokens = fopen("tokens.txt","w");

    int size;
    fseek(file,0,SEEK_END);
    size = ftell(file);
    fseek(file,0,SEEK_SET);

    char chr;
    chr = getc(file);

    while (chr != EOF){

        char keywords [] = "break,case,char,const,continue,do,else,enum,float,for,goto,if,int, long,record,return,static,while";
        char operators [] = "+,-,*,/,++,--,:=";

        int index = 0;
        char *puncts;
        puncts = (char*) calloc (2,sizeof(char));


        char *token;
        token = (char*) calloc (20,sizeof(char));//max size is 20 for keywords and identifiers

        while(isdigit(chr) || isalpha(chr)){ //for identifiers,keywords and integer constants

            //printf("%c",chr); to control reading from file
            token [index] = chr;
            index++;
            chr = getc(file);

        }
        if(isalpha(token[0])){

            char *ptr;
            ptr = strtok(keywords,",");

            while (ptr != NULL){//control loop if token is a keyword.

                    int isTheSame = strcmp(token,ptr);
                    if(isTheSame == 0){

                        fprintf(tokens,"Keyword (%s)\n",token);
                        printf("Keyword (%s)\n",token);
                        break;
                    }
                    else{
                        ptr = strtok(NULL,",\000");
                    }
                    if(ptr == NULL && isTheSame != 0){
                            fprintf(tokens,"Identifier (%s)\n",token);
                            printf("Identifier (%s)\n",token);
                            if(strlen(token) > 20){
                                fprintf(tokens,"Size error! Maximum identifier size is 20 characters.\n");
                                printf("Size error! Maximum identifier size is 20 characters.\n");
                            }
                        }
                }


            }
            if(isdigit(token[0])){

                fprintf(tokens,"IntConst(%s)\n",token);
                printf("IntConst(%s)\n",token);
                if(strlen(token) > 10){
                    fprintf(tokens,"Size error! Maximum integer size is 10 digits.\n");
                    printf("Size error! Maximum integer size is 10 digits.\n");
                }

            }

            free(token);


            if(isspace(chr)){
                chr = getc(file);
                continue;
            }

            if(ispunct(chr)){

                if(chr == 40){//40 equals ( in ASCII

                    chr = getc(file);
                    if (chr == 42){//42 equals * in ASCII
                        chr = getc(file);
                        while (chr != 42){
                            chr = getc(file);

                            if (chr == EOF){
                            fprintf(tokens,"Unterminated Comment Error! A comment cannot terminate before the file end.\n");
                            printf("Unterminated Comment Error! A comment cannot terminate before the file end.\n");
                            break;
                            }
                        }
                        chr = getc(file);
                        if(chr == 41){//41 equals ) in ASCII
                            //fprintf(tokens,"it's a comment\n");
                            printf("it's a comment\n");//to control if it works
                            chr = getc(file);
                            continue;
                        }
                        else{
                            chr = getc(file);
                        }
                    }
                    else{
                        fprintf(tokens,"LeftPar\n");
                        printf("LeftPar\n");
                        chr = getc(file);
                        continue;
                    }
                }
                else if (chr == 41){
                    fprintf(tokens,"RightPar\n");
                    printf("RightPar\n");
                    chr = getc(file);
                    continue;
                }
                else if(chr == 91){//91 equals [ in ASCII
                    fprintf(tokens,"LeftSquareBracket\n");
                    printf("LeftSquareBracket\n");
                    chr = getc(file);
                    continue;

                }
                else if(chr == 93){//93 equals ] in ASCII
                    fprintf(tokens,"RightSquareBracket\n");
                    printf("RightSquareBracket\n");
                    chr = getc(file);
                    continue;
                }
                else if(chr == 123){//123 equals { in ASCII
                    fprintf(tokens,"LeftCurlyBracket\n");
                    printf("LeftCurlyBracket\n");
                    chr = getc(file);
                }
                else if (chr == 125){//125 equals } in ASCII
                    fprintf(tokens,"RightCurlyBracket\n");
                    printf("RightCurlyBracket\n");
                    chr = getc(file);
                }
                else if(chr == 34){//34 equals " in ASCII
                    int lenght = 0;
                    char *string;
                    string = (char*) calloc (lenght,sizeof(char));
                    chr = getc(file);

                    while (chr != 34 && chr != EOF){
                        string = (char*) realloc(string,lenght+1*sizeof(char));
                        string [lenght] = chr;
                        lenght++;
                        chr = getc(file);
                    }
                    if(chr != 34){
                            fprintf(tokens,"Unterminated String Error! A string constant cannot terminate before the file end./n");
                            printf("Unterminated String Error! A string constant cannot terminate before the file end./n");
                            break;
                    }
                    else{
                        fprintf(tokens,"StringConst (%s)\n",string);
                        printf("StringConst (%s)\n",string);
                        chr = getc(file);
                        continue;
                    }
                    free(string);
                    lenght = 0;
                }
                else if (chr == 59){// 59 is equals ; in ASCII
                    fprintf(tokens,"EndOfLine\n");
                    printf("EndOfLine\n");
                    chr = getc(file);
                }
                else{
                    puncts[0] = chr;
                    int lnght2 = strlen(puncts);
                    chr = getc(file);
                    if(ispunct(chr)){
                        puncts[1] = chr;
                    }
                    char *puncttoken;
                    puncttoken = strtok(operators,",");
                    while (puncttoken!= NULL){
                        int lnght = strlen(puncttoken);

                        int isOperator = strcmp(puncts,puncttoken);
                        if(isOperator == 0){
                            fprintf(tokens,"Operator (%s)\n",puncttoken);
                            printf("Operator (%s)\n",puncttoken);

                            break;
                        }
                        else{
                            puncttoken = strtok(NULL,",");
                        }
                    }
                    }
                    free(puncts);
                }
            }
            fclose(file);
            fclose(tokens);
        }



