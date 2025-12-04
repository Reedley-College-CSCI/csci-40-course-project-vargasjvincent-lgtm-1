[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7mdzU3H2)
# CS1 Final Project - Dallas Cowboys Stat Finder
MENTION <SSTREAM>
## 1. Overview
- What problem does your project solve?  
Stats are easily accessible on the internet but when it comes to comparing certain stats across seasons, websites can become lackluster, there is not a great way to view and pull up different stats from different seasons. This project will give the user the ability to do just that. Another problem is having an easy way to compare data of your choosing, a way to do this is to have multiple tabs open from an online database but it becomes tedious switching between each tab to compare data. This project provides a solution by giving the user the option to save it to a user file where they can view all their desired data on one single file making it easy to make comparasions.
- Briefly describe the purpose and key features of your program.  
Purpose: Provide a user friendly, menu driven program that can display desired data to the console and making it easier to interact with Dallas Cowboys data compared to using web pages. 

Key Features: 
- Main menu with multiple reports and comparisons
- Ability to view all seasons or an individual season
- Compare any two seasons
- Add new custom seasons to the database
- Sub menu option from main menu to sort seasons by wins, losses, ties, points per game, opponent points per game,     or playoff success
- Save any report to a personal file
- Data persists between runs using .txt storage

---

## 2. Design Decisions
- What fundamental programming constructs and data types did you use, and why?  
Some fundamental programming constructs I used were for and while loops to read data in, populate my struct, 
and print stats to the console in an efficient matter. These constructs kept the program more modularized,
easier to debug, and over all more organized. As far as data types I used ints, doubles, and strings as they 
complemented the data I was working with logically and naturally. Ints were used for year, wins, losses, and ties
because those stats are always integers. Doubles were used for points per game, and opponent points per game
becauuse these numbers are averages across the season so they are bound to have decimals so I used doubles for that.
Lastly I used strings to store playoff success because storing them as strings would make more sense to the user 
compared to using numbers to symbolize playoff success.
- Why did you choose to structure your data using structs?  
I chose to use a struct because it made sense for the data I was working with to be grouped into one.
Wins, losses, ties, PPG, OPPG, and playoff success are all relevant to see how a team performed for a 
particular season. This being said the data is grouped together in a struct called SeasonStats. The data being 
in a struct gives me the ability to create an array of structs which makes it much easier to print the data
and manipulate it when it is in an array of structs.
- How did you implement searching and sorting? What algorithms did you use and why?  
I implemented searching in the findUserSeason which is a helper function used throughout the program,
the findUserSeason takes in a year from the user and finds the index in the array of structs using
 linear search. The findUserSeason is used in the viewIndividualSeason and compare2Seasons functions because the user is prompted for a year of a season they want to view or compare so the index of their desired season is found using
 the helper function findUserSason. I chose linear search because the most amounnt of seasons there can be is about
 65 currently so linear search will not take very long compared to if there was thousands of seasons. 

 I implemented selection sort in the entire submenu. This submenu gives the user option to sort all the seasons
 in order from best to worst for all the data contained in the SeasonStats struct. A sorting algorithm was needed
 to sort each data type. There is a different selection sort function for each type of data. I made one of them and
 then copy and pasted the algorithm for the other data types and replaced a couple of things so it would serve the
 correct purpose (Dr. Sultana told us programmers save time and use shortcuts). 
- How do you ensure data persistence between program runs?  
I ensure data persistence between programs by storing all season data in a text file named
cowboys_stats.txt. The txt file has 20 seasons to begin with that are read into the array of structs when 
the program is ran. The user can also add a season to the data which is first added to the array of structs
and then added to the cowboys_stats.txt file using a saveToFile function. The user also has the option
to save data to their own file, this file persists between runs and they have the option to save every 
piece of data displayed to the screen

- Did you consider alternative approaches? If so, why did you not use them?  



## 3. Testing Summary
- **Structured Testing Log:** Include a table with test cases, expected output, actual output, and pass/fail status.  
- What testing methods did you use?  
- Provide examples of test inputs (valid and invalid) and describe how your program responds. 

TC-01
Description: Compare 2 seasons
Input: 2007 2023
Expected Output: Here is your comparasion report!
|Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|
2007      13        3         0         28.4         20.3         Lost Divisional Round              
2023      12        5         0         29.9         18.5         Lost Wild Card Round  
Actual Output: Here is your comparasion report!
|Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|
2024      7         10        0         20.6         27.5         Missed Playoffs                    
2024      7         10        0         20.6         27.5         Missed Playoffs  

Pass/Fail: F

TC-02
Description: Compare 2 seasons
Input: 2007 2023
Expected Output: Here is your comparasion report!
|Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|
2007      13        3         0         28.4         20.3         Lost Divisional Round              
2023      12        5         0         29.9         18.5         Lost Wild Card Round  
Actual Output: Here is your comparasion report!
|Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|
2007      13        3         0         28.4         20.3         Lost Divisional Round              
2023      12        5         0         29.9         18.5         Lost Wild Card Round   

Pass/Fail: P

TC-03
Description: Adding new season then calling sort playoff success
Input: 4 1999 10 5 0 24.9 20.3 Missed Playoffs 5 6
Expected Output: Here is your comparasion report!
|Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|
2007      13        3         0         28.4         20.3         Lost Divisional Round              
2023      12        5         0         29.9         18.5         Lost Wild Card Round  
Actual Output: 
*********************************************************
*                                                       *
* ===== Dallas Cowboys Seasons By Playoff Success ===== *
*                                                       *
*                                                       *
* |Year|                |PLAYOFF SUCCESS|               *
* 1999                Missed Playoffs                   *                 
* 2023                Lost Wild Card Round              *                 
* 2022                Lost Divisional Round             *                 
* 2021                Lost Wild Card Round              *                 
* 2020                Missed Playoffs                   *                 
* 2019                Missed Playoffs                   *                 
* 2018                Lost Divisional Round             *                 
* 2017                Missed Playoffs                   *                 
* 2016                Lost Divisional Round             *                 
* 2015                Missed Playoffs                   *                 
* 2014                Lost Divisional Round             *                 
* 2013                Missed Playoffs                   *                 
* 2012                Missed Playoffs                   *                 
* 2011                Missed Playoffs                   *                 
* 2010                Missed Playoffs                   *                 
* 2009                Lost Divisional Round             *                 
* 2008                Missed Playoffs                   *                 
* 2007                Lost Divisional Round             *                 
* 2006                Lost Wild Card Round              *                 
* 2005                Missed Playoffs                   *                 
* 2024                Missed Playoffs                   *                 
* Hope to see a Superbowl soon :(                       *
*********************************************************
Would you like to save this data to your personal file? (Y/N)

Pass/Fail: F
Explanation: 1999 printed at the top of the list even though they missed the playoffs that year so it should actually be at the bottom of the list

TC-04
Description: Adding new season then calling sort playoff success
Input: 4 1999 10 5 0 24.9 20.3 Missed Playoffs 5 6
Expected Output: Here is your comparasion report!
|Year|   |W|       |L|       |T|       |PPG|       |OPP PPG|     |Playoff Results|
2007      13        3         0         28.4         20.3         Lost Divisional Round              
2023      12        5         0         29.9         18.5         Lost Wild Card Round  
Actual Output: 
*********************************************************
*                                                       *
* ===== Dallas Cowboys Seasons By Playoff Success ===== *
*                                                       *
*                                                       *
* |Year|                |PLAYOFF SUCCESS|               *
* 2022                Lost Divisional Round             *                 
* 2018                Lost Divisional Round             *                 
* 2016                Lost Divisional Round             *                 
* 2014                Lost Divisional Round             *                 
* 2009                Lost Divisional Round             *                 
* 2007                Lost Divisional Round             *                 
* 2023                Lost Wild Card Round              *                 
* 2021                Lost Wild Card Round              *                 
* 2006                Lost Wild Card Round              *                 
* 2015                Missed Playoffs                   *                 
* 2017                Missed Playoffs                   *                 
* 2013                Missed Playoffs                   *                 
* 2012                Missed Playoffs                   *                 
* 2011                Missed Playoffs                   *                 
* 2010                Missed Playoffs                   *                 
* 2020                Missed Playoffs                   *                 
* 2008                Missed Playoffs                   *                 
* 2019                Missed Playoffs                   *                 
* 2024                Missed Playoffs                   *                 
* 2005                Missed Playoffs                   *                 
* 1999                Missed Playoffs                   *                 
* Hope to see a Superbowl soon :(                       *
*********************************************************
Would you like to save this data to your personal file? (Y/N)
Pass/Fail: P
Explanation: In the txt files the strings somehow accumulated extra whitespace at the end making them 
not match with specified strings in the program, therefor making all playoff success print in year order 
instead of order of highest to lowest success. So I fixed the whitespace.



---

## 4. Technical Walkthrough
- Explain the main functionality of your program.  
- **Include a link to your required video demonstration** showcasing how the project works (**3-7 minutes**). 
    Make sure it shareable without approval needed.

---

## 5. Challenges and Lessons Learned
- What challenges did you encounter while working on this project?  
- What key lessons did you learn about programming and problem-solving?  

---

## 6. Future Improvements
- If you had more time, what changes or enhancements would you make?  

STUDY BINARY SEARCH
PRINT ALGORITHMS AND STUDY
IF IT IS SORTED USE BINARY SEARCH
USE LAB INSTRUCTIONS? PUT IN CHAT? 