// Filename: quiz.hpp
#pragma once

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

question create_question();

class question {
private:
  string _text;
  string _answer;
public:
  void set_text(string text) { _text = text; }
  void set_answer(string answer) { _answer = answer; }
  string text() { return _text; }
  string answer() { return _answer; }

  question() {
    _text = "";
    _answer = "";
  }
  question(string text, string answer) {
    _text = text;
    _answer = answer;
  }
  bool check(string answer);
  string as_save_text();
};

class quiz {
private:
  question *_questions;
  int _size;
  int _capacity;
public:
  void set_size(int size) { _size = size; }
  void set_capacity(int capacity) { _capacity = capacity; }
  int size() { return _size; }
  int capacity() { return _capacity; }

  quiz() {
    _size = 0;
    _capacity = 100;
    _questions = new question[capacity];
  }
  quiz(int capacity) {
    _size = 0;
    _capacity = capacity;
    _questions = new question[capacity];
  }
  ~quiz() {
    delete[] question;
    question = nullptr;
  }
  question add_question(question q);
  question get_question(int index);
  void display();
  void save(string filename);
  void load(string filename);
};
