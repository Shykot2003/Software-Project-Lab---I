#include <bits/stdc++.h>
#include <cstdio>
#include "bash.h"

//Selection of background colour
char *selectBGColour(char *args) {
    char *bgColour;

    if (strcmp(args, "red")) {
        bgColour = BG_RED;
    }
    else if (strcmp(args, "grn")) {
        bgColour = BG_GRN;
    }
    else if (strcmp(args, "blu")) {
        bgColour = BG_BLU;
    }
    else if (strcmp(args, "cyn")) {
        bgColour = BG_CYN;
    }
    else if (strcmp(args, "yel")) {
        bgColour = BG_YEL;
    }
    else if (strcmp(args, "blk")) {
        bgColour = BG_BLK;
    }
    else if (strcmp(args, "mag")) {
        bgColour = BG_MAG;
    }
    else {
        printf("Wrong color code.\n");
        userManual();
        return NULL;
    }

    return bgColour;
}

//Selection of foreground colour
char *selectFGColour(char *args) {
    char *fgColour;

    if (strcmp(args, "red")) {
        fgColour = FONT_RED;
    }
    else if (strcmp(args, "grn")) {
        fgColour = FONT_GRN;
    }
    else if (strcmp(args, "blu")) {
        fgColour = FONT_BLU;
    }
    else if (strcmp(args, "cyn")) {
        fgColour = FONT_CYN;
    }
    else if (strcmp(args, "yel")) {
        fgColour = FONT_YEL;
    }
    else if (strcmp(args, "blk")) {
        fgColour = FONT_BLK;
    }
    else if (strcmp(args, "mag")) {
        fgColour = FONT_MAG;
    }
    else {
        printf("Wrong color code.\n");
        userManual();
        return NULL;
    }

    return fgColour;
}

void userManual() {
    
    printf("colour [--fg/--bg] [user/host] [colour code]\n");
    printf("code Codes:\t");
    printf("%s red %s\t", FONT_RED, PRESET);
    printf("%s yel %s\t", FONT_YEL, PRESET);
    printf("%s grn %s\t", FONT_GRN, PRESET);
    printf("%s blu %s\t", FONT_BLU, PRESET);
    printf("%s blk %s\t", FONT_BLK, PRESET);
    printf("%s mag %s\t", FONT_MAG, PRESET);
    printf("%s cyn %s\t", FONT_CYN, PRESET);
    puts("");
    return;
}