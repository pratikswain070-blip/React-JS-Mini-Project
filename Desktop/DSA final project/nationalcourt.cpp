#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
using namespace std;

// ---------- Case Structure ----------
struct Case {
    int id;
    string title;
    string type;      // Criminal, Civil, Constitutional, Commercial
    int priority;      // 1-10 (higher = more urgent)
    string status;     // Registered, Scheduled, Under Hearing, Resolved
    string hearingDate;
};

// ---------- Global Data ----------
vector<Case> allCases;
queue<Case> filingQueue;                           // Queue for registration
priority_queue<pair<int,int>> urgentQueue;          // Priority Queue {priority, caseId}
map<int, vector<int>> citationGraph;               // Graph for precedents
map<int, vector<int>> appealGraph;                 // Graph for appeals

// ---------- Helper: Find case by ID ----------
int findCaseIndex(int id) {
    for (int i = 0; i < allCases.size(); i++)
        if (allCases[i].id == id) return i;
    return -1;
}

// ========== 1. CASE REGISTRATION (Queue) ==========
void registerCase() {
    Case c;
    cout << "\n--- Register New Case ---\n";
    cout << "Enter Case ID: ";
    cin >> c.id;

    if (findCaseIndex(c.id) != -1) {
        cout << "Error: Case ID already exists!\n";
        return;
    }

    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, c.title);
    cout << "Enter Type (Criminal/Civil/Constitutional/Commercial): ";
    getline(cin, c.type);
    cout << "Enter Priority (1-10): ";
    cin >> c.priority;
    c.status = "Registered";
    c.hearingDate = "Not Scheduled";

    filingQueue.push(c);
    allCases.push_back(c);

    if (c.priority >= 7)
        urgentQueue.push({c.priority, c.id});

    cout << "Case " << c.id << " registered successfully!\n";
}

// ========== 2. PROCESS FILING QUEUE (Queue - FIFO) ==========
void processQueue() {
    if (filingQueue.empty()) {
        cout << "\nNo cases in filing queue.\n";
        return;
    }
    Case c = filingQueue.front();
    filingQueue.pop();
    cout << "\n--- Processing Case (FIFO Order) ---\n";
    cout << "ID: " << c.id << " | Title: " << c.title
         << " | Type: " << c.type << " | Priority: " << c.priority << endl;
}

// ========== 3. URGENT MATTER HANDLING (Priority Queue) ==========
void handleUrgent() {
    if (urgentQueue.empty()) {
        cout << "\nNo urgent cases pending.\n";
        return;
    }
    auto top = urgentQueue.top();
    urgentQueue.pop();

    int idx = findCaseIndex(top.second);
    if (idx != -1) {
        cout << "\n--- Highest Priority Case ---\n";
        cout << "ID: " << allCases[idx].id << " | Title: " << allCases[idx].title
             << " | Priority: " << top.first
             << " | Status: " << allCases[idx].status << endl;
    } else {
        cout << "Case ID: " << top.second << " | Priority: " << top.first << endl;
    }
}

// ========== 4. CASE RETRIEVAL (Binary Search) ==========
void searchCase() {
    if (allCases.empty()) {
        cout << "\nNo cases in system.\n";
        return;
    }

    sort(allCases.begin(), allCases.end(),
         [](const Case& a, const Case& b) { return a.id < b.id; });

    int target;
    cout << "\nEnter Case ID to search: ";
    cin >> target;

    int low = 0, high = allCases.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (allCases[mid].id == target) {
            cout << "\n--- Case Found ---\n";
            cout << "ID       : " << allCases[mid].id << endl;
            cout << "Title    : " << allCases[mid].title << endl;
            cout << "Type     : " << allCases[mid].type << endl;
            cout << "Priority : " << allCases[mid].priority << endl;
            cout << "Status   : " << allCases[mid].status << endl;
            cout << "Hearing  : " << allCases[mid].hearingDate << endl;
            return;
        }
        if (allCases[mid].id < target) low = mid + 1;
        else high = mid - 1;
    }
    cout << "Case not found.\n";
}

// ========== 5. ADD LEGAL CITATION (Graph) ==========
void addCitation() {
    int from, to;
    cout << "\nEnter Case ID: ";
    cin >> from;
    cout << "Enter Cited Case ID: ";
    cin >> to;
    citationGraph[from].push_back(to);
    cout << "Citation added: Case " << from << " cites Case " << to << endl;
}

// ========== 6. SHOW PRECEDENT GRAPH (Graph) ==========
void showPrecedents() {
    if (citationGraph.empty()) {
        cout << "\nNo citations recorded.\n";
        return;
    }
    cout << "\n--- Legal Precedent Graph ---\n";
    for (auto& p : citationGraph) {
        cout << "Case " << p.first << " cites -> ";
        for (int c : p.second) cout << c << " ";
        cout << endl;
    }
}

// ========== 7. ADD APPEAL LINK (Graph) ==========
void addAppeal() {
    int lower, higher;
    cout << "\nEnter Lower Court Case ID: ";
    cin >> lower;
    cout << "Enter Higher Court Case ID: ";
    cin >> higher;
    appealGraph[lower].push_back(higher);
    cout << "Appeal linked: " << lower << " -> " << higher << endl;
}

// ========== 8. APPEAL TRACKING (DFS) ==========
void dfs(int node, map<int, bool>& visited) {
    visited[node] = true;
    cout << node << " -> ";
    for (int next : appealGraph[node]) {
        if (!visited[next])
            dfs(next, visited);
    }
}

void trackAppeal() {
    int start;
    cout << "\nEnter Starting Case ID: ";
    cin >> start;
    map<int, bool> visited;
    cout << "\nAppeal Journey: ";
    dfs(start, visited);
    cout << "END\n";
}

// ========== 9. VIEW ALL CASES (Sorted by Priority) ==========
void viewAllCases() {
    if (allCases.empty()) {
        cout << "\nNo cases in system.\n";
        return;
    }

    vector<Case> sorted = allCases;
    sort(sorted.begin(), sorted.end(),
         [](const Case& a, const Case& b) { return a.priority > b.priority; });

    cout << "\n--- All Cases (Sorted by Priority: High to Low) ---\n";
    cout << "----------------------------------------------------------------------\n";
    for (auto& c : sorted) {
        cout << "ID: " << c.id << " | " << c.title
             << " | Type: " << c.type
             << " | Priority: " << c.priority
             << " | Status: " << c.status << endl;
    }
    cout << "----------------------------------------------------------------------\n";
    cout << "Total Cases: " << sorted.size() << endl;
}

// ========== 10. FILTER CASES BY TYPE ==========
void filterByType() {
    if (allCases.empty()) {
        cout << "\nNo cases in system.\n";
        return;
    }

    cin.ignore();
    string target;
    cout << "\nEnter Type to filter (Criminal/Civil/Constitutional/Commercial): ";
    getline(cin, target);

    // Case-insensitive comparison
    string lowerTarget = target;
    transform(lowerTarget.begin(), lowerTarget.end(), lowerTarget.begin(), ::tolower);

    bool found = false;
    cout << "\n--- Cases of Type: " << target << " ---\n";
    for (auto& c : allCases) {
        string lowerType = c.type;
        transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);
        if (lowerType.find(lowerTarget) != string::npos) {
            cout << "ID: " << c.id << " | " << c.title
                 << " | Priority: " << c.priority
                 << " | Status: " << c.status << endl;
            found = true;
        }
    }
    if (!found) cout << "No cases found for type \"" << target << "\".\n";
}

// ========== 11. UPDATE CASE STATUS ==========
void updateStatus() {
    int id;
    cout << "\nEnter Case ID: ";
    cin >> id;

    int idx = findCaseIndex(id);
    if (idx == -1) {
        cout << "Case not found.\n";
        return;
    }

    cout << "Current Status: " << allCases[idx].status << endl;
    cout << "Select New Status:\n";
    cout << "  1. Registered\n";
    cout << "  2. Scheduled\n";
    cout << "  3. Under Hearing\n";
    cout << "  4. Resolved\n";
    cout << "Choice: ";
    int opt;
    cin >> opt;

    switch (opt) {
        case 1: allCases[idx].status = "Registered"; break;
        case 2: allCases[idx].status = "Scheduled"; break;
        case 3: allCases[idx].status = "Under Hearing"; break;
        case 4: allCases[idx].status = "Resolved"; break;
        default: cout << "Invalid choice.\n"; return;
    }
    cout << "Status updated to \"" << allCases[idx].status << "\".\n";
}

// ========== 12. SCHEDULE HEARING ==========
void scheduleHearing() {
    int id;
    cout << "\nEnter Case ID: ";
    cin >> id;

    int idx = findCaseIndex(id);
    if (idx == -1) {
        cout << "Case not found.\n";
        return;
    }

    cin.ignore();
    cout << "Enter Hearing Date (e.g. 2026-07-15): ";
    getline(cin, allCases[idx].hearingDate);
    allCases[idx].status = "Scheduled";

    cout << "Hearing scheduled for Case " << id
         << " on " << allCases[idx].hearingDate << endl;
}

// ========== 13. DASHBOARD STATISTICS ==========
void showDashboard() {
    int total = allCases.size();
    int registered = 0, scheduled = 0, hearing = 0, resolved = 0;
    int criminal = 0, civil = 0, constitutional = 0, commercial = 0;
    int urgent = 0;

    for (auto& c : allCases) {
        if (c.status == "Registered") registered++;
        else if (c.status == "Scheduled") scheduled++;
        else if (c.status == "Under Hearing") hearing++;
        else if (c.status == "Resolved") resolved++;

        string t = c.type;
        transform(t.begin(), t.end(), t.begin(), ::tolower);
        if (t == "criminal") criminal++;
        else if (t == "civil") civil++;
        else if (t == "constitutional") constitutional++;
        else if (t == "commercial") commercial++;

        if (c.priority >= 7) urgent++;
    }

    cout << "\n============= COURT DASHBOARD =============\n";
    cout << " Total Cases       : " << total << endl;
    cout << "-------------------------------------------\n";
    cout << " By Status:\n";
    cout << "   Registered      : " << registered << endl;
    cout << "   Scheduled       : " << scheduled << endl;
    cout << "   Under Hearing   : " << hearing << endl;
    cout << "   Resolved        : " << resolved << endl;
    cout << "-------------------------------------------\n";
    cout << " By Type:\n";
    cout << "   Criminal        : " << criminal << endl;
    cout << "   Civil           : " << civil << endl;
    cout << "   Constitutional  : " << constitutional << endl;
    cout << "   Commercial      : " << commercial << endl;
    cout << "-------------------------------------------\n";
    cout << " Urgent Cases (P>=7): " << urgent << endl;
    cout << " Pending in Queue   : " << filingQueue.size() << endl;
    cout << " Citations Recorded : " << citationGraph.size() << endl;
    cout << " Appeal Links       : " << appealGraph.size() << endl;
    cout << "=============================================\n";
}

// ========== 14. MOST INFLUENTIAL CASE (Most Cited) ==========
void mostInfluential() {
    if (citationGraph.empty()) {
        cout << "\nNo citations recorded.\n";
        return;
    }

    map<int, int> citedCount;
    for (auto& p : citationGraph)
        for (int c : p.second)
            citedCount[c]++;

    int maxId = -1, maxCount = 0;
    for (auto& p : citedCount) {
        if (p.second > maxCount) {
            maxCount = p.second;
            maxId = p.first;
        }
    }

    cout << "\n--- Most Influential Judgment ---\n";
    cout << "Case ID: " << maxId << " | Cited " << maxCount << " time(s)\n";

    int idx = findCaseIndex(maxId);
    if (idx != -1)
        cout << "Title: " << allCases[idx].title << endl;
}

// ========== 15. DETECT CIRCULAR CITATIONS ==========
bool dfsCycle(int node, map<int, int>& state) {
    state[node] = 1;  // visiting
    for (int next : citationGraph[node]) {
        if (state[next] == 1) return true;       // back edge = cycle
        if (state[next] == 0 && dfsCycle(next, state)) return true;
    }
    state[node] = 2;  // done
    return false;
}

void detectCircularCitations() {
    map<int, int> state;  // 0=unvisited, 1=visiting, 2=done
    for (auto& p : citationGraph) {
        state[p.first] = 0;
        for (int c : p.second)
            if (state.find(c) == state.end()) state[c] = 0;
    }

    bool hasCycle = false;
    for (auto& p : citationGraph) {
        if (state[p.first] == 0 && dfsCycle(p.first, state)) {
            hasCycle = true;
            break;
        }
    }

    if (hasCycle)
        cout << "\n[WARNING] Circular citation detected! Review precedent links.\n";
    else
        cout << "\n[OK] No circular citations. Precedent structure is valid.\n";
}

// ========== LOAD SAMPLE DATA ==========
#include "sample_data.h"

// ========== LOGIN FUNCTION ==========
bool login() {
    string username, password;
    int attempts = 3;
    cout << "\n================= COURT PORTAL LOGIN =================\n";
    while (attempts > 0) {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (username == "admin" && password == "admin123") {
            cout << "\nLogin Successful! Welcome to the Judicial Portal.\n\n";
            return true;
        } else {
            attempts--;
            cout << "Invalid credentials! Attempts remaining: " << attempts << "\n\n";
        }
    }
    cout << "Too many failed attempts. Access Denied.\n";
    return false;
}

// ========== MAIN MENU ==========
int main() {
    loadSampleData();
    if (!login()) {
        return 0;
    }
    int mainChoice;

    do {
        cout << "\n========== National Judicial Case Management System ==========\n";
        cout << "  1. CASE MANAGEMENT\n";
        cout << "  2. LEGAL ANALYTICS\n";
        cout << "  3. APPEAL TRACKING\n";
        cout << "  4. DASHBOARD\n";
        cout << "  5. Exit\n";
        cout << "===============================================================\n";
        cout << "  Choose option: ";
        cin >> mainChoice;

        if (mainChoice == 1) {
            int subChoice;
            do {
                cout << "\n--- Case Management ---\n";
                cout << "  1. Register New Case              (Queue)\n";
                cout << "  2. Process Filing Queue            (Queue - FIFO)\n";
                cout << "  3. Handle Urgent Case              (Priority Queue)\n";
                cout << "  4. Search Case by ID               (Binary Search)\n";
                cout << "  5. View All Cases                  (Sorted by Priority)\n";
                cout << "  6. Filter Cases by Type\n";
                cout << "  7. Update Case Status\n";
                cout << "  8. Schedule Hearing\n";
                cout << "  9. Go Back\n";
                cout << "  Choose option: ";
                cin >> subChoice;

                switch (subChoice) {
                    case 1:  registerCase();    break;
                    case 2:  processQueue();    break;
                    case 3:  handleUrgent();    break;
                    case 4:  searchCase();      break;
                    case 5:  viewAllCases();    break;
                    case 6:  filterByType();    break;
                    case 7:  updateStatus();    break;
                    case 8:  scheduleHearing(); break;
                    case 9:  break;
                    default: cout << "\nInvalid choice.\n";
                }
            } while (subChoice != 9);

        } else if (mainChoice == 2) {
            int subChoice;
            do {
                cout << "\n--- Legal Analytics ---\n";
                cout << "  1. Add Legal Citation               (Graph)\n";
                cout << "  2. Show Precedent Graph             (Graph)\n";
                cout << "  3. Most Influential Judgment         (Graph Analysis)\n";
                cout << "  4. Detect Circular Citations         (Cycle Detection)\n";
                cout << "  5. Go Back\n";
                cout << "  Choose option: ";
                cin >> subChoice;

                switch (subChoice) {
                    case 1:  addCitation();             break;
                    case 2:  showPrecedents();          break;
                    case 3:  mostInfluential();         break;
                    case 4:  detectCircularCitations(); break;
                    case 5:  break;
                    default: cout << "\nInvalid choice.\n";
                }
            } while (subChoice != 5);

        } else if (mainChoice == 3) {
            int subChoice;
            do {
                cout << "\n--- Appeal Tracking ---\n";
                cout << "  1. Add Appeal Link                   (Graph)\n";
                cout << "  2. Track Appeal Journey              (DFS)\n";
                cout << "  3. Go Back\n";
                cout << "  Choose option: ";
                cin >> subChoice;

                switch (subChoice) {
                    case 1:  addAppeal();    break;
                    case 2:  trackAppeal();  break;
                    case 3:  break;
                    default: cout << "\nInvalid choice.\n";
                }
            } while (subChoice != 3);

        } else if (mainChoice == 4) {
            int subChoice;
            do {
                cout << "\n--- Dashboard ---\n";
                cout << "  1. Show Dashboard Statistics\n";
                cout << "  2. Go Back\n";
                cout << "  Choose option: ";
                cin >> subChoice;

                switch (subChoice) {
                    case 1:  showDashboard(); break;
                    case 2:  break;
                    default: cout << "\nInvalid choice.\n";
                }
            } while (subChoice != 2);

        } else if (mainChoice == 5) {
            cout << "\nThank you! System closed.\n";
        } else {
            cout << "\nInvalid choice.\n";
        }
    } while (mainChoice != 5);

    return 0;
}
