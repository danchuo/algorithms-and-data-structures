#include <iostream>
#include <string>

template<typename T>
class MyDeque {
 private:
  int head;
  int tail;
  bool is_start_positions_set;

  int number_of_elements;

  T *array;

  int const kSizeOfArray = 100;

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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string command;
    MyDeque<int> deque;

    do {
        std::getline(std::cin, command);
        switch (command[0]) {
            case 'p': {
                if (command[1] == 'u') {
                    int number = std::stoi(command.substr(command.find_first_of(' ') + 1));
                    if (command[5] == 'f') {
                        deque.pushFront(number);
                    } else {
                        deque.pushBack(number);
                    }
                    std::cout << "ok\n";
                } else {
                    if (deque.isEmpty()) {
                        std::cout << "error\n";
                    } else {
                        if (command[4] == 'f') {
                            std::cout << deque.popFront() << '\n';
                        } else {
                            std::cout << deque.popBack() << '\n';
                        }
                    }
                }
                break;
            }
            case 'f': {
                if (deque.isEmpty()) {
                    std::cout << "error\n";
                } else {
                    std::cout << deque.front() << '\n';
                }
                break;
            }
            case 'b': {
                if (deque.isEmpty()) {
                    std::cout << "error\n";
                } else {
                    std::cout << deque.back() << '\n';
                }
                break;
            }
            case 's': {
                std::cout << deque.getSize() << '\n';
                break;
            }
            case 'c': {
                std::cout << "ok\n";
                deque.clear();
                break;
            }
            case 'e': {
                std::cout << "bye";
                break;
            }
        }
    } while (command != "exit");

    return 0;
}
