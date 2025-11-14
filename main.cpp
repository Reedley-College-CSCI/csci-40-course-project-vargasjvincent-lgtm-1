// CSCI-40 Final Project
// Author: Vincent Vargas

/* 
 Give user an easy  and accessible main menu that gives options to compare 
 different stats from across 20 seasons for the Dallas Cowboys. Also have the 
 ability to save stats in a file and add stats to the data.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// struct to hold each seasons stats
struct SeasonStats {
    int year;
    int wins;
    int losses;
    int ties;
    double ppg;
    double oppPpg;
    string playoffSuccess;
};

int readStats (SeasonStats cowboysStats[], const int MAX_ENTRIES); //function to read data from file into array of structs
void printAllStats(SeasonStats cowboysStats[], int entries);  //function to print all data cuurently in SeasonStats struct

int main() {
const int MAX_ENTRIES = 100;
SeasonStats cowboysStats[MAX_ENTRIES];
cout << "Hi" << endl;
int entries = readStats(cowboysStats, MAX_ENTRIES);
printAllStats(cowboysStats, entries);







    return 0;
}

int readStats (SeasonStats cowboysStats[], const int MAX_ENTRIES) {
    ifstream inputFile ("cowboys_stats.txt");

    if(!inputFile) {
        cout << "Error, could not open file :(" << endl;
        return -1;
    }
    int numEntries = 0;
    while (numEntries < MAX_ENTRIES && inputFile 
        >> cowboysStats[numEntries].year 
        >> cowboysStats[numEntries].wins 
        >> cowboysStats[numEntries].losses
        >> cowboysStats[numEntries].ties 
        >> cowboysStats[numEntries].ppg 
        >> cowboysStats[numEntries].oppPpg) {
        getline(inputFile >> ws, cowboysStats[numEntries].playoffSuccess);
        numEntries++;
    }
    inputFile.close();
    return numEntries;
    }

    void printAllStats(SeasonStats cowboysStats[], int entries) {
        cout << "================ Dallas Cowboys Total Seasons Stats ================" << "\n\n";
        cout << left;
        cout << "|Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|" << endl;

        for(int i = 0; i < entries; ++i) {
            cout << setw(10) << cowboysStats[i].year
             << setw(10) << cowboysStats[i].wins
             << setw(10) << cowboysStats[i].losses
             << setw(10) << cowboysStats[i].ties
             << setw(13) << cowboysStats[i].ppg
             << setw(13) << cowboysStats[i].oppPpg
             << setw(35) << cowboysStats[i].playoffSuccess 
             << endl;
        }
    }
