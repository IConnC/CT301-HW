#include "Workday.h"
#include "Event.h"
#include "Priority_Event.h"
#include "Holiday.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool less (Event a, Event b) { return (a < b); }

int main() {
    Workday w1("Bingo");
    Workday w2("Generic Store", 200);
    Workday w3("School", "2025-12-25");
    Workday w4("The Big Job", "tomorrow", 200000.01);
    Workday w5("The Mission", 2552, 7, 19);
    // Basic "<<" test
    cout << w1 << "\n\n" << w2 << endl;
    // Basic Comparison tests
    // True/False/False
    cout << boolalpha << (w1 < w2) << "/" << (w2 < w1) << "/" << (w3 < w2) << endl;
    //Uncomment these lines to add tests with Priority Events, No tests will be provided for Holiday
    // Priority_Event p1;
    // Priority_Event p2("Simple");
    // Priority_Event p3("Low Prio", 200);
    // Priority_Event p4("Simple", "2025-12-25", 7);
    // Basic "<<" test
    // cout << p1 << "\n\n" << p2 << endl;
    // Basic comparisons
    // false/false/true
    // cout << (p1 < p2) << "/" << (p2 < p3) << "/" << (p3 < p1) << endl;
    return 0;
}