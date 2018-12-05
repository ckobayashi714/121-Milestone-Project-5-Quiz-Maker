// Author: Paul Salvador Inventado
// Date: November 4, 2018
//
// Contains classes and functions used to define a quiz that contains questions
// with corresponding answers
// Filename: quiz.hpp
#pragma once
#include <iostream>
using namespace std;

class question {
private:
  string _text;
  string _answer;

public:
  question(string text, string answer) {
    _text = text;
    _answer = answer;
  }
  question() : question("", "") {}

  void set_text(string text) { _text = text; }
  void set_answer(string answer) { _answer = answer; }
  string text() { return _text; }
  string answer() { return _answer; }
  bool check(string answer) { return answer == _answer; }
  string as_save_text() { return "[SQ]\n" + _text + "\n" + _answer + "\n"; }
};

class quiz {
private:
  question *_questions;
  int _size;
  int _capacity;

public:
  quiz(int capacity) {
    _size = 0;
    _capacity = capacity;
    _questions = new question[capacity];
  }
  quiz() : quiz(100) {}
  ~quiz() { delete[] _questions; }

  void set_size(int size) { _size = size; }
  void set_capacity(int capacity) { _capacity = capacity; }
  int size() { return _size; }
  int capacity() { return _capacity; }
  void add_question(question q);
  question get_question(int index) { return _questions[index]; }
  void display();
  void save(string filename);
  void load(string filename);
};

question create_question();
