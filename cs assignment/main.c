#include <stdio.h>
#include <stdlib.h>


#define MAX_CITIES 30
#define MAX_NAME_LENGTH 50
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0


// Global variables
char cities[MAX_CITIES][MAX_NAME_LENGTH];
float distance_matrix[MAX_CITIES][MAX_CITIES];
int city_count = 0;
int delivery_count = 0;

// Delivery record arrays
int delivery_id[MAX_DELIVERIES];
char delivery_source[MAX_DELIVERIES][MAX_NAME_LENGTH];
char delivery_destination[MAX_DELIVERIES][MAX_NAME_LENGTH];
float delivery_weight[MAX_DELIVERIES];
char delivery_vehicle_type[MAX_DELIVERIES][10];
float delivery_distance[MAX_DELIVERIES];
float delivery_base_cost[MAX_DELIVERIES];
float delivery_fuel_used[MAX_DELIVERIES];
float delivery_fuel_cost[MAX_DELIVERIES];
float delivery_operational_cost[MAX_DELIVERIES];
float delivery_profit[MAX_DELIVERIES];
float delivery_customer_charge[MAX_DELIVERIES];
float delivery_estimated_time[MAX_DELIVERIES];

// Vehicle data arrays
char vehicle_types[3][10] = {"Van", "Truck", "Lorry"};
int vehicle_capacity[3] = {1000, 5000, 10000};
float vehicle_rate_per_km[3] = {30.0, 40.0, 80.0};
float vehicle_avg_speed[3] = {60.0, 50.0, 45.0};
float vehicle_fuel_efficiency[3] = {12.0, 6.0, 4.0};



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

// Delivery functions
void calculateDelivery(int source, int destination, float weight, int vehicle_type);
float findMinimumDistance(int source, int destination);
void exhaustiveSearch(int source, int destination, float* min_distance, int* path, int* path_length);
void generatePermutations(int cities[], int start, int end, int source, int destination, float* min_distance, int* best_path, int* best_path_length);
float calculatePathDistance(int path[], int length);



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

void editDistance(){
        displayDistanceTable();

    int city1, city2;
    float new_dist;

    printf("Enter first city index: ");
    scanf("%d", &city1);
    printf("Enter second city index: ");
    scanf("%d", &city2);
    printf("Enter new distance (km): ");
    scanf("%f", &new_dist);
    clearInputBuffer();

    if(city1 < 0 || city1 >= city_count || city2 < 0 || city2 >= city_count) {
        printf("Invalid city indices!\n");
        return;
    }

    if(city1 == city2) {
        printf("Distance from a city to itself must be 0!\n");
        return;
    }

    if(new_dist <= 0) {
        printf("Distance must be positive!\n");
        return;
    }

    distance_matrix[city1][city2] = new_dist;
    distance_matrix[city2][city1] = new_dist;
    printf("Distance updated successfully!\n");
}

void displayDistanceTable(){
        if(city_count == 0) {
        printf("No cities available!\n");
        return;
    }

    printf("\n--- Distance Matrix ---\n");
    printf("%-15s", "");
    for(int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
    }
    printf("\n");

    for(int i = 0; i < city_count; i++) {
        printf("%-15s", cities[i]);
        for(int j = 0; j < city_count; j++) {
            if(distance_matrix[i][j] == -1)
                printf("%-15s", "N/A");
            else
                printf("%-15.2f", distance_matrix[i][j]);
        }
        printf("\n");
    }
}


void vehicleManagement() {
        printf("\n--- Vehicle Types ---\n");
    printf("==================================================================\n");
    printf("%-10s %-12s %-15s %-12s %-15s\n",
           "Type", "Capacity(kg)", "Rate/km(LKR)", "Speed(km/h)", "Efficiency(km/l)");
    printf("==================================================================\n");

    for(int i = 0; i < 3; i++) {
        printf("%-10s %-12d %-15.2f %-12.2f %-15.2f\n",
               vehicle_types[i], vehicle_capacity[i], vehicle_rate_per_km[i],
               vehicle_avg_speed[i], vehicle_fuel_efficiency[i]);
    }
    printf("==================================================================\n");

}

void deliveryRequest() {
    if(city_count < 2) {
        printf("Need at least 2 cities for delivery!\n");
        return;
    }

    if(delivery_count >= MAX_DELIVERIES) {
        printf("Maximum delivery records reached!\n");
        return;
    }

    displayCities();
    int source, destination, vehicle_choice;
    float weight;

    printf("Enter source city index: ");
    scanf("%d", &source);
    printf("Enter destination city index: ");
    scanf("%d", &destination);
    printf("Enter weight (kg): ");
    scanf("%f", &weight);

    if(source < 0 || source >= city_count || destination < 0 || destination >= city_count) {
        printf("Invalid city indices!\n");
        return;
    }

    if(source == destination) {
        printf("Source and destination cannot be the same!\n");
        return;
    }

    printf("\nSelect vehicle type:\n");
    printf("1. Van (Capacity: 1000kg)\n");
    printf("2. Truck (Capacity: 5000kg)\n");
    printf("3. Lorry (Capacity: 10000kg)\n");
    printf("Enter choice: ");
    scanf("%d", &vehicle_choice);
    clearInputBuffer();

    if(vehicle_choice < 1 || vehicle_choice > 3) {
        printf("Invalid vehicle choice!\n");
        return;
    }

    vehicle_choice--;

    if(weight > vehicle_capacity[vehicle_choice]) {
        printf("Weight exceeds vehicle capacity!\n");
        return;
    }

    if(weight <= 0) {
        printf("Weight must be positive!\n");
        return;
    }

    calculateDelivery(source, destination, weight, vehicle_choice);
}

void calculateDelivery(int source, int destination, float weight, int vehicle_type) {
    int current_delivery = delivery_count;

    delivery_id[current_delivery] = delivery_count + 1;
    stringCopy(delivery_source[current_delivery], cities[source]);
    stringCopy(delivery_destination[current_delivery], cities[destination]);
    delivery_weight[current_delivery] = weight;
    stringCopy(delivery_vehicle_type[current_delivery], vehicle_types[vehicle_type]);

    // Find minimum distance using exhaustive search
    delivery_distance[current_delivery] = findMinimumDistance(source, destination);

    if(delivery_distance[current_delivery] == -1) {
        printf("No valid route found between %s and %s!\n", cities[source], cities[destination]);
        return;
    }

    // Calculate costs
    delivery_base_cost[current_delivery] = delivery_distance[current_delivery] *
                                         vehicle_rate_per_km[vehicle_type] *
                                         (1 + weight / 10000.0);
    delivery_estimated_time[current_delivery] = delivery_distance[current_delivery] /
                                               vehicle_avg_speed[vehicle_type];
    delivery_fuel_used[current_delivery] = delivery_distance[current_delivery] /
                                         vehicle_fuel_efficiency[vehicle_type];
    delivery_fuel_cost[current_delivery] = delivery_fuel_used[current_delivery] * FUEL_PRICE;
    delivery_operational_cost[current_delivery] = delivery_base_cost[current_delivery] +
                                                 delivery_fuel_cost[current_delivery];
    delivery_profit[current_delivery] = delivery_base_cost[current_delivery] * 0.25;
    delivery_customer_charge[current_delivery] = delivery_operational_cost[current_delivery] +
                                                delivery_profit[current_delivery];

    // Display results
    printf("\n==============================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("==============================================================\n");
    printf("From: %s\n", delivery_source[current_delivery]);
    printf("To: %s\n", delivery_destination[current_delivery]);
    printf("Minimum Distance: %.2f km\n", delivery_distance[current_delivery]);
    printf("Vehicle: %s\n", delivery_vehicle_type[current_delivery]);
    printf("Weight: %.2f kg\n", delivery_weight[current_delivery]);
    printf("==============================================================\n");
    printf("Base Cost: %.2f × %.2f × (1 + %.2f/10000) = %.2f LKR\n",
           delivery_distance[current_delivery], vehicle_rate_per_km[vehicle_type],
           weight, delivery_base_cost[current_delivery]);
    printf("Fuel Used: %.2f L\n", delivery_fuel_used[current_delivery]);
    printf("Fuel Cost: %.2f LKR\n", delivery_fuel_cost[current_delivery]);
    printf("Operational Cost: %.2f LKR\n", delivery_operational_cost[current_delivery]);
    printf("Profit: %.2f LKR\n", delivery_profit[current_delivery]);
    printf("Customer Charge: %.2f LKR\n", delivery_customer_charge[current_delivery]);
    printf("Estimated Time: %.2f hours\n", delivery_estimated_time[current_delivery]);
    printf("==============================================================\n");

    delivery_count++;

    printf("\nSave this delivery? (y/n): ");
    char save;
    scanf("%c", &save);
    clearInputBuffer();

    if(save != 'y' && save != 'Y') {
        delivery_count--;
        printf("Delivery not saved.\n");
    } else {
        printf("Delivery saved successfully!\n");
    }
}
float findMinimumDistance(int source, int destination) {
    float min_distance = -1;
    int best_path[MAX_CITIES];
    int best_path_length = 0;

    // Check direct connection first
    if(distance_matrix[source][destination] != -1) {
        min_distance = distance_matrix[source][destination];
        best_path[0] = source;
        best_path[1] = destination;
        best_path_length = 2;
    }

    // Use exhaustive search for paths with up to 4 cities
    exhaustiveSearch(source, destination, &min_distance, best_path, &best_path_length);

    if(min_distance != -1) {
        printf("Optimal route: ");
        for(int i = 0; i < best_path_length; i++) {
            printf("%s", cities[best_path[i]]);
            if(i < best_path_length - 1) printf(" → ");
        }
        printf(" (%.2f km)\n", min_distance);
    }

    return min_distance;
}
void exhaustiveSearch(int source, int destination, float* min_distance, int* path, int* path_length) {
    if(city_count <= 4) {
        int all_cities[MAX_CITIES];
        for(int i = 0; i < city_count; i++) {
            all_cities[i] = i;
        }
        generatePermutations(all_cities, 0, city_count, source, destination, min_distance, path, path_length);
    } else {
        for(int i = 0; i < city_count; i++) {
            if(i != source && i != destination &&
               distance_matrix[source][i] != -1 &&
               distance_matrix[i][destination] != -1) {

                float total_distance = distance_matrix[source][i] + distance_matrix[i][destination];

                if(*min_distance == -1 || total_distance < *min_distance) {
                    *min_distance = total_distance;
                    path[0] = source;
                    path[1] = i;
                    path[2] = destination;
                    *path_length = 3;
                }
            }
        }
    }
}

void generatePermutations(int cities[], int start, int end, int source, int destination, float* min_distance, int* best_path, int* best_path_length) {
    if(start == end) {
        if(cities[0] == source && cities[end-1] == destination) {
            float total_distance = calculatePathDistance(cities, end);
            if(total_distance != -1 && (*min_distance == -1 || total_distance < *min_distance)) {
                *min_distance = total_distance;
                for(int i = 0; i < end; i++) {
                    best_path[i] = cities[i];
                }
                *best_path_length = end;
            }
        }
        return;
    }

    for(int i = start; i < end; i++) {
        int temp = cities[start];
        cities[start] = cities[i];
        cities[i] = temp;

        generatePermutations(cities, start + 1, end, source, destination, min_distance, best_path, best_path_length);

        temp = cities[start];
        cities[start] = cities[i];
        cities[i] = temp;
    }
}

float calculatePathDistance(int path[], int length) {
        float total_distance = 0;
    for(int i = 0; i < length - 1; i++) {
        if(distance_matrix[path[i]][path[i+1]] == -1) {
            return -1;
        }
        total_distance += distance_matrix[path[i]][path[i+1]];
    }
    return total_distance;
}

void reports() {
    if(delivery_count == 0) {
        printf("No delivery records available!\n");
        return;
    }

    printf("\n--- PERFORMANCE REPORTS ---\n");

    float total_distance = 0, total_time = 0, total_revenue = 0, total_profit = 0;
    float longest_distance = 0, shortest_distance = -1;
    int longest_index = 0, shortest_index = 0;

    for(int i = 0; i < delivery_count; i++) {
        total_distance += delivery_distance[i];
        total_time += delivery_estimated_time[i];
        total_revenue += delivery_customer_charge[i];
        total_profit += delivery_profit[i];

        if(delivery_distance[i] > longest_distance) {
            longest_distance = delivery_distance[i];
            longest_index = i;
        }

        if(shortest_distance == -1 || delivery_distance[i] < shortest_distance) {
            shortest_distance = delivery_distance[i];
            shortest_index = i;
        }
    }

    printf("a. Total Deliveries Completed: %d\n", delivery_count);
    printf("b. Total Distance Covered: %.2f km\n", total_distance);
    printf("c. Average Delivery Time: %.2f hours\n", total_time / delivery_count);
    printf("d. Total Revenue: %.2f LKR\n", total_revenue);
    printf("e. Total Profit: %.2f LKR\n", total_profit);
    printf("f. Longest Route: %s to %s (%.2f km)\n",
           delivery_source[longest_index], delivery_destination[longest_index], longest_distance);
    printf("g. Shortest Route: %s to %s (%.2f km)\n",
           delivery_source[shortest_index], delivery_destination[shortest_index], shortest_distance);
}

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
