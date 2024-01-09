#include <iostream>
#include <new>

template <typename T>
class DequeBasedOnBidirectionalCyclicLinkedList {
private:
    template <typename T>
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;


        Node(T data = T(), Node* next = nullptr, Node* prev = nullptr) {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    Node<T>* first; // Указатель на первый элемент (начало деки)
    Node<T>* last;// Указатель на последний  элемент (конец деки)
    int size; // Размер деки

public:

    int GetSize() const {
        return size;
    };

    // Функция очистки деки
    void clear();

    // Функция добавления элемента в деке
    bool PushFront(const T& element);

    bool PushBack(const T& element);

    // Функция удаления элемента из деки
    bool PopFront(T& element);

    bool PopBack(T& element);

    bool PeekFront(T& element) const;

    bool PeekBack(T& element) const;

    // Конструктор по умолчанию
    DequeBasedOnBidirectionalCyclicLinkedList();

    // Конструктор копирования
    DequeBasedOnBidirectionalCyclicLinkedList(const DequeBasedOnBidirectionalCyclicLinkedList<T>& other);

    // Конструктор перемещения
    DequeBasedOnBidirectionalCyclicLinkedList(DequeBasedOnBidirectionalCyclicLinkedList<T>&& other);

    // Конструктор, принимающий на вход std::initializer_list
    DequeBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T> ilist);

    // Деструктор
    ~DequeBasedOnBidirectionalCyclicLinkedList();

    // Переопределение оператора присваивания (копирования)
    DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(const DequeBasedOnBidirectionalCyclicLinkedList<T>& other);

    // Переопределение оператора присваивания (перемещение)
    DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(DequeBasedOnBidirectionalCyclicLinkedList<T>&& other);

    // Переопределение оператора присваивания (с использованием initializer_list)
    DequeBasedOnBidirectionalCyclicLinkedList<T>& operator=(std::initializer_list<T> ilist);
};

template<typename T>
DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList()
{
    size = 0;
    first = nullptr;
    last = nullptr;
}

template<typename T>
DequeBasedOnBidirectionalCyclicLinkedList<T>::~DequeBasedOnBidirectionalCyclicLinkedList() {
    clear();  // Очищаем дек, используя функцию clear
}


template <typename T>
DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(const DequeBasedOnBidirectionalCyclicLinkedList<T>& other) : first(nullptr), last(nullptr), size(0) {
    *this = other;  // Используем оператор присваивания
}

template <typename T>
DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(DequeBasedOnBidirectionalCyclicLinkedList<T>&& other) : first(nullptr), last(nullptr), size(0) {
    *this = std::move(other);  // Используем оператор присваивания перемещения
}

template <typename T>
DequeBasedOnBidirectionalCyclicLinkedList<T>::DequeBasedOnBidirectionalCyclicLinkedList(std::initializer_list<T> ilist) : first(nullptr), last(nullptr), size(0) {
    *this = ilist;  // Используем оператор присваивания
}


template <typename T>
DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(const DequeBasedOnBidirectionalCyclicLinkedList<T>& other) {
    // Защита от самоприсваивания
    if (this == &other)
        return *this;
    // Очищаем текущий список
    clear();

    // Проверяем, не пуст ли исходный список
    if (other.first == nullptr)
        return *this;


    // Начинаем с элемента, который находится на "дне" исходной деки
    Node<T>* currentOther = other.first;

    do {
        // Копируем элементы из исходного списка в новый с помощью Push
        if (!PushFront(currentOther->data)) {
            // Обработка ошибки выделения памяти, если Push возвращает false
            clear();  // Очищаем уже скопированные элементы
            throw std::bad_alloc();  // Выбрасываем исключение
        }
        currentOther = currentOther->next;
    } while (currentOther != other.first);  // Повторяем, пока не вернемся к начальному узлу



    return *this;
}

template <typename T>
DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(DequeBasedOnBidirectionalCyclicLinkedList<T>&& other) {
    if (this == &other)
        return *this;
    // Защита от самоприсваивания
    clear();  // Очищаем текущий список

    // Перемещаем данные из other в текущий объект
    first = other.first;
    last = other.last;
    size = other.size;

    // Оставляем other в валидном, но пустом состоянии
    other.first = nullptr;
    other.last = nullptr;
    other.size = 0;


    return *this;
}


template <typename T>
DequeBasedOnBidirectionalCyclicLinkedList<T>& DequeBasedOnBidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<T> ilist) {
    clear();  // Очистка текущего списка

    // Добавление каждого элемента из списка инициализации
    for (const T& item : ilist) {
        PushFront(item);
    }

    return *this;  // Возвращение ссылки на текущий объект
}

template<typename T>
void DequeBasedOnBidirectionalCyclicLinkedList<T>::clear() {
    Node<T>* nextNode;
    while (size > 0) {
        nextNode = first->next; // Сохраняем ссылку на следующий элемент
        delete first; // Удаляем текущий узел
        first = nextNode; // Переходим к следующему узлу
        --size;
    }

    first = nullptr; // Обнуляем указатель на начало деки
    last = nullptr; // Обнуляем указатель на конец деки
}

template<typename T>
bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PushFront(const T& element) {
    // Создаем новый узел
    Node<T>* newNode = new(std::nothrow) Node<T>(element);

    // Проверяем, был ли узел успешно создан
    if (newNode == nullptr) {
        // Не удалось выделить память
        return false;
    }

    if (size == 0) {
        // Если список пуст, новый узел становится первым и единственным элементом
        newNode->next = newNode; // Ссылки на самого себя
        last = newNode;
        newNode->prev = newNode;

    }
    else {
        // Вставляем новый узел в начало
        first->prev = newNode;
        newNode->next = first;//Соблюдение цикличности.
        newNode->prev = last;
        last->next = newNode;
    }

    first = newNode; // Обновляем last для указания на новый узел
    size++;
    return true;
}

template<typename T>
bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PushBack(const T& element) {
    // Создаем новый узел
    Node<T>* newNode = new(std::nothrow) Node<T>(element);

    // Проверяем, был ли узел успешно создан
    if (newNode == nullptr) {
        // Не удалось выделить память
        return false;
    }

    if (size == 0) {
        // Если список пуст, новый узел становится первым и единственным элементом
        newNode->next = newNode; // Ссылки на самого себя
        first = newNode;
        newNode->prev = newNode;

    }
    else {
        // Вставляем новый узел в конец
        last->next = newNode;
        newNode->prev = last;//Соблюдение цикличности.
        newNode->next = first;
        first->prev = newNode;

    }

    last = newNode; // Обновляем last для указания на новый узел
    size++;
    return true;
}

template<typename T>
bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PopFront(T& element) {
    // Проверяем, пуста ли дека
    if (size == 0) {
        // дека пуста
        return false;
    }

    // Сохраняем данные первого элемента
    element = first->data;

    // ССылка на старый первый элемент
    Node<T>* toDelete = first;

    // Если в деке остался только один элемент
    if (first == last) {

        first = last = nullptr;
    }
    else {
        // В деке более одного элемента
        first = first->next;
        first->prev = last;
        last->next = first;
    }

    delete toDelete;  // Удаляем старый первый элемент
    --size;           // Уменьшаем размер деке
    return true;
}

template<typename T>
bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PopBack(T& element) {
    // Проверяем, пуста ли дека
    if (size == 0) {
        // дека пуста
        return false;
    }

    // Сохраняем данные первого элемента
    element = last->data;

    // ССылка на старый последний элемент
    Node<T>* toDelete = last;

    // Если в деке остался только один элемент
    if (first == last) {

        first = last = nullptr;
    }
    else {
        // В деке более одного элемента
        last = last->prev;
        last->next = first;
        first->prev = last;
    }

    delete toDelete;  // Удаляем старый первый элемент
    --size;           // Уменьшаем размер деке
    return true;
}

template<typename T>
bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PeekFront(T& element) const {
    // Проверяем, пуста ли деке
    if (size == 0) {
        return false;
    }

    // Копируем данные первого элемента
    element = first->data;

    return true;
}

template<typename T>
bool DequeBasedOnBidirectionalCyclicLinkedList<T>::PeekBack(T& element) const {
    // Проверяем, пуста ли дека
    if (size == 0) {
        return false;
    }

    // Копируем данные последнего элемента
    element = last->data;

    return true;
}

template<typename T>
void printShuffleDeque(const DequeBasedOnBidirectionalCyclicLinkedList<T>& other)
{
    DequeBasedOnBidirectionalCyclicLinkedList<T> new_deque = other;
    T data;

    bool flag;

    while (new_deque.GetSize() > 0)
    {
        if (new_deque.GetSize() % 2 == 0)
            flag = new_deque.PopFront(data);
        else
            flag = new_deque.PopBack(data);
        std::cout << data << "  " << flag << std::endl;


    };

    std::cout << std::endl;

}

template<typename T>
void printDeque(const DequeBasedOnBidirectionalCyclicLinkedList<T>& other)
{
    DequeBasedOnBidirectionalCyclicLinkedList<T> new_deque = other;
    T data;



    while (new_deque.GetSize() > 0)
    {

        bool flag = new_deque.PopFront(data);
        std::cout << data << "  " << flag << std::endl;


    };

    std::cout << std::endl;
}


int main() {
    DequeBasedOnBidirectionalCyclicLinkedList<int>* new_deque = new DequeBasedOnBidirectionalCyclicLinkedList<int>();
    for (int i = 0; i <= 5; i++)
    {
        new_deque->PushFront(i);

    }
    printDeque(*new_deque);
    for (int i = 6; i <= 10; i++)
    {
        new_deque->PushBack(i);

    }

    printDeque(*new_deque);
    printShuffleDeque(*new_deque);
    DequeBasedOnBidirectionalCyclicLinkedList<int>* new_deque1 = new DequeBasedOnBidirectionalCyclicLinkedList<int>();
    for (int i = 11; i <= 15; i++)
    {
        new_deque1->PushFront(i);

    }
    std::swap(new_deque, new_deque1);
    int data;
    new_deque->PeekFront(data);
    printDeque(*new_deque);
    std::cout << data;
    new_deque->PeekBack(data);
    std::cout << data;
    return 0;
}