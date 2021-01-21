# BasicCPhoneBook
Basic Telephone Book program:

• Our program is a basic program that reads and stores phone book data for out users in a text file.

• The program offers the option to read a text file sort it, print what is inside it, Delete, Modify or add an entry to the file.

• The program is very efficient and uses the latest sorting and searching algorithms and works well on large files as well as small ones.

# User Manual #
• First of all you need to put a text file in the program directory which has the data stored in as follows:
lastname,firstname,phone number,address,day,month,year,email

• Then you should run the program and provide the name of the text file to it with the extenstion .txt at the end. Ex:”text.txt”.

• Then you should choose what you want the program to do with your data using the menu shown to you.

• Be careful to save before quitting the program or it will not save any of your changes.

• Make sure that if you use the add entry function to add the data in the correct format and the correct order.

### The use of structures in the program ###
1. Entry:
It is the structure that defines each entry in the file, each entry must have a last name, first name, phone number, address and an email address as strings (phone number is a string because the 0 at the beginning will not appear in an integer) and birthdate (which is an instance of birth).
2. Birth:
It is the structure that defines the birthdate of each entry and it holds a birth day, month and year as integers.

### Global Variables ###
1. FILE *f:
We make our file a global variable to avoid declaring it every time we must use it.
2. Entry *content:
We make our content array which holds all entries in the file a global variable so we don’t have to load it every time and so we can manipulate it without manipulating the original file.
3. Char fileName[20]:
We make our file name a global variable to avoid asking the user for the name of the file multiple time in different functions because no one likes to be asked the same question multiple times.
4. int numRecords:
This variable holds the number of records we have in our file, it is helpful to make it a global variable, so we don’t have to count the number of our entries every time we want to loop out entries.
5. int end=0:
This variable is the variable we check to know if the user want to terminate the program, it can be changed by many functions and checked by the MENU() function so we have to make it a global variable. It is initialized to 0 because if it changes to 1 we terminate the program.

### Helping functions in the program ###
1. int makeDigit(char *s):
This function takes a string of numbers and changes it to an integer. This is very useful when we need to read the file from the user, we want to store the birth date as a number to be able to perform operations like sorting on it later.
2. int validateDate(int day,int month,int year):
This function helps us validate that the user has input a valid date by checking if the day or month or year is a negative number or if the day or month are above their logical limits.
3. int validatePhone(char s[]):
This function helps us validate that the phone number is valid by checking if all the characters the user input are numbers and have no strings.
4. int validateEmail(char s[]):
This function helps us validate the email address by checking if it has an “@” and a “.” in it.
5. int compare(Birth a , Birth b):
This function takes 2 instances of Birth and compares them to check which one is older. We use this function in the sortByDOB function.
### Main functions of the program ###
1. void LOAD():
This function asks the user for the name of the file he wants to load the data from, then takes all that data to an array of the structure Entry with each element in the array represents a line in the text file. It first opens the file the user want to load from in read mode, then it reads strings from it and saves them to the content array while incrementing the numRecords variable. Then it allocates memory for the
content array with the number of records. Then it saves every entry in its appropriate structure. After our content array is ready, we can then use the rest of the functions.
2. void ADD():
This function adds an entry to out content array. It starts by making variables to hold all our data so we can check it before we advance and allocate memory for it. Then we ask the user for all the appropriate data while checking it with some of our helping functions, if all the data is valid, we increment the numRecords variable then we allocate memory for one more position in our content array and empty the variables in that position.
3. void QUERY():
This function searches for last name provided by the user in the content array and prints all entries with that last name.
The exact mechanism of the search is by looping through every entry and getting it’s last name and comparing it with the last name the user entered with the strcmp() function, if they are the same the program puts a flag and prints the entry if the flag is not changed we tell the user that we didn’t find what he is looking for.
4. void Print():
This function asks the user in what order they want to print date of birth or last name and routes them to the function with a switch.
5. void SortByDOB():
This function sorts the entries in content then prints it in order of oldest date of birth. The exact mechanism of how it does this is by using bubble sorting, it repeatedly steps through the array every time it checks the date of birth of every 2 element together to check who is older with the help of the compare() function. It then prints the sorted list to the user.
6. void sortByLname():
This function sorts the entries in content then prints it in alphabetical order. The exact mechanism of how it does it is by using bubble sorting, it repeatedly steps through the array every time it checks every two last names with the strcmp() function. Then it prints the sorted list to the user.
7. void MODIFY():
This function asks the user for the last name of a person in the file and allows him to change his data to correct mistakes. It uses the same searching algorithm as the QUERY() function but instead of printing the entry it saves it’s index and asks the user for the new data while checking it for errors just like the ADD() function. If all the data is correct, it saves in the index we saved earlier.
8. void DELTE():
This function asks the user for the last name of a person in the file and deletes its entry. It uses the same searching algorithm as the QUERY() function but instead of printing the entry it saves it’s index. It then overwrites this entry by moving every entry behind it a step up, decrements the numRecords variable and reallocates memory for the content array with the new value.
9. void SAVE():
This function saves whatever is in our content array back in the file we loaded from in the beginning. It does this by opening it in write mode, putting every entry of our array in a buffer string using sprint() and putting a new line at the end and closing the file.
10. void QUIT():
This function asks the user if he is sure he wants to quit and that every thing that they have not saved will be deleted, if they are sure the program changes the end variable to 1 so the MENU() function doesn’t loop any more.
11. void MENU():
This function is the core of our program it first calls the LOAD() function to load the file, since the program need a file name and to allocate memory for content. Then it asks the user what he needs to do while displaying a menu of all our functions and routing the user through a switch. The MENU() function keeps looping until the end variable is changed.
The main code:
The main code for this program is very simple because all of our core features are in functions and loaded by the MENU() function. It just prints the title of the program and then calls the MENU() function.
### Algorithms ###
1. Sorting:
All soring algorithms in this program use the bubble sort concept which works by passing through the array several times each time checking each to element together and putting the least first (ascending order).
2. Searching:
All searching algorithms in this program use a basic linear search algorithm which works by looping through the array and checking if the element we are positioned at is the one we need.
