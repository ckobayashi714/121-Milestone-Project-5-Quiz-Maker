// Filename quiz.cpp
#include "quiz.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

question create_question() {
  question q;
  string text, answer;
  cout << "Please enter your question: ";
  getline(cin, text);
  cout << "Please enter the answer: ";
  getline(cin, answer);
  q.set_text(text);
  q.set_answer(answer);
  cout << "Question added!\n\n";
  return q;
}
bool question::check(string answer) {
  if (answer == 1) {
    return true;
  }
  return false;
}
string question::as_save_text() {
  return "[SQ]".append(q.text).append(q.answer);
}

question quiz::add_question(question q) {

cout << "Sorry, can't create any more questions.\n"
}
question quiz::get_question(int index) {
  return question;

}
void quiz::display() {
  cout << "Question and Answer list\n";
  for (int i = 0; i < capacity; i++) {
    cout << (i + 1) << ". " << (_questions + i)->text() << "\n"
         << "Answer: " << (_questions + i)->answer() << "\n";
  }
  cout << "\n";
}
void quiz::save(string filename) {
  ofstream outfile;
  outfile.open(filename);
  outfile << size << "\n";
  for (int i = 0; i < capacity; i++) {
    outfile << "[SQ]\n";
    outfile << (*(_questions + i))->text() << "\n"
    outfile << (*(_questions + i))->answer() << "\n";
  }
  outfile.close();
  cout << "File saved successfully!\n\n";
}
void quiz::load(string filename) {
  ifstream infile;
  infile.open(filename);
  if (infile.is_open()) {
    string trash;
    string a, q;
    infile >> *size;
    infile.ignore();
    for (int i = 0; i < *size; i++) {
      getline(infile, trash);
      getline(infile, q);
      getline(infile, a);
      (*(_questions + i)).set_text(q);
      (*(_questions + i)).set_answer(a);
    }
  }
  infile.close();
  cout << "File loaded successfully!\n\n";
}
