#ifndef SAMPLE_DATA_H
#define SAMPLE_DATA_H

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>

// This function accesses struct Case and global data structures declared in nationalcourt.cpp.
void loadSampleData() {
    Case cases[] = {
        // Criminal Cases (Priorities: 4-10)
        {101, "State vs. Sharma (Theft Case)", "Criminal", 4, "Registered", "Not Scheduled"},
        {105, "Murder Trial: State vs. Rao", "Criminal", 10, "Registered", "Not Scheduled"},
        {110, "Homicide Case: State vs. Vikram", "Criminal", 10, "Registered", "Not Scheduled"},
        {115, "Assault & Battery: State vs. Verma", "Criminal", 5, "Registered", "Not Scheduled"},

        // Civil Cases (Priorities: 2-4)
        {102, "Land Boundary Dispute: Patel vs. Gupta", "Civil", 3, "Registered", "Not Scheduled"},
        {106, "Property Rights: Desai vs. Mehta", "Civil", 2, "Registered", "Not Scheduled"},
        {111, "Divorce & Custody: Sen vs. Sen", "Civil", 3, "Registered", "Not Scheduled"},
        {112, "Defamation Suit: Kapoor vs. Puri", "Civil", 4, "Registered", "Not Scheduled"},

        // Constitutional Cases (Priorities: 8-9)
        {103, "Bail Application: State vs. Khan", "Constitutional", 9, "Registered", "Not Scheduled"},
        {107, "Fundamental Rights Petition (Freedom of Speech)", "Constitutional", 8, "Registered", "Not Scheduled"},
        {113, "Writ Petition: Environmental Pollution Action", "Constitutional", 9, "Registered", "Not Scheduled"},

        // Commercial / IP Cases (Priorities: 5-8)
        {104, "Trade Fraud: ABC vs. XYZ Corp", "Commercial", 5, "Registered", "Not Scheduled"},
        {108, "Contract Breach: TechCo vs. DataInc", "Commercial", 6, "Registered", "Not Scheduled"},
        {109, "Corporate Tax Evasion: Alpha Ltd", "Commercial", 7, "Registered", "Not Scheduled"},
        {114, "Intellectual Property: TechSoft vs. AppCorp", "Commercial", 8, "Registered", "Not Scheduled"},
        {116, "Bankruptcy Filing: RetailGlobal Group", "Commercial", 6, "Registered", "Not Scheduled"},

        // Circular Citation Demo Cases (To test Option 12 cycle detection)
        {120, "Patent Dispute: Inventions Inc vs. Creators Ltd", "Commercial", 6, "Registered", "Not Scheduled"},
        {121, "Copyright Infringement: MediaHouse vs. NetBroadcasting", "Commercial", 5, "Registered", "Not Scheduled"},
        {122, "Trademark Opposition: BrandA vs. BrandB", "Commercial", 6, "Registered", "Not Scheduled"}
    };

    // Load cases into list, FIFO queue, and priority queue
    for (auto& c : cases) {
        allCases.push_back(c);
        filingQueue.push(c);
        if (c.priority >= 7) {
            urgentQueue.push({c.priority, c.id});
        }
    }

    // Precedent Citations Graph
    // Case 103 (Bail Application) is highly influential and cited 5 times by other cases:
    citationGraph[104] = {103, 101, 102};
    citationGraph[105] = {103, 101};
    citationGraph[107] = {103};
    citationGraph[113] = {103};
    citationGraph[114] = {103, 104, 102};
    
    // Other citations
    citationGraph[108] = {104, 102};
    citationGraph[109] = {104};
    citationGraph[116] = {104, 108};
    citationGraph[115] = {101};

    // Circular Citations Loop (120 -> 121 -> 122 -> 120) to demonstrate cycle detection
    citationGraph[120] = {121};
    citationGraph[121] = {122};
    citationGraph[122] = {120};

    // Appeal Links (Lower Court -> District Court -> High Court -> Supreme Court) for DFS Tracking
    // Journey 1: 101 -> 201 -> 301 -> 401
    appealGraph[101] = {201};
    appealGraph[201] = {301};
    appealGraph[301] = {401};

    // Journey 2: 102 -> 202 -> 302
    appealGraph[102] = {202};
    appealGraph[202] = {302};

    // Journey 3: 105 -> 205 -> 305
    appealGraph[105] = {205};
    appealGraph[205] = {305};

    std::cout << "[Comprehensive dataset loaded: " << sizeof(cases)/sizeof(cases[0]) 
              << " cases, 12 citation links (including a circular loop), and 3 appeal hierarchies]\n";
}

#endif // SAMPLE_DATA_H
