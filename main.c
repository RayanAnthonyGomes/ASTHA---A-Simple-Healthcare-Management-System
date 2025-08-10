//LIBRARY FILES
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<time.h>

//RANDOM TIME GENERATION FUNCTION
int randomInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

/*
 ____  _____ _____ _   _   _ _   _____  __     _____ _______        __
|  _ \| ____|  ___/ \ | | | | | |_   _| \ \   / /_ _| ____\ \      / /
| | | |  _| | |_ / _ \| | | | |   | |    \ \ / / | ||  _|  \ \ /\ / / 
| |_| | |___|  _/ ___ \ |_| | |___| |     \ V /  | || |___  \ V  V /  
|____/|_____|_|/_/   \_\___/|_____|_|      \_/  |___|_____|  \_/\_/   
*/
void printCentered(const char *text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2;
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
}

void defaultPage()

{
    const int WIDTH = 90;
    //printf("\033[1;36m");  // Bold + Cyan
    printCentered("....###.....######..########.##.....##....###.......###...\n", WIDTH);
    printCentered("...##.##...##....##....##....##.....##...##.##.....##.##..\n", WIDTH);
    printCentered("..##...##..##..........##....##.....##..##...##...##...##.\n", WIDTH);
    printCentered(".##.....##..######.....##....#########.##.....##.##.....##\n", WIDTH);
    printCentered(".#########.......##....##....##.....##.#########.#########\n", WIDTH);
    printCentered(".##.....##.##....##....##....##.....##.##.....##.##.....##\n", WIDTH);
    printCentered(".##.....##..######.....##....##.....##.##.....##.##.....##\n", WIDTH);

    printf("\033[0m"); // Reset color

    printf("\n");
    printCentered("Welcome to \"ASTHAA\". In Simplicity, we believe!\n", WIDTH);
    printf("\n");
    printf("Menu Options:\n");
    printf("1. Registration (For Patients Only)\n");
    printf("2. Login (As Patient, Doctor, Admin)\n");
    printf("3. Emergency Contacts\n");
    printf("4. About Us\n");
    printf("5. Exit\n");
    printf("\n");

    printf("Enter any option (1-5) to continue: ");


/* COLOR CODES
Red: \033[1;31m
Green: \033[1;32m
Yellow: \033[1;33m
Blue: \033[1;34m
Magenta: \033[1;35m
Cyan: \033[1;36m
White: \033[1;37m
*/
}

int main(){
    defaultPage();
}