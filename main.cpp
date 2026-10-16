#include <iostream>
#include <string>
#include <climits>
#include <cctype>
#include <limits>
using namespace std;

const int N = 13;
const int DEPT_COUNT = 24;

string locations[N] = {
    "First Gate",
    "Administrative Building",
    "Multipurpose Building",
    "Cafeteria",
    "Academic Building 1",
    "Academic Building 2",
    "Academic Building 3",
    "Jananeta Abdul Mannan Hall",
    "Osman Hadi Hall",
    "Shaheed Abrar Fahad Hall",
    "Mosque",
    "Temple",
    "Krishnachura Lane"
};

struct Department {
    string code;
    string building;
    string floor;
};

Department departments[DEPT_COUNT] = {
    {"ESRM", "Academic Building 1", "Ground Floor"},
    {"ICT", "Academic Building 1", "1st Floor"},
    {"BGE", "Academic Building 1", "2nd Floor"},
    {"CHEM", "Academic Building 1", "3rd Floor"},
    {"OFFICE / PRAYER / CLASSROOM", "Academic Building 2", "Ground Floor"},
    {"TE", "Academic Building 2", "1st Floor"},
    {"PHY", "Academic Building 2", "2nd Floor"},
    {"STAT", "Academic Building 2", "3rd Floor"},
    {"MATH", "Academic Building 2", "4th Floor"},
    {"ME", "Academic Building 3", "1st Floor"},
    {"CSE", "Academic Building 3", "2nd Floor"},
    {"CPS", "Academic Building 3", "3rd Floor"},
    {"FTNS", "Academic Building 3", "4th Floor"},
    {"ECON", "Academic Building 3", "5th Floor"},
    {"BBA", "Academic Building 3", "6th Floor"},
    {"PHARM", "Academic Building 3", "7th Floor"},
    {"ACC", "Academic Building 3", "8th Floor"},
    {"MGT", "Academic Building 3", "9th Floor"},
    {"ENG", "Academic Building 3", "10th Floor"},
    {"EEE", "Academic Building 3", "11th Floor"},
    {"CONF. ROOM", "Academic Building 3", "12th Floor (accessible via Lift 12)"},
    {"OFFICE", "Academic Building 2", "Ground Floor"},
    {"PRAYER ROOM", "Academic Building 2", "Ground Floor"},
    {"ALTERNATIVE CLASSROOM", "Academic Building 2", "Ground Floor"}
};

int roads[N][N] = {};

void addRoad(int a, int b, int distance) {
    roads[a][b] = distance;
    roads[b][a] = distance;
}

void showLocations() {
    cout << "\n============= CAMPUS LOCATIONS =============\n";

    for (int i = 0; i < N; i++) {
        cout << i + 1 << ". " << locations[i] << '\n';
    }
}

void showRoads() {
    cout << "\n========== KNOWN ROAD CONNECTIONS ==========\n";

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (roads[i][j] > 0) {
                cout << locations[i] << " <-> "
                     << locations[j] << " : "
                     << roads[i][j] << " m\n";
            }
        }
    }

    cout << "Only provided road connections are listed.\n";
}

void findShortestRoute() {
    int start, destination;

    showLocations();

    cout << "\nStart       : ";
    if (!(cin >> start)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a location number.\n";
        return;
    }

    cout << "Destination : ";
    if (!(cin >> destination)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a location number.\n";
        return;
    }

    if (start < 1 || start > N ||
        destination < 1 || destination > N) {
        cout << "Invalid location number. Enter 1 to "
             << N << ".\n";
        return;
    }

    start--;
    destination--;

    if (start == destination) {
        cout << "\nYou are already at "
             << locations[start] << ".\n";
        cout << "Total Distance: 0 meters\n";
        return;
    }

    int dist[N], previous[N];
    bool visited[N] = {};

    for (int i = 0; i < N; i++) {
        dist[i] = INT_MAX;
        previous[i] = -1;
    }

    dist[start] = 0;

    // Dijkstra's Shortest Path Algorithm
    for (int count = 0; count < N; count++) {
        int current = -1;
        int smallest = INT_MAX;

        for (int i = 0; i < N; i++) {
            if (!visited[i] && dist[i] < smallest) {
                smallest = dist[i];
                current = i;
            }
        }

        if (current == -1)
            break;

        visited[current] = true;

        for (int next = 0; next < N; next++) {
            if (roads[current][next] > 0 &&
                !visited[next]) {

                int newDist =
                    dist[current] + roads[current][next];

                if (newDist < dist[next]) {
                    dist[next] = newDist;
                    previous[next] = current;
                }
            }
        }
    }

    if (dist[destination] == INT_MAX) {
        cout << "\nNo route found using the available "
             << "road data.\n";
        cout << "More road information may be needed.\n";
        return;
    }

    int path[N];
    int length = 0;

    for (int current = destination;
         current != -1;
         current = previous[current]) {
        path[length++] = current;
    }

    cout << "\n============== ROUTE RESULT ==============\n";
    cout << "Start       : " << locations[start] << '\n';
    cout << "Destination : "
         << locations[destination] << '\n';

    cout << "\nRoute:\n";

    for (int i = length - 1; i >= 0; i--) {
        cout << locations[path[i]] << '\n';

        if (i > 0) {
            int from = path[i];
            int to = path[i - 1];

            cout << "   |  " << roads[from][to]
                 << " meters\n";
            cout << "   v\n";
        }
    }

    cout << "\nRoute Distance Breakdown:\n";

    int segment = 1;

    for (int i = length - 1; i > 0; i--) {
        int from = path[i];
        int to = path[i - 1];

        cout << segment++ << ". "
             << locations[from] << " -> "
             << locations[to] << " : "
             << roads[from][to] << " m\n";
    }

    cout << "\nTotal Distance: "
         << dist[destination] << " meters\n";
    cout << "==========================================\n";
}

string toUpperCase(string value) {
    for (int i = 0; i < (int)value.length(); i++) {
        value[i] = (char)toupper((unsigned char)value[i]);
    }

    return value;
}

void showDepartments() {
    cout << "\n====== ALL ACADEMIC BUILDINGS & DEPARTMENTS ======\n";

    cout << "\n[ ACADEMIC BUILDING 1 ]\n";
    cout << "Ground Floor : ESRM\n";
    cout << "1st Floor    : ICT\n";
    cout << "2nd Floor    : BGE\n";
    cout << "3rd Floor    : CHEM\n";

    cout << "\n[ ACADEMIC BUILDING 2 ]\n";
    cout << "Ground Floor : OFFICE / PRAYER / CLASSROOM\n";
    cout << "1st Floor    : TE\n";
    cout << "2nd Floor    : PHY\n";
    cout << "3rd Floor    : STAT\n";
    cout << "4th Floor    : MATH\n";

    cout << "\n[ ACADEMIC BUILDING 3 ]\n";
    cout << "1st Floor  : ME\n";
    cout << "2nd Floor  : CSE\n";
    cout << "3rd Floor  : CPS\n";
    cout << "4th Floor  : FTNS\n";
    cout << "5th Floor  : ECON\n";
    cout << "6th Floor  : BBA\n";
    cout << "7th Floor  : PHARM\n";
    cout << "8th Floor  : ACC\n";
    cout << "9th Floor  : MGT\n";
    cout << "10th Floor : ENG\n";
    cout << "11th Floor : EEE\n";
    cout << "12th Floor : CONF. ROOM (Lift 12)\n";

    cout << "==================================================\n";
}

void findDepartment() {
    string code;

    cout << "\nEnter Department Short Form: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, code);

    code = toUpperCase(code);
    bool found = false;

    for (int i = 0; i < DEPT_COUNT; i++) {
        if (toUpperCase(departments[i].code) == code) {
            cout << "\nDepartment : " << departments[i].code << '\n';
            cout << "Building   : " << departments[i].building << '\n';
            cout << "Floor      : " << departments[i].floor << '\n';
            found = true;
        }
    }

    if (!found) {
        cout << "[ERROR] Department not found. Check the short form.\n";
    }
}

int main() {
    addRoad(0, 1, 230);   // First Gate - Administrative Building
    addRoad(0, 5, 450);   // First Gate - Academic Building 2
    addRoad(1, 2, 30);    // Administrative - Multipurpose
    addRoad(1, 3, 290);   // Administrative - Cafeteria
    addRoad(1, 11, 290);  // Administrative - Temple
    addRoad(2, 3, 90);    // Multipurpose - Cafeteria
    addRoad(2, 4, 220);   // Multipurpose - Academic Building 1
    addRoad(3, 4, 110);   // Cafeteria - Academic Building 1
    addRoad(3, 5, 200);   // Cafeteria - Academic Building 2
    addRoad(4, 5, 260);   // Academic Building 1 - Academic Building 2
    addRoad(4, 6, 160);   // Academic Building 1 - Academic Building 3
    addRoad(5, 6, 190);   // Academic Building 2 - Academic Building 3
    addRoad(5, 10, 450);  // Academic Building 2 - Mosque
    addRoad(6, 7, 40);    // Academic Building 3 - Mannan Hall
    addRoad(7, 8, 70);    // Mannan Hall - Osman Hadi Hall
    addRoad(4, 8, 110);   // Academic Building 1 - Osman Hadi Hall
    addRoad(7, 9, 180);   // Mannan Hall - Abrar Fahad Hall
    addRoad(9, 10, 700);  // Abrar Fahad Hall - Mosque
    addRoad(10, 11, 500); // Mosque - Temple

    int choice;

    do {
        cout << "\n================================================\n";
        cout << "       MBSTU CAMPUS NAVIGATION SYSTEM\n";
        cout << "================================================\n";
        cout << "1. Show All Locations\n";
        cout << "2. Find Shortest Route\n";
        cout << "3. Show Known Road Connections\n";
        cout << "4. All Academic Buildings & Departments\n";
        cout << "5. Department & Floor Finder\n";
        cout << "0. Exit\n";
        cout << "------------------------------------------------\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "[ERROR] Enter a number from 0 to 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                showLocations();
                break;
            case 2:
                findShortestRoute();
                break;
            case 3:
                showRoads();
                break;
            case 4:
                showDepartments();
                break;
            case 5:
                findDepartment();
                break;
            case 0:
                cout << "\nThank you for using MBSTU Campus Navigation!\n";
                break;
            default:
                cout << "[ERROR] Invalid choice. Select 0 to 5.\n";
        }

    } while (choice != 0);

    return 0;
}