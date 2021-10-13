#include <iostream>
#include <string>
#include <cstdint>

template<typename T>
class MyDeque {
 private:
  int head;
  int tail;
  bool is_start_positions_set;

  int number_of_elements;

  T *array;

  int const kSizeOfArray = 50000;

 public:
  MyDeque();

  void pushFront(T element);

  void pushBack(T element);

  T popFront();

  T popBack();

  T front();

  T back();

  bool isEmpty();

  int getSize();

  void clear();
};

template<typename T>
MyDeque<T>::MyDeque() {
    head = 0;
    tail = 0;
    number_of_elements = 0;
    is_start_positions_set = false;
    array = new T[kSizeOfArray];
}

template<typename T>
T MyDeque<T>::popFront() {
    T popped = array[head];
    head = (head + 1) % kSizeOfArray;
    --number_of_elements;
    return popped;
}

template<typename T>
T MyDeque<T>::popBack() {
    T popped = array[tail];
    tail = (tail - 1 + kSizeOfArray) % kSizeOfArray;
    --number_of_elements;
    return popped;
}

template<typename T>
void MyDeque<T>::pushFront(T element) {
    if (!is_start_positions_set) {
        tail = head = (head - 1 + kSizeOfArray) % kSizeOfArray;
        is_start_positions_set = true;
    } else {
        head = (head - 1 + kSizeOfArray) % kSizeOfArray;
    }
    array[head] = element;
    ++number_of_elements;
}

template<typename T>
void MyDeque<T>::pushBack(T element) {
    if (!is_start_positions_set) {
        head = tail = (tail + 1) % kSizeOfArray;
        is_start_positions_set = true;
    } else {
        tail = (tail + 1) % kSizeOfArray;
    }
    array[tail] = element;
    ++number_of_elements;
}

template<typename T>
bool MyDeque<T>::isEmpty() {
    return number_of_elements == 0;
}

template<typename T>
T MyDeque<T>::front() {
    return array[head];
}

template<typename T>
T MyDeque<T>::back() {
    return array[tail];
}

template<typename T>
int MyDeque<T>::getSize() {
    return number_of_elements;
}

template<typename T>
void MyDeque<T>::clear() {
    delete[] array;
    head = -1;
    tail = 0;
    number_of_elements = 0;
    is_start_positions_set = false;
    array = new T[kSizeOfArray];
}

void EqualizeQueues(MyDeque<int> *front_half,
                    MyDeque<int> *back_half,
                    int number_of_people);

void ProcessRequests(int number_of_requests);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number_of_requests;
    std::cin >> number_of_requests;
    ProcessRequests(number_of_requests);
    return 0;
}

void ProcessRequests(int const number_of_requests) {
    std::string command;
    MyDeque<int> front_half;
    MyDeque<int> back_half;
    int number_of_people = 0;
    std::getline(std::cin, command);
    std::cin.clear();

    for (int i = 0; i < number_of_requests; ++i) {
        std::getline(std::cin, command);
        int input_number;
        switch (command[0]) {
            case '+': {
                input_number = std::stoi(command.substr(2));
                ++number_of_people;
                back_half.pushBack(input_number);
                break;
            }
            case '*': {
                input_number = std::stoi(command.substr(2));
                ++number_of_people;
                back_half.pushFront(input_number);
                break;
            }
            case '-': {
                --number_of_people;
                std::cout << front_half.popFront() << '\n';
                break;
            }
        }
        EqualizeQueues(&front_half, &back_half, number_of_people);
    }

    front_half.clear();
    back_half.clear();
}

void EqualizeQueues(MyDeque<int> *front_half,
                    MyDeque<int> *back_half,
                    int const number_of_people) {
    while ((back_half->getSize()) != (number_of_people / 2)) {
        int popped = back_half->popFront();
        front_half->pushBack(popped);
    }
}
