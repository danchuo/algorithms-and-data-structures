#include <iostream>
#include <string>

template<typename T>
class MyStack {
 private:
  // Указатель на голову стека
  int top;

  // Размер стека
  int size;

  // Внутренний массив
  T *arr;

 public:
  // Конструктор
  MyStack();

  // Помещение элемента в стек
  void push(T elem);

  // Удаление головного элемента стека
  T pop();

  // Чтение головного элемента стека
  T peek();

  // Проверка на стека на пустоту
  bool isEmpty();

  int getSize();

  void clear();
};

template<typename T>
MyStack<T>::MyStack() {
    top = -1;
    size = 10;
    arr = new T[size];
}

template<typename T>
T MyStack<T>::pop() {
    T popped = arr[top];
    --top;

    return popped;
}

template<typename T>
void MyStack<T>::push(T elem) {
    if (top + 1 >= size) {
        size *= 2;
        int *new_arr = new int[size];

        for (int i = 0; i < size / 2; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
    }

    ++top;
    arr[top] = elem;
}

template<typename T>
bool MyStack<T>::isEmpty() {
    return (top == -1);
}

template<typename T>
T MyStack<T>::peek() {
    return arr[top];
}

template<typename T>
int MyStack<T>::getSize() {
    return top + 1;
}

template<typename T>
void MyStack<T>::clear() {
    delete[] arr;
    top = -1;
    size = 10;
    arr = new T[size];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string command;

    MyStack<int> stack;

    do {
        std::getline(std::cin, command);

        switch (command[0]) {
            case 'p': {
                if (command[1] == 'u') {
                    int number = std::stoi(command.substr(command.find_first_of(' ') + 1));
                    stack.push(number);
                    std::cout << "ok";
                } else {
                    if (stack.isEmpty()) {
                        std::cout << "error";
                    } else {
                        std::cout << stack.pop();
                    }
                }
                break;
            }
            case 'b': {
                if (stack.isEmpty()) {
                    std::cout << "error";
                } else {
                    std::cout << stack.peek();
                }
                break;
            }
            case 's': {
                std::cout << stack.getSize();
                break;
            }
            case 'c': {
                std::cout << "ok";
                stack.clear();
                break;
            }
            case 'e': {
                std::cout << "bye";
                break;
            }
        }
        std::cout << '\n';
    } while (command != "exit");

    stack.clear();
    return 0;
}

