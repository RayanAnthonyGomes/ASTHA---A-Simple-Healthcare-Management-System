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

//clrscreen function
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Helper function to check for "back" command
bool checkForBackCommand(const char* input) {
    return (strcmp(input, "back") == 0 || strcmp(input, "BACK") == 0);
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
    // Prottek Ta Requirements Check kortesi? How? Ctype.h use korar jonno eta possible hoise 
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
    //exactly 11 digits and start with 01
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

void emergencyContacts(void);
void viewAppointments(const char *patientPhone);
int viewDoctorAppointments(const char *doctorPhone);
int viewPatientDetails();
int writePrescription(const char *doctorPhone);


void trimNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// void viewPrescribedMedicine(const char *patientPhone);
// int patientExit(const char *patientPhone);
// Function to get console width

//Pardon
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
 ____  _____ _____ _   _   _ _   _____  __     _____ _______        __
|  _ \| ____|  ___/ \ | | | | | |_   _| \ \   / /_ _| ____\ \      / /
| | | |  _| | |_ / _ \| | | | |   | |    \ \ / / | ||  _|  \ \ /\ / / 
| |_| | |___|  _/ ___ \ |_| | |___| |     \ V /  | || |___  \ V  V /  
|____/|_____|_|/_/   \_\___/|_____|_|      \_/  |___|_____|  \_/\_/   
*/
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
    printCentered("    ###     ######  ######## ##     ##    ###       ###   \n");
    printCentered("   ## ##   ##    ##    ##    ##     ##   ## ##     ## ##  \n");
    printCentered("  ##   ##  ##          ##    ##     ##  ##   ##   ##   ## \n");
    printCentered(" ##     ##  ######     ##    ######### ##     ## ##     ##\n");
    printCentered(" #########       ##    ##    ##     ## ######### #########\n");
    printCentered(" ##     ## ##    ##    ##    ##     ## ##     ## ##     ##\n");
    printCentered(" ##     ##  ######     ##    ##     ## ##     ## ##     ##\n");

    printf("\033[0m"); // Reset color
    printf("\n");
    printCentered("Welcome to \"ASTHAA\". In Simplicity, We Trust!\n");
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
void patientDashboard(char name[], char phone[]);
void doctorDashboard(char name[], char phone[]);
void adminDashboard(char name[], char phone[]);
//Function 2: Login option
//patient
void loginOption(void);
bool appointmentForm(const char *patientPhone);
void cancelAppointment(const char *patientPhone);
//doc
int viewDoctorAppointments(const char *doctorPhone);
int viewPatientDetails(const char *doctorPhone);
int writePrescription(const char *doctorPhone);
//Function 3: Emergency Contacts
void emergencyContacts(void);   



int main() {
    defaultPage();
     int x;
   scanf("%d",&x);
    switch (x) {
  case 1:
    registerPatient();
    break;
  case 2:
    loginOption();
    break;
  case 3:
    emergencyContacts();
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

void registerPatient() {
    FILE *fp = fopen("patients.txt", "a");
    if (fp == NULL) {
        printf("Error: Error Opening Patient Database. Please try again soon. I hope that our admins are on it right at this moment\n");
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


/*
 ____    _    ____  _   _ ____   ___    _    ____  ____  ____  
|  _ \  / \  / ___|| | | | __ ) / _ \  / \  |  _ \|  _ \/ ___| 
| | | |/ _ \ \___ \| |_| |  _ \| | | |/ _ \ | |_) | | | \___ \ 
| |_| / ___ \ ___) |  _  | |_) | |_| / ___ \|  _ <| |_| |___) |
|____/_/   \_\____/|_| |_|____/ \___/_/   \_\_| \_\____/|____/ 
*/
void patientDashboard(char name[], char phone[]) {
    int option;
    char input[10];
    
    while(1) {
        printf("\nPATIENT DASHBOARD\n\n");
        printf("1: Book Appointment\n");
        printf("2: View Appointments\n");
        printf("3: Cancel Appointments\n");
        printf("4: View Prescribed Medicines\n");
        printf("5: Logout\n");
        printf("Type 'back' at any time to return to this menu\n");

        printf("\nPlease select your option (1-4): ");
        scanf("%s", input);
        
        // Check for back command
        if (checkForBackCommand(input)) {
            printf("\nYou're already at the main menu.\n");
            continue;
        }
        
        // Convert input to integer
        option = atoi(input);
        
        switch(option) {
            case 1:
                clearScreen();
                appointmentForm(phone);  // Just pass the variable name
                printf("\nReturning to patient dashboard...\n");
                break;
            case 2:
                clearScreen();
                viewAppointments(phone);
                printf("\nReturning to patient dashboard...\n");
                break;
            case 3:
                clearScreen();
                 cancelAppointment(phone);
                printf("\nReturning to patient dashboard...\n");
                 break;
            case 4:
                printf("Viewing prescribed medicines...\n");
                //viewPrescribedMedicines(phone);
                break;

            case 5:
                printf("Logging out...\nExiting the dashboard...\n");
                defaultPage();
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

// void doctorDashboard(char name[], char phone[]) {
//     int option;
//     char input[10];
    
//     while(1) {
//         printf("\nDOCTOR DASHBOARD\n\n");
//         printf("1: View Scheduled Appointments\n");
//         printf("2: View Patient Details\n");
//         printf("3: Write Prescription\n");
//         printf("4: Logout\n");
//         printf("Type 'back' at any time to return to this menu\n");

//         printf("\nPlease select your option (1-4): ");
//         scanf("%s", input);
        
//         if (checkForBackCommand(input)) {
//             printf("\nYou're already at the main menu.\n");
//             continue;
//         }
        
//         option = atoi(input);
        
//         switch(option) {
//             case 1:
//                 clearScreen();
//                 //viewDoctorAppointments(phone);  
//                 break;
//             case 2:
//                 clearScreen();
//                 //viewPatientDetails();
//                 break;
//             case 3:
//                 clearScreen();
//                 //writePrescription(phone);
//                 break;
//             case 4:
//                 printf("Logging out...\n");
//                 return;
//             default:
//                 printf("Invalid option. Please try again.\n");
//         }
//     }
// }
void doctorDashboard(char name[], char phone[]) {
    int option;
    char input[10];
    
    while(1) {
        clearScreen();
        printf("\n=== DOCTOR DASHBOARD ===\n");
        printf("Welcome, Dr. %s\n\n", name);
        printf("1. View Appointments\n");
        printf("2. View Patient Details\n");
        printf("3. Write Prescription\n");
        printf("4. Logout\n");

        printf("\nSelect option (1-4): ");
        scanf("%9s", input);
        clearInputBuffer();
        
        option = atoi(input);
        
        switch(option) {
            case 1:
                viewDoctorAppointments(phone);
                break;
            case 2:
                viewPatientDetails(phone);
                break;
            case 3:
                writePrescription(phone);
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid option. Please try again.\n");
                printf("Press Enter to continue...");
                clearInputBuffer();
        }
    }
}
void adminDashboard(char name[], char phone[]) {
    int option;
    char input[10];
    
    while(1) {
        printf("\nADMIN DASHBOARD\n\n");
        printf("1: View All Appointments\n");
        printf("2: View Patients\n");
        printf("3: Edit Patients\n");
        printf("4: Delete Patients\n");
        printf("5: Add Doctors\n");
        printf("6: Remove Doctors\n");
        printf("7: Logout\n");
        printf("Type 'back' at any time to return to this menu\n");

        printf("\nPlease select your option (1-7): ");
        scanf("%s", input);
        
        if (checkForBackCommand(input)) {
            printf("\nYou're already at the main menu.\n");
            continue;
        }
        
        option = atoi(input);
        
        switch(option) {
            case 1:
                // if(viewAllAppointments()) {
                //     printf("\nReturning to admin dashboard...\n");
                // }
                break;
            case 2:
                // if(viewPatients()) {
                //     printf("\nReturning to admin dashboard...\n");
                // }
                break;
            case 3:
                // if(editPatients()) {
                //     printf("\nReturning to admin dashboard...\n");
                // }
                break;
            case 4:
                // if(deletePatients()) {
                //     printf("\nReturning to admin dashboard...\n");
                // }
                break;
            case 5:
                // if(addDoctors()) {
                //     printf("\nReturning to admin dashboard...\n");
                // }
                break;
            case 6:
                // if(removeDoctors()) {
                //     printf("\nReturning to admin dashboard...\n");
                // }
                break;
            case 7:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

/*
 ▄█        ▄██████▄     ▄██████▄   ▄█  ███▄▄▄▄  
███       ███    ███   ███    ███ ███  ███▀▀▀██▄
███       ███    ███   ███    █▀  ███▌ ███   ███
███       ███    ███  ▄███        ███▌ ███   ███
███       ███    ███ ▀▀███ ████▄  ███▌ ███   ███
███       ███    ███   ███    ███ ███  ███   ███
███▌    ▄ ███    ███   ███    ███ ███  ███   ███
█████▄▄██  ▀██████▀    ████████▀  █▀    ▀█   █▀ 
▀                                               
*/
int loginPatient(){
//jeta diye login korbe, etar pore email er o option rakhte hobe

char phone[20], password[30];
    //Jeta diye data compare korbo
    char fPhone[20], fPassword[30], name[100], email[100];
    int age;
    float weight;
printf("Patient Login Form: \n");
    printf("Phone Number: ");
    scanf("%s", phone);

    printf("Password: ");
    //MASKED
    inputPassword(password, sizeof(password));

    FILE *fp = fopen("patients.txt", "r");
    if (fp == NULL) {
        printf("Unable to open patients.txtt to read.\n");
        return 0;
    }
     int found = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%d,%[^,],%f\n", fPhone, fPassword, name, &age, email, &weight) != EOF) {
        if (strcmp(fPhone, phone) == 0 && strcmp(fPassword, password) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

     if (found) {
        printf("\nLogin successful! Welcome to our software, Patient %s!\n", name);
        patientDashboard(name, fPhone);
        // Ekhane Patient Dashboard dekhate hobe, jemon Get a New Appointment, View Your Appointments, Cancel a Appointment
        return 1;
    } else {
        printf("\nInvalid phone or password. Try again.\n");
        return 0;
    }


}

int loginDoctor(){
char phone[20], password[30];
    //Jeta diye data compare korbo
    char fPhone[20], fPassword[30], name[100], email[100],specialization[100];
    int age;
    float weight;

printf("Doctor Login Form: \n");
    printf("Phone Number: ");
    scanf("%s", phone);

    printf("Password: ");
    //scanf("%s", password);
    //TEST MASKED CODE
    inputPassword(password, sizeof(password));

    FILE *fp = fopen("doctors.txt", "r");
    if (fp == NULL) {
        printf("Unable to open doctors.txtt to read.\n");
        return 0;
    }

     int found = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%d,%[^,],%f,%[^\n]\n", fPhone, fPassword, name, &age, email, &weight, specialization) != EOF) {
        if (strcmp(fPhone, phone) == 0 && strcmp(fPassword, password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

     if (found) {
        printf("\nLogin successful! Welcome to our software, Doctor %s!\n", name);
        //EKhane Doctro Dashboard e niye jabo, jekhane appointments.txt theke appointment read korbe
        doctorDashboard(name, fPhone);
        return 1;
    } else {
        printf("\nInvalid phone or password. Try again.\n");
        return 0;
    }
}

int loginAdmin(){

char phone[20], password[30];
    //Jeta diye data compare korbo
    char fPhone[20], fPassword[30], name[100], email[100];
    int age;
    float weight;

printf("Admin Login Form: \n");
    printf("Phone Number: ");
    scanf("%s", phone);

    printf("Password: ");
    //scanf("%s", password);
    //TEST MASKING
    inputPassword(password, sizeof(password));
    
    FILE *fp = fopen("admins.txt", "r");
    if (fp == NULL) {
        printf("Unable to open adminss.txtt to read.\n");
        return 0;
    }

     int found = 0;
    while (fscanf(fp, "%[^,],%[^,],%[^,],%d,%[^,],%f\n", fPhone, fPassword, name, &age, email, &weight) != EOF) {
        if (strcmp(fPhone, phone) == 0 && strcmp(fPassword, password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

     if (found) {
        printf("\nLogin successful! Welcome to our software, Admin %s!\n", name);
        //EKhane Admin Dashboard e niye jabo, jekhane EMR, PAtient data, Cancellation, Generate Bill, shob kichur option thakbe
            adminDashboard(name, fPhone);
        return 1;
    } else {
        printf("\nInvalid phone or password. Try again.\n");
        return 0;
    }


}

void loginOption(){
    clearScreen();
    printf("You have selected the login option.\n Please select your option from below.\n1. Login As Patient\n2. Login as Doctor\n3. Login as Admin\n4. Back to Main Menu\n");
    int option;
    printf("Enter Your Option: ");
    scanf("%d",&option);
    switch (option) {
  case 1:
    // code block
    loginPatient();
    break;
  case 2:
    // code block
    loginDoctor();
    break;
  case 3:
    loginAdmin();
    break;
    case 4:
    printf("Returning to main menu...\n");
    defaultPage();  
}
}

void emergencyContacts() {
    printf("\nEmergency Contacts:\n");
    printf("1. Ambulance: 999\n");
    printf("2. Fire Service: 101\n");
    printf("3. Police: 100\n");
    printf("4. Poison Control Center: 106\n");
    printf("5. Local Hospital: 16263\n");
    printf("6. Back to Main Menu\n");
    
}



/*
 _______    ______  ________  ______  ________  __    __  ________       
|       \  /      \|        \|      \|        \|  \  |  \|        \      
| $$$$$$$\|  $$$$$$\\$$$$$$$$ \$$$$$$| $$$$$$$$| $$\ | $$ \$$$$$$$$      
| $$__/ $$| $$__| $$  | $$     | $$  | $$__    | $$$\| $$   | $$         
| $$    $$| $$    $$  | $$     | $$  | $$  \   | $$$$\ $$   | $$         
| $$$$$$$ | $$$$$$$$  | $$     | $$  | $$$$$   | $$\$$ $$   | $$         
| $$      | $$  | $$  | $$    _| $$_ | $$_____ | $$ \$$$$   | $$         
| $$      | $$  | $$  | $$   |   $$ \| $$     \| $$  \$$$   | $$         
 \$$       \$$   \$$   \$$    \$$$$$$ \$$$$$$$$ \$$   \$$    \$$         
                                                                    
 __       __   ______   _______   __    __  __        ________   ______  
|  \     /  \ /      \ |       \ |  \  |  \|  \      |        \ /      \ 
| $$\   /  $$|  $$$$$$\| $$$$$$$\| $$  | $$| $$      | $$$$$$$$|  $$$$$$\
| $$$\ /  $$$| $$  | $$| $$  | $$| $$  | $$| $$      | $$__    | $$___\$$
| $$$$\  $$$$| $$  | $$| $$  | $$| $$  | $$| $$      | $$  \    \$$    \ 
| $$\$$ $$ $$| $$  | $$| $$  | $$| $$  | $$| $$      | $$$$$    _\$$$$$$\
| $$ \$$$| $$| $$__/ $$| $$__/ $$| $$__/ $$| $$_____ | $$_____ |  \__| $$
| $$  \$ | $$ \$$    $$| $$    $$ \$$    $$| $$     \| $$     \ \$$    $$
 \$$      \$$  \$$$$$$  \$$$$$$$   \$$$$$$  \$$$$$$$$ \$$$$$$$$  \$$$$$$ 
                                                                         
*/

bool appointmentForm(const char *patientPhone) {
    clearScreen();
    FILE *pfp = fopen("patients.txt", "r");
    if (pfp == NULL) {
        printf("Error: Could not open patients database\n");
        return false;
    }

    //store patient data
    char pName[100], pEmail[100], pPassword[30];
    int pAge;
    float pWeight;
    int patientFound = 0;
    char input[100]; 

    // Search
    char tempPhone[20];
    while (fscanf(pfp, "%[^,],%[^,],%[^,],%d,%[^,],%f\n", 
                 tempPhone, pPassword, pName, &pAge, pEmail, &pWeight) != EOF) {
        if (strcmp(tempPhone, patientPhone) == 0) {
            patientFound = 1;
            break;
        }
    }
    fclose(pfp);

    if (!patientFound) {
        printf("Error: Patient record not found\n");
        return false;
    }

    //available dates
    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);
    struct tm availableDates[5];
    for (int i = 0; i < 5; i++) {
        availableDates[i] = currentDate;
        int addDays = randomInRange(1, 30);
        availableDates[i].tm_mday += addDays;
        mktime(&availableDates[i]);
    }

    //Medicalinfo
    char bloodGroup[10], problem[300];
    float height, bmi;

    printf("\nAPPOINTMENT BOOKING\n");
    printf("Type 'back' at any time to cancel\n\n");
    printf("Patient: %s (Age: %d, Weight: %.2f kg)\n", pName, pAge, pWeight);

    // Get additional medical info
printf("Height (in meters): ");
    fgets(input, sizeof(input), stdin);
    if (checkForBackCommand(input)) return false;
    sscanf(input, "%f", &height);

// With this more robust version:
        while (1) {
    printf("Height (in meters, e.g. 1.75): ");
    fgets(input, sizeof(input), stdin);
    if (checkForBackCommand(input)) return false;
    
    if (sscanf(input, "%f", &height) != 1) {
        printf("Invalid height! Please enter a number like 1.75\n");
        continue;
    }
    
    if (height < 0.5 || height > 2.5) { // Reasonable height range check
        printf("Please enter a valid height between 0.5 and 2.5 meters\n");
        continue;
    }
    break;
}

    printf("Blood Group (e.g., A+, B-, O+): ");
    fgets(bloodGroup, sizeof(bloodGroup), stdin);
    bloodGroup[strcspn(bloodGroup, "\n")] = '\0';
    if (checkForBackCommand(bloodGroup)) return false;

    printf("Briefly describe your health issue: ");
    fgets(problem, sizeof(problem), stdin);
    problem[strcspn(problem, "\n")] = '\0';
    if (checkForBackCommand(problem)) return false;

    // Calculate BMI
    bmi = pWeight / (height * height);
    
    // Load doctors
    FILE *fp = fopen("doctors.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open doctors.txt\n");
        return false;
    }

    char dPhone[20], dPass[30], dName[100], dEmail[100], specialization[100];
    int dAge;
    float dWeight;

    char doctorIDs[20][10];
    char doctorNames[20][100];
    char doctorSpecs[20][100];
    int docCount = 0;

    printf("\n\nAvailable Doctors:\n");
    while (fscanf(fp, "%[^,],%[^,],%[^,],%d,%[^,],%f,%[^\n]\n",
                  dPhone, dPass, dName, &dAge, dEmail, &dWeight, specialization) != EOF) {
        printf("ID: %s\nName: Dr. %s\nSpecialization: %s\n", dPhone, dName, specialization);

        if (strcmp(specialization, "General Physician") == 0)
            printf("Example Issues: Fever, Cold, Weakness\n");
        else if (strcmp(specialization, "Pediatrician") == 0)
            printf("Example Issues: Child fever, Vaccine, Nutrition\n");
        else if (strcmp(specialization, "Dermatologist") == 0)
            printf("Example Issues: Skin rash, Acne, Allergy\n");
        else if (strcmp(specialization, "Cardiologist") == 0)
            printf("Example Issues: Chest pain, Heart disease, Hypertension\n");
         
        printf("-----------------------------------\n");

        strcpy(doctorIDs[docCount], dPhone);
        strcpy(doctorNames[docCount], dName);
        strcpy(doctorSpecs[docCount], specialization);
        docCount++;
    }
    fclose(fp);

    // Doctor selection
    char selectedDoctorID[20];
    printf("\nEnter Doctor ID to book appointment with (or 'back' to cancel): ");
    fgets(selectedDoctorID, sizeof(selectedDoctorID), stdin);
    selectedDoctorID[strcspn(selectedDoctorID, "\n")] = '\0';
    if (checkForBackCommand(selectedDoctorID)) return false;

    int found = -1;
    for (int i = 0; i < docCount; i++) {
        if (strcmp(selectedDoctorID, doctorIDs[i]) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Invalid Doctor ID. Appointment not booked.\n");
        return false;
    }

    // Date selection
    printf("\nAvailable Dates:\n");
    for(int i = 0; i < 5; i++){
        printf("%d. %02d-%02d-%d\n",i+1, availableDates[i].tm_mday, 
               availableDates[i].tm_mon + 1, availableDates[i].tm_year + 1900);
    }

    printf("\nSelect a date from options 1-5 (or 'back' to cancel): ");
    fgets(input, sizeof(input), stdin);
    if (checkForBackCommand(input)) return false;
    
    int dateChoice = atoi(input);
    if (dateChoice < 1 || dateChoice > 5) {
        printf("Invalid date choice. Appointment not booked.\n");
        return false;
    }
    struct tm chosenDate = availableDates[dateChoice - 1];

    // Time selection
    int numslots = randomInRange(3, 5);
    char timeSlots[5][10];
    int hourOptions[] = {9,10,11,12,13,14,15,16,17};

    for (int i = 0; i < numslots; i++) {
        int hour = hourOptions[randomInRange(0, 8)];
        snprintf(timeSlots[i], sizeof(timeSlots[i]), "%02d:00", hour);
    }

    printf("\nAvailable Time Slots:\n");
    for (int i = 0; i < numslots; i++) {
        printf("%d. %s\n", i + 1, timeSlots[i]);
    }

    printf("\nSelect a time slot (1-%d) (or 'back' to cancel): ", numslots);
    fgets(input, sizeof(input), stdin);
    if (checkForBackCommand(input)) return false;
    
    int timeChoice = atoi(input);
    if (timeChoice < 1 || timeChoice > numslots) {
        printf("Invalid time choice. Appointment not booked.\n");
        return false;
    }

    // Show summary
    clearScreen();
    printf("\n=== APPOINTMENT SUMMARY ===\n");
    printf("Patient Name: %s\nAge: %d\nHeight: %.2f m\nWeight: %.2f kg\nBMI: %.2f\n", 
           pName, pAge, height, pWeight, bmi);
    printf("Blood Group: %s\nProblem: %s\n", bloodGroup, problem);
    printf("Doctor: Dr. %s (%s)\nDate: %02d-%02d-%d\nTime: %s\n",
           doctorNames[found], doctorSpecs[found],
           chosenDate.tm_mday, chosenDate.tm_mon + 1, chosenDate.tm_year + 1900,
           timeSlots[timeChoice - 1]);

    printf("\nConfirm booking? ('y' for yes or 'n' for no): ");
    char confirm;
    scanf(" %c", &confirm);
    getchar(); // Consume newline
    
    if (tolower(confirm) != 'y') {
        printf("Appointment cancelled.\n");
        return false;
    }

    // Save appointment
    FILE *afp = fopen("appointments.txt", "a");
    if (afp == NULL) {
        printf("Error: Could not save appointment\n");
        return false;
    }

    fprintf(afp, "%s,%s,%d,%.2f,%.2f,%s,%.2f,%s,%s,%s,%s,%02d-%02d-%d,%s\n",
        patientPhone, pName, pAge, height, pWeight, bloodGroup, bmi,
        problem, doctorIDs[found], doctorNames[found], doctorSpecs[found],
        chosenDate.tm_mday, chosenDate.tm_mon + 1, chosenDate.tm_year + 1900,
        timeSlots[timeChoice - 1]);

    fclose(afp);
    printf("\nAppointment successfully booked!\n");
    return true;
}

void viewAppointments(const char *patientPhone) {
    FILE *fp = fopen("appointments.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open appointments database\n");
        return;
    }

    char line[512];
    int found = 0;
    int appointmentCount = 0;

    clearScreen();
    printf("\nYOUR APPOINTMENTS\n\n");

    while (fgets(line, sizeof(line), fp)) {
        // Initialize all variables
        char phone[20] = {0}, name[100] = {0}, bloodGroup[10] = {0}, problem[300] = {0};
        int age = 0;
        float height = 0, weight = 0, bmi = 0;
        char docID[20] = {0}, docName[100] = {0}, specialization[100] = {0}, date[20] = {0}, time[20] = {0};

        // More robust parsing with error checking
        if (sscanf(line, "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
               phone, name, &age, &height, &weight, bloodGroup, &bmi, problem,
               docID, docName, specialization, date, time) < 13) {
            printf("Warning: Skipping malformed appointment record\n");
            continue;
        }

        if (strcmp(phone, patientPhone) == 0) {
            found = 1;
            appointmentCount++;
            
            printf("Appointment #%d\n", appointmentCount);
            printf("----------------------------\n");
            printf("Patient Name     : %s\n", name);
            printf("Age              : %d\n", age);
            printf("Height           : %.2f m\n", height);
            printf("Weight           : %.2f kg\n", weight);
            printf("Blood Group      : %s\n", bloodGroup);
            printf("BMI              : %.2f\n", bmi);
            printf("Health Concern   : %s\n", problem);
            printf("Doctor           : Dr. %s (%s)\n", docName, specialization);
            printf("Appointment Date : %s\n", date);
            printf("Time Slot        : %s\n", time);
            printf("----------------------------\n\n");
        }
    }

    fclose(fp);

    if (!found) {
        printf("No appointments found for your account.\n");
    }
    
    printf("\nPress any key to return to dashboard...");
    getch();
}

// Function to cancel appointments
void cancelAppointment(const char *patientPhone) {
    FILE *fp = fopen("appointments.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open appointments database\n");
        return;
    }

    // Load all appointments for this patient
    char lines[100][512]; // Store up to 100 appointments
    int appointmentCount = 0;
    int patientAppointments[100]; // Indexes of patient's appointments
    int patientAppointmentCount = 0;

    char line[512];
    while (fgets(line, sizeof(line), fp)) {
        strcpy(lines[appointmentCount], line);
        
        // Extract patient phone
        char phone[20];
        if (sscanf(line, "%19[^,]", phone) == 1 && strcmp(phone, patientPhone) == 0) {
            patientAppointments[patientAppointmentCount++] = appointmentCount;
        }
        appointmentCount++;
    }
    fclose(fp);

    if (patientAppointmentCount == 0) {
        printf("\nYou have no appointments to cancel.\n");
        printf("Press any key to return...");
        getch();
        return;
    }

    // Display appointments with serial numbers
    clearScreen();
    printf("\nYOUR APPOINTMENTS (Select one to cancel)\n\n");
    printf("Serial | Doctor ID | Doctor Name         | Date       | Time  | Issue\n");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < patientAppointmentCount; i++) {
        int idx = patientAppointments[i];
        char phone[20], name[100], bloodGroup[10], problem[300];
        int age;
        float height, weight, bmi;
        char docID[20], docName[100], specialization[100], date[20], time[20];

        if (sscanf(lines[idx], "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
               phone, name, &age, &height, &weight, bloodGroup, &bmi, problem,
               docID, docName, specialization, date, time) >= 13) {
            
            printf("%6d | %9s | %-20s | %10s | %5s | %-30s\n", 
                   i+1, docID, docName, date, time, problem);
        }
    }

    // Get which appointment to cancel
    printf("\nEnter serial number to cancel (0 to go back): ");
    int choice;
    scanf("%d", &choice);
    getchar(); // Consume newline

    if (choice <= 0 || choice > patientAppointmentCount) {
        printf("Cancellation aborted.\n");
        return;
    }

    // Get the selected appointment index
    int selectedIdx = patientAppointments[choice-1];
    char selectedLine[512];
    strcpy(selectedLine, lines[selectedIdx]);

    // Parse the selected appointment
    char phone[20], name[100], bloodGroup[10], problem[300];
    int age;
    float height, weight, bmi;
    char docID[20], docName[100], specialization[100], date[20], time[20];

    if (sscanf(selectedLine, "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
           phone, name, &age, &height, &weight, bloodGroup, &bmi, problem,
           docID, docName, specialization, date, time) < 13) {
        printf("Error reading appointment data.\n");
        return;
    }

    // Confirm cancellation
    printf("\nAre you sure you want to cancel this appointment?\n");
    printf("Doctor: Dr. %s (%s)\n", docName, specialization);
    printf("Date: %s at %s\n", date, time);
    printf("Issue: %s\n", problem);
    printf("\nConfirm (y/n)? ");
    char confirm;
    scanf(" %c", &confirm);
    getchar();

    if (tolower(confirm) != 'y') {
        printf("Cancellation aborted.\n");
        return;
    }

    // Save to CancelAppointment.txt
    FILE *cancelFp = fopen("CancelAppointment.txt", "a");
    if (cancelFp) {
        fprintf(cancelFp, "%s,%s,%s,%s,%s,%s\n", 
                phone, name, docID, docName, date, time);
        fclose(cancelFp);
    }

    // Remove from appointments.txt by rewriting the file
    FILE *newFp = fopen("appointments.txt", "w");
    if (newFp) {
        for (int i = 0; i < appointmentCount; i++) {
            if (i != selectedIdx) {
                fprintf(newFp, "%s", lines[i]);
            }
        }
        fclose(newFp);
    }

    printf("\nAppointment successfully cancelled!\n");
    printf("Press any key to continue...");
    getch();
}


/*
▓█████▄  ▒█████   ▄████▄  ▄▄▄█████▓ ▒█████   ██▀███          
▒██▀ ██▌▒██▒  ██▒▒██▀ ▀█  ▓  ██▒ ▓▒▒██▒  ██▒▓██ ▒ ██▒        
░██   █▌▒██░  ██▒▒▓█    ▄ ▒ ▓██░ ▒░▒██░  ██▒▓██ ░▄█ ▒        
░▓█▄   ▌▒██   ██░▒▓▓▄ ▄██▒░ ▓██▓ ░ ▒██   ██░▒██▀▀█▄          
░▒████▓ ░ ████▓▒░▒ ▓███▀ ░  ▒██▒ ░ ░ ████▓▒░░██▓ ▒██▒        
 ▒▒▓  ▒ ░ ▒░▒░▒░ ░ ░▒ ▒  ░  ▒ ░░   ░ ▒░▒░▒░ ░ ▒▓ ░▒▓░        
 ░ ▒  ▒   ░ ▒ ▒░   ░  ▒       ░      ░ ▒ ▒░   ░▒ ░ ▒░        
 ░ ░  ░ ░ ░ ░ ▒  ░          ░      ░ ░ ░ ▒    ░░   ░         
   ░        ░ ░  ░ ░                   ░ ░     ░             
 ░               ░                                           
 ███▄ ▄███▓ ▒█████  ▓█████▄  █    ██  ██▓    ▓█████   ██████ 
▓██▒▀█▀ ██▒▒██▒  ██▒▒██▀ ██▌ ██  ▓██▒▓██▒    ▓█   ▀ ▒██    ▒ 
▓██    ▓██░▒██░  ██▒░██   █▌▓██  ▒██░▒██░    ▒███   ░ ▓██▄   
▒██    ▒██ ▒██   ██░░▓█▄   ▌▓▓█  ░██░▒██░    ▒▓█  ▄   ▒   ██▒
▒██▒   ░██▒░ ████▓▒░░▒████▓ ▒▒█████▓ ░██████▒░▒████▒▒██████▒▒
░ ▒░   ░  ░░ ▒░▒░▒░  ▒▒▓  ▒ ░▒▓▒ ▒ ▒ ░ ▒░▓  ░░░ ▒░ ░▒ ▒▓▒ ▒ ░
░  ░      ░  ░ ▒ ▒░  ░ ▒  ▒ ░░▒░ ░ ░ ░ ░ ▒  ░ ░ ░  ░░ ░▒  ░ ░
░      ░   ░ ░ ░ ▒   ░ ░  ░  ░░░ ░ ░   ░ ░      ░   ░  ░  ░  
       ░       ░ ░     ░       ░         ░  ░   ░  ░      ░  
                     ░                                       
*/


// View Appointments for Doctor (Fixed)
int viewDoctorAppointments(const char *doctorPhone) {
    printf("\n--- Your Scheduled Appointments ---\n");
    
    FILE *fp = fopen("appointments.txt", "r");
    if (fp == NULL) {
        printf("No appointments found.\n");
        return 0;
    }

    char line[512];
    int found = 0;
    int serial = 1;

    printf("\n%-5s %-20s %-15s %-10s %-30s %-15s\n", 
           "No.", "Patient Name", "Date", "Time", "Problem", "Specialization");
    printf("----------------------------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        char pPhone[20], pName[50], pAge[10], pHeight[10], pWeight[10], 
             bloodGroup[5], bmi[10], problem[100], 
             dID[10], dName[50], specialization[50], date[20], time[10];
        
        // Parse all fields from the line
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]", 
                  pPhone, pName, pAge, pHeight, pWeight, bloodGroup, bmi, problem,
                  dID, dName, specialization, date, time) == 13) {
            
            // Check if this appointment belongs to the current doctor
            if (strcmp(dID, doctorPhone) == 0) {
                printf("%-5d %-20s %-15s %-10s %-30s %-15s\n", 
                       serial++, pName, date, time, problem, specialization);
                found = 1;
            }
        }
    }

    fclose(fp);

    if (!found) {
        printf("You have no scheduled appointments.\n");
    }

    printf("\nPress Enter to return...");
    clearInputBuffer();
    return 1;
}
// View Patient Details (Fixed)
int viewPatientDetails(const char *doctorPhone) {
    printf("\n--- Your Patients ---\n");
    
    FILE *apptFile = fopen("appointments.txt", "r");
    if (apptFile == NULL) {
        printf("No appointments found.\n");
        return 0;
    }

    char patients[100][20]; // Store patient phones
    char patientNames[100][50]; // Store patient names
    int patientCount = 0;
    char line[512];

    // Get patients for this doctor
    while (fgets(line, sizeof(line), apptFile)) {
        char pPhone[20], pName[50], dID[20];
        if (sscanf(line, "%[^,],%[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,]", 
                  pPhone, pName, dID) >= 3) {
            if (strcmp(dID, doctorPhone) == 0) {
                // Check if patient already in list
                int exists = 0;
                for (int i = 0; i < patientCount; i++) {
                    if (strcmp(patients[i], pPhone) == 0) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists && patientCount < 100) {
                    strcpy(patients[patientCount], pPhone);
                    strcpy(patientNames[patientCount], pName);
                    patientCount++;
                }
            }
        }
    }
    fclose(apptFile);

    if (patientCount == 0) {
        printf("You have no patients.\n");
        printf("\nPress Enter to return...");
        clearInputBuffer();
        return 0;
    }

    // Display patient list
    printf("\n%-5s %-20s %-15s\n", "No.", "Phone", "Name");
    printf("---------------------------------\n");
    for (int i = 0; i < patientCount; i++) {
        printf("%-5d %-20s %-15s\n", i+1, patients[i], patientNames[i]);
    }

    // Let doctor select a patient
    printf("\nEnter patient number (1-%d): ", patientCount);
    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice < 1 || choice > patientCount) {
        printf("Invalid selection.\n");
        return 0;
    }

    // Now show full details of selected patient
    FILE *patientFile = fopen("patients.txt", "r");
    if (patientFile == NULL) {
        printf("Error accessing patient records.\n");
        return 0;
    }

    int found = 0;
    while (fgets(line, sizeof(line), patientFile)) {
        char pPhone[20], pPassword[30], name[100], email[100], bloodGroup[5], medicalHistory[500];
        int age;
        float weight, height, bmi;
        
        if (sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%f,%f,%[^,],%f,%[^\n]", 
                  pPhone, pPassword, name, &age, email, &weight, &height, bloodGroup, &bmi, medicalHistory) >= 9) {
            if (strcmp(pPhone, patients[choice-1]) == 0) {
                found = 1;
                printf("\n--- Patient Medical Record ---\n");
                printf("Name: %s\n", name);
                printf("Phone: %s\n", pPhone);
                printf("Age: %d\n", age);
                printf("Weight: %.1f kg\n", weight);
                printf("Height: %.1f cm\n", height);
                printf("BMI: %.1f\n", bmi);
                printf("Blood Group: %s\n", bloodGroup);
                printf("Email: %s\n", email);
                printf("\nMedical History:\n%s\n", medicalHistory);
                break;
            }
        }
    }
    fclose(patientFile);

    if (!found) {
        printf("Patient details not found.\n");
    }

    printf("\nPress Enter to return...");
    clearInputBuffer();
    return 1;
}
// Doctor Dashboard (Fixed)
int writePrescription(const char *doctorPhone) {
    // First show doctor's upcoming appointments
    printf("\n--- Your Appointments ---\n");
    
    FILE *apptFile = fopen("appointments.txt", "r");
    if (apptFile == NULL) {
        printf("No appointments found.\n");
        return 0;
    }

    char patients[100][20]; // Store patient phones
    char patientNames[100][50]; // Store patient names
    int patientCount = 0;
    char line[512];

    printf("\n%-5s %-20s %-15s\n", "No.", "Phone", "Name");
    printf("---------------------------------\n");

    while (fgets(line, sizeof(line), apptFile)) {
        char pPhone[20], pName[50], dID[20], date[20], time[10];
        if (sscanf(line, "%[^,],%[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%[^,],%*[^,],%*[^,],%[^,],%[^\n]", 
                  pPhone, pName, dID, date, time) >= 5) {
            if (strcmp(dID, doctorPhone) == 0) {
                strcpy(patients[patientCount], pPhone);
                strcpy(patientNames[patientCount], pName);
                printf("%-5d %-20s %-15s (Appt: %s %s)\n", 
                      patientCount+1, pPhone, pName, date, time);
                patientCount++;
            }
        }
    }
    fclose(apptFile);

    if (patientCount == 0) {
        printf("You have no appointments.\n");
        printf("\nPress Enter to return...");
        clearInputBuffer();
        return 0;
    }

    // Get patient selection
    printf("\nEnter patient number (1-%d): ", patientCount);
    int choice;
    scanf("%d", &choice);
    clearInputBuffer();

    if (choice < 1 || choice > patientCount) {
        printf("Invalid selection.\n");
        return 0;
    }

    char patientPhone[20];
    strcpy(patientPhone, patients[choice-1]);

    // Get prescription details
    char date[11], medications[500], dosage[200], instructions[500];
    
    // Get current date
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(date, sizeof(date), "%d-%m-%Y", t);

    printf("\n--- New Prescription for %s ---\n", patientNames[choice-1]);
    printf("Medications (comma separated): ");
    fgets(medications, sizeof(medications), stdin);
    trimNewline(medications);

    printf("Dosage: ");
    fgets(dosage, sizeof(dosage), stdin);
    trimNewline(dosage);

    printf("Instructions: ");
    fgets(instructions, sizeof(instructions), stdin);
    trimNewline(instructions);

    // Save to prescriptions file
    FILE *fp = fopen("prescriptions.txt", "a");
    if (fp == NULL) {
        printf("Error saving prescription.\n");
        return 0;
    }

    fprintf(fp, "%s,%s,%s,%s,%s,%s\n", 
            doctorPhone, patientPhone, date, medications, dosage, instructions);
    fclose(fp);

    printf("\nPrescription saved successfully!\n");
    printf("Press Enter to continue...");
    clearInputBuffer();
    return 1;
}