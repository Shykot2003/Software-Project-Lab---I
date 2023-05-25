#include <bits/stdc++.h>
#include <cstdio>
#include <stdlib.h>
#include <ctype.h>

#include "bash.h"

using namespace std;


char *userFontColor = FONT_RED, *bgColor = "\u001b[230;5;m", *hostFontColor = FONT_CYN;

char *takeUserInputFunction(char *colorcolorCode, char *colorType, int fsl, FILE *fp) {
    char *buffer, *path;
    char ch;
    int location = 0, bufferSize = 1024;

    //Dynamically allocate memory to store the user prompt
    buffer = (char *)malloc(sizeof(char) * bufferSize);

    //Check if new color colorCode is applied or not
    if (strlen(colorcolorCode) != 0) {
        promptWithColours(colorcolorCode, colorType);
    }   else
            prompt();

    int quoteStart = 0;
    char *temp;

    while (1) {
        scanf("%c", &ch);
        if (ch == '\r')
            continue;

        if (location >= bufferSize) {
            bufferSize += 1024;
            buffer = (char *)realloc(buffer, bufferSize);
        }

        if ((int)ch == EOF or ch == '\n' or buffer == NULL) {

            //For taking multiline input delimited by '\'
            int tmploc = location - 1;

            if (buffer[tmploc] == '\\') {
                location--;
                printf("> ");
                continue;
            }

            buffer[location] = '\0';
            break;
        }

        buffer[location] = ch;
        location++;
    }

    return buffer;
}//End of *takeUserInputFunction()

//Tokenization of command string
char **stringTokenize(char *ch, char sep) {

    char *newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    char **raw_words = (char **)malloc(sizeof(char) * BUFFER_SIZE);

    int cnt = 0, k = 0, j = 0, qFlag = 0, changed = 0;

    //Splits the string into words based on delimeters
    for (int i = 0;; i++) {
        if (ch[i] == '\"' or ch[i] == '\'') {
            newstr[j++] = ch[i];

            //Starting of a quote
            if (qFlag == 0) {
                qFlag = 1;
                continue;
            }   
            //Ending of a quote
            else {
                qFlag = 0;
                i++;
            }
        }

        if (!qFlag) {
            if (((ch[i] == sep && i > 0) || (ch[i] == '\0') || (ch[i] == '\n')) && (ch[i - 1] != sep)) {
                cnt++;
                newstr[j] = '\0';
                raw_words[k++] = newstr;
                changed = 1;

                newstr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
                j = 0;

                if (ch[i] == '\0')
                    break;
            }   else {
                    newstr[j++] = ch[i];
                }
            
        }   else {
                newstr[j++] = ch[i];
            }
    }   

    raw_words[k] = NULL;

    if (changed == 0) {
        raw_words[0] = ch;
        raw_words[1] = NULL;
    }

    return raw_words;
}//End of **stringTokenize()

//Removal of white spaces from each words
char **removeWhiteSpace(char **raw_data) {
    char **words = (char **)malloc(sizeof(char) * BUFFER_SIZE);
    int i = 0;

    for (; raw_data[i]; i++) {
        char *demo = (char *)malloc(sizeof(char) * BUFFER_SIZE);
        int id = 0;

        for (int j = 0; j < strlen(raw_data[i]); j++) {

            if (raw_data[i][j] != ' ')
                demo[id++] = raw_data[i][j];
        }

        words[i] = demo;
    }

    words[i] = NULL;

    return words;
}

//Removal of redundant space or newline
char *strip(char *word) {

    int id = 0;
    char *demo = (char *)malloc(sizeof(char) * 1024);

    int stflag = 0, endflag = 0;

    for (int i = 0; i < strlen(word); i++) {

        if ((word[i] == ' ' or word[i] == '\n') and i == 0)
            continue;
        else if ((word[i] == ' ' or word[i] == '\n') and i == strlen(word) - 1)
            continue;
        else
            demo[id++] = word[i];
    }

    demo[id] = '\0';

    return demo;
}

//Printing my command prompt
void prompt() {
    char *path = getCurrentDirectory();
    char *myuser = userName();
    char *myhost = hostName();

    printf("%s%s@%s:%s%s", userFontColor, myuser, myhost, userFontColor, PRESET);
    printf("%s\u001b[1m%s%s$ %s\u001b[1m%s", PRESET, hostFontColor, getCurrentDirectory(), hostFontColor, PRESET);
}

//Printing my command prompt with colour
void promptWithColours(char *code, char *colorType) {
    char *path = getCurrentDirectory();
    char *myuser = userName();
    char *myhost = hostName();

    if (strcmp(colorType, "user")) {
        userFontColor = code;
    }
    else if (strcmp(colorType, "host")) {
        hostFontColor = code;
    }   else {
        bgColor = code;
    }

    if (bgColor != NULL)
        printf("%s", bgColor);

    printf("\u001b[1m%s\u001b[1m%s@%s:\u001b[1m%s\u001b[1m%s", userFontColor, myuser, myhost, userFontColor, PRESET);

    if (bgColor != NULL)
        printf("%s", bgColor);

    printf("\u001b[1m%s\u001b[1m%s$ \u001b[1m%s\u001b[1m%s", hostFontColor, getCurrentDirectory(), hostFontColor, PRESET);

    if (bgColor != NULL)
        printf("%s", bgColor);
}