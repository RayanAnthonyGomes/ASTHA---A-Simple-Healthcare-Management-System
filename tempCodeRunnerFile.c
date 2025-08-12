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
