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

// Utility functions
void clearInputBuffer();
void stringCopy(char* dest, char* src);

int main() {
    initializeSystem();

    int choice;
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch(choice) {
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
    } while(choice != 7);

    return 0;
}

void initializeSystem() {
    // Initialize distance matrix
    for(int i = 0; i < MAX_CITIES; i++) {
        for(int j = 0; j < MAX_CITIES; j++) {
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

void displayMainMenu() {
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


void cityManagement(){}
void distanceManagement(){}
void vehicleManagement(){}
void deliveryRequest(){}
void reports(){}
void fileHandling(){}



// Custom string utility functions
void clearInputBuffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void stringCopy(char* dest, char* src) {
    int i = 0;
    while(src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

