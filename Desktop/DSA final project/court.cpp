#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <string>
#include <cctype>

using namespace std;

// -------------------- Case Structure --------------------
struct Case
{
    int caseId;
    string title;
    string type;
    int priority; // Higher value = More urgent

    bool operator<(const Case& other) const
    {
        return caseId < other.caseId;
    }
};

// -------------------- Global Data --------------------
vector<Case> allCases;
queue<Case> registrationQueue;
priority_queue<pair<int, Case>> urgentQueue;

map<int, vector<int>> precedentGraph;
map<int, vector<int>> appealGraph;
map<int, string> caseStatusMap;

// -------------------- Register Case --------------------
void registerCase()
{
    Case c;

    cout << "\nEnter Case ID: ";
    cin >> c.caseId;

    cin.ignore();

    cout << "Enter Case Title: ";
    getline(cin, c.title);

    cout << "Enter Case Type: ";
    getline(cin, c.type);

    cout << "Enter Priority (1-10): ";
    cin >> c.priority;

    registrationQueue.push(c);
    allCases.push_back(c);
    caseStatusMap[c.caseId] = "Registered";

    if (c.priority >= 7)
    {
        urgentQueue.push({c.priority, c});
    }

    cout << "\nCase Registered Successfully.\n";
}

// -------------------- Process Filing Queue --------------------
void processRegistrationQueue()
{
    if (registrationQueue.empty())
    {
        cout << "\nNo cases waiting.\n";
        return;
    }

    Case c = registrationQueue.front();
    registrationQueue.pop();

    cout << "\nProcessing Case:\n";
    cout << "Case ID : " << c.caseId << endl;
    cout << "Title   : " << c.title << endl;
    cout << "Status  : " << (caseStatusMap.count(c.caseId) ? caseStatusMap[c.caseId] : "Unknown") << endl;
}

// -------------------- Handle Urgent Cases --------------------
void handleUrgentCases()
{
    if (urgentQueue.empty())
    {
        cout << "\nNo urgent cases.\n";
        return;
    }

    auto topCase = urgentQueue.top();
    urgentQueue.pop();

    Case c = topCase.second;

    cout << "\nMost Urgent Case:\n";
    cout << "Case ID : " << c.caseId << endl;
    cout << "Title   : " << c.title << endl;
    cout << "Priority: " << c.priority << endl;
    cout << "Status  : " << (caseStatusMap.count(c.caseId) ? caseStatusMap[c.caseId] : "Unknown") << endl;
}

// -------------------- Binary Search --------------------
bool compareCase(Case a, Case b)
{
    return a.caseId < b.caseId;
}

void searchCase()
{
    if (allCases.empty())
    {
        cout << "\nNo cases available.\n";
        return;
    }

    sort(allCases.begin(), allCases.end(), compareCase);

    int target;

    cout << "\nEnter Case ID to Search: ";
    cin >> target;

    int low = 0;
    int high = allCases.size() - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (allCases[mid].caseId == target)
        {
            cout << "\nCase Found\n";
            cout << "Case ID : " << allCases[mid].caseId << endl;
            cout << "Title   : " << allCases[mid].title << endl;
            cout << "Type    : " << allCases[mid].type << endl;
            cout << "Status  : " << (caseStatusMap.count(allCases[mid].caseId) ? caseStatusMap[allCases[mid].caseId] : "Unknown") << endl;
            return;
        }

        if (allCases[mid].caseId < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    cout << "\nCase Not Found.\n";
}

// -------------------- Add Legal Citation --------------------
void addCitation()
{
    int caseA, caseB;

    cout << "\nEnter Case ID: ";
    cin >> caseA;

    cout << "Enter Referenced Case ID: ";
    cin >> caseB;

    precedentGraph[caseA].push_back(caseB);

    cout << "\nCitation Added Successfully.\n";
}

// -------------------- Display Citation Graph --------------------
void showPrecedents()
{
    cout << "\nLegal Precedent Graph\n";

    for (auto x : precedentGraph)
    {
        cout << "Case " << x.first << " cites -> ";

        for (int child : x.second)
        {
            cout << child << " ";
        }

        cout << endl;
    }
}

// -------------------- Appeal Tracking --------------------
void addAppeal()
{
    int lowerCourtCase, higherCourtCase;

    cout << "\nEnter Lower Court Case ID: ";
    cin >> lowerCourtCase;

    cout << "Enter Higher Court Appeal Case ID: ";
    cin >> higherCourtCase;

    appealGraph[lowerCourtCase].push_back(higherCourtCase);

    cout << "\nAppeal Added.\n";
}

// -------------------- DFS --------------------
void dfs(int current, map<int, bool>& visited)
{
    visited[current] = true;

    cout << current << " ";

    for (int next : appealGraph[current])
    {
        if (!visited[next])
        {
            dfs(next, visited);
        }
    }
}

void trackAppeal()
{
    int startCase;

    cout << "\nEnter Starting Case ID: ";
    cin >> startCase;

    map<int, bool> visited;

    cout << "\nAppeal Journey:\n";

    dfs(startCase, visited);

    cout << endl;
}

// Helper function for DFS cycle detection in precedent graph
bool detectCycleDFS(int node, map<int, vector<int>>& adj, map<int, int>& visited)
{
    visited[node] = 1; // visiting

    for (int neighbor : adj[node])
    {
        if (visited[neighbor] == 1)
        {
            return true;
        }
        if (visited[neighbor] == 0)
        {
            if (detectCycleDFS(neighbor, adj, visited))
                return true;
        }
    }

    visited[node] = 2; // fully visited
    return false;
}

void detectCircularCitations()
{
    map<int, int> visited;
    
    for (auto const& pair : precedentGraph)
    {
        visited[pair.first] = 0;
        for (int neighbor : pair.second)
        {
            if (visited.find(neighbor) == visited.end())
            {
                visited[neighbor] = 0;
            }
        }
    }

    bool hasCycle = false;
    for (auto const& pair : precedentGraph)
    {
        int startNode = pair.first;
        if (visited[startNode] == 0)
        {
            if (detectCycleDFS(startNode, precedentGraph, visited))
            {
                hasCycle = true;
                break;
            }
        }
    }

    if (hasCycle)
    {
        cout << "\n[ALERT] Circular citations (precedent dependency cycle) detected in the system!\n";
    }
    else
    {
        cout << "\n[SUCCESS] No circular citations detected. Precedent structure is clean.\n";
    }
}

bool comparePriority(const Case& a, const Case& b)
{
    if (a.priority != b.priority)
    {
        return a.priority > b.priority;
    }
    return a.caseId < b.caseId;
}

void listCasesSortedByPriority()
{
    if (allCases.empty())
    {
        cout << "\nNo cases available.\n";
        return;
    }

    vector<Case> sortedCases = allCases;
    sort(sortedCases.begin(), sortedCases.end(), comparePriority);

    cout << "\n========== All Cases (Sorted by Priority) ==========\n";
    for (const Case& c : sortedCases)
    {
        string status = caseStatusMap.count(c.caseId) ? caseStatusMap[c.caseId] : "Unknown";
        cout << "ID: " << c.caseId << " | Title: " << c.title 
             << " | Type: " << c.type << " | Priority: " << c.priority 
             << " | Status: " << status << "\n";
    }
}

void filterCasesByType()
{
    if (allCases.empty())
    {
        cout << "\nNo cases available to filter.\n";
        return;
    }

    cin.ignore();
    string targetType;
    cout << "\nEnter Case Type to Filter: ";
    getline(cin, targetType);

    string lowerTarget = targetType;
    transform(lowerTarget.begin(), lowerTarget.end(), lowerTarget.begin(), ::tolower);

    bool foundAny = false;
    cout << "\n========== Matching Cases for Type \"" << targetType << "\" ==========\n";
    for (const Case& c : allCases)
    {
        string lowerType = c.type;
        transform(lowerType.begin(), lowerType.end(), lowerType.begin(), ::tolower);

        if (lowerType.find(lowerTarget) != string::npos)
        {
            foundAny = true;
            string status = caseStatusMap.count(c.caseId) ? caseStatusMap[c.caseId] : "Unknown";
            cout << "ID: " << c.caseId << " | Title: " << c.title 
                 << " | Priority: " << c.priority << " | Status: " << status << "\n";
        }
    }

    if (!foundAny)
    {
        cout << "No cases found matching type \"" << targetType << "\".\n";
    }
}

void updateCaseStatus()
{
    int targetId;
    cout << "\nEnter Case ID to update status: ";
    cin >> targetId;

    bool exists = false;
    for (const Case& c : allCases)
    {
        if (c.caseId == targetId)
        {
            exists = true;
            break;
        }
    }

    if (!exists)
    {
        cout << "\nCase ID not found in the system.\n";
        return;
    }

    cout << "Current Status: " << (caseStatusMap.count(targetId) ? caseStatusMap[targetId] : "Unknown") << "\n";
    cout << "Select New Status:\n";
    cout << "1. Registered\n";
    cout << "2. Under Hearing\n";
    cout << "3. Resolved\n";
    cout << "Choose option: ";
    int opt;
    cin >> opt;

    string newStatus;
    if (opt == 1) newStatus = "Registered";
    else if (opt == 2) newStatus = "Under Hearing";
    else if (opt == 3) newStatus = "Resolved";
    else {
        cout << "\nInvalid choice. Status not updated.\n";
        return;
    }

    caseStatusMap[targetId] = newStatus;
    cout << "\nStatus updated successfully to \"" << newStatus << "\".\n";
}

// -------------------- Dashboard --------------------
void dashboard()
{
    cout << "\n========== Judicial Case Management System ==========\n";
    cout << "1. Register New Case\n";
    cout << "2. Process Registration Queue\n";
    cout << "3. Handle Urgent Case\n";
    cout << "4. Search Case (Binary Search)\n";
    cout << "5. Add Legal Citation\n";
    cout << "6. Show Precedent Graph\n";
    cout << "7. Add Appeal\n";
    cout << "8. Track Appeal (DFS)\n";
    cout << "9. List Cases Sorted by Priority\n";
    cout << "10. Filter Cases by Type\n";
    cout << "11. Update Case Status\n";
    cout << "12. Detect Circular Citations\n";
    cout << "13. Exit\n";
    cout << "Choose Option: ";
}

// -------------------- Load Sample Data --------------------
void loadSampleData()
{
    Case c1 = {101, "State vs. John Doe (Theft)", "Criminal", 5};
    Case c2 = {102, "Land Dispute: Smith vs. Jones", "Civil", 3};
    Case c3 = {103, "Company A vs. Company B (Patent)", "IP", 8};
    Case c4 = {104, "State vs. Richard Roe (Murder)", "Criminal", 10};
    Case c5 = {105, "Tax Evasion: IRS vs. Miller", "Financial", 6};

    allCases.push_back(c1);
    allCases.push_back(c2);
    allCases.push_back(c3);
    allCases.push_back(c4);
    allCases.push_back(c5);

    caseStatusMap[101] = "Registered";
    caseStatusMap[102] = "Registered";
    caseStatusMap[103] = "Registered";
    caseStatusMap[104] = "Registered";
    caseStatusMap[105] = "Registered";

    registrationQueue.push(c1);
    registrationQueue.push(c2);
    registrationQueue.push(c5);

    urgentQueue.push({c3.priority, c3});
    urgentQueue.push({c4.priority, c4});

    precedentGraph[103] = {101, 102};
    precedentGraph[105] = {102};

    appealGraph[101] = {201};
    appealGraph[201] = {301};

    cout << "\n[System] Sample data loaded successfully.\n";
}

// -------------------- Login --------------------
bool login()
{
    string username, password;
    int attempts = 3;
    cout << "\n================= COURT PORTAL LOGIN =================\n";
    while (attempts > 0)
    {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (username == "admin" && password == "admin123")
        {
            cout << "\nLogin Successful! Welcome to the Judicial Portal.\n\n";
            return true;
        }
        else
        {
            attempts--;
            cout << "Invalid credentials! Attempts remaining: " << attempts << "\n\n";
        }
    }
    cout << "Too many failed attempts. Access Denied.\n";
    return false;
}

// -------------------- Main --------------------
int main()
{
    loadSampleData();
    if (!login())
    {
        return 0;
    }
    int choice;

    do
    {
        dashboard();
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerCase();
            break;

        case 2:
            processRegistrationQueue();
            break;

        case 3:
            handleUrgentCases();
            break;

        case 4:
            searchCase();
            break;

        case 5:
            addCitation();
            break;

        case 6:
            showPrecedents();
            break;

        case 7:
            addAppeal();
            break;

        case 8:
            trackAppeal();
            break;

        case 9:
            listCasesSortedByPriority();
            break;

        case 10:
            filterCasesByType();
            break;

        case 11:
            updateCaseStatus();
            break;

        case 12:
            detectCircularCitations();
            break;

        case 13:
            cout << "\nThank You.\n";
            break;

        default:
            cout << "\nInvalid Choice.\n";
        }

    } while (choice != 13);

    return 0;
}