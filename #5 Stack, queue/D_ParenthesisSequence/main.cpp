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
    size = 100;
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
        T *new_arr = new T[size];

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

bool IsParenthesisSequenceCorrect(const std::string &sequence);

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string sequence;
    std::getline(std::cin, sequence);

    std::cout << (IsParenthesisSequenceCorrect(sequence) ? "yes" : "no");

    return 0;
}

bool IsParenthesisSequenceCorrect(const std::string &sequence) {
    MyStack<char> stack;

    for (char symbol : sequence) {
        if ((symbol == '{') || (symbol == '[') || (symbol == '(')) {
            stack.push(symbol);
        } else {
            switch (symbol) {
                case ']': {
                    if (stack.pop() != '[') {
                        return false;
                    }
                    break;
                }
                case '}': {
                    if (stack.pop() != '{') {
                        return false;
                    }
                    break;
                }
                default: {
                    if (stack.pop() != '(') {
                        return false;
                    }
                    break;
                }
            }
        }
    }

    bool answer = stack.isEmpty();
    stack.clear();
    return answer;
}
