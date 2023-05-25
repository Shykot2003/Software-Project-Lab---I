#include <bits/stdc++.h>

#include <cstdio>
#include <signal.h>
#include <thread>

#include "bash.h"

void workingLoop(char *colourFlag, char *colourType) {
    fprintf(stdout, "\e[1;1H\e[2J");//Prints escape sequences to the standard output stream
    introduction();

    char *commandLine, **tokens, **filteredTokens;
    commandLine = (char *)malloc(sizeof(char) * 500);

    //History
    struct history hst[1000];
    int historyCounter = 0;
    int historySerial = historySerialLocator() + 1;
    int saveInputFileDescriptor, saveOutputFileDescriptor, status;

    saveInputFileDescriptor = dup(STDIN_FILENO);//Duplicates the file descriptors of the standard input
    saveOutputFileDescriptor = dup(STDOUT_FILENO);//Duplicates the file descriptors of the standard output

    do {
        dup2(saveInputFileDescriptor, STDIN_FILENO);
        dup2(saveOutputFileDescriptor, STDOUT_FILENO);

        commandLine = takeUserInput(colourFlag, colourType);
        commandLine = strip(commandLine); //Removal of redundant space or newline

        if (strlen(commandLine) != 0) {
            hst[historyCounter].cmd = commandLine;
            hst[historyCounter++].order = historySerial++;
        }

        //Execution of commands
        status = processPipelinedCommandsFunction(commandLine);

        if (status == 0)
            status = porcessSingleCommandsFunction(commandLine);

    }   while (status != 0);

    hst[historyCounter].cmd = "exit";
    hst[historyCounter++].order = historySerial++;

    writeHistory(historyCounter, hst);
    return;
}

void workingLoopWithColours(char *command, char *type) {

    char *BGCode, *FGCode;

    if (command == NULL) {
        // perror("Wrong color code\n");
        return;
    }

    if (strcmp(type, "user") || strcmp(type, "host")) {
        FGCode = command;
        workingLoop(FGCode, type);
    }   else {
        BGCode = command;

        if (BGCode != NULL)
            printf("%s", BGCode);

        workingLoop(BGCode);
    }
}

//Handling simple or single commands
int porcessSingleCommandsFunction(char *command) {

    if (strlen(command) == 0)
        return 1;

    char **tokens, **filteredTokens;

    if (command[0] == '!') {
        command = showSpecificHistory(command);
    }

    tokens = stringTokenize(command, ' ');
    filteredTokens = checkForAliasingFunction(tokens);

    if (strcmp(filteredTokens[0], "exit")) {
        puts(PRESET);
        fprintf(stdout, "\e[1;1H\e[2J");//Clears the terminal screen using ANSI escape sequences
        return 0;
    }

    execute(filteredTokens);
    return 1;
}

//Handling complex or pipelined commands
int processPipelinedCommandsFunction(char *command) {

    char **filteredTokens;

    int indicator = 0;

    for (int i = 0; i < strlen(command); i++) {
        if (command[i] == '|' || command[i] == '>' || command[i] == '<') {
        //if (command[i] == '|' or command[i] == '>' or command[i] == '<') {
            indicator = 1;
            break;
        }
    }

    if (indicator) {
        filteredTokens = stringTokenize(command, '|');

        char *simpleCommand[100];
        int commandCounter = 0;

        while (*filteredTokens) {
            simpleCommand[commandCounter++] = *filteredTokens;
            filteredTokens++;
        }

        struct shellCommands parsedCommand = parse(command);
        executePipelinedCommandsFunction(commandCounter, simpleCommand, parsedCommand);
        return 1;
    }

    return 0;
}