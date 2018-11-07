#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "gtest_ext.h"
#include "../quiz.hpp"
using ::testing::HasSubstr;
using ::testing::StartsWith;
using ::testing::MatchesRegex;
using ::testing::ContainsRegex;

TEST(question, PublicMethodsPresent) {
  question q;
  ASSERT_NO_THROW({
    q.text();
    q.answer();
    q.set_text("a");
    q.set_answer("b");
    q.as_save_text();
    q.check("c");
  });
}

TEST(question, DefaultConstructor) {
  question q;
  ASSERT_EQ(q.text(), "");
  ASSERT_EQ(q.answer(), "");
}

TEST(question, TextAnswerConstructor) {
  std::string unittest_text, unittest_answer;
  unittest_text = generate_string(10);
  unittest_answer = generate_string(10);
  question q(unittest_text, unittest_answer);
  ASSERT_EQ(q.text(), unittest_text);
  ASSERT_EQ(q.answer(), unittest_answer);
}

TEST(question, MutatorsAndAccessors) {
  question q;
  std::string text, answer;
  text = generate_string(10);
  answer = generate_string(10);
  ASSERT_NO_THROW({
    q.set_text(text);
    q.set_answer(answer);
  });
  ASSERT_EQ(q.text(), text);
  ASSERT_EQ(q.answer(), answer);
}

TEST(question, as_save_text) {
  question q;
  std::string text, answer;
  text = generate_string(10);
  answer = generate_string(10);
  q.set_text(text);
  q.set_answer(answer);
  std::string unittest_output = "[SQ]\n" + text + "\n" + answer + "\n";
  ASSERT_EQ(q.as_save_text(), unittest_output);
}

TEST(question, check) {
  question q;
  std::string correct_answer, incorrect_answer;
  correct_answer = generate_string(10);
  incorrect_answer = generate_string(10);
  q.set_answer(correct_answer);
  ASSERT_TRUE(q.check(correct_answer));
  ASSERT_FALSE(q.check(incorrect_answer));
}

TEST(quiz, DefaultConstructor) {
  quiz q;
  ASSERT_EQ(q.size(), 0);
  ASSERT_EQ(q.capacity(), 100);
}

TEST(quiz, CapacityConstructor) {
  int unittest_capacity = rand() % 100 + 1;
  quiz q(unittest_capacity);
  ASSERT_EQ(q.size(), 0);
  ASSERT_EQ(q.capacity(), unittest_capacity);
}

TEST(quiz, add_question) {
  quiz q(3);
  for (int i = 0; i < 3; i++) {
    q.add_question(question());
    int unittest_changed_size = i + 1;
    ASSERT_EQ(q.size(), unittest_changed_size);
  }
  ASSERT_SIO_EQ("", "Sorry, can't create any more questions.\n", {
    q.add_question(question());
  });
}

TEST(quiz, get_question) {
  int capacity = rand() % 10 + 1;
  quiz q(capacity);
  question* questions = new question[capacity];

  for (int i = 0; i < capacity; i++) {
    std::string text, answer;
    text = generate_string(10);
    answer = generate_string(10);
    question temp = question(text, answer);
    questions[i] = temp;
    q.add_question(temp);
  }

  for (int i = 0; i < capacity; i++) {
    question unittest_question_object = questions[i];
    ASSERT_EQ(q.get_question(i).text(), unittest_question_object.text());
    ASSERT_EQ(q.get_question(i).answer(), unittest_question_object.answer());
  }
}

TEST(quiz, display) {
  int capacity = rand() % 10 + 1;
  quiz q(capacity);
  std::ostringstream unittest_display;
  unittest_display << "Question and Answer list\n";

  for (int i = 0; i < capacity; i++) {
    std::string text, answer;
    text = generate_string(10);
    answer = generate_string(10);
    unittest_display << (i+1) << ". " << text << "\n" << "Answer: " << answer
                     << "\n";
    q.add_question(question(text, answer));
  }
  unittest_display << "\n";
  ASSERT_SIO_EQ("", unittest_display.str(), {
    q.display();
  });
}

TEST(quiz, save) {
  for(int i = 0; i < 10; i++) {
    int repetitions = rand() % 10 + 1;
    quiz q(repetitions);

    question questions[repetitions];
    std::string expected_file_contents = std::to_string(repetitions) + "\n";
    for (int j = 0; j < repetitions; j++) {
      std::string text, answer;
      text = generate_string(10);
      answer = generate_string(10);

      q.add_question(question(text, answer));

      expected_file_contents += "[SQ]\n";
      expected_file_contents += text + "\n";
      expected_file_contents += answer + "\n";
    }

    std::string filename = generate_string(5) + ".txt";
    ASSERT_DURATION_LE(3, {
      ASSERT_SIO_EQ("", "File saved successfully!\n\n", {
        q.save(filename);
      });
    });

    ifstream save_file(filename);
    ASSERT_TRUE(save_file.good()) << "Save file was not created";
    std::string actual_file_contents, temp_holder;
    while(save_file >> temp_holder) {
      actual_file_contents += temp_holder + "\n";
    }
    save_file.close();
    remove(filename.c_str());

    ASSERT_EQ(actual_file_contents, expected_file_contents);
  }
}

TEST(quiz, load) {
  for(int i = 0; i < 10; i++) {
    int file_questions_size = rand() % 10 + 1;
    question* file_questions = new question[file_questions_size];
    std::string file_contents = std::to_string(file_questions_size) + "\n";
    for (int j = 0; j < file_questions_size; j++) {
      std::string text, answer;
      text = generate_string(10);
      answer = generate_string(10);
      file_questions[j].set_text(text);
      file_questions[j].set_answer(answer);
      file_contents += "[SQ]\n";
      file_contents += text + "\n";
      file_contents += answer + "\n";
    }

    std::string filename = generate_string(5) + ".txt";
    ofstream out_file(filename);
    out_file << file_contents;
    out_file.close();

    quiz q;
    ASSERT_DURATION_LE(3, {
      ASSERT_SIO_EQ("", "File loaded successfully!\n\n", {
        q.load(filename);
      });
    });

    ASSERT_EQ(q.size(), file_questions_size);
    ASSERT_EQ(q.capacity(), file_questions_size + 30);
    for (int j = 0; j < file_questions_size; j++) {
      ASSERT_EQ(q.get_question(j).text(), file_questions[j].text());
      ASSERT_EQ(q.get_question(j).answer(), file_questions[j].answer());
    }
    delete[] file_questions;
    remove(filename.c_str());
  }
}
//

TEST(Global, CreateQuestion) {
  for(int i = 0; i < 10; i++) {
    std::string text, answer;
    text = generate_string(10);
    answer = generate_string(10);
    question temp, actual;
    temp.set_text(text);
    temp.set_answer(answer);
    std::string input = text+"\n"+answer;
    SIMULATE_CIN(input, {
      actual = create_question();
    });
    ASSERT_EQ(temp.text(), actual.text());
    ASSERT_EQ(temp.answer(), actual.answer());
  }
}



TEST(main, CreateQuestionChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nPlease enter your question: Please enter the "
                         "answer: Question added!\n\nWhat would you like to do?"
                         "\na. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit"
                         "\nChoice: \nThank you for using QuizMaker!\n";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", "a\nX\nX\ne", expected);
  });
}

TEST(main, FiniteChoiceLoop) {
  srand (time(NULL));
  ASSERT_DURATION_LE(3, {
    main_output("quizgen", "a\nX\nX\ne");
  });
}

TEST(main, DisplayQuestionsChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nPlease enter your question: Please enter the "
                         "answer: Question added!\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nQuestion and Answer list\n1. X\nAnswer: X"
                         "\n\nWhat would you like to do?\na. Create a question"
                         "\nb. Display questions\nc. Save questions\nd. Load "
                         "questions\ne. Quit\nChoice: \nThank you for using "
                         "QuizMaker!\n";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", "a\nX\nX\nb\ne", expected);
  });
}

TEST(main, SaveQuestionsChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nWhat filename would you like to use? File "
                         "saved successfully!\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nThank you for using QuizMaker!\n";
  string filename = generate_string(5) + ".txt";
  string input = "c\n" + filename + "\ne";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", input, expected);
  });
  std::remove(filename.c_str());
}

TEST(main, LoadQuestionsChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nWhat file would you like to load? File "
                         "loaded successfully!\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nThank you for using QuizMaker!\n";
  string filename = generate_string(5) + ".txt";
  string input = "d\n" + filename + "\ne";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", input, expected);
  });
  std::remove(filename.c_str());
}

TEST(main, QuitChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nThank you for using QuizMaker!\n";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", "e", expected);
  });
}

TEST(main, InvalidOptionChoice) {
  std::string expected = "Welcome to QuizMaker\n\nWhat would you like to do?\n"
                         "a. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nInvalid option\n\nWhat would you like to "
                         "do?\na. Create a question\nb. Display questions\n"
                         "c. Save questions\nd. Load questions\ne. Quit\n"
                         "Choice: \nThank you for using QuizMaker!\n";
  ASSERT_DURATION_LE(3, {
    ASSERT_EXECIO_EQ("quizgen", "x\ne",expected);
  });
}

TEST(main, ChoiceLoopLowercase) {
  int repetitions = rand() % 10 + 1;
  for (int i = 0; i < repetitions; i++) {
    std::string input = "";
    std::string question_list = "Question and Answer list\n";
    std::string expected = "Welcome to QuizMaker\n\n";
    std::vector<std::string> filenames;
    std::string load_file_name = generate_string(10) + ".txt";
    ofstream out_file(load_file_name);
    out_file << 1 << "\n" << "[SQ]\nq\na\n";
    out_file.close();
    int question_ctr = 1;
    char choice;
    do {
      choice = rand() % 5 + 97;
      expected += "What would you like to do?\na. Create a question\n"
                  "b. Display questions\nc. Save questions\nd. Load questions\n"
                  "e. Quit\nChoice: \n";
      std::string s_choice(1, choice);
      input += s_choice + "\\n";
      switch (choice) {
        case 'a':
          expected += "Please enter your question: Please enter the answer: "
                      "Question added!\n\n";
          input += "q\\na\\n";
          question_list += std::to_string(question_ctr) +". q\nAnswer: a\n";
          question_ctr++;
          break;
        case 'b':
          expected += question_list + "\n";
          break;
        case 'c':
          {
            expected += "What filename would you like to use? File saved successfully!\n\n";
            std::string filename = generate_string(5) + ".txt";
            filenames.push_back(filename);
            input += filename+"\n";
            break;
          }
        case 'd':
          {
            expected += "What file would you like to load? File loaded successfully!\n\n";
            input += load_file_name+"\n";
            question_list = "Question and Answer list\n1. q\nAnswer: a\n";
            question_ctr = 2;
            break;
          }
        case 'e':
          expected += "Thank you for using QuizMaker!\n";
          break;
        default:
          expected += "Invalid option\n\n";
      }
    } while(choice!= 'e');
    ASSERT_DURATION_LE(3, {
      ASSERT_EXECIO_EQ("quizgen", input, expected);
    });
    remove(load_file_name.c_str());
    for(std::string fn : filenames) {
      remove(fn.c_str());
    }
  }
}

TEST(main, ChoiceLoopUppercase) {
  int repetitions = rand() % 10 + 1;
  for (int i = 0; i < repetitions; i++) {
    std::string input = "";
    std::string question_list = "Question and Answer list\n";
    std::string expected = "Welcome to QuizMaker\n\n";
    std::vector<std::string> filenames;
    std::string load_file_name = generate_string(10) + ".txt";
    ofstream out_file(load_file_name);
    out_file << 1 << "\n" << "[SQ]\nq\na\n";
    out_file.close();
    int question_ctr = 1;
    char choice;
    do {
      choice = rand() % 5 + 65;
      expected += "What would you like to do?\na. Create a question\n"
                  "b. Display questions\nc. Save questions\nd. Load questions\n"
                  "e. Quit\nChoice: \n";
      std::string s_choice(1, choice);
      input += s_choice + "\\n";
      switch (choice) {
        case 'A':
          expected += "Please enter your question: Please enter the answer: "
                      "Question added!\n\n";
          input += "q\\na\\n";
          question_list += std::to_string(question_ctr) +". q\nAnswer: a\n";
          question_ctr++;
          break;
        case 'B':
          expected += question_list + "\n";
          break;
        case 'C':
          {
            expected += "What filename would you like to use? File saved successfully!\n\n";
            std::string filename = generate_string(5) + ".txt";
            filenames.push_back(filename);
            input += filename+"\n";
            break;
          }
        case 'D':
          {
            expected += "What file would you like to load? File loaded successfully!\n\n";
            input += load_file_name+"\n";
            question_list = "Question and Answer list\n1. q\nAnswer: a\n";
            question_ctr = 2;
            break;
          }
        case 'E':
          expected += "Thank you for using QuizMaker!\n";
          break;
        default:
          expected += "Invalid option\n\n";
      }
    } while(choice!= 'E');
    ASSERT_DURATION_LE(3, {
      ASSERT_EXECIO_EQ("quizgen", input, expected);
    });
    remove(load_file_name.c_str());
    for(std::string fn : filenames) {
      remove(fn.c_str());
    }
  }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
