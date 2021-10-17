#include <iostream>
#include <string>

class SpecialNode {
public:
    static const size_t kArraySize = 1400;
    SpecialNode *next;
    int number_of_elements;
    int result_of_operation;
    int *array;

    SpecialNode();
    ~SpecialNode();
};

SpecialNode::SpecialNode() {
    next = nullptr;
    number_of_elements = 0;
    result_of_operation = 0;
    array = new int[kArraySize];
}

SpecialNode::~SpecialNode() {
    delete[] array;
    delete next;
}

class UnrolledList {
public:
    SpecialNode *head;
    int size;
    char operation;
    int mod_by;

    int getOperationResult(SpecialNode *node);
    void insert(int position, int value);
    void erase(int position);
    void change(int position, int value);
    int at(int position);
    int compute(int left, int right);
    int moduloAddition(int left, int right);
    int doOperation(int left, int right);

    static UnrolledList initiateList() {
        char input_operation;
        int length_of_array;
        std::cin >> input_operation;

        UnrolledList list(input_operation);

        if (input_operation == '+') {
            std::cin >> list.mod_by;
        }

        std::cin >> length_of_array;

        int input_number;
        for (int i = 1; i <= length_of_array; ++i) {
            std::cin >> input_number;
            list.insert(i, input_number);
        }

        return list;
    }

    explicit UnrolledList(char operation);
    ~UnrolledList();
};

UnrolledList::UnrolledList(char operation) {
    size = 0;
    mod_by = 1;
    this->operation = operation;
    head = new SpecialNode();
}

UnrolledList::~UnrolledList() {
    delete head;
}

int UnrolledList::moduloAddition(int left, int right) {
    int64_t result = ((left + right) % mod_by);
    return static_cast<int>(result);
}

int UnrolledList::at(int const position) {
    int number_of_past_elements = 0;
    SpecialNode *current_node = head;

    while (position - number_of_past_elements > current_node->number_of_elements) {
        number_of_past_elements += current_node->number_of_elements;
        current_node = current_node->next;
    }

    return current_node->array[(position - number_of_past_elements) - 1];
}

int UnrolledList::compute(int const left, int const right) {
    if (left == right) {
        if (operation == '+') {
            return (at(left) % mod_by);
        } else {
            return at(left);
        }
    }

    int number_of_past_elements = 0;
    SpecialNode *current_node = head;

    while (left - number_of_past_elements > current_node->number_of_elements) {
        number_of_past_elements += current_node->number_of_elements;
        current_node = current_node->next;
    }

    int index_of_element_in_current_array = left - number_of_past_elements - 1;

    int result = 0;

    for (int i = 0; i <= right - left; ++i) {
        if ((index_of_element_in_current_array == 0) &&
            (i + current_node->number_of_elements <= right - left + 1)) {
            result = doOperation(result, current_node->result_of_operation);
            i += current_node->number_of_elements - 1;
            current_node = current_node->next;
            index_of_element_in_current_array = 0;
        } else {
            result = doOperation(result, current_node->array[index_of_element_in_current_array]);
            if (index_of_element_in_current_array + 1 == current_node->number_of_elements) {
                current_node = current_node->next;
                index_of_element_in_current_array = 0;
            } else {
                ++index_of_element_in_current_array;
            }
        }
    }

    return result;
}

int UnrolledList::doOperation(int left, int right) {
    if (operation == '+') {
        return moduloAddition(left, right);
    } else {
        return (left ^ right);
    }
}

void UnrolledList::change(int position, int value) {
    int number_of_past_elements = 0;
    SpecialNode *current_node = head;

    while (position - number_of_past_elements > current_node->number_of_elements) {
        number_of_past_elements += current_node->number_of_elements;
        current_node = current_node->next;
    }

    current_node->array[(position - number_of_past_elements) - 1] = value;

    current_node->result_of_operation = getOperationResult(current_node);
}
void UnrolledList::insert(int position, int value) {
    int number_of_past_elements = 0;
    SpecialNode *current_node = head;

    if (size + 1 != position) {
        while (position - number_of_past_elements > current_node->number_of_elements) {
            number_of_past_elements += current_node->number_of_elements;
            current_node = current_node->next;
        }
    } else {
        while (position - number_of_past_elements - 1 > current_node->number_of_elements) {
            number_of_past_elements += current_node->number_of_elements;
            current_node = current_node->next;
        }
    }

    int index_of_element_in_current_array = position - number_of_past_elements - 1;

    // if current index == 0 we can insert in previous node

    if (current_node->number_of_elements < SpecialNode::kArraySize) {
        for (int i = 0; i < current_node->number_of_elements - index_of_element_in_current_array;
             ++i) {
            (current_node->array)[current_node->number_of_elements - i] =
                (current_node->array)[current_node->number_of_elements - 1 - i];
        }

        (current_node->array)[index_of_element_in_current_array] = value;
        current_node->number_of_elements += 1;
        current_node->result_of_operation = doOperation(current_node->result_of_operation, value);
        ++size;
    } else {
        SpecialNode *new_node = new SpecialNode();
        new_node->next = current_node->next;
        current_node->next = new_node;

        for (int i = 0; i < current_node->kArraySize / 2; ++i) {
            (new_node->array)[i] = (current_node->array)[i + current_node->kArraySize / 2];
            current_node->number_of_elements -= 1;
            new_node->number_of_elements += 1;
        }

        current_node->result_of_operation = getOperationResult(current_node);
        new_node->result_of_operation = getOperationResult(new_node);
        insert(position, value);
    }
}

void UnrolledList::erase(int position) {
    int number_of_past_elements = 0;
    SpecialNode *current_node = head;
    SpecialNode *previous_node = nullptr;

    while (position - number_of_past_elements > current_node->number_of_elements) {
        number_of_past_elements += current_node->number_of_elements;
        previous_node = current_node;
        current_node = current_node->next;
    }

    int index = position - number_of_past_elements - 1;

    if ((index == 0) && (current_node->number_of_elements == 1) && (previous_node != nullptr)) {
        previous_node->next = current_node->next;
        current_node->next = nullptr;

        delete current_node;
    } else {
        for (int i = index; i < current_node->number_of_elements - 1; ++i) {
            (current_node->array)[i] = (current_node->array)[i + 1];
        }
        current_node->number_of_elements -= 1;
        current_node->result_of_operation = getOperationResult(current_node);
    }
    --size;
}
int UnrolledList::getOperationResult(SpecialNode *node) {
    int result = 0;

    for (int i = 0; i < node->number_of_elements; ++i) {
        result = doOperation(result, (node->array)[i]);
    }

    return result;
}

void processCommands(UnrolledList *list, int const number_of_commands) {
    std::string command;
    std::getline(std::cin, command);
    int first_number;
    int second_number;

    for (int i = 0; i < number_of_commands; ++i) {
        std::getline(std::cin, command);
        if (command[1] != 'i') {
            first_number = std::stoi(command.substr(command.find_first_of(' ') + 1));
        }
        switch (command[1]) {
            case 'n': {
                second_number = std::stoi(command.substr(command.find_last_of(' ') + 1));
                list->insert(first_number, second_number);
                break;
            }
            case 'r': {
                list->erase(first_number);
                break;
            }
            case 'h': {
                second_number = std::stoi(command.substr(command.find_last_of(' ') + 1));
                list->change(first_number, second_number);
                break;
            }
            case 't': {
                std::cout << list->at(first_number) << '\n';
                break;
            }
            case 'o': {
                second_number = std::stoi(command.substr(command.find_last_of(' ') + 1));
                std::cout << list->compute(first_number, second_number) << '\n';
                break;
            }
            case 'i': {
                std::cout << list->size << '\n';
                break;
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number_of_commands;
    // why wa15 I'm crying

    UnrolledList list = UnrolledList::initiateList();

    std::cin >> number_of_commands;

    processCommands(&list, number_of_commands);

    return 0;
}
