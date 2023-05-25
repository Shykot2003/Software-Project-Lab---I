#include <bits/stdc++.h>
#include <cstdio>
#include <stdlib.h>
#include "bash.h"

#define BUFFER_SIZE 1024

void settingAliasFunction(char *cmd, char *alias) {

    char *aliasfp = strcatt(strcatt("/home/", userName()), "/.slsh_ilias");

    if (access(aliasfp, F_OK) != 0) {
        puts("C");
        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "w+")) == NULL) {
            puts("Failed to create aliasfp files");
        }
        fclose(fp3);
    }

    FILE *f1;

    if ((f1 = fopen(aliasfp, "a+")) == NULL) {
        puts("Failed to open aliasfp file");
    }

    fprintf(f1, "%s %s\n", cmd, alias);
    fclose(f1);
}

void aliasCommandsFunction(char **words) {

    char *aliasfp = strcatt(strcatt("/home/", userName()), "/.slsh_alias");
    char **refactor = (char **)malloc(sizeof(char) * 500);

    if (strlen2(words) == 1) {
        char s;

        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "r")) == NULL) {
            puts("Failed to create aliasfp files");
        }

        while ((s = fgetc(fp3)) != EOF) {
            printf("%c", s);
        }
        fclose(fp3);

        return;
    }

    if (strcontain(words[1], "=")) {
        if (strcmpr(words[0], "alias")) {
            refactor = stringTokenize(words[1], '=');
            puts(refactor[0]); // ls
            puts(refactor[1]); // list
            settingAliasFunction(refactor[0], refactor[1]);
        }
    } else {
        puts("Wrong command formate.\n[alias command=aliasName]");
        return;
    }
}

char *removeQuotes(char *str) {
    char *editedStr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    int i, k = 0;

    for (i = 0; str[i]; i++) {
        if (str[i] == '\'' or str[i] == '\"')
            continue;
        else
            editedStr[k++] = str[i];
    }

    editedStr[k] = '\0';
    return editedStr;
}

char **checkForAliasing(char **data) {

    char *aliasfp = strcatt(strcatt("/home/", userName()), "/.slsh_alias");

    if (access(aliasfp, F_OK) != 0) {
        FILE *fp3;
        if ((fp3 = fopen(aliasfp, "w+")) == NULL) {
            puts("Failed to create aliasfp files");
        }
        fclose(fp3);
    }

    char *newargs[500];
    char **chunks = (char **)malloc(sizeof(char) * 500);
    int id = 0;

    while (*data) {

        if (id == 0) {
            FILE *f2;
            f2 = fopen(aliasfp, "r");

            char *line = NULL;
            size_t len = 0;
            ssize_t read;
            int flag = 1;

            while ((read = getline(&line, &len, f2)) != -1) {
                chunks = stringTokenize(line, ' ');

                int wordLen = strlen2(chunks);

                if (strcmpr(chunks[wordLen - 2], *data)) {

                    for (int i = 0; i < wordLen - 2; i++) {
                        newargs[id++] = chunks[i];
                    }

                    flag = 0;
                }
            }

            if (flag)
                newargs[id++] = removeQuotes(*data);
            fclose(f2);
        }

        else {
            newargs[id++] = removeQuotes(*data);
        }

        data++;
    }

    newargs[id] = NULL;
    char **ans;

    //if we pass 'alias command' then the first will be discarded...
    if(strlen2(newargs) >= 2 and !strcontain(newargs[1],"=")) ans = checkForWildCards(newargs);
    else ans = newargs;

    return ans;
}