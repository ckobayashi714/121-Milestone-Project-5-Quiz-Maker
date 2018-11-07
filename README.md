# QuizMaker Project Milestone 5

This is milestone 5 of the [QuizMaker Project](https://docs.google.com/document/d/1kxz9GX_Fm1rGeQZCyvOVQ7Szpre8MZwEgXG5zyMIcI8/edit?usp=sharing).

# Requirements
The goal of this milestone is to refactor our code from Milestone 4 so that it uses proper object-oriented design. Reorganize your code so that it follows the class designs described below. Take note that you have already implemented most functionalities in the previous milestones so you can reuse most of your code.

## question class
### data members
- `_text` - question text
- `_answer` - answer to the question

### constructors
- `question()` - initializes the question object by setting `_text` and
`_answer` as empty strings.
- `question(string text, string answer)` - initializes the question object by
setting `_text` and `_answer` according to the parameters
### member functions
- accessor and mutator functions for `_text` and `_answer`
- `check(string answer)` - returns a `bool` that indicates whether the
parameter is the correct answer to the question
- `as_save_text()` - converts the question object into a `string` that is used
for saving it to a file, the function returns this `string` and follows the
format below
```
[SQ]
question
answer
```

## quiz class
### data members
- `_questions` - pointer to an array of questions in the heap
- `_size` - the number of `question` objects in the array
- `capacity` - total number of `question` objects the array can hold
### constructors/destructors
  - `quiz()` - initialize `_size` to 0, set `_capacity` to 100, and create an
  array with a capacity of 100 `question` objects in the heap
  - `quiz(int capacity)` - initialize `_size` to 0, set `_capacity` to the
  given parameter, and create an array of `question` objects in the heap
  with a capacity according to the parameter
- `~quiz()` - deallocate the memory occupied by the array that `_questions`
points to
### member functions
- accessor functions for `_size` and `_capacity`
- `add_question(question q)` - adds `question` objects to the array until
capacity is reached, updates `_size` accordingly, if capacity is reached display
the error message: `Sorry, can't create any more questions.\n`
- `get_question(int index)` - returns the `question` object in the specified
index   
- `display()` - displays all `question` objects in the array using the following
format (see the expected output for more details)
```
Question and Answer list
1. Question
Answer: Answer

```
- `save(string filename)` - saves all `question` objects to a file whose name is
given as a parameter, this should use the `as_save_text()` function of each
object, use the same format in previous milestones
```
1
[SQ]
Who developed Linux?
Linus Torvalds
```
- `load(string filename)` - loads a file using the parameter and creates the
corresponding `question` objects, the old `_questions` array should be deleted
and a new `_questions` array should be created whose `_capacity` is the number of
questions in the file + 30, size should be updated accordingly

## global functions
- `create_question()` - asks the user to input the text and answer for a
question then creates and returns a corresponding `question` object (same
as previous milestones)

## main
Create a quiz object with 50 questions capacity and use the same menu in
previous milestones, but this time using the `quiz` and `question` objects
accordingly.

### menu
- *Create a question* - call the `create_question` function to create a
`question` object and store the `question` into the `quiz` object
- *Display questions* - display all `question`s inside the `quiz` object
- *Save questions* - save all `question`s to a file using the given filename, it
 should use each `question` object's `as_save_text()` member function
- *Load questions* - load the file given as parameter, create `question` objects
and store into the `question` array, it should replace the current contents of
the array.
- *Quit* - exit the program

### Sample output
```
Welcome to QuizMaker

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: d

What file would you like to load? questions.txt
File loaded successfully!

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: b

Question and Answer list
1. Who is the mother of the COBOL programming language?
Answer: Grace Hopper
2. Who developed C++?
Answer: Bjarne Stroustrup
3. Who developed the Ruby programming language?
Answer: Yukihiro Matsumoto

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: a

Please enter your question: Who developed Java?
Please enter the answer: James Gosling
Question added!

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: b

Question and Answer list
1. Who is the mother of the COBOL programming language?
Answer: Grace Hopper
2. Who developed C++?
Answer: Bjarne Stroustrup
3. Who developed the Ruby programming language?
Answer: Yukihiro Matsumoto
4. Who developed Java?
Answer: James Gosling

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: c

What filename would you like to use? questions.txt
File saved successfully!

What would you like to do?
a. Create a question
b. Display questions
c. Save questions
d. Load questions
e. Quit
Choice: e

Thank you for using QuizMaker!
```

Place the function prototypes and classes in `quiz.hpp`, the function
implementations in `quiz.cpp`, and the main function in `quizgen.cpp`.

# Coding style
We are rolling out a CSUF coding style that we have been using in class. Please
use this new style for this milestone and your following milestones. See [CSUF C++ Style Guide](https://drive.google.com/file/d/1KmXTwiDfpGUN-5GTVZn_xfwJ4yXDMJ4k/view?usp=sharing).

# Documentation
See [google's style guide](https://google.github.io/styleguide/cppguide.html#Comments) for
commenting details.

*Take note that we only use th Google document for commenting
style and not coding style.*

## File comments
Describe the contents of the file on the first line. For example:

```cpp
// This file implements a simple calculator
```

## Function comments
Describe the use of the function and how it is implemented if it is non-obvious. For example:

```cpp
// Displays a greeting on the command line using the name parameter.
void show_greeting(string name) {
  // ...
}
```

## Implementation comments
Provide comments in tricky, non-obvious, interesting, or important parts of your code.

```cpp
// Compute the distance between two points using the distance formula
// sqrt((x1-x2)^2 + (y1-y2)^2)
double dist = sqrt(pow(x1 - x2, 2) + pow(y1-y2, 2));
```

# Code evaluation
Open the terminal and navigate to the folder that contains this milestone. Assuming you have pulled the code inside of `/home/student/project01-tuffy` and you are currently in `/home/student` you can issue the following commands

```
cd project01-tuffy
```

Use the `g++` command to compile your code and the `./` command to run it. The sample commands below shows how you would compile code save in `quizgen.cpp` and into the executable file `quizgen`. Make sure you use the correct filenames required in this problem.  Take note that if you make any changes to your code, you will need to compile it first before you see changes when running it.

```
g++ -std=c++17 quizgen.cpp quiz.cpp -o quizgen
./quizgen
```

You can run one, two, or all the commands below to `test` your code, `stylecheck` your code's design, or `formatcheck` your work. Kindly make sure that you have compiled and executed your code before issuing any of the commands below to avoid errors.

```
make test
make stylecheck
make formatcheck
```

A faster way of running all these tests uses the `all` parameter.

```
make all
```

# Submission
1. When everything runs correctly, let's copy your code into the Github repository. The first step is to add your code to what is called the staging area using git's `add` command. The parameter after `add` is the name of the file you want to add. There are cases when you have multiple changed files, so you can just type . (period) to add all modified files.

    ```
    git add .
    ```

1. Once everything is in the staging area, we use the `commit` command to tell git that we have added everything we need into the staging area.

    ```
    git commit
    ```

1. In case it asks you  to configure global variables for an email and name, just copy the commands it provides then replace the dummy text with your email and Github username.

    ```
    git config --global user.email "tuffy@csu.fullerton.edu"
    git config --global user.name "Tuffy Titan"
    ```

    When you're done, make sure you type `git commit` again.   

1. Git will ask you to describe what you have added to the staging area. By default, you will use a command-line based editor called *nano*. Go ahead and provide a description then press <kbd>Ctrl</kbd> + <kbd>x</kbd> to exit. Press <kbd>Y</kbd> to confirm that you want to make changes and then press <kbd>Enter</kbd>.

1. Lets push all changes to the Github repository using git's `push` command. Provide your Github username and password when you are asked.

    ```
    git push
    ```

1. When you finish the exercise, go back to Titanium and click on the `Add submission` button in the project milestone page. Provide a short message in the text area such as "finished milestone" and click on `Save changes`. Finally click on `Submit assignment` to inform your instructor that you are done.
