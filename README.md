# Loan-Management-System-Experiment
 
In this Repo, i experiment with python and c++ features to create a Loan Management System. This repo basically works as a proof of concept, especially with python features that I am not fully skilled in. The whole idea is to actually see how things work, take a look at trade offs in readability maintainability, and scalability. This allows me to gain experience in the python language, while also having first hand experience on the structure of the loan management system.
Currently, I intend to use the loan management cpp library as is. 

# Current Features
  1.) Generate data <br>
  2.) Client - Server functionality <br>
  3.) Storing data in sqlite3 database <br>
  4.) Recieving user data from web app <br>
  5.) Recieving user data from command line interface <br>
  5.) Displaying user data once received from database both in cli and web app <br>
  6.) Using csv file for analysis of data in excel, possibly data analysis in python <br>
  6.) Retrieving stored user data from web app and cli <br>
  7.) Experimented with and successfully used Linear / Matrix algebra to simplify and optimize multiple function calls to a simple linear equation with high Accuracy <br>
  8.) Improved database insert speed. <br>

# Extending Features
- Sqlite3 C++ database abstraction <br>

 # Known Future Changes
  1.) A revision of the risk assessment methods to utilise statistics, this will be added once i have finished a basic statistics library in c++ <br>
  2.) Currently looking at possibilities of making the program more linux friendly. <br>

# Using Deprecated Files
The current server based files currently has most of the functionality used in the depricated files, however if you want to use or modify the depricated files, remove them from the depricated files folder, and place them back into the Loan Management System Experiment folder <br>

# Dependencies
 1.) C++ compiler (MINGW) version 11 <br>
 2.) Make, which could be downloaded from chocolatey <br>
 3.) Python 3.8 and above <br>
 4.) Sqlite3 database <br>
 5.) Included logger for logging while debugging. <br>

# Installation
 1.) Install Python <br>
 2.) Install a Mingw and add it to path <br>
 3.) Install make and add it to path manually, or use chocolatey to add it automatically. <br>
 4.) Get an alpha vantage api key for free, and store it in the file to get up to date federal funds rate and other related metrics. Do note there is an option to use default rate values wihout requiring API keys <br>
 5.) Add the sqlite3 header file into the header files folder, or unzip the similarly named zipped file. <br>

