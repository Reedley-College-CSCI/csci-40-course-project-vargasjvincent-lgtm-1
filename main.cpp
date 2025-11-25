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
//seaons they want to compare, better than doing it over and over in different functions, uses LINEAR SEARCH
void compare2Seasons(SeasonStats cowboysStats[], int entries); // function to compare two seasons, uses findUser season to find desired seasons 
int convertPlayoffSuccess(const string playoffResult); // function to convert playoff success into integer value to make easier to compare
void selectionSortWins(SeasonStats cowboysStats[], int entries); // function to sort all seasons by wins and prints them in order
void selectionSortLosses(SeasonStats cowboysStats[], int entries); // function to sort all seasons by losses and prints them in order
void selectionSortTies(SeasonStats cowboysStats[], int entries); // function to sort all seasons by ties and prints them in order
void selectionSortPpg(SeasonStats cowboysStats[], int entries); // function to sort all seasons by PPG and prints them in order
void selectionSortOppPpg(SeasonStats cowboysStats[], int entries); // function to sort all seasons by OPP PPG and prints them in order
void selectionSortPlayoffSuccess(SeasonStats cowboysStats[], int entries); // function to sort all seasons by playoff success and prints them in order

int main() {
const int MAX_ENTRIES = 100;
SeasonStats cowboysStats[MAX_ENTRIES];
cout << "Hi" << endl;
int entries = readStats(cowboysStats, MAX_ENTRIES);
//printAllStats(cowboysStats, entries);
//compare2Seasons(cowboysStats, entries);
//selectionSortWins(cowboysStats, entries);
//selectionSortLosses(cowboysStats, entries);
//selectionSortTies(cowboysStats, entries);
//selectionSortPpg(cowboysStats, entries);
//selectionSortoppPpg(cowboysStats, entries);
selectionSortPlayoffSuccess(cowboysStats, entries);



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
        cout << "*******************************************************************************************" 
        << "*************\n";
        cout << "*\n* ================ Dallas Cowboys Total Seasons Stats ================                                 *";
        cout << "\n*" << setw(103) << "*"
        << "\n*                                                                                                      *";
        cout << left;
        cout << "\n* |Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|"
        << "                   *" << endl;

        for(int i = 0; i < entries; ++i) {
            cout << "* " << setw(10) << cowboysStats[i].year
             << setw(10) << cowboysStats[i].wins
             << setw(10) << cowboysStats[i].losses
             << setw(10) << cowboysStats[i].ties
             << setw(13) << cowboysStats[i].ppg
             << setw(13) << cowboysStats[i].oppPpg
             << setw(35) << cowboysStats[i].playoffSuccess << setw(2) << "*"
             << endl;
        }
         cout << "*******************************************************************************************" 
         << "*************\n";
    }

    int findUserSeason(SeasonStats cowboysStats[], int entries, int year) { // linear seach !
        for (int i = 0; i < entries; i++) {
            if (cowboysStats[i].year == year) {
                return i;
            }
        }
        return -1; // year not found
    }

    int convertPlayoffSuccess(const string playoffResult) {
        if (playoffResult == "Missed Playoffs") return 1;
        if (playoffResult == "Lost Wild Card Round") return 2;
        if (playoffResult == "Lost Divisional Round") return 3;
        if (playoffResult == "Lost Conference Championship") return 4;
        if (playoffResult == "Lost Superbowl") return 5;
        if (playoffResult == "Won Superbowl") return 6;
        return -1;
    }

    void compare2Seasons(SeasonStats cowboysStats[], int entries) {
        int year1;
        int year2;
        int season1;
        int season2;

        cout << "\nGreat! You want to compare 2 seasons of the Dallas Cowboys." << endl;
      
        // big while loop to validate the years that the user enters, makes sure the years exist 
        // or if they entered the same year
        while (true) {
             cout << "\n\nEnter the year of first season (2005-2024): ";
             if (!(cin >> year1)) {
             cin.clear();
             cin.ignore(1000, '\n');
             cout << "Try again, please enter a year in data (2005-2024)" << endl;
             continue;
            }
             cout << "\nOkay, now the year of the other season (2005-2024):  ";
             if (!(cin >> year2)) {
             cin.clear();
             cin.ignore(1000, '\n');
             cout << "Try again, please enter a year in data (2005-2024)" << endl;
             continue;
            }
             season1 = findUserSeason(cowboysStats, entries, year1);
             season2 = findUserSeason(cowboysStats, entries, year2);

             if (season1 == -1 || season2 == -1) {
                cout << "One of the years you entered is not in the data, try again." << endl;
                continue;
             }

             if (season1 == season2) {
                cout << "You entered the same year, try again." << endl;
                continue;
             }
             break;     
        }

        cout << "\nHere is your comparison report!\n " << endl;
         cout << "*******************************************************************************************" 
        << "*************\n";
        cout << "*" << setw(103) << "*"
        << "\n* ====================== " << cowboysStats[season1].year << " and " << cowboysStats[season2].year
        << " Comparison Report ===============================" << setw(22) << "*";
        cout << "\n*" << setw(103) << "*"
        << "\n*                                                                                                      *";
        cout << left;
        cout << "\n* |Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|"
        << "                   *" << endl;

       
            cout << "* " << setw(10) << cowboysStats[season1].year
             << setw(10) << cowboysStats[season1].wins
             << setw(10) << cowboysStats[season1].losses
             << setw(10) << cowboysStats[season1].ties
             << setw(13) << cowboysStats[season1].ppg
             << setw(13) << cowboysStats[season1].oppPpg
             << setw(35) << cowboysStats[season1].playoffSuccess << setw(2) << "*"
             << endl;
              cout << "* " << setw(10) << cowboysStats[season2].year
             << setw(10) << cowboysStats[season2].wins
             << setw(10) << cowboysStats[season2].losses
             << setw(10) << cowboysStats[season2].ties
             << setw(13) << cowboysStats[season2].ppg
             << setw(13) << cowboysStats[season2].oppPpg
             << setw(35) << cowboysStats[season2].playoffSuccess << setw(2) << "*"
             << endl;
         cout << "*******************************************************************************************" 
         << "*************\n";
       

             int winsDifference;
             int lossDifference;
             int tiesDifference;
             double ppgDifference;
             double oppPpgDifference;

             cout << "\nMore in depth analysis:\n";
             if (cowboysStats[season1].wins > cowboysStats[season2].wins) {
             winsDifference = cowboysStats[season1].wins - cowboysStats[season2].wins;
             cout << "In " << cowboysStats[season1].year << " the Cowboys had " << winsDifference
             << " more win/wins than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].wins < cowboysStats[season2].wins) {
             winsDifference = cowboysStats[season2].wins - cowboysStats[season1].wins;
             cout << "In " << cowboysStats[season2].year << " the Cowboys had " << winsDifference
             << " more win/wins than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].wins == cowboysStats[season2].wins) {
             cout << "In " << cowboysStats[season1].year << " the Cowboys had the same amount of wins";
             cout << " as in " << cowboysStats[season2].year << "\n\n";
             }
             if (cowboysStats[season1].losses > cowboysStats[season2].losses) {
             lossDifference = cowboysStats[season1].losses - cowboysStats[season2].losses;
             cout << "In " << cowboysStats[season1].year << " the Cowboys had " << lossDifference
             << " more loss/losses than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].losses < cowboysStats[season2].losses) {
             lossDifference = cowboysStats[season2].losses - cowboysStats[season1].losses;
             cout << "In " << cowboysStats[season2].year << " the Cowboys had " << lossDifference
             << " more loss/losses than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].losses == cowboysStats[season2].losses) {
             cout << "In " << cowboysStats[season1].year << " the Cowboys had the same amount of losses";
             cout << " as in " << cowboysStats[season2].year << "\n\n";
             }
              if (cowboysStats[season1].ties > cowboysStats[season2].ties) {
             tiesDifference = cowboysStats[season1].ties - cowboysStats[season2].ties;
             cout << "In " << cowboysStats[season1].year << " the Cowboys had " << tiesDifference
             << " more tie/ties than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].ties < cowboysStats[season2].ties) {
             tiesDifference = cowboysStats[season2].ties - cowboysStats[season1].ties;
             cout << "In " << cowboysStats[season2].year << " the Cowboys had " << tiesDifference
             << " more tie/ties than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].ties == cowboysStats[season2].ties) {
             cout << "In " << cowboysStats[season1].year << " the Cowboys had the same amount of ties";
             cout << " as in " << cowboysStats[season2].year << "\n\n";
             }
              if (cowboysStats[season1].ppg > cowboysStats[season2].ppg) {
             ppgDifference = cowboysStats[season1].ppg - cowboysStats[season2].ppg;
             cout << "In " << cowboysStats[season1].year << " the Cowboys averaged " << ppgDifference
             << " more PPG than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].ppg < cowboysStats[season2].ppg) {
             ppgDifference = cowboysStats[season2].ppg - cowboysStats[season1].ppg;
              cout << "In " << cowboysStats[season2].year << " the Cowboys averaged " << ppgDifference
             << " more PPG than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].ppg == cowboysStats[season2].ppg) {
             cout << "In " << cowboysStats[season1].year << " the Cowboys had the same PPG";
             cout << " as in " << cowboysStats[season2].year << "\n\n";
             }
             if (cowboysStats[season1].oppPpg > cowboysStats[season2].oppPpg) {
             oppPpgDifference = cowboysStats[season1].oppPpg - cowboysStats[season2].oppPpg;
             cout << "In " << cowboysStats[season1].year << " the Cowboys averaged " << oppPpgDifference
             << " more OPP PPG than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].oppPpg < cowboysStats[season2].oppPpg) {
             oppPpgDifference = cowboysStats[season2].oppPpg - cowboysStats[season1].oppPpg;
             cout << "In " << cowboysStats[season2].year << " the Cowboys averaged " << oppPpgDifference
             << " more OPP PPG than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].oppPpg == cowboysStats[season2].oppPpg) {
             cout << "In " << cowboysStats[season1].year << " the Cowboys had the same  OPP PPG";
             cout << " as in " << cowboysStats[season2].year << "\n\n";    
    }
    
    int playoffsSzn1 = convertPlayoffSuccess(cowboysStats[season1].playoffSuccess);
    int playoffsSzn2 = convertPlayoffSuccess(cowboysStats[season2].playoffSuccess);

    if (playoffsSzn1 > playoffsSzn2) {
        cout << "The Cowboys advanced farther in the playoffs in  " << cowboysStats[season1].year
        << " than in " << cowboysStats[season2].year << endl;
    }
    else if (playoffsSzn2 > playoffsSzn1) {
        cout << "The Cowboys advanced farther in the playoffs in  " << cowboysStats[season2].year
        << " than in " << cowboysStats[season1].year << endl;
    }
    else if (playoffsSzn1 == playoffsSzn2) {
        cout << "The Cowboys had the same amount of playoff success in " << cowboysStats[season1].year
        << " and " << cowboysStats[season2].year << endl;
    }
    else if (playoffsSzn1 == 1 && playoffsSzn2 == 1) {
        cout << "The Cowboys did not make the playoffs in " << cowboysStats[season1].year
        << " or " << cowboysStats[season2].year << ":(" << endl;
    }
cout << endl;
}

void selectionSortWins(SeasonStats cowboysStats[], int entries) {
    
    int startScan, minIndex, i;

    for(startScan = 0; startScan < (entries - 1); startScan++) {
        minIndex = startScan;

        for(i = startScan + 1; i < entries; i++) {
            if (cowboysStats[i].wins > cowboysStats[minIndex].wins) {
                minIndex = i;
            }
        }

        SeasonStats temp = cowboysStats[minIndex];
        cowboysStats[minIndex] = cowboysStats[startScan];
        cowboysStats[startScan] = temp;
        
    }
    cout << "**********************************************\n";
        cout << "*" << setw(45) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Wins =====" << setw(2) << "*";
        cout << "\n*" << setw(45) << "*"
        << "\n*" << setw(45) << "*";
        cout << left;
        cout << "\n* |Year|                |WINS|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            cout << "* " << setw(24) << cowboysStats[i].year << setw(19) << cowboysStats[i].wins
            << setw(22) << "*"
             << endl;
        }
         cout << "**********************************************\n";
    }

    void selectionSortLosses(SeasonStats cowboysStats[], int entries) {
    
    int startScan, minIndex, i;

    for(startScan = 0; startScan < (entries - 1); startScan++) {
        minIndex = startScan;

        for(i = startScan + 1; i < entries; i++) {
            if (cowboysStats[i].losses > cowboysStats[minIndex].losses) {
                minIndex = i;
            }
        }

        SeasonStats temp = cowboysStats[minIndex];
        cowboysStats[minIndex] = cowboysStats[startScan];
        cowboysStats[startScan] = temp;
        
    }
    cout << "************************************************\n";
        cout << "*" << setw(47) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Losses ===== *";  //<< setw(2) << "*";
        cout << "\n*" << setw(47) << "*"
        << "\n*" << setw(47) << "*";
        cout << left;
        cout << "\n* |Year|               |LOSSES|" << "                *" << endl;

        for(int i = 0; i < entries; ++i) {
            cout << "* " << setw(24) << cowboysStats[i].year << setw(21) << cowboysStats[i].losses
            << setw(23) << "*"
             << endl;
        }
         cout << "************************************************\n";
    }

    void selectionSortTies(SeasonStats cowboysStats[], int entries) {
    
    int startScan, minIndex, i;

    for(startScan = 0; startScan < (entries - 1); startScan++) {
        minIndex = startScan;

        for(i = startScan + 1; i < entries; i++) {
            if (cowboysStats[i].ties > cowboysStats[minIndex].ties) {
                minIndex = i;
            }
        }

        SeasonStats temp = cowboysStats[minIndex];
        cowboysStats[minIndex] = cowboysStats[startScan];
        cowboysStats[startScan] = temp;
        
    }

    int allTimeTies = 0;

    for(int j = 0; j < entries; j++) {
        allTimeTies = allTimeTies + cowboysStats[j].ties;
    }
    
    if (allTimeTies == 0) {
        cout << "\nFor the current data (2005-2024), there have been 0 total ties across all seasons\n";
    }

    else if (allTimeTies > 0) {
    cout << "**********************************************\n";
        cout << "*" << setw(45) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Ties =====" << setw(2) << "*";
        cout << "\n*" << setw(45) << "*"
        << "\n*" << setw(45) << "*";
        cout << left;
        cout << "\n* |Year|                |TIES|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            cout << "* " << setw(24) << cowboysStats[i].year << setw(19) << cowboysStats[i].wins
            << setw(22) << "*"
             << endl;
        }
         cout << "**********************************************\n";
    }
    }

    void selectionSortPpg(SeasonStats cowboysStats[], int entries) {
    
    int startScan, minIndex, i;

    for(startScan = 0; startScan < (entries - 1); startScan++) {
        minIndex = startScan;

        for(i = startScan + 1; i < entries; i++) {
            if (cowboysStats[i].ppg > cowboysStats[minIndex].ppg) {
                minIndex = i;
            }
        }

        SeasonStats temp = cowboysStats[minIndex];
        cowboysStats[minIndex] = cowboysStats[startScan];
        cowboysStats[startScan] = temp;
        
    }
    cout << "**********************************************\n";
        cout << "*" << setw(45) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Wins =====" << setw(2) << "*";
        cout << "\n*" << setw(45) << "*"
        << "\n*" << setw(45) << "*";
        cout << left;
        cout << "\n* |Year|                 |PPG|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            cout << "* " << setw(24) << cowboysStats[i].year << setw(19) << cowboysStats[i].ppg
            << setw(22) << "*"
             << endl;
        }
         cout << "**********************************************\n";
    }

    void selectionSortOppPpg(SeasonStats cowboysStats[], int entries) {
    
    int startScan, minIndex, i;

    for(startScan = 0; startScan < (entries - 1); startScan++) {
        minIndex = startScan;

        for(i = startScan + 1; i < entries; i++) {
            if (cowboysStats[i].oppPpg < cowboysStats[minIndex].oppPpg) {
                minIndex = i;
            }
        }

        SeasonStats temp = cowboysStats[minIndex];
        cowboysStats[minIndex] = cowboysStats[startScan];
        cowboysStats[startScan] = temp;
        
    }
    cout << "**********************************************\n";
        cout << "*" << setw(45) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Wins =====" << setw(2) << "*";
        cout << "\n*" << setw(45) << "*"
        << "\n*" << setw(45) << "*";
        cout << left;
        cout << "\n* |Year|                |OPP PPG|" << "            *" << endl;

        for(int i = 0; i < entries; ++i) {
            cout << "* " << setw(24) << cowboysStats[i].year << setw(19) << cowboysStats[i].oppPpg
            << setw(22) << "*"
             << endl;
        }
         cout << "**********************************************\n";
    }

    void selectionSortPlayoffSuccess(SeasonStats cowboysStats[], int entries) {
    
    int startScan, minIndex, i;

    for(startScan = 0; startScan < (entries - 1); startScan++) {
        minIndex = startScan;

        for(i = startScan + 1; i < entries; i++) {

            //using convertPlayoffSuccess to convert strings to integers because sorting by 
            //numbers is easier
            int current = convertPlayoffSuccess(cowboysStats[i].playoffSuccess);
            int best = convertPlayoffSuccess(cowboysStats[minIndex].playoffSuccess);

            if (current > best) {
                minIndex = i;
            }
        }

        SeasonStats temp = cowboysStats[minIndex];
        cowboysStats[minIndex] = cowboysStats[startScan];
        cowboysStats[startScan] = temp;
        
    }
    cout << "*********************************************************\n";
        cout << "*" << setw(56) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Playoff Success =====" << setw(2) << "*";
        cout << "\n*" << setw(56) << "*"
        << "\n*" << setw(56) << "*";
        cout << left;
        cout << "\n* |Year|                |PLAYOFF SUCCESS|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            cout << "* " << setw(20) << cowboysStats[i].year << setw(34) << cowboysStats[i].playoffSuccess
            << setw(18) << "*"
             << endl;
        }
         cout << "* Hope to see a Superbowl soon :(                       *\n";
         cout << "*********************************************************\n";
    }



   
 
          