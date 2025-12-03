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
#include <sstream>
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

int readStats(SeasonStats cowboysStats[], const int MAX_ENTRIES); // function to read data from file into array of structs
string printAllStats(SeasonStats cowboysStats[], int entries);  // function to print all data cuurently in SeasonStats struct
string viewOneSeason(SeasonStats cowboysStats[], int entries); // function to find one individual season and prints its stats
int findUserSeason(SeasonStats cowboysStats[], int entries, int year); // chose to make this function to call it in other functions to find what
//seaons they want to compare, better than doing it over and over in different functions, uses LINEAR SEARCH
int validateInt(const string &prompt, int minVal, int maxVal); // helper function to validate integer data
double validateDouble(const string &prompt, double minVal, double maxVal); // helper function to validate double data
string compare2Seasons(SeasonStats cowboysStats[], int entries); // function to compare two seasons, uses findUser season to find desired seasons 
int convertPlayoffSuccess(const string playoffResult); // function to convert playoff success into integer value to make easier to compare
string selectionSortWins(SeasonStats cowboysStats[], int entries); // function to sort all seasons by wins and prints them in order
string selectionSortLosses(SeasonStats cowboysStats[], int entries); // function to sort all seasons by losses and prints them in order
string selectionSortTies(SeasonStats cowboysStats[], int entries); // function to sort all seasons by ties and prints them in order
string selectionSortPpg(SeasonStats cowboysStats[], int entries); // function to sort all seasons by PPG and prints them in order
string selectionSortOppPpg(SeasonStats cowboysStats[], int entries); // function to sort all seasons by OPP PPG and prints them in order
string selectionSortPlayoffSuccess(SeasonStats cowboysStats[], int entries); // function to sort all seasons by playoff success and prints them in order
void addSeasonToData(SeasonStats cowboysStats[], int& entries); // function to add data do the data already stored in cowboys_stats.txt
void saveToUserFile(const string& dataToSave); // function that makes a user file and stores desired data in it if user chooses
void saveToCowboysData(SeasonStats cowboysStats[], int entries); // saves seasons that are added by user to cowboys_stats.txt
void printMainMenu(); // function to print main menu, practical for being used in loop to prompt user 
void printSubMenu(); // function to print sub menu, practical for being used in loop to prompt user
void promptToSaveData(const string data); // function to ask user if they want to save data to their file, applicable in main menu


int main() {


const int MAX_ENTRIES = 100;
SeasonStats cowboysStats[MAX_ENTRIES];   // array of structs, holds all the data
int entries = readStats(cowboysStats, MAX_ENTRIES); // reads in data FIRST before doing anything else
//addSeasonToData(cowboysStats, entries);

//cout << selectionSortPlayoffSuccess(cowboysStats, entries);

int choice;
//cout << selectionSortPlayoffSuccess(cowboysStats, entries);

while (true) {
    printMainMenu();
    
    cin >> choice;

    if (choice < 1 || choice > 6) {    // this is for when user has invalid input
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice, must be 1-6\n";
        continue;
    }

    cin.ignore(1000, '\n');

    switch (choice) {

        case 1: {
            string output = printAllStats(cowboysStats, entries);
            cout << output;
            promptToSaveData(output);
            break;
        }

        case 2: {
            string output = viewOneSeason(cowboysStats, entries);
            cout << output;
            promptToSaveData(output);
            break;
        }

        case 3: {
            string output = compare2Seasons(cowboysStats, entries);
            cout << output;
            promptToSaveData(output);
            break;
        }

        case 4: {
            addSeasonToData(cowboysStats, entries);
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }

        case 5: {           // case 5 holds the enture submenu, contains another switch menu
            bool inSubMenu = true;
            int subMenuChoice;

            while (inSubMenu) {
                printSubMenu();
                subMenuChoice = validateInt("Enter submenu choice: ", 1, 7);

                switch(subMenuChoice) {

                    case 1: {
                       string output = selectionSortWins(cowboysStats, entries);
                       cout << output;
                       promptToSaveData(output);
                       break;
                    }

                    case 2: {
                       string output = selectionSortLosses(cowboysStats, entries);
                       cout << output;
                       promptToSaveData(output);
                       break;
                    }

                    case 3: {
                       string output = selectionSortTies(cowboysStats, entries);
                       cout << output;
                       promptToSaveData(output);
                       break;
                    }

                    case 4: {
                       string output = selectionSortPpg(cowboysStats, entries);
                       cout << output;
                       promptToSaveData(output);
                       break;
                    }

                    case 5: {
                       string output = selectionSortOppPpg(cowboysStats, entries);
                       cout << output;
                       promptToSaveData(output);
                       break;
                    }

                    case 6: {
                       string output = selectionSortPlayoffSuccess(cowboysStats, entries);
                       cout << output;
                       promptToSaveData(output);
                       break;
                    }

                    case 7: {
                       inSubMenu = false;
                       break;
                    }

                    default: {
                        cout << "Not a valid option\n";
                    }
                }
            }
            break;

        }

        case 6: {
            cout << "Goodbye! Hope you made good use of the Dallas Cowboys Stats Sorter!\n";
            return 0;
        }

        default:
        cout << "Not a valid option\n";
    }
}

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

    string printAllStats(SeasonStats cowboysStats[], int entries) {

        stringstream output; // collects strings into this variable, like filling up a bucket, the whole data table will be in the output variable
        output << "*******************************************************************************************" 
        << "*************\n";
        output << "*" << setw(103) << "*";
        output << "\n* ================ Dallas Cowboys Total Seasons Stats ================                                 *";
        output << "\n*" << setw(103) << "*"
        << "\n*                                                                                                      *";
        output << left;
        output << "\n* |Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|"
        << "                   *" << endl;

        for(int i = 0; i < entries; ++i) {
            output << "* " << setw(10) << cowboysStats[i].year
             << setw(10) << cowboysStats[i].wins
             << setw(10) << cowboysStats[i].losses
             << setw(10) << cowboysStats[i].ties
             << setw(13) << cowboysStats[i].ppg
             << setw(13) << cowboysStats[i].oppPpg
             << setw(35) << cowboysStats[i].playoffSuccess << setw(2) << "*"
             << endl;
        }
         output << "*******************************************************************************************" 
         << "*************\n";

         return output.str();
    }

   

    int findUserSeason(SeasonStats cowboysStats[], int entries, int year) { // linear seach !
        for (int i = 0; i < entries; i++) {
            if (cowboysStats[i].year == year) { 
                return i;
            }
        }
        return -1; // year not found
    }

    int validateInt(const string &prompt, int minVal, int maxVal) {
        int userVal;

        while (true) {  
            cout << prompt;
            cin >> userVal;

            if (!cin) {  // checks if input is an integer
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input, must be a whole number\n";
                continue;
            }

            if (userVal < minVal || userVal > maxVal) { // makes sure input makes sense (cannot have 1093833 wins in season)
                cout << "Number must be between " << minVal << " and " << maxVal << "\n";
                continue;
            }
            return userVal;
        }


    }

    double validateDouble(const string &prompt, double minVal, double maxVal) {
        double userVal;

        while (true) {  
            cout << prompt;
            cin >> userVal;

            if (!cin) {  // checks if input is an double
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input, must be a number\n";
                continue;
            }

            if (userVal < minVal || userVal > maxVal) { // makes sure input makes sense (cannot have 10938.4 PPG in season)
                cout << "Number must be between " << minVal << " and " << maxVal << "\n";
                continue;
            }
            return userVal;
        }


    }

    string viewOneSeason(SeasonStats cowboysStats[], int entries) {
        
        stringstream output;
        int userYear;
        int userSeasonIndex;

        output << "Okay great! You want to view one season individually\n";
        userYear = validateInt("Enter the year of the season you want to view: ", 1960, 2500);

        userSeasonIndex = findUserSeason(cowboysStats, entries, userYear);

        if (userSeasonIndex == -1) {
            return string("That season is currently not in the database\n");
        }
    
       output << left;
       output << "**********************************************\n";
       output << setw(45) << "*" << "*\n";
       output << setw(18) << "*" << cowboysStats[userSeasonIndex].year  << setw(23) << "   Stats" << "*\n";
       output << setw(45) << "*" << "*";
       output << setw(24) << "\n* Wins -->" << setw(22) <<  cowboysStats[userSeasonIndex].wins << "*\n";
       output << setw(45) << "*" << "*";
       output << setw(24) << "\n* Losses -->" << setw(22) <<  cowboysStats[userSeasonIndex].losses << "*\n";
       output << setw(45) << "*" << "*";
       output << setw(24) << "\n* Ties -->" << setw(22) <<  cowboysStats[userSeasonIndex].ties << "*\n";
       output << setw(45) << "*" << "*";
       output << setw(24) << "\n* PPG -->" << setw(22) <<  cowboysStats[userSeasonIndex].ppg << "*\n";
       output << setw(45) << "*" << "*";
       output << setw(24) << "\n* OPP PPG -->" << setw(22) << cowboysStats[userSeasonIndex].oppPpg << "*\n";
       output << setw(45) << "*" << "*";
       output << "\n* Playoff Success -->" << setw(23) << cowboysStats[userSeasonIndex].playoffSuccess << " *\n";
       output << setw(45) << "*" << "*";
       output << "\n**********************************************\n";
       
       return output.str();
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

    string compare2Seasons(SeasonStats cowboysStats[], int entries) {

        stringstream output;
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

        output << "\nHere is your comparison report!\n " << endl;
        output << "*******************************************************************************************" 
        << "*************\n";
        output << "*" << setw(103) << "*"
        << "\n* ====================== " << cowboysStats[season1].year << " and " << cowboysStats[season2].year
        << " Comparison Report ===============================" << setw(16) << "*";
        output << "\n*" << setw(103) << "*"
        << "\n*                                                                                                      *";
        output << left;
        output << "\n* |Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|"
        << "                   *" << endl;

       
            output << "* " << setw(10) << cowboysStats[season1].year
             << setw(10) << cowboysStats[season1].wins
             << setw(10) << cowboysStats[season1].losses
             << setw(10) << cowboysStats[season1].ties
             << setw(13) << cowboysStats[season1].ppg
             << setw(13) << cowboysStats[season1].oppPpg
             << setw(35) << cowboysStats[season1].playoffSuccess << setw(2) << "*"
             << endl;
             output << "* " << setw(10) << cowboysStats[season2].year
             << setw(10) << cowboysStats[season2].wins
             << setw(10) << cowboysStats[season2].losses
             << setw(10) << cowboysStats[season2].ties
             << setw(13) << cowboysStats[season2].ppg
             << setw(13) << cowboysStats[season2].oppPpg
             << setw(35) << cowboysStats[season2].playoffSuccess << setw(2) << "*"
             << endl;
         output << "*******************************************************************************************" 
         << "*************\n";
       

             int winsDifference;
             int lossDifference;
             int tiesDifference;
             double ppgDifference;
             double oppPpgDifference;

             output << "\nMore in depth analysis:\n";
             if (cowboysStats[season1].wins > cowboysStats[season2].wins) {
             winsDifference = cowboysStats[season1].wins - cowboysStats[season2].wins;
             output << "In " << cowboysStats[season1].year << " the Cowboys had " << winsDifference
             << " more win/wins than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].wins < cowboysStats[season2].wins) {
             winsDifference = cowboysStats[season2].wins - cowboysStats[season1].wins;
             output << "In " << cowboysStats[season2].year << " the Cowboys had " << winsDifference
             << " more win/wins than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].wins == cowboysStats[season2].wins) {
             output << "In " << cowboysStats[season1].year << " the Cowboys had the same amount of wins";
             output << " as in " << cowboysStats[season2].year << "\n\n";
             }
             if (cowboysStats[season1].losses > cowboysStats[season2].losses) {
             lossDifference = cowboysStats[season1].losses - cowboysStats[season2].losses;
             output << "In " << cowboysStats[season1].year << " the Cowboys had " << lossDifference
             << " more loss/losses than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].losses < cowboysStats[season2].losses) {
             lossDifference = cowboysStats[season2].losses - cowboysStats[season1].losses;
             output << "In " << cowboysStats[season2].year << " the Cowboys had " << lossDifference
             << " more loss/losses than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].losses == cowboysStats[season2].losses) {
             output << "In " << cowboysStats[season1].year << " the Cowboys had the same amount of losses";
             output << " as in " << cowboysStats[season2].year << "\n\n";
             }
              if (cowboysStats[season1].ties > cowboysStats[season2].ties) {
             tiesDifference = cowboysStats[season1].ties - cowboysStats[season2].ties;
             output << "In " << cowboysStats[season1].year << " the Cowboys had " << tiesDifference
             << " more tie/ties than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].ties < cowboysStats[season2].ties) {
             tiesDifference = cowboysStats[season2].ties - cowboysStats[season1].ties;
             output << "In " << cowboysStats[season2].year << " the Cowboys had " << tiesDifference
             << " more tie/ties than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].ties == cowboysStats[season2].ties) {
             output << "In " << cowboysStats[season1].year << " the Cowboys had the same amount of ties";
             output << " as in " << cowboysStats[season2].year << "\n\n";
             }
              if (cowboysStats[season1].ppg > cowboysStats[season2].ppg) {
             ppgDifference = cowboysStats[season1].ppg - cowboysStats[season2].ppg;
             output << "In " << cowboysStats[season1].year << " the Cowboys averaged " << ppgDifference
             << " more PPG than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].ppg < cowboysStats[season2].ppg) {
             ppgDifference = cowboysStats[season2].ppg - cowboysStats[season1].ppg;
             output << "In " << cowboysStats[season2].year << " the Cowboys averaged " << ppgDifference
             << " more PPG than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].ppg == cowboysStats[season2].ppg) {
             output << "In " << cowboysStats[season1].year << " the Cowboys had the same PPG";
             output << " as in " << cowboysStats[season2].year << "\n\n";
             }
             if (cowboysStats[season1].oppPpg > cowboysStats[season2].oppPpg) {
             oppPpgDifference = cowboysStats[season1].oppPpg - cowboysStats[season2].oppPpg;
             output << "In " << cowboysStats[season1].year << " the Cowboys averaged " << oppPpgDifference
             << " more OPP PPG than in  " << cowboysStats[season2].year << "\n\n";
             }
             else if (cowboysStats[season1].oppPpg < cowboysStats[season2].oppPpg) {
             oppPpgDifference = cowboysStats[season2].oppPpg - cowboysStats[season1].oppPpg;
             output << "In " << cowboysStats[season2].year << " the Cowboys averaged " << oppPpgDifference
             << " more OPP PPG than in  " << cowboysStats[season1].year << "\n\n";
             }
             else if (cowboysStats[season1].oppPpg == cowboysStats[season2].oppPpg) {
             output << "In " << cowboysStats[season1].year << " the Cowboys had the same  OPP PPG";
             output << " as in " << cowboysStats[season2].year << "\n\n";    
    }
    
    int playoffsSzn1 = convertPlayoffSuccess(cowboysStats[season1].playoffSuccess);
    int playoffsSzn2 = convertPlayoffSuccess(cowboysStats[season2].playoffSuccess);

    if (playoffsSzn1 > playoffsSzn2) {
        output << "The Cowboys advanced farther in the playoffs in  " << cowboysStats[season1].year
        << " than in " << cowboysStats[season2].year << endl;
    }
    else if (playoffsSzn2 > playoffsSzn1) {
        output << "The Cowboys advanced farther in the playoffs in  " << cowboysStats[season2].year
        << " than in " << cowboysStats[season1].year << endl;
    }
    else if (playoffsSzn1 == playoffsSzn2) {
        output << "The Cowboys had the same amount of playoff success in " << cowboysStats[season1].year
        << " and " << cowboysStats[season2].year << endl;
    }
    else if (playoffsSzn1 == 1 && playoffsSzn2 == 1) {
        output << "The Cowboys did not make the playoffs in " << cowboysStats[season1].year
        << " or " << cowboysStats[season2].year << ":(" << endl;
    }
output << endl;

return output.str();
}

string selectionSortWins(SeasonStats cowboysStats[], int entries) {
    
    stringstream output;
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
    output << "**********************************************\n";
        output << "*" << setw(45) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Wins =====" << setw(2) << "*";
        output << "\n*" << setw(45) << "*"
        << "\n*" << setw(45) << "*";
        output << left;
        output << "\n* |Year|                |WINS|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            output << "* " << setw(24) << cowboysStats[i].year << setw(19) << cowboysStats[i].wins
            << setw(22) << "*"
             << endl;
        }
         output << "**********************************************\n";

         return output.str();
    }

    string selectionSortLosses(SeasonStats cowboysStats[], int entries) {
    
    stringstream output;
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
    output << "************************************************\n";
        output << "*" << setw(47) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Losses ===== *";  //<< setw(2) << "*";
        output << "\n*" << setw(47) << "*"
        << "\n*" << setw(47) << "*";
        output << left;
        output << "\n* |Year|               |LOSSES|" << "                *" << endl;

        for(int i = 0; i < entries; ++i) {
            output << "* " << setw(24) << cowboysStats[i].year << setw(21) << cowboysStats[i].losses
            << setw(23) << "*"
             << endl;
        }
         output << "************************************************\n";

         return output.str();
    }

    string selectionSortTies(SeasonStats cowboysStats[], int entries) {
    
    stringstream output;
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
        output << "\nFor the current data (2005-2024), there have been 0 total ties across all seasons\n";
    }

    else if (allTimeTies > 0) {
    output << "**********************************************\n";
        output << "*" << setw(45) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Ties =====" << setw(2) << "*";
        output << "\n*" << setw(45) << "*"
        << "\n*" << setw(45) << "*";
        output << left;
        output << "\n* |Year|                |TIES|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            output << "* " << setw(24) << cowboysStats[i].year << setw(19) << cowboysStats[i].wins
            << setw(22) << "*"
             << endl;
        }
         output << "**********************************************\n";
    }

    return output.str();
    }

    string selectionSortPpg(SeasonStats cowboysStats[], int entries) {
    
    stringstream output;
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
    output << "**********************************************\n";
        output << "*" << setw(45) << "*"
        << "\n* ===== Dallas Cowboys Seasons By PPG =====" << setw(2) << "*";
        output << "\n*" << setw(45) << "*"
        << "\n*" << setw(45) << "*";
        output << left;
        output << "\n* |Year|                 |PPG|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            output << "* " << setw(24) << cowboysStats[i].year << setw(19) << cowboysStats[i].ppg
            << setw(22) << "*"
             << endl;
        }
         output << "**********************************************\n";
         return output.str();
    }

    string selectionSortOppPpg(SeasonStats cowboysStats[], int entries) {
    
    stringstream output;
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
    output << "*************************************************\n";
        output << "*" << setw(48) << "*";
        output << "\n* ===== Dallas Cowboys Seasons By OPP PPG ===== *";
        output << "\n*" << setw(48) << "*"
        << "\n*" << setw(48) << "*";
        output << left;
        output << "\n* |Year|                |OPP PPG|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            output << "* " << setw(24) << cowboysStats[i].year << setw(22) << cowboysStats[i].oppPpg
            << setw(25) << "*"
             << endl;
        }
         output << "*************************************************\n";

         return output.str();
    }

    string selectionSortPlayoffSuccess(SeasonStats cowboysStats[], int entries) {
    
    stringstream output;
    int startScan, maxIndex, i;

    for(startScan = 0; startScan < (entries - 1); startScan++) {
        maxIndex = startScan;

        for(i = startScan + 1; i < entries; i++) {

            //using convertPlayoffSuccess to convert strings to integers because sorting by 
            //numbers is easier
            int current = convertPlayoffSuccess(cowboysStats[i].playoffSuccess);
            int best = convertPlayoffSuccess(cowboysStats[maxIndex].playoffSuccess);

            //treats invalid as worst success
            if (current < 0) current = 0;
            if (best < 0) best = 0;

            if (current > best) {
                maxIndex = i;
            }
        }

        SeasonStats temp = cowboysStats[maxIndex];
        cowboysStats[maxIndex] = cowboysStats[startScan];
        cowboysStats[startScan] = temp;
        
    }
    output << "*********************************************************\n";
        output << "*" << setw(56) << "*"
        << "\n* ===== Dallas Cowboys Seasons By Playoff Success =====" << setw(2) << "*";
        output << "\n*" << setw(56) << "*"
        << "\n*" << setw(56) << "*";
        output << left;
        output << "\n* |Year|                |PLAYOFF SUCCESS|" << "               *" << endl;

        for(int i = 0; i < entries; ++i) {
            output << "* " << setw(20) << cowboysStats[i].year << setw(34) << cowboysStats[i].playoffSuccess
            << setw(18) << "*"
             << endl;
        }
         output << "* Hope to see a Superbowl soon :(                       *\n";
         output << "*********************************************************\n";
         return output.str();
    }

    void addSeasonToData(SeasonStats cowboysStats[], int& entries) {

        int userYear;
        bool inCurrentData = false;

        while (true) {   // input validation while loop
        inCurrentData = false;
        cout << "Okay great, you want to add a season of data to the data collection!\n"
        << "Enter the year of the season you want to add (1960-2004 or 2025-Future): ";
        cin >> userYear;
        
        if (!cin) {   // checks if input is an integer
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input, year must be in numbers not characters\n";
            continue;
        }
        if (userYear < 1960) {  
            cout << "Enter another year, the Dallas Cowboys did not exist yet\n";
            continue;
        }

        if (userYear >= 2005 && userYear <= 2024) {
            cout << "That year is already in the pre loaded data (2005-2024)\n";
            continue;
        }

        // checks if userSeason is already in the data
        for (int i = 0; i < entries; i++) {
            if (cowboysStats[i].year == userYear) {
                inCurrentData = true;
                break;
            }
        }

        if (inCurrentData) {
            cout << "The year you entered is already in the database\n";
            continue;
        }

        break; //valid year has been found
    }
    // populating new season with data
    SeasonStats newSeason;
    newSeason.year = userYear;
    int playoffSuccess;

    // using helper functions validateInt and validateDouble to validate each piece of data before using it
    newSeason.wins = validateInt("Enter wins (0-17): ", 0, 17);
    newSeason.losses = validateInt("Enter losses (0-17): ", 0, 17);
    newSeason.ties = validateInt("Enter ties (0-17): ", 0, 17);
    newSeason.ppg = validateDouble("Enter PPG (0.0-50.0): ", 0.0, 50.0);
    newSeason.oppPpg = validateDouble("Enter OPP PPG (0.0-50.0): ", 0.0, 50.0);

    cin.ignore(1000, '\n');

    while (true) {

        cout << "Enter playoff success (Please enter Missed Playoffs, Lost Wild Card Round"
    << ", Lost Divisional Round, Lost Conference Championship, Lost Superbowl, or Won Superbowl (capitalization"
    << " and whitespace matter): ";
    
    getline(cin, newSeason.playoffSuccess);
    
    playoffSuccess = convertPlayoffSuccess(newSeason.playoffSuccess);
cout << "NEW PLAYOFF SUCCESS " << newSeason.playoffSuccess << endl;
    if (playoffSuccess == -1) {
        cout << "Input is not one of the specified playoff outcomes stated above, check for typos\n";
        continue;
    }
        break; // valid
    }

    // depending on year, season gets added before 2005 or after 2024 to keep order chronological
    
    if (userYear >= 2004) {
    // finds the first index where year is greater or equal to 2005
    int insertIndex = 0;
    while (insertIndex < entries && cowboysStats[insertIndex].year <= 2004) {
        insertIndex++;
    }
        for (int i = entries; i > insertIndex; i--) {  // shifts everything down 1 spot
            cowboysStats[i] = cowboysStats[i - 1];
        }
        // puts new season in correct chronological spot in data
        cowboysStats[insertIndex] = newSeason;
    }

    else { // adds new season at the end of array of structs
        cowboysStats[entries] = newSeason;
    }
     entries++;

     // saves the new season to the rest of the data in cowboys_stats.txt
     saveToCowboysData(cowboysStats, entries); 

     cout << "Season " << userYear << " successfully added to data!\n";
     cout << "Here is the data for the new season\n";
     cout << left;
       cout << "**********************************************\n";
       cout << setw(45) << "*" << "*\n";
       cout << setw(18) << "*" << newSeason.year  << setw(23) << "   Stats" << "*\n";
       cout << setw(45) << "*" << "*";
       cout << setw(24) << "\n* Wins -->" << setw(22) <<  newSeason.wins << "*\n";
       cout << setw(45) << "*" << "*";
       cout << setw(24) << "\n* Losses -->" << setw(22) <<  newSeason.losses << "*\n";
       cout << setw(45) << "*" << "*";
       cout << setw(24) << "\n* Ties -->" << setw(22) <<  newSeason.ties << "*\n";
       cout << setw(45) << "*" << "*";
       cout << setw(24) << "\n* PPG -->" << setw(22) <<  newSeason.ppg << "*\n";
       cout << setw(45) << "*" << "*";
       cout << setw(24) << "\n* OPP PPG -->" << setw(22) << newSeason.oppPpg << "*\n";
       cout << setw(45) << "*" << "*";
       cout << setw(24) << "\n* Playoff Success -->" << newSeason.playoffSuccess << " *\n";
       cout << setw(45) << "*" << "*";
       cout << "\n**********************************************\n";

    }

    void saveToUserFile(const string& dataToSave) {
        ofstream outFile("users_collection.txt", ios::app);

        if (!outFile) {
            cout << "Error opening users file!" << endl;
        }

        outFile << dataToSave << endl;
        outFile.close();

        cout << "Data saved to your file! " << endl;
    }

    void saveToCowboysData(SeasonStats cowboysStats[], int entries) {
        ofstream outFile("cowboys_stats.txt");

        if (!outFile) {
            cout << "Error opening file to add data!\n";
            return;
        }
        //saves each new season in same format that the original 20 SZNS are saved in
        for (int i = 0; i < entries; i++) {
            outFile << cowboysStats[i].year << " "
                    << cowboysStats[i].wins << " "
                    << cowboysStats[i].losses << " "
                    << cowboysStats[i].ties << " "
                    << cowboysStats[i].ppg << " "
                    << cowboysStats[i].oppPpg << " "
                    << cowboysStats[i].playoffSuccess << " "
                    << "\n";
        }
        outFile.close();
    }

    void printMainMenu() {
    cout << "\n*****************************************************\n";
    cout << "*" << setw(53) << "*\n";
    cout << "*       =====Dallas Cowboy's Stats Sorter=====      *\n";
    cout << "*" << setw(53) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 1. View All Season Stats" << setw(28) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 2. View Individual Season" << setw(27) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 3. Compare 2 Seasons" << setw(32) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 4. Add New Season" << setw(35) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 5. Reports & Rankings (Submenu)" << setw(21) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 6. Quit" << setw(45) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "*****************************************************\n";
}

void printSubMenu() {
    cout << "\n*****************************************************\n";
    cout << "*" << setw(53) << "*\n";
    cout << "*         =====Reports & Rankings Menu=====         *\n";
    cout << "*" << setw(53) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 1. Sort by Wins" << setw(37) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 2. Sort by Losses" << setw(35) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 3. Sort by Ties" << setw(37) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 4. Sort by PPG" << setw(38) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 5. Sort by OPP PPG" << setw(34) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 6. Sort by Playoff Success" << setw(26) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "* 7. Return to Main Menu" << setw(30) << "*\n";
    cout << "*" << setw(53) << "*\n";
    cout << "*****************************************************\n\n";
}
   
// takes string that is returned from the stringstream (output) and asks if user wants to save this to their file
// if yes, it uses the passed string (data) and adds it to user file
void promptToSaveData(const string data) {
    char choice;
    cout << "Would you like to save this data to your personal file? (Y/N)\n";
    cin >> choice;
    choice = toupper(choice); // toupper converts lowercase into uppercase incase user uses lowercase

    if (choice == 'Y') {
        saveToUserFile(data);
    }

    cin.ignore(1000,'\n'); // clears garbage

}
 
          