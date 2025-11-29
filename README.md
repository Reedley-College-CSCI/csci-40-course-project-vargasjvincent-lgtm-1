[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7mdzU3H2)
# CS1 Final Project - Dallas Cowboys Stat Finder
MENTION <SSTREAM>
## 1. Overview
- What problem does your project solve?  
Stats are easily accessible on the internet but when it comes to comparing certain stats across seasons, websites can become lackluster, there is not a great way to view and pull up different stats from different seasons. This project will give the user the ability to do just that.
- Briefly describe the purpose and key features of your program.  
Purpose: Give user an easy and accessible main menu that gives options to compare different stats from across seasons. Also have the ability to save stats in a file and add stats to the data.
Key Features: 

---

## 2. Design Decisions
- What fundamental programming constructs and data types did you use, and why?  
- Why did you choose to structure your data using structs?  
- How did you implement searching and sorting? What algorithms did you use and why?  
- How do you ensure data persistence between program runs?  
- Did you consider alternative approaches? If so, why did you not use them?  

---

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
