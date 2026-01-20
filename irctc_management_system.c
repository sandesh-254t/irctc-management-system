#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define ADMIN_USER "admin"
#define ADMIN_PASS "irctc123"
#define MAX 20
struct train{
    int number;
    char name[50];
    char source[50];
    char destination[50];
    char arrival[50];
    char departure[50];
    
};
struct train trains[MAX];
int trainCount = 6;

void data(){
    trains[0] = (struct train){12723, "Telangana Express", "Hyderabad", "New Delhi", "06:30", "06:45"};
    trains[1] = (struct train){12627, "Karnataka Express", "Bengaluru", "New Delhi", "19:20", "19:35"};
    trains[2] = (struct train){12839, "Howrah Mail", "Chennai", "Howrah", "05:10", "05:25"};
    trains[3] = (struct train){12707, "A P Sampark Kranti", "Tirupati", "Nizamuddin", "08:40", "08:55"};
    trains[4] = (struct train){12615, "Grand Trunk Express", "Chennai", "New Delhi", "18:50", "19:05"};
    trains[5] = (struct train){12711, "Kondaveedu Express","Machilipatnam","Yesvantpur Jn","--","15:55"};
}
void pauseScreen() {
    printf("\n\n\t\tPress Enter to continue...");
    getchar();  // consume leftover newline
    getchar();  // wait for Enter
}
void saveFile(){
    FILE *fp;
    fp = fopen("traindat.dat","wb");
    if (fp == NULL){
        printf("Error opening file!");
        return;
    }
    fwrite(&trainCount,sizeof(int),1,fp);
    fwrite(trains,sizeof(struct train),trainCount,fp);
    fclose(fp);
    
}
void openFile(){
    FILE *fp = fopen("traindat.dat","rb");

    if(fp == NULL){
        // File does not exist → load default data
        data();
        saveFile();
        return;
    }

    fread(&trainCount, sizeof(int), 1, fp);

    // Safety check
    if(trainCount <= 0 || trainCount > MAX){
        fclose(fp);
        data();
        saveFile();
        return;
    }

    fread(trains, sizeof(struct train), trainCount, fp);
    fclose(fp);
}

void dispTrains(){
    printf("\t\t----- Train Schedule -----");
    for(int i =0;i<trainCount;i++){
        printf("\n\t\tTrain No : %d",trains[i].number);
        printf("\n\t\tName     : %s",trains[i].name);
        printf("\n\t\tFrom     : %s",trains[i].source);
        printf("\n\t\tTo       : %s",trains[i].destination);
        printf("\n\t\tArrival  : %s",trains[i].arrival);
        printf("\n\t\tDeparture: %s",trains[i].departure);
        printf("\n\t\t----------------------");
    }
}

void searchTrain(){
    int trnum;
    printf("Enter Train number to search: ");
    scanf("%d",&trnum);
    int found = 0;
    for(int i =0;i<trainCount;i++){
        if(trnum == trains[i].number){
            printf("\n\t\tTrain Found!");
            printf("\n\t\tTrain No : %d", trains[i].number);
            printf("\n\t\tName     : %s", trains[i].name);
            printf("\n\t\tFrom     : %s", trains[i].source);
            printf("\n\t\tTo       : %s", trains[i].destination);
            printf("\n\t\tArrival  : %s", trains[i].arrival);
            printf("\n\t\tDeparture: %s", trains[i].departure);
            found = 1;
            break;
        }
    }
    if(found == 0){
        printf("\t\t!!Train Not Found!!\n");
    }
}
void userMenu() {
    int ch;

    while (1) {
        system("cls");
        printf("\n\n\t\t==============================");
        printf("\n\t\t           USER MENU");
        printf("\n\t\t==============================");
        printf("\n\t\t1. Show all trains");
        printf("\n\t\t2. Search train by number");
        printf("\n\t\t0. Back");
        printf("\n\t\tEnter your choice: ");

        scanf("%d", &ch);

        switch (ch) {
            case 1:
                dispTrains();
                pauseScreen();
                break;

            case 2:
                searchTrain();
                pauseScreen();
                break;

            case 0:
                return;

            default:
                printf("\n\t\tInvalid choice!");
                pauseScreen();
        }
    }
}


int adminLogin() {
    char user[20], pass[20];

    printf("\n\t\tEnter admin username: ");
    scanf("%s", user);

    printf("\t\tEnter admin password: ");
    scanf("%s", pass);

    if (strcmp(user, ADMIN_USER) == 0 && strcmp(pass, ADMIN_PASS) == 0) {
        printf("\n\t\tLogin successful!\n");
        pauseScreen();
        return 1;
    } else {
        printf("\n\t\tInvalid credentials!\n");
        pauseScreen();
        return 0;
    }
}

void addTrain() {
    if (trainCount >= MAX) {
        printf("\n\t\tTrain list full! Cannot add more.\n");
        return;
    }

    struct train t;

    printf("\n\t\tEnter Train Number: ");
    scanf("%d", &t.number);

    for (int i = 0; i < trainCount; i++) {
        if (trains[i].number == t.number) {
            printf("\n\t\tTrain number already exists!\n");
            return;
        }
    }

    printf("\t\tEnter Train Name: ");
    scanf(" %[^\n]", t.name);

    printf("\t\tEnter Source: ");
    scanf(" %[^\n]", t.source);

    printf("\t\tEnter Destination: ");
    scanf(" %[^\n]", t.destination);

    printf("\t\tEnter Arrival Time: ");
    scanf(" %[^\n]", t.arrival);

    printf("\t\tEnter Departure Time: ");
    scanf(" %[^\n]", t.departure);

    trains[trainCount++] = t;
    saveFile();

    printf("\n\t\tTrain added successfully!\n");
}

void deleteTrain() {
    int num, found = 0;

    printf("\n\t\tEnter Train Number to delete: ");
    scanf("%d", &num);

    for (int i = 0; i < trainCount; i++) {
        if (trains[i].number == num) {
            for (int j = i; j < trainCount - 1; j++) {
                trains[j] = trains[j + 1];
            }
            trainCount--;
            saveFile();
            printf("\n\t\tTrain deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n\t\tTrain not found!\n");
    }
}

void updateTrain() {
    int num, found = 0;

    printf("\n\t\tEnter Train Number to update: ");
    scanf("%d", &num);

    for (int i = 0; i < trainCount; i++) {
        if (trains[i].number == num) {
            printf("\t\tEnter new Arrival Time: ");
            scanf(" %[^\n]", trains[i].arrival);

            printf("\t\tEnter new Departure Time: ");
            scanf(" %[^\n]", trains[i].departure);

            saveFile();
            printf("\n\t\tTrain timings updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n\t\tTrain not found!\n");
    }
}



void adminMenu() {
    int ch;

    if (!adminLogin()) return;

    while (1) {
        system("cls");
        printf("\n\n\t\t==============================");
        printf("\n\t\t          ADMIN MENU");
        printf("\n\t\t==============================");
        printf("\n\t\t1. Show all trains");
        printf("\n\t\t2. Add new train");
        printf("\n\t\t3. Delete train");
        printf("\n\t\t4. Update train timings");
        printf("\n\t\t0. Logout");
        printf("\n\t\tEnter your choice: ");

        scanf("%d", &ch);

        switch (ch) {
            case 1: dispTrains(); 
            pauseScreen();
            break;

            case 2: addTrain();
            pauseScreen();
            break;
            case 3: deleteTrain();
            pauseScreen();
            break;
            pauseScreen();
            case 4: updateTrain();
            pauseScreen();
            break;
            case 0:
                saveFile();
                printf("\n\t\tLogged out.\n");
                return;
            default:
                printf("\n\t\tInvalid choice! Try again.\n");
        }
    }
}


int main() {
    int role;

    openFile();   // load data once at start

    while (1) {
        system("cls");
        printf("\n\n\t\t==============================");
        printf("\n\t\t         IRCTC SYSTEM");
        printf("\n\t\t==============================");
        printf("\n\t\t1. User");
        printf("\n\t\t2. Admin");
        printf("\n\t\t0. Exit");
        printf("\n\t\tEnter your choice: ");

        scanf("%d", &role);

        switch (role) {
            case 1:
                userMenu();
                break;

            case 2:
                adminMenu();
                break;

            case 0:
                saveFile();
                printf("\n\t\tThank you! Exiting...\n");
                return 0;

            default:
                printf("\n\t\tInvalid choice! Try again.\n");
        }
    }
    
}


