//LIBRARY FILES
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <windows.h>
#include<stdbool.h>


//VERIFICATION AND SMALL INTERNAL MODULES



//RANDOM TIME GENERATION FUNCTION
int randomInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//password validation
bool validatePasswordWithFeedback(const char *password) {
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    int length = strlen(password);
    
    // Check length first
    if (length < 8) {
        printf("Too short password.(minimun 8 characters is the standard password)\n");
        return false;
    }
    
    // Check each requirement
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else if (ispunct(password[i])) hasSpecial = true;
    }
    
    // Give specific feedback
    bool valid = true;
    if (!hasUpper) {
        printf("Missing uppercase letter\n");
        valid = false;
    }
    if (!hasLower) {
        printf("Missing lowercase letter\n");
        valid = false;
    }
    if (!hasDigit) {
        printf("Missing digit\n");
        valid = false;
    }
    if (!hasSpecial) {
        printf("Missing special character\n");
        valid = false;
    }
    
    return valid;
}

//Bangladeshi phone validation
bool isValidBangladeshiPhone(const char *phone) {
    // Must be exactly 11 digits and start with 01
    if (strlen(phone) != 11) {
        printf("Must be exactly 11 digits\n");
        return false;
    }
    
    if (phone[0] != '0' || phone[1] != '1') {
        printf("Must start with 01 (e.g. 017XXXXXXXX)\n");
        return false;
    }
    
    for (int i = 0; i < 11; i++) {
        if (!isdigit(phone[i])) {
            printf("Only digits allowed\n");
            return false;
        }
    }
    
    return true;
}

//email valid?
bool isValidEmail(const char *email) {
    int atCount = 0, dotCount = 0;
    int length = strlen(email);
    
    if (length < 5) return false; // a@b.c
    
    for (int i = 0; i < length; i++) {
        if (email[i] == '@') atCount++;
        else if (email[i] == '.') dotCount++;
    }
    
    return (atCount == 1) && (dotCount >= 1);
}

//strong pass?
bool isStrongPassword(const char *password) {
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    int length = strlen(password);
    
    if (length < 8) return false;
    
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else if (ispunct(password[i])) hasSpecial = true;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

//Mask pass
void inputPassword(char *password, int maxLength) {
    int i = 0;
    char ch;
    
    while (1) {
        ch = getch(); // Read character without echo
        
        if (ch == '\r' || ch == '\n') { // Enter key
            password[i] = '\0';
            printf("\n");
            break;
        } else if (ch == '\b' && i > 0) { // Backspace
            i--;
            printf("\b \b"); // Move cursor back, print space, move back again
        } else if (i < maxLength - 1 && isprint(ch)) { // Printable character
            password[i++] = ch;
            printf("*"); // Print asterisk instead of actual character
        }
    }
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
/*
   █████████    █████████  ███████████ █████   █████   █████████  
  ███░░░░░███  ███░░░░░███░█░░░███░░░█░░███   ░░███   ███░░░░░███ 
 ░███    ░███ ░███    ░░░ ░   ░███  ░  ░███    ░███  ░███    ░███ 
 ░███████████ ░░█████████     ░███     ░███████████  ░███████████ 
 ░███░░░░░███  ░░░░░░░░███    ░███     ░███░░░░░███  ░███░░░░░███ 
 ░███    ░███  ███    ░███    ░███     ░███    ░███  ░███    ░███ 
 █████   █████░░█████████     █████    █████   █████ █████   █████
░░░░░   ░░░░░  ░░░░░░░░░     ░░░░░    ░░░░░   ░░░░░ ░░░░░   ░░░░░ 
*/
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

//Global Functions gula ekhane dibo so that amader everytime out of scope na hoy

//Function 1: Patient registration
void registerPatient(void);



int main() {
    defaultPage();
     int x;
   scanf("%d",&x);
switch (x) {
  case 1:
    registerPatient();
    break;
  case 2:
    //loginOption();
    break;
  case 3:
    //blah blah.
    break;
  case 4:
    //blah blah.
    break;
  case 5: 
    break;

}
    return 0;
}

/*
                      █████     ███                       █████         
                     ░░███     ░░░                       ░░███          
 ████████   ██████   ███████   ████   ██████  ████████   ███████        
░░███░░███ ░░░░░███ ░░░███░   ░░███  ███░░███░░███░░███ ░░░███░         
 ░███ ░███  ███████   ░███     ░███ ░███████  ░███ ░███   ░███          
 ░███ ░███ ███░░███   ░███ ███ ░███ ░███░░░   ░███ ░███   ░███ ███      
 ░███████ ░░████████  ░░█████  █████░░██████  ████ █████  ░░█████       
 ░███░░░   ░░░░░░░░    ░░░░░  ░░░░░  ░░░░░░  ░░░░ ░░░░░    ░░░░░        
 ░███                                                                   
 █████                                                                  
░░░░░                                                                   
                              ███           █████                       
                             ░░░           ░░███                        
 ████████   ██████   ███████ ████   █████  ███████   ████████   ██████  
░░███░░███ ███░░███ ███░░███░░███  ███░░  ░░░███░   ░░███░░███ ░░░░░███ 
 ░███ ░░░ ░███████ ░███ ░███ ░███ ░░█████   ░███     ░███ ░░░   ███████ 
 ░███     ░███░░░  ░███ ░███ ░███  ░░░░███  ░███ ███ ░███      ███░░███ 
 █████    ░░██████ ░░███████ █████ ██████   ░░█████  █████    ░░████████
░░░░░      ░░░░░░   ░░░░░███░░░░░ ░░░░░░     ░░░░░  ░░░░░      ░░░░░░░░ 
                    ███ ░███                                            
                   ░░██████                                             
                    ░░░░░░                                              
  █████     ███                                                         
 ░░███     ░░░                                                          
 ███████   ████   ██████  ████████                                      
░░░███░   ░░███  ███░░███░░███░░███                                     
  ░███     ░███ ░███ ░███ ░███ ░███                                     
  ░███ ███ ░███ ░███ ░███ ░███ ░███                                     
  ░░█████  █████░░██████  ████ █████                                    
   ░░░░░  ░░░░░  ░░░░░░  ░░░░ ░░░░░                                     
*/

// void registerPatient()
// {
//  //First step is to open my database and get the patients.txt file to edit it. Append mode e jawa lagbe age then shob kichu korte parbo
//  FILE *fp = fopen("patients.txt", "a");
//     if (fp == NULL) {
//         printf("Error opening file for writing.\n");
//         return;
//     }


// //Variables declare korsi
// char name[100], email[100], phone[20], password[30];
// int age;
// float weight;

// printf("You have selected the patient register option. \nPlease fill the form up to continue your registration.\n\nPatient Registration Form:\n");

// printf("Enter Your Name: ");
//     getchar(); //previous input theke line clear korlam
// fgets(name, sizeof(name), stdin); //fgets diye input nicchi
//     name[strcspn(name, "\n")] = 0; //Notun line shoraitesi

// printf("Age: ");
//     scanf("%d", &age);

// printf("Weight (kg): ");
//     scanf("%f", &weight);

// printf("Email: ");
//     scanf("%s", email);

// printf("Phone Number: ");
//     scanf("%s", phone);

// printf("Set a Password: ");
// //password masking ++ STRONG PASSSWORD CHECK KORTESI

// while (1) {
//     inputPassword(password, sizeof(password));
//     printf("Password must be at least 8 characters long, and include:\n- 1 uppercase letter\n- 1 lowercase letter\n- 1 number\n- 1 symbol\n");
//     if (!isStrongPassword(password)) {
//         printf("Password must be at least 8 characters long, contain 1 uppercase, 1 lowercase, and 1 symbol.\n");
//         printf("Enter again: ");
//     } else {
//         break;
//     }
// }

// //Patients.txt file e data dicchi
// fprintf(fp, "%s,%s,%s,%d,%s,%.2f\n", phone, password, name, age, email, weight);

// fclose(fp);

// printf("\n\nRegistration Successfully Done!\n");
// printf("Your Details:\nName: %s,\nPhone Number: %s,\nAge: %d,\nEmail: %s,\n Weight: %.2f,\nPassword: ********\n",name, phone, age, email, weight, password);
// printf("/nIf you want to see your password please press 1, Otherwise press 2 to login to our software.\n");
// int postOption;
// scanf("%d", &postOption);
// if (postOption == 1) {
//     printf("Your Password is: %s\n", password);

// }else if (postOption == 2) {
//     printf("You can now login to our software.\n");
//     //loginOption();
// }
// }


void registerPatient() {
    FILE *fp = fopen("patients.txt", "a");
    if (fp == NULL) {
        printf("Error: Error Opening Patients Database. Please try again soon.\n");
        return;
    }

    printf("\nPatient Registration\n");
    
    char name[100], email[100], phone[20], password[30];
    int age;
    float weight;

    // Name
    printf("\nFull Name: ");
    fflush(stdin);
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    // Age
    while (1) {
        printf("Age: ");
        if (scanf("%d", &age) != 1 || age < 0 || age > 120) {
            printf("Invalid age (0-120 only)!!\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    // Weight
    while (1) {
        printf("Weight (kg): ");
        if (scanf("%f", &weight) != 1 || weight < 0 || weight > 150) {
            printf("Invalid weight (0-150 kg only)!!\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }

    // Bangladesh phone verif
    while (1) {
        printf("Phone (01XXXXXXXXX): ");
        scanf("%s", phone);
        if (isValidBangladeshiPhone(phone)) break;
    }

    // Email verif
    while (1) {
        printf("Email: ");
        scanf("%s", email);
        if (isValidEmail(email)) break;
    }

    // Password requirements
    printf("\nPassword Requirements:");
    printf("\n8+ characters 1 uppercase 1 lowercase");
    printf("\n1 number 1 special character\n\n");
    
    while (1) {
        printf("Set Password: ");
        inputPassword(password, sizeof(password));
    
        printf("\n");
        if (validatePasswordWithFeedback(password)) {
            printf("You Got Strong Password There!\n");
            break;
        }
        printf("\nSomething went wrong! \n Please try again now: ");
    }

    // Save to file
    fprintf(fp, "%s,%s,%s,%d,%s,%.2f\n", phone, password, name, age, email, weight);
    fclose(fp);

    printf("\n!!!Registration Successful!!!\n");
    printf("Note: Your phone number is your username\n\n");
    
    printf("1. Show password\n");
    printf("2. Login now\n");
    printf("3. Return to menu\n");
    printf("Choose: ");
    
    int option;
    scanf("%d", &option);
    
    if (option == 1) {
        printf("\nYour password: %s\n", password);
        printf("Keep this confidential! Do not share this with anyone! Not even your friends!\n");
    } else if (option == 2) {
         //loginOption();
    }else if (option ==3){
        defaultPage();
    }
  
}