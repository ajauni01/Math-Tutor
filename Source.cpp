/*****************************************************************************
Program    : Math Tutor
Programmer : Ajharul Islam Aunik
Last Edited: 10/30/22

Description:  This program gives the user three opportunities to answer a
series of elementary math questions. These questions are generated at random.
It also inquires whether the user wishes to continue playing; if the user 
declines, the program thanks the user and displays the report. 
The report is generated primarily by storing user data in a two-dimensional
vector; finally, the program reads user data from the two-dimensional vector 
and outputs the questions, answers, and the number of attempts required to solve
those questions. If the user cannot correctly answer the question after three
attempts, the program labels the user's responses as "incorrect." In addition,
this math game is designed specifically for children; if the random number on 
the left is greater than the random number on the right, 
logic has been programmed to flip them, and the result is always positive.
This program also includes a statement to avoid fractions, as its intended 
user is young children.

********************************************************************************/


#include <algorithm> // to convert the user response to uppercase
#include <cstdlib>  // for generating random numbers & srand() function
#include <ctime>    // for system time
#include <iomanip>  // to right align the integers in the summary section
#include <iostream> // for basic inputs and outputs
#include <string>   // for generating string
#include <vector>   // to generate two dimensional vector to store the user data
 

using namespace std;

int main() {
    //DEBBIE: const and enum should be the first items you declare in main and you should at least document some of your variables
  // Declare the variables, and initialize them
    enum OperatorTypes { ADD, SUBSTRACT, MULTIPLY, DIVIDE };
    const int MAX_ATTEMPT = 3; //the number of attempts user can have to answer questions
    string firstName = "?";
    int leftRandNum = 0;
    int rightRandNum = 0;
    int operatorRandNum = 0; //dictate whether the question is about addition, subtraction, multiplication, or division
    int tempValue = 0; // to store value to flip the left and right random numbers if the left random number is less than the right random number.
    int correctAnswer = 0;
    int userAnswer = 0;
    int totalQuestions = 0;
    int totalCorrect = 0;
    string operatorType = "?"; //to store addition, subtraction, multiplication, and division operators
    string userResponse = "Y"; //to initiate the outer while loop
   

    // Display the header
    cout << "-------------------------------------------" << endl;
    cout << "|               MATH TUTOR                |" << endl;
    cout << "-------------------------------------------" << endl;
    // Get user input
    cout << "Please enter your first name: ";
    getline(cin, firstName);
    // Greet user
    cout << "Hello"
        << " " << firstName << "!" << endl;

    // Seed random numbers with current time.
    srand(time(0));


    vector<vector<int> > mathData;// declare the two dimensional vector variable to store the user input

    while (userResponse == "Y" || userResponse == "YES") {

        ++totalQuestions;

        leftRandNum = rand() % 10 + 1; // to generate a random number from 0 to 10
        rightRandNum = rand() % 10 + 1; // to generate a random number from 0 to 10
        operatorRandNum = rand() % 4; //to generate random number from 0 to 3 
                                      // 0 = addition, 1 = Subtraction, 2 = Multiplication, 3 = Division

        // To make sure that LeftRandNum is always biggger than RightRandNum
        if (leftRandNum < rightRandNum) {
            tempValue = leftRandNum;
            leftRandNum = rightRandNum;
            rightRandNum = tempValue;
        }

        // int OperatorRandNum = 100; // To test the default
        // Using Switch statements to execute the logics

   vector <int> rowNum = { leftRandNum, operatorRandNum, rightRandNum }; // to temporarily store a row's data

        switch (operatorRandNum) {



        case ADD:
            operatorType = "+";
            correctAnswer = leftRandNum + rightRandNum;

            break;

        case SUBSTRACT:
            operatorType = "-";
            correctAnswer = leftRandNum - rightRandNum;

            break;

        case MULTIPLY:
            operatorType = "*";
            correctAnswer = leftRandNum * rightRandNum;

            break;

        case DIVIDE:

            operatorType = "/";
            correctAnswer = leftRandNum; // To avoid fractions
            leftRandNum *= rightRandNum; // To avoid fractions

            break;

        default: // For any unexpected OperatorRandNum
            cout << "Invalid question type:" << operatorRandNum << endl;
            cout << "Program ended with an error -1" << endl;
            cout << "Please report this error to Ajharul Islam Aunik" << endl;
            return -1;
        }

        cout << endl;
        cout << endl;




        for (int i = 1; i <= MAX_ATTEMPT; ++i) { //provides the user three opportunities to answer the question correctly
           

         if (i == 1) {  
                cout << "-----------"
                    << "1st Attempt"
                    << "----------------" << endl;
                cout << endl;

            }

            else if (i == 2) {
                cout << endl;

                cout << "-----------"
                    << "2nd Attempt"
                    << "----------------" << endl;

                cout << endl;

            }

            else if (i == 3) {
                cout << endl;

                cout << "-----------"
                    << "3rd Attempt"
                    << "----------------" << endl;

                cout << endl;
            }

            cout << "What is"
                << " " << leftRandNum << operatorType << rightRandNum << "?";

            // to handle the non integer input
            while (!(cin >> userAnswer)) { //DEBBIE: really should document all of this because it's all very confusing
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number: " << endl;
            }

            if (userAnswer == correctAnswer) {

                rowNum.push_back(i);
                
                cout << "Awesome! Your answer is correct." << endl;
                ++totalCorrect;
                cout << endl;
                break;

            } 

            else {
                cout << "Opps! Your answer is incorrect!" << endl;

                rowNum.push_back(0);

      
            }

            cout << "You have"
                << " " << MAX_ATTEMPT - i << " "
                << "attempts left" << endl;

            cout << endl;
        }

        // end of for loop

        mathData.push_back(rowNum);

        //ask the user whether he wants to continue this game

        cout << "Do you want to continue this game (Y= YES | N= NO) " << endl;
        

        cin >> userResponse; //get the user's response

        

      //convert the response to uppercase 

        for_each(userResponse.begin(), userResponse.end(), [](char& c) {
             c = ::toupper(c);

             });

        cout << endl;

        // thank the user if he does not want to contiue the game

        if (userResponse == "N" || userResponse == "N0") {

            cout << "Thank you for playing this game. Your report is given below." << endl;

        }
}

// end of outer while loop



cout << endl;

//display the math detail report title

cout << "|-------------------------------------------------|" << endl;
cout << "|--------------" << "MATH DETAIL REPORT" <<"-----------------|" << endl;
cout << "|-------------------------------------------------|" << endl;
cout << endl;

   

cout << setw(5) << "QUESTIONS" << setw(16) << right << "ATTEMPTS" << endl;
cout << endl;
  

    int findAttempt = 0; //to find the last index of the row
    int totalAttempt = 0; // using the 'findAttempt' variable, we can find the last attempt 
                          // which tells us the number of attempts the user took
    string totalAttempt2 = "?"; // if the user could not answer the questions correctly even after three attemptd
    

    for (int i = 0; i < mathData.size(); ++i) {

        leftRandNum = mathData.at(i).at(0);

        operatorRandNum = mathData.at(i).at(1);

        rightRandNum = mathData.at(i).at(2);

        findAttempt = mathData.at(i).size() - 1; // find the index for the last item of the row
        totalAttempt = mathData.at(i).at(findAttempt); // use the last index to find the total attempts
       
  // another switch statement to display the math operator type and correct answer along with
   //the questions and number of attempts
        
        switch (operatorRandNum) {



        case ADD:

            operatorType = "+";
            correctAnswer = leftRandNum + rightRandNum;

            break;

        case SUBSTRACT:
            operatorType = "-";
            correctAnswer = leftRandNum - rightRandNum;
            break;

        case MULTIPLY:
            operatorType = "*";
            correctAnswer = leftRandNum * rightRandNum;

            break;

        case DIVIDE:

            operatorType = "/";
            correctAnswer = leftRandNum;
            leftRandNum *= rightRandNum;


           
         

            break;

        default: // For any unexpected OperatorRandNum
            cout << "Invalid question type:" << operatorRandNum << endl;
            cout << "Program ended with an error -1" << endl;
            cout << "Please report this error to Ajharul Islam Aunik" << endl;
            return -1;
        }

        // end of switch statements
     

        if (totalAttempt == 0) { // if the user is unable to provide correct answer after three attempts

            totalAttempt2 = "Incorrect";

  cout << setw(2) << leftRandNum << " " << operatorType << " " << setw(3) << left << rightRandNum << "=" << " " << correctAnswer << " " << setw(12) << right << totalAttempt2 << endl;



        }

    else {

     cout <<setw(3) << leftRandNum << " " << operatorType << " " << setw(2) << left << rightRandNum << "=" << " " << correctAnswer << " " << setw(7) << right << totalAttempt << endl;

        }
     
    }

    // end of report





    return 0;
}
