//LIBRARY FILES
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<cstdlib>
#include<random>

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


void defaultPage()

{
    //printf("\033[1;36m");  // Bold + Cyan
    printf("\033[1;35m");
    printf(
"....###.....######..########.##.....##....###.......###...\n"
"...##.##...##....##....##....##.....##...##.##.....##.##..\n"
"..##...##..##..........##....##.....##..##...##...##...##.\n"
".##.....##..######.....##....#########.##.....##.##.....##\n"
".#########.......##....##....##.....##.#########.#########\n"
".##.....##.##....##....##....##.....##.##.....##.##.....##\n"
".##.....##..######.....##....##.....##.##.....##.##.....##\n"
);
    printf("\033[0m");
    printf("Welcome to \"ASTHAA\"\n");
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


/*
 _   _ ____  ____    _  _____ _____         
| | | |  _ \|  _ \  / \|_   _| ____|        
| | | | |_) | | | |/ _ \ | | |  _|          
| |_| |  __/| |_| / ___ \| | | |___         
 \___/|_|   |____/_/   \_\_| |_____|      _ 
|  _ \ __ _ ___ _____      _____  _ __ __| |
| |_) / _` / __/ __\ \ /\ / / _ \| '__/ _` |
|  __/ (_| \__ \__ \\ V  V / (_) | | | (_| |
|_|   \__,_|___/___/ \_/\_/ \___/|_|  \__,_|


*/
void inputPassword(char *password, int maxLen) {
    int i = 0;
    char ch;

    while (1) {
        ch = getch();

        if (ch == 13) { // Enter
            password[i] = '\0';
            break;
        }
        else if (ch == 8) { // Backspace
            if (i > 0) {
                i--;
                printf("\b \b"); //backspace dile ar count hoitese na alada character
            }
        }
        else if (i < maxLen - 1) {
            password[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
}

int isStrongPassword(const char *password) {
    int hasUpper = 0, hasLower = 0, hasSymbol = 0;
    int length = strlen(password);

    if (length < 8) return 0;
//ekhn user has to enter a password with at least 8 characters, 1 uppercase, 1 lowercase, and 1 symbol
    for (int i = 0; i < length; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (ispunct(password[i])) hasSymbol = 1;
        //Another condition can be added for digit check
        else if (isdigit(password[i])) hasSymbol = 1; // Treat digits as symbols
    }
    return hasUpper && hasLower && hasSymbol;
}



/*
 ____   _  _____ ___ _____ _   _ _____                             
|  _ \ / \|_   _|_ _| ____| \ | |_   _|                            
| |_) / _ \ | |  | ||  _| |  \| | | |                              
|  __/ ___ \| |  | || |___| |\  | | |                              
|_|_/_/___\_\_|_|___|_____|_|_\_|_|_|      _  _____ ___ ___  _   _ 
|  _ \| ____/ ___|_ _/ ___|_   _|  _ \    / \|_   _|_ _/ _ \| \ | |
| |_) |  _|| |  _ | |\___ \ | | | |_) |  / _ \ | |  | | | | |  \| |
|  _ <| |__| |_| || | ___) || | |  _ <  / ___ \| |  | | |_| | |\  |
|_| \_\_____\____|___|____/ |_| |_| \_\/_/   \_\_| |___\___/|_| \_|*/

void registerPatient()
{
 //First step is to open my database and get the patients.txt file to edit it. Append mode e jawa lagbe age then shob kichu korte parbo

 FILE *fp = fopen("patients.txt", "a");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
//Variables declare korsi
char name[100], email[100], phone[20], password[30];
int age;
float weight;

printf("You have selected the patient register option. \nPlease fill the form up to continue your registration.\n\nPatient Registration Form:\n");

printf("Enter Your Name: ");
    getchar(); //previous input theke line clear korlam
    fgets(name, sizeof(name), stdin); //fgets diye input nicchi
    name[strcspn(name, "\n")] = 0; //Notun line shoraitesi

printf("Age: ");
    scanf("%d", &age);

printf("Weight (kg): ");
    scanf("%f", &weight);

printf("Email: ");
    scanf("%s", email);

printf("Phone Number: ");
    scanf("%s", phone);

printf("Set a Password: ");
//password masking    ++ STRONG PASSSWORD CHECK KORTESI
while (1) {
    inputPassword(password, sizeof(password));
    printf("Password must be at least 8 characters long, and include:\n- 1 uppercase letter\n- 1 lowercase letter\n- 1 number\n- 1 symbol\n");
    if (!isStrongPassword(password)) {
        printf("Password must be at least 8 characters long, contain 1 uppercase, 1 lowercase, and 1 symbol.\n");
        printf("Enter again: ");
    } else {
        break;
    }
}

//Patients.txt file e data dicchi
fprintf(fp, "%s,%s,%s,%d,%s,%.2f\n", phone, password, name, age, email, weight);

fclose(fp);

printf("\n\nRegistration Successfully Done!\n");
printf("Your Details:\nName: %s,\nPhone Number: %s,\nAge: %d,\nEmail: %s,\n Weight: %.2f,\nPassword: ********\n",name, phone, age, email, weight, password);
printf("/nIf you want to see your password please press 1, Otherwise press 2 to login to our software.\n");
int postOption;
scanf("%d", &postOption);
if (postOption == 1) {
    printf("Your Password is: %s\n", password);

}else if (postOption == 2) {
    printf("You can now login to our software.\n");
    //loginOption();
} else {
    printf("Invalid option selected. Exiting you to homepage...If by any chace the program is stuck please restart the program.\n");
    defaultPage();
}
}

/*
    _    ____  ____   ___ ___ _   _ _____ __  __ _____ _   _ _____ 
   / \  |  _ \|  _ \ / _ \_ _| \ | |_   _|  \/  | ____| \ | |_   _|
  / _ \ | |_) | |_) | | | | ||  \| | | | | |\/| |  _| |  \| | | |  
 / ___ \|  __/|  __/| |_| | || |\  | | | | |  | | |___| |\  | | |  
/_/___\_\_| __|_| __ \___/___|_| \_| |_| |_|  |_|_____|_| \_| |_|  
|  ___/ _ \|  _ \|  \/  |                                          
| |_ | | | | |_) | |\/| |                                          
|  _|| |_| |  _ <| |  | |                                          
|_|   \___/|_| \_\_|  |_|                                          

*/

void appointmentForm(const char *patientPhone){
    //Appointment form er shuru
    char name[100], bloodGroup[10], problem[300];
    int age;
    float height, weight, bmi;

    //TIME GENERATION ER PART
    srand(time(NULL)); // Random number generation er jonno srand use korsi
//Ajker date fix kortesi
    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);
    struct tm avvailableDates[5]; // 5 ta available date rakhsi
    for (int i = 0; i<5; i++){
        avvailableDates[i] = currentDate; //current date theke shuru hobe
        int addDays = randomInRange(1, 30); // 1 theke 30 din er moddhe random date add korbo;
        avvailableDates[i].tm_mday += addDays; //din add korlam
        mktime(&avvailableDates[i]); //mktime diye date ke normalize korlam
    }

//Patient er info nicchi abr
    printf("\nPatient Medical Info\n");
    printf("Your Full Name: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;//Notun line shoraitesi

    printf("Age: ");
    scanf("%d", &age);

    printf("Height (in meters): ");
    scanf("%f", &height);

    printf("Weight (in kg): ");
    scanf("%f", &weight);

    printf("Blood Group (e.g., A+, B-, O+): ");
    scanf("%s", bloodGroup);

    bmi = weight / (height * height);

    //baki shob data niye BMI dekhabo. AUTO Process er ekta jinish + EMR e boshaite parbo

    getchar();
    printf("Briefly describe your health issue: ");
    fgets(problem, sizeof(problem), stdin);
    problem[strcspn(problem, "\n")] = 0;

    FILE *fp = fopen("doctors.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open doctors.txt\n");
        return;
    }
    //temp vars nisi
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
    //ebar doc slect korbe
    char selectedDoctorID[20];
    printf("Enter Doctor ID to book appointment with: ");
    scanf("%s", selectedDoctorID);

    int found = -1;
    for (int i = 0; i < docCount; i++) {
        if (strcmp(selectedDoctorID, doctorIDs[i]) == 0) {
            found = i;
            break;
        }
    }
    if (found == -1) {
        printf("Invalid Doctor ID. Appointment not booked.\n"); //jodi pick e na kore tahole to appt dite parbo na
        return;
    }

    //SELECT Date and Time 
    //nicher ta re baad diye random date and time generate korbo
    // char date[20], time[20];
    // printf("Enter Appointment Date (Year-Month-Date): ");
    // scanf("%s", date);
    // printf("Enter Appointment Time (for example, 10:30AM): ");
    // scanf("%s", time);

    printf("Available Dates:\n");
    for(int i = 0; i < 5; i++){
        printf("%d. %02d-%02d-%d\n",i+1, avvailableDates[i].tm_mday, avvailableDates[i].tm_mon + 1, avvailableDates[i].tm_year + 1900);
    }

    //ekhn patient date select korbe
        int dateChoice;
    printf("Select a date form options 1-5: ");
    scanf("%d", &dateChoice);
    if (dateChoice < 1 || dateChoice > 5) {
        printf("Invalid date choice. Appointment not booked.\n");
        return;
    }
        struct tm chosenDate = avvailableDates[dateChoice - 1]; // 1-5 er moddhe select korbe

        //ekhn user re diye time select korabo

        int numslots = randomInRange(3, 5); // 3 theke 5 ta time slot generate korbo

char timeSlots[5][10]; // Assuming 24-hour format like "14:00"

int hourOptions[] = {9,10,11,12,13,14,15,16,17}; // 9AM - 5PM

for (int i = 0; i < numslots; i++) {
    int hour = hourOptions[randomInRange(0, 8)];
    snprintf(timeSlots[i], sizeof(timeSlots[i]), "%02d:00", hour); //I USED snprintf to format and store the time like "09:00", "14:00", etc. 
}
 printf("Available Time Slots for 27-08-2025:\n");

    // Display time slots to user
    for (int i = 0; i < numslots; i++) {
        printf("%d. %s\n", i + 1, timeSlots[i]);
    }


                //ekhn patient time select korbe
                int timeChoice;
                printf("Select a time slot (1-%d): ", numslots);
                scanf("%d", &timeChoice);
                if (timeChoice < 1 || timeChoice > numslots) {
    printf("Invalid time choice. Appointment not booked.\n");
    return;
}

    //pura appt er details show korabo
    printf("\nAppointment Summary \n");
    printf("Patient Name: %s\nAge: %d\nHeight: %.2f m\nWeight: %.2f kg\nBMI: %.2f\n", name, age, height, weight, bmi);
    printf("Blood Group: %s\nProblem: %s\n", bloodGroup, problem);
   printf("Doctor: Dr. %s (%s)\nDate: %02d-%02d-%d\nTime: %s\n",
       doctorNames[found], doctorSpecs[found],
       chosenDate.tm_mday, chosenDate.tm_mon + 1, chosenDate.tm_year + 1900,
       timeSlots[timeChoice - 1]);

    //appts.txt e te shob kichu save korbo afp dewar karon hocche fp agei diye disi eta basically var er naam eta jekono kisu hoite pare
    FILE *afp = fopen("appointments.txt", "a");
    if (afp == NULL) {
        printf("Error: Could not open appointments.txt\n");
        return;
    }

    fprintf(afp, "%s,%s,%d,%.2f,%.2f,%s,%.2f,%s,%s,%s,%s,%02d-%02d-%d,%s\n",
        patientPhone, name, age, height, weight, bloodGroup, bmi,
        problem, doctorIDs[found], doctorNames[found], doctorSpecs[found],
        chosenDate.tm_mday, chosenDate.tm_mon + 1, chosenDate.tm_year + 1900,
        timeSlots[timeChoice - 1]);
    fclose(afp);
    //confirmation msg dekhabo
    printf("\nAppointment successfully booked!\n");
}

void viewAppointments(const char *patientPhone) {
    FILE *fp = fopen("appointments.txt", "r");
    if (fp == NULL) {
        printf("Error: Cant open appointments.txt\n");
        return;
    }

    char line[512];
    int found = 0;

    printf("\nYour Appointments\n");

    // Variables to match the columns
    char phone[20], name[100], bloodGroup[10], problem[300];
    int age;
    float height, weight, bmi;
    char docID[20], docName[100], specialization[100], date[20], time[20];

    while (fgets(line, sizeof(line), fp)) {
            //purapuri string scan kortesi
        sscanf(line, "%[^,],%[^,],%d,%f,%f,%[^,],%f,%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
               phone, name, &age, &height, &weight, bloodGroup, &bmi, problem,
               docID, docName, specialization, date, time);
//paisi document e and summary show korbo
        if (strcmp(phone, patientPhone) == 0) {
            found = 1;
            printf("\nAppointment Summary\n");
            printf("Patient Name     : %s\n", name);
            printf("Age              : %d\n", age);
            printf("Height           : %.2f m\n", height);
            printf("Weight           : %.2f kg\n", weight);
            printf("Blood Group      : %s\n", bloodGroup);
            printf("BMI              : %.2f\n", bmi);
            printf("Problem          : %s\n", problem);
            printf("Doctor           : Dr. %s (%s)\n", docName, specialization);
            printf("Date & Time      : %s at %s\n", date, time);
            printf("================================\n");
        }
    }

    fclose(fp);

    if (!found) {
        printf("No appointments found for your account.\n");
    }
}


void cancelAppointment(const char* patientPhone){
//    viewAppointments(const char* patientPhone);
    printf("PLease select the appointment which u want to cancel.");
    int x;
    scanf("%d",&x);
    printf("Your appointment will soon be canceled by the admin.");
}



/*
██████╗  ██████╗  ██████╗████████╗ ██████╗ ██████╗           
██╔══██╗██╔═══██╗██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗          
██║  ██║██║   ██║██║        ██║   ██║   ██║██████╔╝          
██║  ██║██║   ██║██║        ██║   ██║   ██║██╔══██╗          
██████╔╝╚██████╔╝╚██████╗   ██║   ╚██████╔╝██║  ██║          
╚═════╝  ╚═════╝  ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝          
                                                             
███╗   ███╗ ██████╗ ██████╗ ██╗   ██╗██╗     ███████╗███████╗
████╗ ████║██╔═══██╗██╔══██╗██║   ██║██║     ██╔════╝██╔════╝
██╔████╔██║██║   ██║██║  ██║██║   ██║██║     █████╗  ███████╗
██║╚██╔╝██║██║   ██║██║  ██║██║   ██║██║     ██╔══╝  ╚════██║
██║ ╚═╝ ██║╚██████╔╝██████╔╝╚██████╔╝███████╗███████╗███████║
╚═╝     ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝╚══════╝

*/
void viewDoctorAppointments(char doctorID[]) {
    FILE *fp = fopen("appointments.txt", "r");
    if (!fp) {
        printf("No appointment records found.\n");
        return;
    }

    char line[256];
    int found = 0;

    printf("\n--- Appointments for Doctor %s ---\n", doctorID);
    while (fgets(line, sizeof(line), fp)) {
        char pName[50], pAge[5], pGender[10], pPhone[20];
        char dID[20], dName[50], date[15], time[10];

        sscanf(line, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
               pName, pAge, pGender, pPhone,
               dID, dName, date, time);

        if (strcmp(dID, doctorID) == 0) {
            printf("\nPatient Name: %s\nAge: %s\nGender: %s\nPhone: %s\n", pName, pAge, pGender, pPhone);
            printf("Date: %s\nTime: %s\n", date, time);
            found = 1;
        }
    }

    if (!found) {
        printf("No appointments found for you.\n");
    }
    fclose(fp);
}
/*
 ____    _    ____  _   _ ____   ___    _    ____  ____  ____  
|  _ \  / \  / ___|| | | | __ ) / _ \  / \  |  _ \|  _ \/ ___| 
| | | |/ _ \ \___ \| |_| |  _ \| | | |/ _ \ | |_) | | | \___ \ 
| |_| / ___ \ ___) |  _  | |_) | |_| / ___ \|  _ <| |_| |___) |
|____/_/   \_\____/|_| |_|____/ \___/_/   \_\_| \_\____/|____/ 
*/
void patientDashboard(char name[], char phone[]) {
    printf("PATIENT DASHBOARD\n\n");
    printf("1: Book Appointment\n");
    printf("2: View Appointments\n");
    printf("3: Cancel Appointments\n");
    printf("4: Logout\n");

    printf("Please select your option (1-4): ");
    int option;
    scanf("%d", &option);

    if (option == 1) {
        appointmentForm(phone);
    } else if (option == 2) {
        //viewAppointments(phone);
    } else if (option == 3) {
        // callCancelAppointment(phone);
    } else if (option == 4) {
        printf("Logging out...\n");
        defaultPage();
    } else {
        printf("Invalid option. Please try again.\n");
    }
}

void doctorDashboard(char name[], char phone[]) {
    printf("DOCTOR DASHBOARD\n\n");
    printf("1: View Scheduled Appointments\n");
    printf("2: View Patient Details\n");
    printf("3: Write Prescription\n");
    printf("4: Logout\n");

    printf("Please select your option (1-4): ");
    int option;
    scanf("%d", &option);

    if (option == 1) {
       viewDoctorAppointments(phone); 
    } else if (option == 2) {
        // viewPatientDetails();
    } else if (option == 3) {
        // writePrescription(phone);
    } else if (option == 4) {
        printf("Logging out...\n");
    } else {
        printf("Invalid option. Please try again.\n");
    }
}

void adminDashboard(char name[], char phone[]) {
    printf("ADMIN DASHBOARD\n\n");
    printf("1: View All Appointments\n");
    printf("2: View Patients\n");
    printf("3: Edit Patients\n");
    printf("4: Delete Patients\n");
    printf("5: Add Doctors\n");
    printf("6: Remove Doctors\n");
    printf("7: Logout\n");

    printf("Please select your option (1-7): ");
    int option;
    scanf("%d", &option);

    if (option == 1) {
        // viewAllAppointments();
    } else if (option == 2) {
        // viewPatients();
    } else if (option == 3) {
        // editPatients();
    } else if (option == 4) {
        // deletePatients();
    } else if (option == 5) {
        // addDoctors();
    } else if (option == 6) {
        // removeDoctors();
    } else if (option == 7) {
        printf("Logging out...\n");
    } else {
        printf("Invalid option. Please try again.\n");
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
    printf("You have selected the login option.\n Please select your option from below.\n1. Login As Patient\n2. Login as Doctor\n3. Login as Admin\n");
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
}
}

//   ▄▄▄▄███▄▄▄▄      ▄████████  ▄█  ███▄▄▄▄  
// ▄██▀▀▀███▀▀▀██▄   ███    ███ ███  ███▀▀▀██▄
// ███   ███   ███   ███    ███ ███▌ ███   ███
// ███   ███   ███   ███    ███ ███▌ ███   ███
// ███   ███   ███ ▀███████████ ███▌ ███   ███
// ███   ███   ███   ███    ███ ███  ███   ███
// ███   ███   ███   ███    ███ ███  ███   ███
//  ▀█   ███   █▀    ███    █▀  █▀    ▀█   █▀ 


int main()

{   //home page
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
