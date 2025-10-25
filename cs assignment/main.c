#include <stdio.h>
#include <stdlib.h>


#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50
// Global variables
char cities[MAX_CITIES][MAX_NAME_LENGTH];
float distance_matrix[MAX_CITIES][MAX_CITIES];
int city_count = 0;


// Function prototypes
void initializeSystem();
void displayMainMenu();
void cityManagement();
void distanceManagement();
void vehicleManagement();
void deliveryRequest();
void reports();
void fileHandling();

// City management functions
void addCity();
void renameCity();
void removeCity();
void displayCities();
int findCityIndex(char* city_name);

// Distance management functions
void inputDistance();
void editDistance();
void displayDistanceTable();



// Utility functions
void clearInputBuffer();
void stringCopy(char* dest, char* src);
void toLowerCase(char* str);
int isValidCityName(char* name);
int stringCompare(char* str1, char* str2);
int stringLength(char* str);
int isAlphaNumeric(char c);
char toLowerChar(char c);

int main()
{
    initializeSystem();

    int choice;
    do
    {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice)
        {
        case 1:
            cityManagement();
            break;
        case 2:
            distanceManagement();
            break;
        case 3:
            vehicleManagement();
            break;
        case 4:
            deliveryRequest();
            break;
        case 5:
            reports();
            break;
        case 6:
            fileHandling();
            break;
        case 7:
            printf("Saving data and exiting...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }
    while(choice != 7);

    return 0;
}

void initializeSystem()
{
    // Initialize distance matrix
    for(int i = 0; i < MAX_CITIES; i++)
    {
        for(int j = 0; j < MAX_CITIES; j++)
        {
            if(i == j)
                distance_matrix[i][j] = 0;
            else
                distance_matrix[i][j] = -1;
        }
    }

    // Add some default cities
    stringCopy(cities[city_count++], "Colombo");
    stringCopy(cities[city_count++], "Kandy");
    stringCopy(cities[city_count++], "Galle");
    stringCopy(cities[city_count++], "Jaffna");


    // Add some default distances
    distance_matrix[0][1] = distance_matrix[1][0] = 120;
    distance_matrix[0][2] = distance_matrix[2][0] = 115;
    distance_matrix[0][3] = distance_matrix[3][0] = 400;
    distance_matrix[1][2] = distance_matrix[2][1] = 200;
    distance_matrix[1][3] = distance_matrix[3][1] = 350;


}

void displayMainMenu()
{
    printf("\n========================================\n");
    printf("    LOGISTICS MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. City Management\n");
    printf("2. Distance Management\n");
    printf("3. Vehicle Management\n");
    printf("4. Delivery Request\n");
    printf("5. Reports\n");
    printf("6. File Handling\n");
    printf("7. Exit\n");
    printf("========================================\n");
}


void cityManagement()
{
    int choice;
    do
    {
        printf("\n--- City Management ---\n");
        printf("1. Add New City\n");
        printf("2. Rename City\n");
        printf("3. Remove City\n");
        printf("4. Display Cities\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice)
        {
        case 1:
            addCity();
            break;
        case 2:
            renameCity();
            break;
        case 3:
            removeCity();
            break;
        case 4:
            displayCities();
            break;
        case 5:
            break;
        default:
            printf("Invalid choice!\n");
        }
    }
    while(choice != 5);
}

void addCity(){
        if(city_count >= MAX_CITIES) {
        printf("Maximum number of cities reached!\n");
        return;
    }

    char city_name[MAX_NAME_LENGTH];
    printf("Enter city name: ");

    int i = 0;
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF && i < MAX_NAME_LENGTH - 1) {
        city_name[i++] = ch;
    }
    city_name[i] = '\0';

    if(!isValidCityName(city_name)) {
        printf("Invalid city name!\n");
        return;
    }

    // Check if city already exists
    for(int i = 0; i < city_count; i++) {
        char temp1[MAX_NAME_LENGTH], temp2[MAX_NAME_LENGTH];
        stringCopy(temp1, cities[i]);
        stringCopy(temp2, city_name);
        toLowerCase(temp1);
        toLowerCase(temp2);

        if(stringCompare(temp1, temp2) == 0) {
            printf("City already exists!\n");
            return;
        }
    }

    stringCopy(cities[city_count], city_name);
    city_count++;
    printf("City '%s' added successfully!\n", city_name);
}


void renameCity(){
        if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    displayCities();
    int index;
    printf("Enter city index to rename: ");
    scanf("%d", &index);
    clearInputBuffer();

    if(index < 0 || index >= city_count) {
        printf("Invalid city index!\n");
        return;
    }

    char new_name[MAX_NAME_LENGTH];
    printf("Enter new name for %s: ", cities[index]);

    int i = 0;
    char ch;
    while((ch = getchar()) != '\n' && ch != EOF && i < MAX_NAME_LENGTH - 1) {
        new_name[i++] = ch;
    }
    new_name[i] = '\0';

    if(!isValidCityName(new_name)) {
        printf("Invalid city name!\n");
        return;
    }

    printf("City '%s' renamed to '%s'\n", cities[index], new_name);
    stringCopy(cities[index], new_name);
}


void removeCity(){
    if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    displayCities();
    int index;
    printf("Enter city index to remove: ");
    scanf("%d", &index);
    clearInputBuffer();

    if(index < 0 || index >= city_count) {
        printf("Invalid city index!\n");
        return;
    }

    printf("Are you sure you want to remove '%s'? (y/n): ", cities[index]);
    char confirm;
    scanf("%c", &confirm);
    clearInputBuffer();

    if(confirm == 'y' || confirm == 'Y') {
        // Shift cities array
        for(int i = index; i < city_count - 1; i++) {
            stringCopy(cities[i], cities[i + 1]);
        }

        // Shift distance matrix
        for(int i = index; i < city_count - 1; i++) {
            for(int j = 0; j < city_count; j++) {
                distance_matrix[i][j] = distance_matrix[i + 1][j];
            }
        }
        for(int j = index; j < city_count - 1; j++) {
            for(int i = 0; i < city_count; i++) {
                distance_matrix[i][j] = distance_matrix[i][j + 1];
            }
        }

        city_count--;
        printf("City removed successfully!\n");
    }
}



void displayCities(){
    printf("\n--- Cities List ---\n");
    for(int i = 0; i < city_count; i++) {
        printf("%d. %s\n", i, cities[i]);
    }
}

void distanceManagement() {
    int choice;
    do {
        printf("\n--- Distance Management ---\n");
        printf("1. Input Distance\n");
        printf("2. Edit Distance\n");
        printf("3. Display Distance Table\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
            case 1:
                inputDistance();
                break;
            case 2:
                editDistance();
                break;
            case 3:
                displayDistanceTable();
                break;
            case 4:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 4);
}


void inputDistance(){
        if(city_count < 2) {
        printf("Need at least 2 cities to input distances!\n");
        return;
    }

    displayCities();
    int city1, city2;
    float dist;

    printf("Enter first city index: ");
    scanf("%d", &city1);
    printf("Enter second city index: ");
    scanf("%d", &city2);
    printf("Enter distance (km): ");
    scanf("%f", &dist);
    clearInputBuffer();

    if(city1 < 0 || city1 >= city_count || city2 < 0 || city2 >= city_count) {
        printf("Invalid city indices!\n");
        return;
    }

    if(city1 == city2) {
        printf("Distance from a city to itself must be 0!\n");
        return;
    }

    if(dist <= 0) {
        printf("Distance must be positive!\n");
        return;
    }

    distance_matrix[city1][city2] = dist;
    distance_matrix[city2][city1] = dist;
    printf("Distance between %s and %s set to %.2f km\n",
           cities[city1], cities[city2], dist);
}

void editDistance(){}
void displayDistanceTable(){}


void vehicleManagement() {}
void deliveryRequest() {}
void reports() {}
void fileHandling() {}



// Custom string utility functions
void clearInputBuffer()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void stringCopy(char* dest, char* src)
{
    int i = 0;
    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

int stringCompare(char* str1, char* str2) {
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
        i++;
    }
    return str1[i] - str2[i];
}

void toLowerCase(char* str) {
    for(int i = 0; str[i] != '\0'; i++) {
        str[i] = toLowerChar(str[i]);
    }
}

int isValidCityName(char* name) {
    int len = stringLength(name);
    if(len == 0 || len >= MAX_NAME_LENGTH) {
        return 0;
    }

    for(int i = 0; name[i] != '\0'; i++) {
        if(!isAlphaNumeric(name[i]) && name[i] != ' ' && name[i] != '-') {
            return 0;
        }
    }

    return 1;
}

int stringLength(char* str) {
    int len = 0;
    while(str[len] != '\0') {
        len++;
    }
    return len;
}

int isAlphaNumeric(char c) {
    return (c >= '0' && c <= '9') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z');
}


char toLowerChar(char c) {
    if(c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}
