#include <bits/stdc++.h>

#include <cstdio>
#include <stdlib.h>
#include <unistd.h>

//ANSI Colour Code Configuration (Background)
#define BG_BLK "\u001b[40m"
#define BG_RED "\u001b[41m"
#define BG_GRN "\u001b[42m"
#define BG_YEL "\u001b[43m"
#define BG_BLU "\u001b[44m"
#define BG_MAG "\u001b[45m"
#define BG_CYN "\u001b[46m"
#define BG_WHT "\u001b[47m"

#define BG_DARK_BLK "\u001b[40m;1m"
#define BG_DARK_RED "\u001b[41m;1m"
#define BG_DARK_GRN "\u001b[42m;1m"
#define BG_DARK_YEL "\u001b[43m;1m"
#define BG_DARK_BLU "\u001b[44m;1m"
#define BG_DARK_MAG "\u001b[45m;1m"
#define BG_DARK_CYN "\u001b[46m;1m"
#define BG_DARK_WHT "\u001b[47m;1m"

//ANSI Colour Code Configuration (Font)
#define FONT_BLK "\u001b[30m"
#define FONT_RED "\u001b[31m"
#define FONT_GRN "\u001b[32m"
#define FONT_YEL "\u001b[33m"
#define FONT_BLU "\u001b[34m"
#define FONT_MAG "\u001b[35m"
#define FONT_CYN "\u001b[36m"
#define FONT_WHT "\u001b[37m"
#define PRESET "\u001b[0m"

#define FONT_DARK_BLK "\u001b[30m;1m"
#define FONT_DARK_RED "\u001b[31m;1m"
#define FONT_DARK_GRN "\u001b[32m;1m"
#define FONT_DARK_YEL "\u001b[33m;1m"
#define FONT_DARK_BLU "\u001b[34m;1m"
#define FONT_DARK_MAG "\u001b[35m;1m"
#define FONT_DARK_CYN "\u001b[36m;1m"
#define FONT_DARK_WHT "\u001b[37m;1m"


#define BUFFER_SIZE 1024

//Shell Command Structure
struct shellCommands {
    char *simpleCommands[100];
    char *inputFile;
    char *outputFile;
    char size = 0;
};

//Autorrection of Commands
struct cmdFrequency {
    char *cmd;
    int freq;
    int prev;
};

//Burkhard Keller (BK) Tree Node
struct node {
    int levenshteinDistance;
    char *word;
    struct node *leftNode;
    struct node *rightNode;
};

void frequencyCalculator(char *command, FILE *save);
void assembleFrequencyOutput();
int generateAutoCommand(char *cmd);
void showValue(char *value);
void updateCmdFrequency();
int count(char *data[], char *info, int size);
void commandSuggestion(int flag, char **args);
char *AutoCommandCompletion(int flag, char *args);

//History Structure
struct history {
    char *cmd;
    int order;
};

int historySerialLocator();
void writeHistory(int size, struct history hst[]);
char *readHistory(int serial = -1);
char *showSpecificHistory(char *cmd);
void clearHistory();

//Main Driver Loop
void workingLoop(char *code = "", char *type = "");
void workingLoopWithColours(char *ch = "", char *type = "");

//Command Prompt
void prompt();
void promptWithColors(char *code, char *colorType);
char *takeUserInput(char *code = "", char *colorType = "", int fsl = 0, FILE *fp = NULL);
char **stringTokenize(char *ch, char sep);

//Command Execution Implementation
void findExecutionFileName(char *cmd);
void cmdExecute(char **args);
void execute(char **args);
void saveInfo();

void changeDirectory(char *path);
char *currentDirectory();
char *getCurrentDirectory();
char *hostName();
char *userName();

int processPipelinedCommandsFunction(char *command);
void executePipelinedCommandsFunction(int size, char *simpleCommand[], struct shellCommands command);
int porcessSingleCommandsFunction(char *command);

char **checkForAliasingFunction(char **cmd);
void aliasCommandsFunction(char **words);
void settingAliasFunction(char *cmd, char *alias);
char *getAliasFunction(char *data);

char **checkForWildCards(char **data);

void BKTreeGenerationFunction(char *cmd);

struct shellCommands parse(char *data);

//Fundamental String Operations
size_t strlen(const char *str);
bool strcmp(const char *a, const char *b);
int strlen2(char **str);
char *strcpy(const char *b);
char *strchr(const char *a, const char ch);
char *strcatt(const char *with, const char *str);
char *strreplace(const char *info, const char *with, const char *str);
bool strcontain(const char *data, const char *substr);
char **removeWhiteSpace(char **raw_data);
void prefixTable(char *neddle, int neddle_len, int *LPS);
int strsubstr(char *neddle, char *heystack);
char **strsplit(char *find, char *text);
char *strip(char *word);
char *selectBGColor(char *args);
char *selectFGColor(char *args);
char *numToString(int num);
void userManual();
bool wildCardMatching(char *str, char *pat, int slen, int plen);
void introduction();