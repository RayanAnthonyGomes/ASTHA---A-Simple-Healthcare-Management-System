//LIBRARY FILES
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <windows.h>

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
// Function to get console width
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
void printCentered(const char *text) {
    int consoleWidth = getConsoleWidth();
    int len = strlen(text);
    // Remove newline character from length calculation if present
    int textLen = (text[len-1] == '\n') ? len-1 : len;
    int padding = (consoleWidth - textLen) / 2;
    if (padding < 0) padding = 0;  // Ensure padding isn't negative
    
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
}

void defaultPage() {
    printf("\033[1;36m");  // Bold + Cyan
    printCentered("....###.....######..########.##.....##....###.......###...\n");
    printCentered("...##.##...##....##....##....##.....##...##.##.....##.##..\n");
    printCentered("..##...##..##..........##....##.....##..##...##...##...##.\n");
    printCentered(".##.....##..######.....##....#########.##.....##.##.....##\n");
    printCentered(".#########.......##....##....##.....##.#########.#########\n");
    printCentered(".##.....##.##....##....##....##.....##.##.....##.##.....##\n");
    printCentered(".##.....##..######.....##....##.....##.##.....##.##.....##\n");

    printf("\033[0m"); // Reset color

    printf("\n");
    printCentered("Welcome to \"ASTHAA\". In Simplicity, We Trust!\n");
    printf("\n");
    
    // For the menu options, we'll not center them 

    printf("\n");
    printf("Menu Options:\n");
    printf("1. Registration (For Patients Only)\n");
    printf("2. Login (As Patient, Doctor, Admin)\n");
    printf("3. Emergency Contacts\n");
    printf("4. About Us\n");
    printf("5. Exit\n");
    printf("\n");
    printf("Enter any option (1-5) to continue: ");

}

int main() {
    defaultPage();
    return 0;
}