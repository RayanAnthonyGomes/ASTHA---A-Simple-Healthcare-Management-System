/*
Notes: ASTHAA is a simple hms. Made by Rayan, Bappi & Tanvir.

We have used files to store data. We have taken help from Stack Overflow, GeeksforGeeks and many other sources. 

Work Distribution: 
Rayan -> All of the patient modules, helper functions, file handling
Bappi -> All of the admin modules
Tanvir -> All of the doctor modules, UI

Little Explanation of each of everything:

1. Why static?
-> Ei function ta sudhu ei file er moddhei use kora jabe. Baire theke access kora jabe na. Naming conflict komay, Compiler function ta better optimize korte pare

2. Why clear buffer input?
-> scanf er por jeta leftover thake, seta clear kore, Enter press er por je newline thake, seta remove kore, Character input skip howa bondho kore

3. Why not clrscr()?
-> clrscr() is not a standard C function. It is not portable. So we use system("cls") for Windows and system("clear") for Linux/Mac.  It won’t work in GCC, \
    Clang, MSVC, or modern compilers unless we use Turbo C (which is outdated). Jodi use kori tahole "fatal error dekhay"

4. why use trim?
-> trim function ta string er trailing spaces, tabs, newlines remove kore. Jemon fgets diye input neyar por, \n thake, seta remove kore.

5. Why use replaceCommas?
-> String er moddhe joto , ache sob ; diye replace kore. File storage e previous commit porzonto eta chilo na, add korar reason hocche comma er jonno column ulta palta hoy. haracter by character check kore, , paile ; diye replace kore

6. Why RandomInRange?
-> RandomInRange function ta random number generate kore, jekhane minimum and maximum range diye dite hoy. Random number er jonno rand() use kora hoyeche.

7. Why nowTimestamp?
-> nowTimestamp function ta current date and time er format "dd-mm-YYYY HH:MM" e output kore. File storage e date/time store korar jonno use kora hoyeche.

8. Why isValidBangladeshiPhone?
-> Previous demonstration e sir bolechilen, random number add na kore ekta valid phone number use korte hobe. tai 01 theke shuru hoye 11 digit porzsonto jabe

9. Why isValidEmail?
-> Previous demonstration e sir bolechilen, random kisu email dicchi kintu input hocche, jeta real life er sathe milay na. Tai email er khetre @ lagbe and . lagbe ekta

10. why alada read line function?
-> Reads a full line of input from stdin into buf, Makes sure the buffer size is not exceeded (cap), Strips trailing \n and \r (newline + carriage return)

11. Is back ?
-> back, Back, bAck... shob gula nibe kintu backspace nibe na. Ek dhap agay jabe function.

12.  validatePasswordWithFeedback?
-> CTYPE.H lib ta use korsi, upper, lower, digit er count nitesi jodi 1 tar kom thake taile feedback dibo.

13. why inputPassword? why not scanf?
-> password masking er jinish ta implement kora hoise.

14. 
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <strings.h>



//SMALL HELPERS (Stack Overflow Combined Helper Functions)

// clear screen -> Function ta OS check kore. Windows hole cls, ar onno OS hole clear command chalai. system() diye command prompt/terminal e command chalano hoy.

static void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// flush leftover input (use after scanf)
static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// trim trailing \r \n spaces tabs
static void trim(char *s) {
    size_t n = strlen(s);
    while (n && (s[n-1] == '\r' || s[n-1] == '\n' || s[n-1] == ' ' || s[n-1] == '\t')) s[--n] = '\0';
}

// replace commas with ';' to keep CSV stable
static void replaceCommas(char *s) {
    for (char *p = s; *p; ++p) if (*p == ',') *p = ';';
}

// random integer in [min,max]
static int randomInRange(int min, int max) {
    if (max < min) return min;
    return rand() % (max - min + 1) + min;
}

// current timestamp "dd-mm-YYYY HH:MM"
static void nowTimestamp(char *out, size_t cap) {
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    strftime(out, cap, "%d-%m-%Y %H:%M", lt);
}

// read a line into buf and strip trailing \r or \n; returns 1 on success
static int read_line(char *buf, size_t cap) {
    if (!fgets(buf, cap, stdin)) return 0;
    size_t n = strlen(buf);
    while (n && (buf[n-1] == '\n' || buf[n-1] == '\r')) buf[--n] = '\0';
    return 1;
}

// case-insensitive check for "back"
static int is_back(const char *s) {
    char tmp[16];
    size_t n = strlen(s);
    if (n >= sizeof(tmp)) n = sizeof(tmp)-1;
    for (size_t i = 0; i < n; i++) tmp[i] = (char)tolower((unsigned char)s[i]);
    tmp[n] = '\0';
    return strcmp(tmp, "back") == 0;
}

// rstrip trailing spaces/tabs/CR/LF (for parsed fields)
static void rstrip(char *s) {
    size_t n = strlen(s);
    while (n && (s[n-1] == ' ' || s[n-1] == '\t' || s[n-1] == '\n' || s[n-1] == '\r')) s[--n] = '\0';
}

// unique time slots between 09:00 and 17:00
static int build_time_slots(char slots[][10], int max_slots) {
    int want = randomInRange(3, 5);
    if (want > max_slots) want = max_slots;
    int hours[] = {9,10,11,12,13,14,15,16,17};
    int used[9] = {0}, made = 0;
    while (made < want) {
        int i = randomInRange(0, 8);
        if (!used[i]) {
            used[i] = 1;
            snprintf(slots[made], 10, "%02d:00", hours[i]);
            made++;
        }
    }
    return made;
}
// ========== VALIDATION ==========

// BD phone: 11 digits, starts with 01
static int isValidBangladeshiPhone(const char *phone) {
    if (!phone) return 0;
    if (strlen(phone) != 11) {
        printf("Must be exactly 11 digits.\n");
        return 0;
    }
    if (phone[0] != '0' || phone[1] != '1') {
        printf("Must start with 01 (e.g., 017XXXXXXXX)\n");
        return 0;
    }
    for (int i = 0; i < 11; i++) {
        if (!isdigit((unsigned char)phone[i])) {
            printf("Only digits allowed.\n");
            return 0;
        }
    }
    return 1;
}

// very basic email check: exactly one '@' and at least one '.'
static int isValidEmail(const char *email) {
    if (!email || strlen(email) < 5) return 0;
    int at = 0, dot = 0;
    for (const char *p = email; *p; ++p) {
        if (*p == '@') at++;
        else if (*p == '.') dot++;
    }
    return (at == 1 && dot >= 1);
}

// Password feedback (>=8, upper, lower, digit, special)
static int validatePasswordWithFeedback(const char *pw) {
    if (!pw) return 0;
    int len = (int)strlen(pw);
    if (len < 8) { printf("Too short (min 8).\n"); return 0; }
    int up=0, lo=0, di=0, sp=0;
    for (int i=0;i<len;i++){
        if (isupper((unsigned char)pw[i])) up=1;
        else if (islower((unsigned char)pw[i])) lo=1;
        else if (isdigit((unsigned char)pw[i])) di=1;
        else if (ispunct((unsigned char)pw[i])) sp=1;
    }
    if (!up) printf("Missing uppercase.\n");
    if (!lo) printf("Missing lowercase.\n");
    if (!di) printf("Missing digit.\n");
    if (!sp) printf("Missing special character.\n");
    return up && lo && di && sp;
}

// masked password input using getch()
static void inputPassword(char *password, int maxLen) {
    int i = 0;
    while (1) {
        int ch = getch();
        if (ch == '\r' || ch == '\n') { // Enter
            password[i] = '\0';
            printf("\n");
            break;
        } else if ((ch == 8 || ch == 127) && i > 0) { // Backspace
            i--;
            printf("\b \b");
        } else if (isprint(ch) && i < maxLen-1) {
            password[i++] = (char)ch;
            printf("*");
        }
    }
}

//ACCOUNTS er choto ekta section jekhane basic constant info dewa. Jekhane send korbe ar ki ar koto taka lagbe
#define APPOINTMENT_FEE 500
static const char *MFS_RECEIVER_NUMBER   = "01700000000";   // bKash/Rocket/Nagad receiver
static const char *BANK_RECEIVER_ACCOUNT = "012345678901";  // receiver bank account
static const char *BANK_RECEIVER_NAME    = "ASTHAA HEALTHCARE";

//Function er prototype gula globally call kore rakhtesi. nahole pore jhamela hobe na jodi ektar por ekta func banaite thaki.. .. Basically sequence maintain korte hobe na
//UI + Dash + loginOPT DEclaration
static void defaultPage(void);
static void loginOption(void);
static void patientDashboard(char name[], char phone[]);
static void doctorDashboard(char name[], char phone[]);
static void adminDashboard(char name[], char phone[]);

//Patient er work flow. reg -> login -> dashboard ...
static void registerPatient(void);
static int  loginPatient(void);
static int  loginDoctor(void);
static int  loginAdmin(void);
static bool appointmentForm(const char *patientPhone);
static void viewAppointments(const char *patientPhone);
static void requestCancelAppointment(const char *patientPhone);
static void viewPrescribedMedicines(const char *patientPhone);
static void patientLogout(const char *patientPhone);

//Doctor er work flow. Login -> dashboard ...
static int viewDoctorAppointments(const char *doctorPhone);
static int viewPatientDetails(const char *doctorPhone);
static int writePrescription(const char *doctorPhone);

//admin flow
static int viewAllAppointments(void);
static int viewAllPatients(void);
static int editPatientRecord(void);
static int deletePatients(void);
static int addDoctors(void);
static int removeDoctors(void);

//payment -> bappi
static void  paymentFlow(const char *pPhone, const char *pName,
                         const char *dID, const char *dName, const char *spec,
                         const char *dateStr, const char *timeStr);
static int   isAppointmentPaid(const char *pPhone, const char *dID,
                               const char *dateStr, const char *timeStr);
static void  payLaterMenu(const char *pPhone, const char *pName);
static void  viewPaymentHistory(const char *patientPhone);

// small CSV-safe writer for payments
static int writePaymentRecord(const char *timestamp,
                              const char *pPhone, const char *pName,
                              const char *dID, const char *dName, const char *spec,
                              const char *dateStr, const char *timeStr,
                              const char *method, const char *provider,
                              const char *receiver, const char *sender,
                              int amount, const char *status) {
    FILE *pf = fopen("payments.txt", "a");
    if (!pf) return 0;
    fprintf(pf, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%s\n",
            timestamp, pPhone, pName, dID, dName, spec,
            dateStr, timeStr, method, provider, receiver, sender, amount, status);
    fclose(pf);
    return 1;
}

//UI  DEFAULT PAGE
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
/* COLOR CODES
Red: \033[1;31m
Green: \033[1;32m
Yellow: \033[1;33m
Blue: \033[1;34m
Magenta: \033[1;35m
Cyan: \033[1;36m
White: \033[1;37m
*/
static void defaultPage() {
    printf("\033[1;36m");  // Bold + Cyan
printCentered("   ###     ######  ######## ##     ##    ###       ###   \n");
printCentered("  ## ##   ##    ##    ##    ##     ##   ## ##     ## ##  \n");
printCentered(" ##   ##  ##          ##    ##     ##  ##   ##   ##   ## \n");
printCentered("##     ##  ######     ##    ######### ##     ## ##     ##\n");
printCentered("#########       ##    ##    ##     ## ######### #########\n");
printCentered("##     ## ##    ##    ##    ##     ## ##     ## ##     ##\n");
printCentered("##     ##  ######     ##    ##     ## ##     ## ##     ##\n");

    printf("\033[0m"); // Reset color
    printf("\n");
    printf("\033[1;32m");
    printCentered("Your Wellbeing, Our Commitment\n");
    printCentered("Trust in care, Trust in ASTHAA\n\n");
    printf("\033[0m"); // Reset color
    printf("\n");
    printf("\033[1;33m");
    printf("Menu Options:\n");
    printf("\033[0m"); // Reset color
    printf("1. Registration (For Patients Only)\n");
    printf("2. Login (As Patient, Doctor, Admin)\n");
    printf("3. Emergency Contacts\n");
    printf("4. About Us\n");
    printf("5. Exit\n");
    printf("\n");
    printf("Enter any option (1-5) to continue: ");
}

// emergency contacts (simple)
static void emergencyContacts(void) {
    clearScreen();
    printf("\nEmergency Contacts:\n");
    printf("1. Ambulance: 999\n");
    printf("2. Fire Service: 101\n");
    printf("3. Police: 100\n");
    printf("4. Poison Control Center: 106\n");
    printf("5. Local Hospital: 16263\n");
    printf("\nPress Enter to return...");
    clearInputBuffer();
}

// ========== PATIENT: REGISTER ==========
static void registerPatient(void) {
    FILE *fp = fopen("patients.txt", "a");
    if (!fp) {
        printf("Error: Opening patient database failed.\n");
        return;
    }

    clearScreen();
    printf("\nPatient Registration\n");

    char name[100], email[100], phone[20], password[30];
    int age = 0; float weight = 0;

    // Name
    printf("Full Name: ");
    clearInputBuffer();
    if (!fgets(name, sizeof(name), stdin)) { fclose(fp); return; }
    trim(name);
    if (strlen(name) == 0) { printf("Name required.\n"); fclose(fp); return; }
    replaceCommas(name);

    // Age
    while (1) {
        char buf[32];
        printf("Age (0-120): ");
        if (!fgets(buf, sizeof(buf), stdin)) { fclose(fp); return; }
        if (sscanf(buf, "%d", &age) == 1 && age >= 0 && age <= 120) break;
        printf("Invalid age.\n");
    }

    // Weight
    while (1) {
        char buf[32];
        printf("Weight (kg 0-150): ");
        if (!fgets(buf, sizeof(buf), stdin)) { fclose(fp); return; }
        if (sscanf(buf, "%f", &weight) == 1 && weight >= 0 && weight <= 150) break;
        printf("Invalid weight.\n");
    }

    // Phone
    while (1) {
        printf("Phone (01XXXXXXXXX): ");
        if (!fgets(phone, sizeof(phone), stdin)) { fclose(fp); return; }
        trim(phone);
        if (isValidBangladeshiPhone(phone)) break;
    }

    // Email
    while (1) {
        printf("Email: ");
        if (!fgets(email, sizeof(email), stdin)) { fclose(fp); return; }
        trim(email);
        if (isValidEmail(email)) break;
        printf("Invalid email.\n");
    }
    replaceCommas(email);

    // Password
    printf("\nPassword needs 8+ chars with upper, lower, digit, special.\n");
    while (1) {
        printf("Set Password: ");
        inputPassword(password, sizeof(password));
        if (validatePasswordWithFeedback(password)) break;
        printf("Try again.\n");
    }

    // Save
    fprintf(fp, "%s,%s,%s,%d,%s,%.2f\n", phone, password, name, age, email, weight);
    fclose(fp);

    printf("\nRegistration Successful.\n");
    printf("(Username is your phone number.)\n");

    // Simple next steps menu
    while (1) {
        char buf[16];
        printf("\n1. Show password\n2. Login now\n3. Back to main\nChoose: ");
        if (!fgets(buf, sizeof(buf), stdin)) break;
        int op = atoi(buf);
        if (op == 1) {
            printf("Your password: %s\n", password);
            printf("Keep it secret.\n");
        } else if (op == 2) {
            loginOption();
            return;
        } else if (op == 3) {
            return;
        } else {
            printf("Invalid.\n");
        }
    }
}

// ========== PATIENT: LOGIN ==========
static int loginPatient(void) {
    char phone[20], password[30];

    clearScreen();
    printf("Patient Login\n");
    printf("Phone: ");
    scanf("%19s", phone);
    clearInputBuffer();

    printf("Password: ");
    inputPassword(password, sizeof(password));

    FILE *fp = fopen("patients.txt", "r");
    if (!fp) { printf("Unable to open patients.txt\n"); return 0; }

    char fPhone[20], fPassword[30], name[100], email[100];
    int age=0; float weight=0;
    int found = 0;

    while (fscanf(fp, "%19[^,],%29[^,],%99[^,],%d,%99[^,],%f\n",
                  fPhone, fPassword, name, &age, email, &weight) == 6) {
        if (strcmp(fPhone, phone) == 0 && strcmp(fPassword, password) == 0) {
            found = 1; break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Invalid phone or password.\n");
        printf("Press Enter..."); clearInputBuffer();
        return 0;
    }

    printf("\nWelcome, %s!\n", name);
    patientDashboard(name, phone);
    return 1;
}

// ========== DOCTOR: LOGIN ==========
static int loginDoctor(void) {
    char phone[20], password[30];

    clearScreen();
    printf("Doctor Login\n");
    printf("Phone: ");
    scanf("%19s", phone);
    clearInputBuffer();

    printf("Password: ");
    inputPassword(password, sizeof(password));

    FILE *fp = fopen("doctors.txt", "r");
    if (!fp) { printf("Unable to open doctors.txt\n"); return 0; }

    char fPhone[20], fPassword[30], name[100], email[100], spec[100];
    int age=0; float weight=0;
    int found = 0;

    while (fscanf(fp, "%19[^,],%29[^,],%99[^,],%d,%99[^,],%f,%99[^\n]\n",
                  fPhone, fPassword, name, &age, email, &weight, spec) >= 6) {
        if (strcmp(fPhone, phone) == 0 && strcmp(fPassword, password) == 0) {
            found = 1; break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Invalid phone or password.\n");
        printf("Press Enter..."); clearInputBuffer();
        return 0;
    }

    printf("\nWelcome, Dr. %s!\n", name);
    doctorDashboard(name, phone);
    return 1;
}

// ========== ADMIN: LOGIN ==========
int loginAdmin(void) {
    char phone[20], password[30];

    printf("Admin Login Form:\n");
    printf("Phone Number: ");
    if (scanf("%19s", phone) != 1) return 0;

    printf("Password: ");
    inputPassword(password, sizeof(password)); // masked
    clearInputBuffer(); // clean leftover newline

    FILE *fp = fopen("admins.txt", "r");   // <-- make sure the file is named admins.txt
    if (!fp) {
        printf("Unable to open admins.txt to read.\n");
        return 0;
    }

    char line[512];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        // skip blank lines or a CSV header row
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') continue;
        if (strncasecmp(line, "phone", 5) == 0) continue;

        // support both 6-field and optional 7th specialization field
        char fPhone[21] = "", fPass[31] = "", name[101] = "", email[101] = "", spec[128] = "";
        int  age = 0;
        float weight = 0.0f;

        // Try to read 7 fields; if only 6 exist it still passes with got >= 6
        int got = sscanf(line, "%20[^,],%30[^,],%100[^,],%d,%100[^,],%f,%127[^\n]",
                         fPhone, fPass, name, &age, email, &weight, spec);

        if (got >= 6) {
            // trim trailing spaces/CR/LF on phone/password read from file
            for (char *p = fPhone; *p; ++p) if (*p == '\r' || *p == '\n') *p = '\0';
            for (char *p = fPass;  *p; ++p) if (*p == '\r' || *p == '\n') *p = '\0';

            if (strcmp(fPhone, phone) == 0 && strcmp(fPass, password) == 0) {
                found = 1;
                // success
                printf("\nLogin successful! Welcome, Admin %s!\n", name[0] ? name : fPhone);
                fclose(fp);
                adminDashboard(name[0] ? name : fPhone, fPhone);
                return 1;
            }
        }
        // else malformed line; just skip it
    }

    fclose(fp);
    printf("\nInvalid phone or password. Try again.\n");
    return 0;
}

// ========== LOGIN OPTION (ROLE PICKER) ==========
static void loginOption(void) {
    clearScreen();
    printf("Login Menu\n");
    printf("1. Patient\n2. Doctor\n3. Admin\n4. Back\nChoose: ");
    int op=0;
    if (scanf("%d", &op) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();
    if (op == 1) loginPatient();
    else if (op == 2) loginDoctor();
    else if (op == 3) loginAdmin();
    else return;
}

// ========== APPOINTMENT BOOKING ==========
static void buildUniqueTimeSlots(char timeSlots[][10], int *outCount) {
    int num = randomInRange(3, 5);
    int hourOptions[] = {9,10,11,12,13,14,15,16,17};
    int used[9]={0}, made=0;
    while (made < num) {
        int idx = randomInRange(0,8);
        if (!used[idx]) { used[idx]=1; snprintf(timeSlots[made],10,"%02d:00", hourOptions[idx]); made++; }
    }
    *outCount = num;
}

bool appointmentForm(const char *patientPhone) {

    clearScreen();

    // ---- load patient basic info from patients.txt ----
    FILE *pfp = fopen("patients.txt", "r");
    if (!pfp) {
        printf("Error: Could not open patients database\n");
        printf("Press any key to continue..."); getch();
        return false;
    }

    char pName[100] = "", pEmail[100] = "", pPassword[30] = "";
    int  pAge = 0;
    float pWeight = 0.0f;

    char line[512];
    int patientFound = 0;
    while (fgets(line, sizeof(line), pfp)) {
        // phone,password,name,age,email,weight
        char fPhone[20], fPass[30], fName[100], fEmail[100];
        int  fAge; float fWeight;
        int got = sscanf(line, "%19[^,],%29[^,],%99[^,],%d,%99[^,],%f",
                         fPhone, fPass, fName, &fAge, fEmail, &fWeight);
        if (got == 6 && strcmp(fPhone, patientPhone) == 0) {
            strncpy(pName, fName, sizeof(pName)-1);
            strncpy(pEmail, fEmail, sizeof(pEmail)-1);
            strncpy(pPassword, fPass, sizeof(pPassword)-1);
            pAge = fAge; pWeight = fWeight;
            patientFound = 1;
            break;
        }
    }
    fclose(pfp);

    if (!patientFound) {
        printf("Error: Patient record not found\n");
        printf("Press any key to continue..."); getch();
        return false;
    }

    // ---- precompute 5 random dates within 30 days ----
    time_t now = time(NULL);
    struct tm base = *localtime(&now);
    struct tm avail[5];
    for (int i = 0; i < 5; i++) {
        avail[i] = base;
        avail[i].tm_mday += randomInRange(1, 30);
        mktime(&avail[i]); // normalize
    }

    // ---- collect medical info (all with fgets) ----
    char buf[256];
    float height = 0.0f;
    char blood[10] = "";
    char problem[300] = "";

    printf("\nAPPOINTMENT BOOKING\n");
    printf("Type 'back' anytime to cancel\n\n");
    printf("Patient: %s (Age: %d, Weight: %.2f kg)\n\n", pName, pAge, pWeight);

    // Height
    while (1) {
        printf("Height (in meters, e.g. 1.72): ");
        if (!read_line(buf, sizeof(buf))) return false;
        if (is_back(buf)) return false;
        if (sscanf(buf, "%f", &height) != 1) {
            printf("Invalid height. Try again.\n");
            continue;
        }
        if (height < 0.5f || height > 2.5f) {
            printf("Please enter between 0.5 and 2.5 meters.\n");
            continue;
        }
        break;
    }

    // Blood group
    while (1) {
        printf("Blood Group (A+, A-, B+, B-, AB+, AB-, O+, O-): ");
        if (!read_line(blood, sizeof(blood))) return false;
        if (is_back(blood)) return false;
        if (strlen(blood) == 0) {
            printf("Blood group cannot be empty.\n");
            continue;
        }
        break;
    }

    // Problem
    while (1) {
        printf("Briefly describe your health issue: ");
        if (!read_line(problem, sizeof(problem))) return false;
        if (is_back(problem)) return false;
        if (strlen(problem) == 0) {
            printf("Please enter a short description.\n");
            continue;
        }
        break;
    }

    float bmi = pWeight / (height * height);

    // ---- load doctors ----
    FILE *df = fopen("doctors.txt", "r");
    if (!df) {
        printf("Error: Could not open doctors database\n");
        printf("Press any key to continue..."); getch();
        return false;
    }

    // arrays to list doctors to user
    char dIDs[50][20], dNames[50][100], dSpecs[50][100];
    int dCount = 0;

    printf("\nAvailable Doctors:\n");
    while (fgets(line, sizeof(line), df)) {
        // phone,password,name,age,email,weight,specialization
        char dPhone[20], dPass[30], dName[100], dEmail[100], dSpec[100];
        int dAge; float dWeight;
        int got = sscanf(line, "%19[^,],%29[^,],%99[^,],%d,%99[^,],%f,%99[^\n]",
                         dPhone, dPass, dName, &dAge, dEmail, &dWeight, dSpec);
        if (got == 7) {
            printf("ID: %s | Dr. %s | %s\n", dPhone, dName, dSpec);
            if (dCount < 50) {
                strncpy(dIDs[dCount], dPhone, sizeof(dIDs[dCount])-1);
                strncpy(dNames[dCount], dName,  sizeof(dNames[dCount])-1);
                strncpy(dSpecs[dCount], dSpec,  sizeof(dSpecs[dCount])-1);
                dCount++;
            }
        }
    }
    fclose(df);

    if (dCount == 0) {
        printf("\nNo doctors available right now.\n");
        printf("Press any key to continue..."); getch();
        return false;
    }

    // ---- choose doctor by ID ----
    char chosenDocID[32];
    int docIndex = -1;
    while (1) {
        printf("\nEnter Doctor ID to book (or 'back'): ");
        if (!read_line(chosenDocID, sizeof(chosenDocID))) return false;
        if (is_back(chosenDocID)) return false;

        // find index
        docIndex = -1;
        for (int i = 0; i < dCount; i++) {
            if (strcmp(chosenDocID, dIDs[i]) == 0) { docIndex = i; break; }
        }
        if (docIndex == -1) {
            printf("Invalid Doctor ID. Try again.\n");
            continue;
        }
        break;
    }

    // ---- pick date ----
    printf("\nAvailable Dates:\n");
    for (int i = 0; i < 5; i++) {
        printf("%d) %02d-%02d-%d\n", i+1, avail[i].tm_mday, avail[i].tm_mon+1, avail[i].tm_year+1900);
    }

    int dateChoice = 0;
    while (1) {
        printf("Choose date (1-5) or 'back': ");
        if (!read_line(buf, sizeof(buf))) return false;
        if (is_back(buf)) return false;
        dateChoice = atoi(buf);
        if (dateChoice < 1 || dateChoice > 5) {
            printf("Invalid choice. Try 1-5.\n");
            continue;
        }
        break;
    }
    struct tm chosenDate = avail[dateChoice - 1];

    // ---- pick time ----
    char timeSlots[5][10];
    int slotCount = build_time_slots(timeSlots, 5);

    printf("\nAvailable Time Slots:\n");
    for (int i = 0; i < slotCount; i++) {
        printf("%d) %s\n", i+1, timeSlots[i]);
    }

    int timeChoice = 0;
    while (1) {
        printf("Choose time (1-%d) or 'back': ", slotCount);
        if (!read_line(buf, sizeof(buf))) return false;
        if (is_back(buf)) return false;
        timeChoice = atoi(buf);
        if (timeChoice < 1 || timeChoice > slotCount) {
            printf("Invalid choice.\n");
            continue;
        }
        break;
    }

    // ---- summary ----
    char dateStr[16];
    snprintf(dateStr, sizeof(dateStr), "%02d-%02d-%d",
             chosenDate.tm_mday, chosenDate.tm_mon + 1, chosenDate.tm_year + 1900);

    clearScreen();
    printf("=== APPOINTMENT SUMMARY ===\n");
    printf("Patient: %s\n", pName);
    printf("Age: %d | Height: %.2f m | Weight: %.2f kg | BMI: %.2f\n", pAge, height, pWeight, bmi);
    printf("Blood Group: %s\n", blood);
    printf("Issue: %s\n", problem);
    printf("Doctor: Dr. %s (%s)\n", dNames[docIndex], dSpecs[docIndex]);
    printf("Date: %s | Time: %s\n", dateStr, timeSlots[timeChoice-1]);

    // ---- confirm ----
    while (1) {
        printf("\nConfirm booking? (y/n): ");
        if (!read_line(buf, sizeof(buf))) return false;
        if (buf[0] == 'y' || buf[0] == 'Y') break;
        if (buf[0] == 'n' || buf[0] == 'N') {
            printf("Appointment cancelled.\n");
            printf("Press any key to continue..."); getch();
            return false;
        }
        printf("Please type y or n.\n");
    }

    // ---- write to appointments.txt ----
    FILE *afp = fopen("appointments.txt", "a");
    if (!afp) {
        printf("Error: Could not save appointment\n");
        printf("Press any key to continue..."); getch();
        return false;
    }
    fprintf(afp, "%s,%s,%d,%.2f,%.2f,%s,%.2f,%s,%s,%s,%s,%s,%s\n",
            patientPhone, pName, pAge, height, pWeight, blood, bmi,
            problem, dIDs[docIndex], dNames[docIndex], dSpecs[docIndex],
            dateStr, timeSlots[timeChoice-1]);
    fclose(afp);

    printf("\nAppointment successfully booked!\n");

    // If you have a payment flow, call it here (optional):
    // paymentFlow(patientPhone, pName, dIDs[docIndex], dNames[docIndex], dSpecs[docIndex], dateStr, timeSlots[timeChoice-1]);

    printf("Press any key to continue..."); getch();
    return true;
}


// ========== VIEW APPOINTMENTS (PATIENT) ==========
static void viewAppointments(const char *patientPhone) {
    FILE *fp = fopen("appointments.txt", "r");
    if (!fp) { printf("Error: appointments.txt\n"); return; }

    clearScreen();
    printf("YOUR APPOINTMENTS\n\n");

    char line[1024]; int found=0; int n=0;

    while (fgets(line, sizeof(line), fp)) {
        char pPhone[20], pName[100], blood[10], problem[300];
        int age=0; float h=0, w=0, bmi=0;
        char dID[20], dName[100], spec[100], date[20], time[20];

        int ok = sscanf(line,
            "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
            pPhone, pName, &age, &h, &w, blood, &bmi, problem,
            dID, dName, spec, date, time);

        if (ok < 13) continue;

        trim(pPhone); if (strcmp(pPhone, patientPhone) != 0) continue;
        found=1; n++;

        trim(pName); trim(blood); trim(problem); trim(dName); trim(spec); trim(date); trim(time);
        printf("Appointment #%d\n", n);
        printf("Doctor: Dr. %s (%s)\n", dName, spec);
        printf("Date: %s  Time: %s\n", date, time);
        printf("Reason: %s\n", problem);
        printf("-----------------------------\n");
    }
    fclose(fp);

    if (!found) printf("No appointments found.\n");

    printf("\nPress Enter to return...");
    clearInputBuffer();
}

// ========== CANCEL APPOINTMENT (REQUEST ONLY) ==========
static int hasPendingCancelRequest(const char *pPhone, const char *dID, const char *date, const char *time) {
    FILE *fp = fopen("CancelAppointment.txt", "r");
    if (!fp) return 0;
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char _pp[32], _pn[128], _dID[32], _dn[128], _date[32], _time[32], _reason[400], _ts[64], _status[32];
        int ok = sscanf(line, "%31[^,],%127[^,],%31[^,],%127[^,],%31[^,],%31[^,],%399[^,],%63[^,],%31[^\n]",
                        _pp, _pn, _dID, _dn, _date, _time, _reason, _ts, _status);
        if (ok >= 9) {
            trim(_pp); trim(_dID); trim(_date); trim(_time); trim(_status);
            if (strcmp(_status,"PENDING")==0 &&
                strcmp(_pp,pPhone)==0 && strcmp(_dID,dID)==0 &&
                strcmp(_date,date)==0 && strcmp(_time,time)==0) {
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);
    return 0;
}

static void requestCancelAppointment(const char *patientPhone) {
    FILE *fp = fopen("appointments.txt", "r");
    if (!fp) { printf("Error: appointments.txt\n"); return; }

    // load user's appointments
    char lines[120][1024];
    int idxs[120]; int used=0; int total=0;
    char line[1024];
    while (used<120 && fgets(line, sizeof(line), fp)) {
        strcpy(lines[used], line);
        char pPhone[20];
        if (sscanf(line, "%19[^,]", pPhone) == 1 && strcmp(pPhone, patientPhone)==0) {
            idxs[total++] = used;
        }
        used++;
    }
    fclose(fp);

    clearScreen();
    if (total==0) { printf("You have no appointments to request cancel.\n"); printf("Press Enter..."); clearInputBuffer(); return; }

    printf("YOUR APPOINTMENTS (Request Cancel)\n");
    printf("%-4s %-10s %-20s %-10s %-6s %-24s\n","#","DocID","Doctor","Date","Time","Reason");
    printf("-----------------------------------------------------------------------\n");

    for (int i=0;i<total;i++) {
        int idx = idxs[i];
        char pPhone[20], pName[100], blood[10], problem[300];
        int age=0; float h=0, w=0, bmi=0;
        char dID[20], dName[100], spec[100], date[20], time[20];

        int ok = sscanf(lines[idx],
            "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
            pPhone, pName, &age, &h, &w, blood, &bmi, problem,
            dID, dName, spec, date, time);
        if (ok < 13) continue;

        trim(dID); trim(dName); trim(date); trim(time); trim(problem);
        printf("%-4d %-10s %-20s %-10s %-6s %-24s\n", i+1, dID, dName, date, time, problem);
    }

    printf("\nPick number to request cancel (0 to back): ");
    int pick=0; if (scanf("%d",&pick)!=1){ clearInputBuffer(); return; }
    clearInputBuffer();
    if (pick<=0 || pick>total) { printf("Cancelled.\n"); return; }

    // parse chosen appointment
    char pPhone[20], pName[100], blood[10], problem[300];
    int age=0; float h=0, w=0, bmi=0;
    char dID[20], dName[100], spec[100], date[20], timeStr[20];

    if (sscanf(lines[idxs[pick-1]],
            "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
            pPhone, pName, &age, &h, &w, blood, &bmi, problem, dID, dName, spec, date, timeStr) < 13) {
        printf("Read error.\n"); return;
    }
    trim(pName); trim(dID); trim(dName); trim(spec); trim(date); trim(timeStr);

    // already pending?
    if (hasPendingCancelRequest(patientPhone, dID, date, timeStr)) {
        printf("A pending request for this appointment already exists.\n");
        printf("Press Enter..."); clearInputBuffer(); return;
    }

    // reason (optional)
    char reason[400];
    printf("Reason (optional, Enter to skip): ");
    if (!fgets(reason, sizeof(reason), stdin)) reason[0] = '\0';
    trim(reason);
    replaceCommas(reason);

    printf("\nSend request? (y/n): ");
    char c = getchar(); clearInputBuffer();
    if (tolower((unsigned char)c) != 'y') { printf("Cancelled.\n"); return; }

    char ts[64]; nowTimestamp(ts, sizeof(ts));
    FILE *rf = fopen("CancelAppointment.txt", "a");
    if (!rf) { printf("Error opening CancelAppointment.txt\n"); return; }
    fprintf(rf, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            pPhone, pName, dID, dName, date, timeStr,
            (strlen(reason)?reason:"N/A"), ts, "PENDING");
    fclose(rf);

    printf("Request sent. Status: PENDING.\n");
    printf("Press Enter..."); clearInputBuffer();
}

// ========== PRESCRIPTIONS (PATIENT VIEW) ==========
static void viewPrescribedMedicines(const char *patientPhone) {
    clearScreen();
    printf("YOUR PRESCRIPTIONS\n\n");

    FILE *fp = fopen("prescriptions.txt", "r");
    if (!fp) { printf("No prescriptions yet.\n"); printf("Press Enter..."); clearInputBuffer(); return; }

    // get name
    char patientName[100] = "Unknown";
    FILE *pf = fopen("patients.txt", "r");
    if (pf) {
        char ph[20], pw[30], nm[100], em[100]; int ag=0; float w=0;
        while (fscanf(pf, "%19[^,],%29[^,],%99[^,],%d,%99[^,],%f\n", ph, pw, nm, &ag, em, &w) == 6) {
            if (strcmp(ph, patientPhone)==0) { strncpy(patientName, nm, sizeof(patientName)-1); break; }
        }
        fclose(pf);
    }

    printf("Patient: %s (%s)\n\n", patientName, patientPhone);
    printf("%-4s %-12s %-12s %-24s %-32s\n", "#", "Date", "DoctorID", "Medications", "Instructions");
    printf("--------------------------------------------------------------------------\n");

    char line[1024]; int count=0, any=0;

    // first pass: summary list
    while (fgets(line, sizeof(line), fp)) {
        char dPhone[20], pPhone[20], date[20], meds[500], dosage[200], instr[500];
        int ok = sscanf(line, "%19[^,],%19[^,],%19[^,],%499[^,],%199[^,],%499[^\n]",
                        dPhone, pPhone, date, meds, dosage, instr);
        if (ok != 6) continue;
        trim(pPhone); if (strcmp(pPhone, patientPhone)!=0) continue;
        trim(dPhone); trim(date); trim(meds); trim(instr);

        any=1; count++;

        // shorten for table
        char sM[25]={0}, sI[33]={0};
        strncpy(sM, meds, 24); sM[24]='\0';
        strncpy(sI, instr, 32); sI[32]='\0';
        printf("%-4d %-12s %-12s %-24s %-32s\n", count, date, dPhone, sM, sI);
    }
    fclose(fp);

    if (!any) {
        printf("No prescriptions found.\n");
        printf("Press Enter..."); clearInputBuffer(); return;
    }

    // detail view
    printf("\nEnter prescription number for details (0 to back): ");
    int pick=0; if (scanf("%d",&pick)!=1){ clearInputBuffer(); return; }
    clearInputBuffer();
    if (pick<=0 || pick>count) { return; }

    // second pass to print that one
    fp = fopen("prescriptions.txt", "r");
    if (!fp) return;
    int current=0;
    while (fgets(line, sizeof(line), fp)) {
        char dPhone[20], pPhone[20], date[20], meds[500], dosage[200], instr[500];
        int ok = sscanf(line, "%19[^,],%19[^,],%19[^,],%499[^,],%199[^,],%499[^\n]",
                        dPhone, pPhone, date, meds, dosage, instr);
        if (ok==6 && strcmp(pPhone, patientPhone)==0) {
            current++;
            if (current==pick) {
                trim(dPhone); trim(date); trim(meds); trim(dosage); trim(instr);
                clearScreen();
                printf("PRESCRIPTION DETAILS\n\n");
                printf("Patient : %s (%s)\n", patientName, patientPhone);
                printf("Date    : %s\n", date);
                printf("DoctorID: %s\n\n", dPhone);
                printf("Medications:\n%s\n\n", meds);
                printf("Dosage:\n%s\n\n", dosage);
                printf("Instructions:\n%s\n", instr);
                break;
            }
        }
    }
    fclose(fp);

    printf("\nPress Enter to return...");
    clearInputBuffer();
}

// ========== PATIENT DASHBOARD ==========
static void patientLogout(const char *patientPhone) {
    (void)patientPhone;
    printf("Logged out.\n");
}

static void patientDashboard(char name[], char phone[]) {
    (void)name; // not used everywhere, but kept for clarity
    char input[16];

    while (1) {
        clearScreen();
        printf("PATIENT DASHBOARD\n\n");
        printf("1. Book Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Request Cancel Appointment\n");
        printf("4. View Prescribed Medicines\n");
        printf("5. Payments\n");
        printf("6. Logout\n");
        printf("\nChoose (1-6): ");

        if (!fgets(input, sizeof(input), stdin)) continue;
        int op = atoi(input);

        if (op == 1) {
            appointmentForm(phone);
        } else if (op == 2) {
            viewAppointments(phone);
        } else if (op == 3) {
            requestCancelAppointment(phone);
        } else if (op == 4) {
            viewPrescribedMedicines(phone);
        } else if (op == 5) {
            // small payment hub
            while (1) {
                clearScreen();
                printf("PAYMENTS\n");
                printf("1. Pay for an appointment (UNPAID)\n");
                printf("2. View my payment history\n");
                printf("3. Back\n");
                printf("Choose: ");
                if (!fgets(input, sizeof(input), stdin)) break;
                if (input[0]=='1') {
                    payLaterMenu(phone, name);
                } else if (input[0]=='2') {
                    viewPaymentHistory(phone);
                } else if (input[0]=='3') {
                    break;
                } else {
                    printf("Invalid.\n");
                }
            }
        } else if (op == 6) {
            patientLogout(phone);
            return;
        } else {
            printf("Invalid.\n");
            printf("Press Enter..."); clearInputBuffer();
        }
    }
}

// ========== DOCTOR DASHBOARD & FUNCTIONS ==========
static int viewDoctorAppointments(const char *doctorPhone) {
    clearScreen();
    printf("Your Scheduled Appointments\n\n");

    FILE *fp = fopen("appointments.txt", "r");
    if (!fp) { printf("No appointments found.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    printf("%-4s %-18s %-10s %-6s %-26s %-14s\n",
           "#", "Patient", "Date", "Time", "Reason", "Specialization");
    printf("-------------------------------------------------------------------------------\n");

    char line[1024]; int n=0, any=0;
    while (fgets(line, sizeof(line), fp)) {
        char pPhone[20], pName[100], blood[10], problem[300];
        int age=0; float h=0,w=0,bmi=0;
        char dID[20], dName[100], spec[100], date[20], time[20];

        int ok = sscanf(line,
            "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
            pPhone, pName, &age, &h, &w, blood, &bmi, problem,
            dID, dName, spec, date, time);
        if (ok < 13) continue;

        trim(dID); if (strcmp(dID, doctorPhone)!=0) continue;
        any=1; n++;

        trim(pName); trim(problem); trim(spec); trim(date); trim(time);
        printf("%-4d %-18s %-10s %-6s %-26s %-14s\n",
               n, pName, date, time, problem, spec);
    }
    fclose(fp);

    if (!any) printf("You have no scheduled appointments.\n");

    printf("\nPress Enter to return...");
    clearInputBuffer();
    return 1;
}

static int viewPatientDetails(const char *doctorPhone) {
    clearScreen();
    printf("Your Patients\n\n");

    // collect unique patients from appointments
    FILE *ap = fopen("appointments.txt", "r");
    if (!ap) { printf("No appointments found.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    char phones[200][20], names[200][100];
    int used=0;
    char line[1024];

    while (fgets(line, sizeof(line), ap)) {
        char pPhone[20], pName[100], dID[20];
        int ok = sscanf(line, "%19[^,],%99[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%19[^,]",
                        pPhone, pName, dID);
        if (ok >= 3 && strcmp(dID, doctorPhone)==0) {
            int exists=0;
            for (int i=0;i<used;i++) if (strcmp(phones[i], pPhone)==0) { exists=1; break; }
            if (!exists && used<200) { strcpy(phones[used], pPhone); strcpy(names[used], pName); used++; }
        }
    }
    fclose(ap);

    if (used==0) { printf("You have no patients.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    for (int i=0;i<used;i++) { trim(names[i]); }
    printf("%-4s %-13s %-20s\n", "#", "Phone", "Name");
    printf("-------------------------------\n");
    for (int i=0;i<used;i++) printf("%-4d %-13s %-20s\n", i+1, phones[i], names[i]);

    printf("\nPick a patient (1-%d): ", used);
    int pick=0; if (scanf("%d",&pick)!=1 || pick<1 || pick>used){ clearInputBuffer(); printf("Invalid.\n"); return 0; }
    clearInputBuffer();

    // show details from patients.txt
    FILE *pf = fopen("patients.txt", "r");
    if (!pf) { printf("Error: patients.txt\n"); return 0; }

    int shown=0;
    while (fgets(line, sizeof(line), pf)) {
        char pPhone[20], pPass[30], pName[100], email[100];
        int age=0; float weight=0;
        int ok = sscanf(line, "%19[^,],%29[^,],%99[^,],%d,%99[^,],%f",
                        pPhone, pPass, pName, &age, email, &weight);
        if (ok==6 && strcmp(pPhone, phones[pick-1])==0) {
            trim(pName); trim(email);
            clearScreen();
            printf("Patient Medical Record\n\n");
            printf("Name : %s\n", pName);
            printf("Phone: %s\n", pPhone);
            printf("Age  : %d\n", age);
            printf("Weight: %.1f kg\n", weight);
            printf("Email: %s\n", email);
            shown=1;
            break;
        }
    }
    fclose(pf);

    if (!shown) printf("Details not found.\n");

    printf("\nPress Enter to return...");
    clearInputBuffer();
    return 1;
}

static int writePrescription(const char *doctorPhone) {
    clearScreen();
    printf("Your Appointments (to pick patient)\n\n");

    FILE *ap = fopen("appointments.txt", "r");
    if (!ap) { printf("No appointments.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    char pPhones[200][20], pNames[200][100], apDate[200][20], apTime[200][20];
    int used=0;
    char line[1024];

    printf("%-4s %-13s %-18s %-10s %-6s\n","#","Phone","Name","Date","Time");
    printf("------------------------------------------------------\n");
    while (fgets(line, sizeof(line), ap)) {
        char pPhone[20], pName[100], dID[20], date[20], time[20];
        int ok = sscanf(line, "%19[^,],%99[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%19[^,],%*[^,],%*[^,],%19[^,],%19[^\n]",
                        pPhone, pName, dID, date, time);
        if (ok>=5 && strcmp(dID, doctorPhone)==0 && used<200) {
            strcpy(pPhones[used], pPhone);
            strcpy(pNames[used], pName);
            strcpy(apDate[used], date);
            strcpy(apTime[used], time);
            trim(pNames[used]); trim(apDate[used]); trim(apTime[used]);
            printf("%-4d %-13s %-18s %-10s %-6s\n", used+1, pPhones[used], pNames[used], apDate[used], apTime[used]);
            used++;
        }
    }
    fclose(ap);

    if (used==0) {
        printf("You have no appointments.\n");
        printf("Press Enter..."); clearInputBuffer();
        return 0;
    }

    printf("\nPick a patient (1-%d): ", used);
    int pick=0; if (scanf("%d",&pick)!=1 || pick<1 || pick>used){ clearInputBuffer(); printf("Invalid.\n"); return 0; }
    clearInputBuffer();

    char patientPhone[20]; strcpy(patientPhone, pPhones[pick-1]);

    // prescription fields
    char date[16], meds[500], dosage[200], instr[500];
    time_t now=time(NULL); struct tm *lt=localtime(&now);
    strftime(date, sizeof(date), "%d-%m-%Y", lt);

    printf("\nNew Prescription for %s\n", pNames[pick-1]);
    printf("Medications (comma separated): ");
    if (!fgets(meds, sizeof(meds), stdin)) return 0;
    trim(meds); replaceCommas(meds);

    printf("Dosage: ");
    if (!fgets(dosage, sizeof(dosage), stdin)) return 0;
    trim(dosage); replaceCommas(dosage);

    printf("Instructions: ");
    if (!fgets(instr, sizeof(instr), stdin)) return 0;
    trim(instr); replaceCommas(instr);

    FILE *pf = fopen("prescriptions.txt", "a");
    if (!pf) { printf("Error saving prescription.\n"); return 0; }
    fprintf(pf, "%s,%s,%s,%s,%s,%s\n", doctorPhone, patientPhone, date, meds, dosage, instr);
    fclose(pf);

    printf("\nPrescription saved.\n");
    printf("Press Enter to continue...");
    clearInputBuffer();
    return 1;
}

static void doctorDashboard(char name[], char phone[]) {
    (void)name;
    char buf[16];
    while (1) {
        clearScreen();
        printf("DOCTOR DASHBOARD\n\n");
        printf("1. View Appointments\n");
        printf("2. View Patient Details\n");
        printf("3. Write Prescription\n");
        printf("4. Logout\n");
        printf("\nChoose (1-4): ");

        if (!fgets(buf, sizeof(buf), stdin)) continue;
        int op = atoi(buf);

        if (op==1) viewDoctorAppointments(phone);
        else if (op==2) viewPatientDetails(phone);
        else if (op==3) writePrescription(phone);
        else if (op==4) return;
        else { printf("Invalid.\n"); printf("Press Enter..."); clearInputBuffer(); }
    }
}

// ========== PAYMENTS ==========
static void paymentFlow(const char *pPhone, const char *pName,
                        const char *dID, const char *dName, const char *spec,
                        const char *dateStr, const char *timeStr) {
    char input[64], ts[64];
    nowTimestamp(ts, sizeof(ts));

    while (1) {
        clearScreen();
        printf("Payment Modules\n");
        printf("1. Mobile Banking (bKash / Rocket / Nagad)\n");
        printf("2. Bank Payment\n");
        printf("3. Cancel (pay later)\n");
        printf("\nAppointment Fee: %d\n", APPOINTMENT_FEE);
        printf("Choose (1-3): ");

        if (!fgets(input, sizeof(input), stdin)) return;
        int opt = atoi(input);

        if (opt == 1) {
            while (1) {
                clearScreen();
                printf("Mobile Banking\n");
                printf("1. bKash  2. Rocket  3. Nagad  4. Back\n");
                printf("Receiver Number: %s\n", MFS_RECEIVER_NUMBER);
                printf("Choose: ");
                if (!fgets(input, sizeof(input), stdin)) return;
                int m = atoi(input);
                const char *provider = (m==1 ? "bKash" : m==2 ? "Rocket" : m==3 ? "Nagad" : NULL);
                if (!provider) break;

                char sender[32];
                while (1) {
                    printf("Sender Number (11 digits, starts 01): ");
                    if (!fgets(sender, sizeof(sender), stdin)) return;
                    trim(sender);
                    if (isValidBangladeshiPhone(sender)) break;
                }

                if (!writePaymentRecord(ts, pPhone, pName, dID, dName, spec,
                                        dateStr, timeStr, "MOBILE", provider,
                                        MFS_RECEIVER_NUMBER, sender,
                                        APPOINTMENT_FEE, "SUCCESS")) {
                    printf("Could not save payment.\n");
                    printf("Press Enter..."); clearInputBuffer();
                    return;
                }
                printf("Payment successful via %s.\n", provider);
                printf("Press Enter..."); clearInputBuffer();
                return;
            }
        } else if (opt == 2) {
            clearScreen();
            printf("Bank Payment\n");
            printf("Receiver Bank: %s\n", BANK_RECEIVER_NAME);
            printf("Receiver Acc : %s\n", BANK_RECEIVER_ACCOUNT);

            char bankName[128], senderAcc[64];

            printf("Your Bank Name: ");
            if (!fgets(bankName, sizeof(bankName), stdin)) return;
            trim(bankName); replaceCommas(bankName);
            if (strlen(bankName)==0) strcpy(bankName, "Unknown");

            while (1) {
                printf("Your Account No (digits only, 6-20): ");
                if (!fgets(senderAcc, sizeof(senderAcc), stdin)) return;
                trim(senderAcc);
                int ok=1, L=(int)strlen(senderAcc);
                if (L<6 || L>20) ok=0;
                for (int i=0;i<L;i++) if (!isdigit((unsigned char)senderAcc[i])) ok=0;
                if (ok) break;
                printf("Invalid account.\n");
            }

            if (!writePaymentRecord(ts, pPhone, pName, dID, dName, spec,
                                    dateStr, timeStr, "BANK", bankName,
                                    BANK_RECEIVER_ACCOUNT, senderAcc,
                                    APPOINTMENT_FEE, "SUCCESS")) {
                printf("Could not save payment.\n");
                printf("Press Enter..."); clearInputBuffer();
                return;
            }
            printf("Payment successful via Bank.\n");
            printf("Press Enter..."); clearInputBuffer();
            return;
        } else if (opt == 3) {
            printf("You can pay later from the dashboard.\n");
            printf("Press Enter..."); clearInputBuffer();
            return;
        } else {
            printf("Invalid.\n");
        }
    }
}

static int isAppointmentPaid(const char *pPhone, const char *dID,
                             const char *dateStr, const char *timeStr) {
    FILE *pf = fopen("payments.txt", "r");
    if (!pf) return 0;
    char line[1024];
    while (fgets(line, sizeof(line), pf)) {
        char ts[64], pp[32], pn[128], dd[32], dn[128], sp[128];
        char apDate[32], apTime[32], method[32], provider[64], receiver[64], sender[64], status[32];
        int amount=0;

        int ok = sscanf(line,
            "%63[^,],%31[^,],%127[^,],%31[^,],%127[^,],%127[^,],%31[^,],%31[^,],%31[^,],%63[^,],%63[^,],%63[^,],%d,%31[^\n]",
            ts, pp, pn, dd, dn, sp, apDate, apTime, method, provider, receiver, sender, &amount, status);
        if (ok==14) {
            trim(pp); trim(dd); trim(apDate); trim(apTime); trim(status);
            if (strcmp(pp,pPhone)==0 && strcmp(dd,dID)==0 &&
                strcmp(apDate,dateStr)==0 && strcmp(apTime,timeStr)==0 &&
                strcmp(status,"SUCCESS")==0) {
                fclose(pf);
                return 1;
            }
        }
    }
    fclose(pf);
    return 0;
}

static void payLaterMenu(const char *patientPhone, const char *patientName) {
    (void)patientName; // not necessary to print here
    // load patient appointments
    FILE *fp = fopen("appointments.txt", "r");
    if (!fp) { printf("No appointments.\n"); printf("Press Enter..."); clearInputBuffer(); return; }

    typedef struct {
        char dID[20], dName[100], spec[100], date[20], time[20];
        int paid;
    } Row;

    Row rows[200]; int n=0;
    char line[1024];

    while (n<200 && fgets(line,sizeof(line),fp)) {
        char pPhone[20], pName[100], blood[10], problem[300];
        int age=0; float h=0,w=0,bmi=0;
        char dID[20], dName[100], spec[100], date[20], timeStr[20];

        int ok = sscanf(line,
            "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
            pPhone, pName, &age, &h, &w, blood, &bmi, problem,
            dID, dName, spec, date, timeStr);
        if (ok>=13 && strcmp(pPhone,patientPhone)==0) {
            trim(dID); trim(dName); trim(spec); trim(date); trim(timeStr);
            strcpy(rows[n].dID, dID);
            strcpy(rows[n].dName, dName);
            strcpy(rows[n].spec, spec);
            strcpy(rows[n].date, date);
            strcpy(rows[n].time, timeStr);
            rows[n].paid = isAppointmentPaid(patientPhone, dID, date, timeStr);
            n++;
        }
    }
    fclose(fp);

    clearScreen();
    if (n==0) { printf("You have no appointments.\n"); printf("Press Enter..."); clearInputBuffer(); return; }

    printf("MY APPOINTMENTS & PAYMENTS (fee %d)\n\n", APPOINTMENT_FEE);
    printf("%-4s %-10s %-18s %-10s %-6s %-7s\n","#","DocID","Doctor","Date","Time","Status");
    printf("--------------------------------------------------------\n");
    for (int i=0;i<n;i++) {
        printf("%-4d %-10s %-18s %-10s %-6s %-7s\n",
               i+1, rows[i].dID, rows[i].dName, rows[i].date, rows[i].time, rows[i].paid?"PAID":"UNPAID");
    }

    // any unpaid?
    int unpaid=0; for (int i=0;i<n;i++) if (!rows[i].paid) unpaid=1;
    if (!unpaid) { printf("\nAll paid. Nice!\n"); printf("Press Enter..."); clearInputBuffer(); return; }

    while (1) {
        char buf[16];
        printf("\nPick number to PAY (0 back): ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        int pick = atoi(buf);
        if (pick==0) return;
        if (pick<1 || pick>n) { printf("Invalid.\n"); continue; }
        if (rows[pick-1].paid) { printf("Already paid.\n"); continue; }

        paymentFlow(patientPhone, (char*)patientName,
                    rows[pick-1].dID, rows[pick-1].dName, rows[pick-1].spec,
                    rows[pick-1].date, rows[pick-1].time);

        rows[pick-1].paid = isAppointmentPaid(patientPhone, rows[pick-1].dID, rows[pick-1].date, rows[pick-1].time);
        printf("Updated: #%d is now %s.\n", pick, rows[pick-1].paid?"PAID":"UNPAID");
        printf("Pay another? (y/n): ");
        if (!fgets(buf, sizeof(buf), stdin)) return;
        if (tolower((unsigned char)buf[0])!='y') return;

        // redraw simple table
        clearScreen();
        printf("MY APPOINTMENTS & PAYMENTS (fee %d)\n\n", APPOINTMENT_FEE);
        printf("%-4s %-10s %-18s %-10s %-6s %-7s\n","#","DocID","Doctor","Date","Time","Status");
        printf("--------------------------------------------------------\n");
        for (int i=0;i<n;i++) {
            printf("%-4d %-10s %-18s %-10s %-6s %-7s\n",
                   i+1, rows[i].dID, rows[i].dName, rows[i].date, rows[i].time, rows[i].paid?"PAID":"UNPAID");
        }
    }
}

static void viewPaymentHistory(const char *patientPhone) {
    FILE *pf = fopen("payments.txt", "r");
    if (!pf) { printf("No payments yet.\n"); printf("Press Enter..."); clearInputBuffer(); return; }

    clearScreen();
    printf("MY PAYMENT HISTORY\n\n");
    printf("%-4s %-16s %-10s %-18s %-10s %-6s %-8s\n",
           "#","Timestamp","DocID","Doctor","Date","Time","Status");
    printf("----------------------------------------------------------------------------\n");

    char line[1024]; int n=0, any=0;

    while (fgets(line, sizeof(line), pf)) {
        char ts[64], pPhone[32], pName[128], dID[32], dName[128], spec[128];
        char apptDate[32], apptTime[32], method[32], provider[64], receiver[64], sender[64], status[32];
        int amount=0;

        int ok = sscanf(line,
            "%63[^,],%31[^,],%127[^,],%31[^,],%127[^,],%127[^,],%31[^,],%31[^,],%31[^,],%63[^,],%63[^,],%63[^,],%d,%31[^\n]",
            ts, pPhone, pName, dID, dName, spec, apptDate, apptTime, method, provider, receiver, sender, &amount, status);
        if (ok==14 && strcmp(pPhone,patientPhone)==0) {
            trim(ts); trim(dID); trim(dName); trim(apptDate); trim(apptTime); trim(status);
            any=1; n++;
            printf("%-4d %-16s %-10s %-18s %-10s %-6s %-8s\n",
                   n, ts, dID, dName, apptDate, apptTime, status);
        }
    }
    fclose(pf);

    if (!any) printf("No payments found.\n");
    printf("\nPress Enter to return..."); clearInputBuffer();
}

// ========== ADMIN MODULES ==========
static int viewAllAppointments(void) {
    clearScreen();
    printf("ALL SCHEDULED APPOINTMENTS\n\n");

    FILE *fp = fopen("appointments.txt", "r");
    if (!fp) { printf("No appointments found.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    printf("%-4s %-13s %-18s %-8s %-8s %-5s %-6s %-22s %-8s %-12s %-10s %-5s\n",
           "#", "PatientPhone", "PatientName", "Height", "Weight", "BG", "BMI",
           "Reason", "DocID", "Doctor", "Spec", "Time");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    char line[1024]; int count=0;
    while (fgets(line, sizeof(line), fp)) {
        char pPhone[20], pName[100], blood[10], problem[300];
        int age=0; float h=0, w=0, bmi=0;
        char dID[20], dName[100], spec[100], date[20], time[20];

        int ok = sscanf(line,
            "%19[^,],%99[^,],%d,%f,%f,%9[^,],%f,%299[^,],%19[^,],%99[^,],%99[^,],%19[^,],%19[^\n]",
            pPhone, pName, &age, &h, &w, blood, &bmi, problem, dID, dName, spec, date, time);
        if (ok < 13) continue;

        trim(pPhone); trim(pName); trim(blood); trim(problem); trim(dID); trim(dName); trim(spec); trim(date); trim(time);
        printf("%-4d %-13s %-18s %-8.2f %-8.2f %-5s %-6.2f %-22s %-8s %-12s %-10s %-5s\n",
               ++count, pPhone, pName, h, w, blood, bmi, problem, dID, dName, spec, time);
    }
    fclose(fp);

    if (count==0) printf("No appointments found.\n");
    printf("\nPress Enter to return..."); clearInputBuffer();
    return 1;
}

static int viewAllPatients(void) {
    clearScreen();
    printf("ALL PATIENTS\n\n");

    FILE *fp = fopen("patients.txt", "r");
    if (!fp) { printf("No patient records.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    printf("%-4s %-13s %-20s %-5s %-22s %-7s\n",
           "#","Phone","Name","Age","Email","Weight");
    printf("--------------------------------------------------------------------------\n");

    char line[1024]; int count=0;
    while (fgets(line, sizeof(line), fp)) {
        char phone[20], pass[30], name[100], email[100];
        int age=0; float weight=0;
        int ok = sscanf(line, "%19[^,],%29[^,],%99[^,],%d,%99[^,],%f",
                        phone, pass, name, &age, email, &weight);
        if (ok!=6) continue;
        trim(phone); trim(name); trim(email);
        printf("%-4d %-13s %-20s %-5d %-22s %-7.1f\n",
               ++count, phone, name, age, email, weight);
    }
    fclose(fp);

    if (count==0) printf("No patients registered.\n");
    printf("\nPress Enter to return..."); clearInputBuffer();
    return 1;
}

static int editPatientRecord(void) {
    viewAllPatients();
    char target[20];
    printf("\nEnter patient PHONE to edit (or 'back'): ");
    if (scanf("%19s", target) != 1) { clearInputBuffer(); return 0; }
    clearInputBuffer();
    if (strcmp(target,"back")==0 || strcmp(target,"BACK")==0) return 0;

    FILE *in=fopen("patients.txt","r");
    if (!in){ printf("Error patients.txt\n"); return 0; }
    FILE *out=fopen("patients_tmp.txt","w");
    if (!out){ fclose(in); printf("Temp error\n"); return 0; }

    int found=0; char line[1024];
    while (fgets(line, sizeof(line), in)) {
        char phone[20], pass[30], name[100], email[100];
        int age=0; float weight=0;
        int ok = sscanf(line,"%19[^,],%29[^,],%99[^,],%d,%99[^,],%f",
                        phone, pass, name, &age, email, &weight);
        if (ok==6 && strcmp(phone,target)==0) {
            found=1;
            trim(name); trim(email);
            printf("\nEditing %s (%s)\n", name, phone);
            printf("Old Email : %s\n", email);
            printf("Old Weight: %.1f\n", weight);

            // new email
            char newEmail[100];
            while (1) {
                printf("New Email (blank = keep): ");
                if (!fgets(newEmail,sizeof(newEmail),stdin)) { strcpy(newEmail,email); break; }
                trim(newEmail);
                if (strlen(newEmail)==0) { strcpy(newEmail,email); break; }
                if (isValidEmail(newEmail)) break;
                printf("Invalid.\n");
            }
            // new weight
            char buf[64]; float newW=weight;
            while (1) {
                printf("New Weight kg (0-300, blank keep %.1f): ", weight);
                if (!fgets(buf,sizeof(buf),stdin)) { newW=weight; break; }
                trim(buf);
                if (strlen(buf)==0) { newW=weight; break; }
                if (sscanf(buf,"%f",&newW)==1 && newW>=0 && newW<=300) break;
                printf("Invalid.\n");
            }

            replaceCommas(name); replaceCommas(newEmail);
            fprintf(out,"%s,%s,%s,%d,%s,%.2f\n", phone, pass, name, age, newEmail, newW);
        } else {
            fputs(line,out);
        }
    }
    fclose(in); fclose(out);

    if (!found) { remove("patients_tmp.txt"); printf("Patient not found.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    remove("patients.txt");
    rename("patients_tmp.txt","patients.txt");
    printf("\nUpdated.\nPress Enter..."); clearInputBuffer();
    return 1;
}

static int deletePatients(void) {
    viewAllPatients();
    char target[20];
    printf("\nEnter patient PHONE to delete (or 'back'): ");
    if (scanf("%19s", target) != 1) { clearInputBuffer(); return 0; }
    clearInputBuffer();
    if (strcmp(target,"back")==0 || strcmp(target,"BACK")==0) return 0;

    printf("Confirm delete %s? (y/n): ", target);
    char c=getchar(); clearInputBuffer();
    if (tolower((unsigned char)c)!='y') { printf("Cancelled.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    FILE *in=fopen("patients.txt","r");
    if (!in){ printf("Error patients.txt\n"); return 0; }
    FILE *out=fopen("patients_tmp.txt","w");
    if (!out){ fclose(in); printf("Temp error\n"); return 0; }

    int removed=0; char line[1024], delName[100]="";
    while (fgets(line, sizeof(line), in)) {
        char phone[20], pass[30], name[100], email[100];
        int age=0; float weight=0;
        int ok = sscanf(line,"%19[^,],%29[^,],%99[^,],%d,%99[^,],%f", phone, pass, name, &age, email, &weight);
        if (ok==6 && strcmp(phone,target)==0) { removed=1; trim(name); strncpy(delName,name,sizeof(delName)-1); }
        else fputs(line,out);
    }
    fclose(in); fclose(out);
    if (!removed) { remove("patients_tmp.txt"); printf("Not found.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    remove("patients.txt");
    rename("patients_tmp.txt","patients.txt");

    // drop their appointments too
    FILE *ai=fopen("appointments.txt","r");
    if (ai) {
        FILE *ao=fopen("appointments_tmp.txt","w");
        if (ao) {
            while (fgets(line,sizeof(line),ai)) {
                char pPhone[20];
                if (sscanf(line,"%19[^,]",pPhone)==1 && strcmp(pPhone,target)==0) {
                    // skip
                } else fputs(line, ao);
            }
            fclose(ao);
            remove("appointments.txt");
            rename("appointments_tmp.txt","appointments.txt");
        }
        fclose(ai);
    }

    printf("Deleted: %s (%s)\n", delName, target);
    printf("Press Enter..."); clearInputBuffer();
    return 1;
}

static int addDoctors(void) {
    clearScreen();
    printf("ADD NEW DOCTOR\n");

    char name[100], email[100], phone[20], password[30], spec[100];
    int age=0; float weight=0; char buf[64];

    printf("Full Name: ");
    clearInputBuffer();
    if (!fgets(name,sizeof(name),stdin)) return 0;
    trim(name); if (strlen(name)==0){ printf("Name required.\n"); return 0; }

    while (1) {
        printf("Age (25-80): ");
        if (!fgets(buf,sizeof(buf),stdin)) return 0;
        if (sscanf(buf,"%d",&age)==1 && age>=25 && age<=80) break;
        printf("Invalid.\n");
    }
    while (1) {
        printf("Weight (40-150 kg): ");
        if (!fgets(buf,sizeof(buf),stdin)) return 0;
        if (sscanf(buf,"%f",&weight)==1 && weight>=40 && weight<=150) break;
        printf("Invalid.\n");
    }
    while (1) {
        printf("Phone (01XXXXXXXXX): ");
        if (!fgets(phone,sizeof(phone),stdin)) return 0;
        trim(phone);
        if (isValidBangladeshiPhone(phone)) break;
    }
    while (1) {
        printf("Email: ");
        if (!fgets(email,sizeof(email),stdin)) return 0;
        trim(email);
        if (isValidEmail(email)) break;
        printf("Invalid.\n");
    }
    printf("Specialization: ");
    if (!fgets(spec,sizeof(spec),stdin)) return 0;
    trim(spec);

    printf("Set Password: ");
    inputPassword(password, sizeof(password));

    replaceCommas(name); replaceCommas(email); replaceCommas(spec);

    FILE *fp=fopen("doctors.txt","a");
    if (!fp){ printf("doctors.txt error\n"); return 0; }
    fprintf(fp, "%s,%s,%s,%d,%s,%.2f,%s\n", phone, password, name, age, email, weight, spec);
    fclose(fp);

    printf("Doctor added: %s (%s)\n", name, spec);
    printf("Press Enter..."); clearInputBuffer();
    return 1;
}

static int removeDoctors(void) {
    clearScreen();
    printf("REMOVE DOCTOR\n");

    FILE *fp=fopen("doctors.txt","r");
    if (!fp){ printf("No doctors found.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    char line[1024];
    char phones[200][20], names[200][100], specs[200][100];
    int n=0;

    printf("%-4s %-13s %-22s %-16s\n", "#","Phone","Name","Specialization");
    printf("------------------------------------------------------------\n");

    while (n<200 && fgets(line,sizeof(line),fp)) {
        char ph[20], pw[30], nm[100], em[100], sp[100];
        int age=0; float w=0;
        int ok = sscanf(line,"%19[^,],%29[^,],%99[^,],%d,%99[^,],%f,%99[^\n]",
                        ph, pw, nm, &age, em, &w, sp);
        if (ok>=6) {
            trim(ph); trim(nm); trim(sp);
            strcpy(phones[n], ph);
            strcpy(names[n], nm);
            strcpy(specs[n], sp);
            printf("%-4d %-13s %-22s %-16s\n", n+1, phones[n], names[n], specs[n]);
            n++;
        }
    }
    fclose(fp);

    if (n==0) { printf("No doctors registered.\n"); printf("Press Enter..."); clearInputBuffer(); return 0; }

    printf("\nPick number to remove (0 cancel): ");
    int pick=0; if (scanf("%d",&pick)!=1 || pick<1 || pick>n){ clearInputBuffer(); printf("Cancelled.\n"); return 0; }
    clearInputBuffer();

    printf("Confirm remove Dr. %s (%s)? (y/n): ", names[pick-1], phones[pick-1]);
    char c=getchar(); clearInputBuffer();
    if (tolower((unsigned char)c)!='y'){ printf("Cancelled.\n"); return 0; }

    FILE *in=fopen("doctors.txt","r");
    FILE *out=fopen("doctors_tmp.txt","w");
    if (!in || !out){ if(in)fclose(in); if(out)fclose(out); printf("File error.\n"); return 0; }

    while (fgets(line,sizeof(line),in)) {
        char ph[20];
        if (sscanf(line,"%19[^,]",ph)==1 && strcmp(ph,phones[pick-1])==0) {
            // skip
        } else fputs(line,out);
    }
    fclose(in); fclose(out);
    remove("doctors.txt");
    rename("doctors_tmp.txt","doctors.txt");

    // remove their appointments
    FILE *ai=fopen("appointments.txt","r");
    if (ai) {
        FILE *ao=fopen("appointments_tmp.txt","w");
        if (ao) {
            while (fgets(line,sizeof(line),ai)) {
                char dID[20];
                int ok = sscanf(line,"%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%19[^,]", dID);
                if (ok==1 && strcmp(dID,phones[pick-1])==0) {
                    // skip
                } else fputs(line, ao);
            }
            fclose(ao);
            remove("appointments.txt");
            rename("appointments_tmp.txt","appointments.txt");
        }
        fclose(ai);
    }

    printf("Doctor removed.\n");
    printf("Press Enter..."); clearInputBuffer();
    return 1;
}

static void adminDashboard(char name[], char phone[]) {
    (void)name; (void)phone;
    char buf[16];
    while (1) {
        clearScreen();
        printf("ADMIN DASHBOARD\n\n");
        printf("1. View All Appointments\n");
        printf("2. View Patients\n");
        printf("3. Edit Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Add Doctor\n");
        printf("6. Remove Doctor\n");
        printf("7. Back\n");
        printf("\nChoose (1-7): ");

        if (!fgets(buf,sizeof(buf),stdin)) continue;
        int op = atoi(buf);

        if (op==1) viewAllAppointments();
        else if (op==2) viewAllPatients();
        else if (op==3) editPatientRecord();
        else if (op==4) deletePatients();
        else if (op==5) addDoctors();
        else if (op==6) removeDoctors();
        else if (op==7) return;
        else { printf("Invalid.\n"); printf("Press Enter..."); clearInputBuffer(); }
    }
}

// ========== MAIN ==========
int main(void) {
    srand((unsigned)time(NULL));

    while (1) {
        defaultPage();
        int x=0;
        if (scanf("%d", &x) != 1) { clearInputBuffer(); continue; }
        clearInputBuffer();

        if (x==1) { registerPatient(); }
        else if (x==2) { loginOption(); }
        else if (x==3) { emergencyContacts(); }
        else if (x==4) {
            clearScreen();
            printf("About Us: ASTHAA — Simple healthcare desk tool.\n");
            printf("Press Enter to return..."); clearInputBuffer();
        }
        else if (x==5) { printf("Goodbye!\n"); return 0; }
        else { printf("Invalid option.\n"); printf("Press Enter..."); clearInputBuffer(); }
    }
    return 0;
}
