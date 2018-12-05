// Author: Paul Salvador Inventado
// Date: November 4, 2018
//
// Contains classes and functions used to define a quiz that contains questions
// with corresponding answers
#include "quiz.hpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
  /* This will create an array of 100 question objects*/
  // quiz q;
  // question q;
  // question question;
  quiz quizmaker(50);
  /* This program will reapteadly ask the user to input a question or exit. If
  the user inputs something other than a or b (capital letters too), they will
  be notified with an invalid message, but will then be asked again what option
  they would like to choose.*/
  char choice;
  string filename;

  cout << "Welcome to QuizMaker\n\n";

  do {
    cout << "What would you like to do?\n"
         << "a. Create a question\n"
         << "b. Display questions\n"
         << "c. Save questions\n"
         << "d. Load questions\n"
         << "e. Quit\n"
         << "Choice: ";
    cin >> choice;
    cin.ignore();
    cout << endl;
    switch (choice) {
    case 'a':
    case 'A':
      quizmaker.add_question(create_question());
      break;
    case 'b':
    case 'B':
      quizmaker.display();
      break;
    case 'c':
    case 'C':
      cout << "What filename would you like to use? ";
      getline(cin, filename);
      quizmaker.save(filename);
      break;
    case 'd':
    case 'D':
      cout << "What file would you like to load? ";
      getline(cin, filename);
      quizmaker.load(filename);
      break;
    case 'e':
    case 'E':
      break;
    default:
      cout << "Invalid option\n\n";
    }
  } while (choice != 'e' && choice != 'E');
  cout << "Thank you for using QuizMaker!\n";
  return 0;
}
