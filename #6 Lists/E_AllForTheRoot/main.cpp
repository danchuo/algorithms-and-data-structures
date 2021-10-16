#include <iostream>
#include <string>

class SpecialNode {
public:
    static const int kArraySize = 3;
    SpecialNode *next;
    int number_of_elements;
    int result_of_operation;
    int *array;

    explicit SpecialNode();
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

    void insert(int position, int value);
    void erase(int position);
    void change(int position, int value);
    int at(int position);
    int compute(int left, int right);
    int moduloAddition(int left, int right);
    int doOperation(int left, int right);
    int undoOperation(int result, int minus_element);

    UnrolledList(char operation);
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
    int64_t result = ((left % mod_by) + (right % mod_by));
    return static_cast<int>(result % mod_by);
}

int UnrolledList::at(int const position) {
    int number_of_past_elements = 0;
    SpecialNode *current_node = head;

    while (position - number_of_past_elements >= current_node->number_of_elements) {
        number_of_past_elements += head->number_of_elements;
        current_node = current_node->next;
    }

    return current_node->array[(position - number_of_past_elements) - 1];
}

int UnrolledList::compute(int const left, int const right) {
    if (left == right) {
        if (operation == '+') {
            return (at(left - 1) % mod_by);
        } else {
            return at(left - 1);
        }
    }

    int number_of_past_elements = 0;
    SpecialNode *current_node = head;

    while (left - number_of_past_elements >= current_node->number_of_elements) {
        number_of_past_elements += head->number_of_elements;
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
            result =
                doOperation(result, current_node->array[index_of_element_in_current_array]);
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
        return (left xor right);
    }
}

int UnrolledList::undoOperation(int result, int minus_element) {
    if (operation == '+') {
        if (minus_element > 0) {
            return (result - (minus_element % mod_by));
        } else {
            return (result + (minus_element % mod_by));
        }
    } else {
        return (result xor minus_element);
    }
}

void UnrolledList::change(int position, int value) {
    int number_of_past_elements = 0;
    SpecialNode *current_node = head;

    while (position - number_of_past_elements >= current_node->number_of_elements) {
        number_of_past_elements += head->number_of_elements;
        current_node = current_node->next;
    }

    int result = undoOperation(current_node->result_of_operation,
                               current_node->array[(position - number_of_past_elements) - 1]);

    current_node->array[(position - number_of_past_elements) - 1] = value;

    current_node->result_of_operation = doOperation(result, value);
}
void UnrolledList::insert(int position, int value) {

    // generate position in current array AND current node

    int number_of_past_elements = 0;
    SpecialNode *current_node = head;

    while (position - number_of_past_elements >= current_node->number_of_elements) {
        number_of_past_elements += head->number_of_elements;
        current_node = current_node->next;
    }

    // requires position in current array AND current node

    int index_of_element_in_current_array = position - number_of_past_elements - 1;

    if (current_node->number_of_elements + 1 < SpecialNode::kArraySize) {

        for (int i = 0; i < current_node->number_of_elements - index_of_element_in_current_array; ++i) {
            current_node->array[current_node->number_of_elements - index_of_element_in_current_array + i + 1] =
                current_node->array[current_node->number_of_elements - index_of_element_in_current_array + i];
        }

        current_node->array[index_of_element_in_current_array] = value;
        current_node->result_of_operation = doOperation(current_node->result_of_operation, value);
        current_node->number_of_elements += 1;
        ++size;
    } else {
        // create new node

        SpecialNode *new_node = new SpecialNode();
        new_node->next = current_node->next;
        current_node->next = new_node;

        for (int i = 0; i < current_node->kArraySize / 2; ++i) {
            new_node->array[i] = current_node->array[i + current_node->kArraySize / 2];
            current_node->number_of_elements -= 1;
            current_node->result_of_operation =
                undoOperation(current_node->result_of_operation,
                              current_node->array[i + current_node->kArraySize / 2]);

            new_node->number_of_elements += 1;
            new_node->result_of_operation = doOperation(new_node->result_of_operation, new_node->array[i]);
        }

        insert(position, value);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    char operation;
    int number_of_commands;
    int length_of_array;

    std::cin >> operation;

    UnrolledList list(operation);

    if (operation == '+') {
        std::cin >> list.mod_by;
    }

   // std::cin >> length_of_array >> number_of_commands;
    for (int i = 0; i < 10; ++i) {

        list.insert(i, i);
    }

    std::cout << list.size;

    return 0;
}
