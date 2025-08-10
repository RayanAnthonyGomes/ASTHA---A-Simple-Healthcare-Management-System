//LIBRARY FILES
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include <windows.h>
#include<stdbool.h>

// Clear screen function (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//VERIFICATION AND SMALL INTERNAL MODULES

//RANDOM TIME GENERATION FUNCTION
int randomInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
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

void emergencyContacts(void);

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
    clearScreen();
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
    printf("Menu Options:\n");
    printf("1. Registration (For Patients Only)\n");
    printf("2. Login (As Patient, Doctor, Admin)\n");
    printf("3. Emergency Contacts\n");
    printf("4. About Us\n");
    printf("5. Exit\n");
    printf("\n");
    printf("Enter any option (1-5) to continue: ");
}

// Function prototypes
void registerPatient(void);
void patientDashboard(char name[], char phone[]);
void doctorDashboard(char name[], char phone[]);
void adminDashboard(char name[], char phone[]);
void loginOption(void);
bool appointmentForm(const char *patientPhone);

int main() {
    srand(time(NULL)); // Seed random number generator
    
    while(1) {
        defaultPage();
        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        if (checkForBackCommand(input)) {
            printf("You're already at the main menu.\n");
            continue;
        }
        
        int option = atoi(input);
        
        switch (option) {
            case 1:
                registerPatient();
                break;
            case 2:
                loginOption();
                break;
            case 3:
                emergencyContacts();
                printf("\nPress any key to continue...");
                getch();
                break;
            case 4:
                // About Us
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid option!\n");
                Sleep(1000);
        }
    }
    return 0;
}

void registerPatient() {
    clearScreen();
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
    getchar(); // Consume newline
    
    if (option == 1) {
        printf("\nYour password: %s\n", password);
        printf("Keep this confidential! Do not share this with anyone! Not even your friends!\n");
        printf("\nPress any key to continue...");
        getch();
    } else if (option == 2) {
        loginOption();
    }
}

void patientDashboard(char name[], char phone[]) {
    char input[20];
    
    while(1) {
        clearScreen();
        printf("\n=== PATIENT DASHBOARD ===\n");
        printf("Welcome, %s\n\n", name);
        printf("1. Book Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Cancel Appointments\n");
        printf("4. Logout\n");
        printf("\nEnter choice (1-4) or 'back' to return: ");
        
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        if (checkForBackCommand(input)) {
            printf("\nYou're at the main menu. Type '4' to logout.\n");
            Sleep(1500);
            continue;
        }
        
        int option = atoi(input);
        
        switch(option) {
            case 1:
                clearScreen();
                if (appointmentForm(phone)) {
                    printf("\nPress any key to continue...");
                    getch();
                }
                break;
            case 2:
                // viewAppointments(phone);
                break;
            case 3:
                // cancelAppointment(phone);
                break;
            case 4:
                printf("Logging out...\n");
                Sleep(1000);
                return;
            default:
                printf("Invalid option!\n");
                Sleep(1000);
        }
    }
}

bool appointmentForm(const char *patientPhone) {
    clearScreen();
    FILE *pfp = fopen("patients.txt", "r");
    if (pfp == NULL) {
        printf("Error: Could not open patients database\n");
        return false;
    }

    // Variables to store patient data
    char pName[100], pEmail[100], pPassword[30];
    int pAge;
    float pWeight;
    int patientFound = 0;

    // Search for patient in database
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

    // Generate available dates
    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);
    struct tm availableDates[5];
    for (int i = 0; i < 5; i++) {
        availableDates[i] = currentDate;
        int addDays = randomInRange(1, 30);
        availableDates[i].tm_mday += addDays;
        mktime(&availableDates[i]);
    }

    // Medical info
    char bloodGroup[10], problem[300];
    float height, bmi;

    printf("\n=== APPOINTMENT BOOKING ===\n");
    printf("Type 'back' at any time to cancel\n\n");
    printf("Patient: %s (Age: %d, Weight: %.2f kg)\n", pName, pAge, pWeight);

    // Get additional medical info
    printf("Height (in meters): ");
    char input[100];
    fgets(input, sizeof(input), stdin);
    if (checkForBackCommand(input)) return false;
    sscanf(input, "%f", &height);

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

    printf("\nConfirm booking? (y/n): ");
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

// [Rest of your functions (doctorDashboard, adminDashboard, loginPatient, loginDoctor, 
// loginAdmin, loginOption, emergencyContacts) remain the same but should be updated 
// with similar improvements as shown above]
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
        printf("4: Logout\n");
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
                appointmentForm(phone);  // Just pass the variable name
                printf("\nReturning to patient dashboard...\n");
                break;
            case 2:
                // if(viewAppointments(phone)) {
                //     printf("\nReturning to patient dashboard...\n");
                // }
                break;
            case 3:
                // if(cancelAppointment(phone)) {
                //     printf("\nReturning to patient dashboard...\n");
                // }
                break;
            case 4:
                printf("Logging out...\n");
                defaultPage();
                return;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

void doctorDashboard(char name[], char phone[]) {
    int option;
    char input[10];
    
    while(1) {
        printf("\nDOCTOR DASHBOARD\n\n");
        printf("1: View Scheduled Appointments\n");
        printf("2: View Patient Details\n");
        printf("3: Write Prescription\n");
        printf("4: Logout\n");
        printf("Type 'back' at any time to return to this menu\n");

        printf("\nPlease select your option (1-4): ");
        scanf("%s", input);
        
        if (checkForBackCommand(input)) {
            printf("\nYou're already at the main menu.\n");
            continue;
        }
        
        option = atoi(input);
        
        switch(option) {
            case 1:
                // if(viewDoctorAppointments(phone)) {
                //     printf("\nReturning to doctor dashboard...\n");
                // }
                break;
            case 2:
                // if(viewPatientDetails()) {
                //     printf("\nReturning to doctor dashboard...\n");
                // }
                break;
            case 3:
                // if(writePrescription(phone)) {
                //     printf("\nReturning to doctor dashboard...\n");
                // }
                break;
            case 4:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid option. Please try again.\n");
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