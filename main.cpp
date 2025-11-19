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

int readStats(SeasonStats cowboysStats[], const int MAX_ENTRIES); //function to read data from file into array of structs
void printAllStats(SeasonStats cowboysStats[], int entries);  //function to print all data cuurently in SeasonStats struct
int findUserSeason(SeasonStats cowboysStats[], int entries, int year); // chose to make this function to call it in other functions to find what 
//seaons they want to compare, better than doing it over and over in different functions
void compare2Seasons(SeasonStats cowboysStats[], int entries); // function to compare two seasons, uses findUser season to find desired seasons 

int main() {
const int MAX_ENTRIES = 100;
SeasonStats cowboysStats[MAX_ENTRIES];
cout << "Hi" << endl;
int entries = readStats(cowboysStats, MAX_ENTRIES);
//printAllStats(cowboysStats, entries);
compare2Seasons(cowboysStats, entries);







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

    int findUserSeason(SeasonStats cowboysStats[], int entries, int year) {
        for (int i = 0; i < entries; i++) {
            if (cowboysStats[i].year == year) {
                return i;
            }
        }
        return -1; // year not found
    }

    void compare2Seasons(SeasonStats cowboysStats[], int entries) {
        int year1;
        int year2;
        int season1;
        int season2;

        cout << "Great! You want to compare 2 seasons of the Dallas Cowboys." << endl;

        while (true) {
             cout << "Enter the year of first season (2005-2024): ";
             cin >> year1;
             cout << "\nOkay, now the year of the other season (2005-2024):  ";
             cin >> year2;
             season1 = findUserSeason(cowboysStats, entries, year1);
             season2 = findUserSeason(cowboysStats, entries, year2);

             if (season1 == -1 || season2 == -1) {
                cout << "One of the years you entered is not in the data, try again." << endl;
                continue;
             }

             if (year1 == year2) {
                cout << "You entered the same year, try again." << endl;
                continue;
             }
             break;     
        }

        cout << "Here is your comparasion report!" << endl;
        cout << left;
        cout << "|Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|" << endl;
        cout << setw(10) << cowboysStats[season1].year
             << setw(10) << cowboysStats[season1].wins
             << setw(10) << cowboysStats[season1].losses
             << setw(10) << cowboysStats[season1].ties
             << setw(13) << cowboysStats[season1].ppg
             << setw(13) << cowboysStats[season1].oppPpg
             << setw(35) << cowboysStats[season1].playoffSuccess 
             << endl;

             cout << setw(10) << cowboysStats[season2].year
             << setw(10) << cowboysStats[season2].wins
             << setw(10) << cowboysStats[season2].losses
             << setw(10) << cowboysStats[season2].ties
             << setw(13) << cowboysStats[season2].ppg
             << setw(13) << cowboysStats[season2].oppPpg
             << setw(35) << cowboysStats[season2].playoffSuccess 
             << endl;
    
    }
             