#include <memory>
#include <iostream>
#include <optional>
#include <limits>



template<typename T, size_t NodeMaxSize = 10, typename Allocator = std::allocator<T>>



class unrolled_list {

private:

    struct Node {

        std::optional<T> elements[NodeMaxSize];
        size_t size = 0;

        Node* next = nullptr;
        Node* prev = nullptr;
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    size_t all_size = 0;

    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    NodeAllocator alloc;

public:

    using allocator_type = Allocator;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using difference_type = std::ptrdiff_t;
    using size_type = size_t;

    template<bool Const>
    class Iterator {

    private:
        
        using Pointer = std::conditional_t<Const, const T*, T*>;
        using Type = std::conditional_t<Const, const T&, T&>;
        using __Node__ = std::conditional_t<Const, const Node*, Node*>;

        __Node__ node;
        size_t index;

    public:

        using value_type = typename unrolled_list<T, NodeMaxSize, Allocator>::value_type;
        using reference = typename std::conditional<Const, const T&, T&>::type;
        using const_reference = const T&;
        using pointer = typename std::conditional<Const, const T*, T*>::type;
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = typename unrolled_list<T, NodeMaxSize, Allocator>::difference_type;
        using size_type = typename unrolled_list<T, NodeMaxSize, Allocator>::size_type; 
        
        friend class unrolled_list<T, NodeMaxSize, Allocator>; 
        
        Iterator(__Node__ node = nullptr, size_t index = 0) : node(node), index(index) {}

        Type operator*(){
            return *(node -> elements[index]);
        }

        Pointer operator->(){
            return &(*(node -> elements[index]));
        }

        Iterator& operator++(){

            if (!node) return *this;

            if (index + 1 < node -> size) ++index;

            else if (node -> next){

                index = 0;
                node = node -> next;
            }

            else {

                node = nullptr;
                index = 0;
            }

            return *this;
        }

        Iterator& operator--(){

            if (!node) return *this;

            if (index > 0) --index;

            else if (node -> prev){

                index = node -> size - 1;
                node = node -> prev;
            }

            return *this;
        }

        Iterator operator++(int){

            Iterator temp = *this;
            ++(*this);

            return temp;
        }

        Iterator operator--(int){

            Iterator temp = *this;
            --(*this);

            return temp;
        }

        bool operator==(const Iterator& other) const {
            return node == other.node && index == other.index;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
    };



    using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;



    size_t size() {
        return all_size;
    }

    bool empty() const {
        return all_size == 0;
    }

    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    allocator_type get_allocator() const {
        return allocator_type();
    }    

    bool operator==(const unrolled_list& other) const {

        if (all_size != other.all_size) return false;

        auto it1 = this -> begin();
        auto it2 = other.begin();

        while (it1 != this->end()) {

            if (*it1 != *it2) return false;

            ++it1;
            ++it2;
        }

        return true;
    }

    unrolled_list& operator=(const unrolled_list& other) {

        if (this == &other) return *this;
    
        clear();

        alloc = other.alloc;
    
        for (const auto& elem : other) {
            push_back(elem);
        }
    
        return *this;
    }    

    iterator begin() {
        return iterator(head, 0);
    }

    iterator end() {

        if (tail)
            return iterator(tail -> next, 0);

        else
            return iterator(nullptr, 0);
    }

    const_iterator begin() const {
        return const_iterator(head, 0);
    }

    const_iterator end() const {
        return const_iterator(nullptr, 0);
    }

    const_iterator cbegin() const {
        return const_iterator(head, 0);
    }

    const_iterator cend() const {
        return const_iterator(nullptr, 0);
    }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }

    const_reverse_iterator rbegin() const { return const_reverse_iterator(cend()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(cbegin()); }
    
    const_reverse_iterator crbegin() const { return const_reverse_iterator(cend()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }



    unrolled_list() : head(nullptr), tail(nullptr), all_size(0), alloc(Allocator()) {}

    unrolled_list(const Allocator& allocator) : head(nullptr), tail(nullptr), all_size(0), alloc(allocator) {}

    unrolled_list(size_t n, const T& value) {

        for (size_t i = 0; i < n; i++)
            push_back(value);
    }

    template<typename temp_iterator>

    unrolled_list(temp_iterator first, temp_iterator second, const Allocator& allocator = Allocator())
    : alloc(allocator), head(nullptr), tail(nullptr), all_size(0) {

        try {

            for (auto element = first; element != second; element++)
                push_back(*element);
        } 
        
        catch (...) {

            clear();
            throw;
        }
    }

    unrolled_list(std::initializer_list<T> array) {

        for (const auto& element : array)
            push_back(element);
    }

    unrolled_list(unrolled_list&& other, const Allocator& allocator)
    : head(nullptr), tail(nullptr), all_size(0), alloc(allocator) {
    
        if (alloc == other.alloc) {

            head = other.head;
            tail = other.tail;
            all_size = other.all_size;

            other.head = nullptr;
            other.tail = nullptr;
            other.all_size = 0;
        } 
        
        else {
            for (auto it = other.begin(); it != other.end(); it++)
                push_back(*it);
        }
    }

    unrolled_list& operator=(std::initializer_list<T> array) {

        clear();

        for (const auto& element : array)
            push_back(element);

        return *this;
    }



    void push_front(const T& value) {

        Node* new_node = nullptr;

        try {

            if (!head) {

                new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
                std::allocator_traits<NodeAllocator>::construct(alloc, new_node);

                head = tail = new_node;
            } 
            
            else if (head->size == NodeMaxSize) {

                new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
                std::allocator_traits<NodeAllocator>::construct(alloc, new_node);

                new_node -> next = head;
                head -> prev = new_node;

                head = new_node;
            } 
            
            else {

                for (size_t i = head -> size; i > 0; i--) {

                    try {
                        head -> elements[i].emplace(*(head -> elements[i - 1]));
                        head -> elements[i - 1].reset();
                    } 
                    
                    catch (...) {

                        for (size_t j = i; j < head -> size; j++)
                            head -> elements[j].reset();
                        
                        throw;
                    }
                }
            }

            head -> elements[0] = std::make_optional<T>(value);

            head->size++;
            all_size++;

        } 
        
        catch (...) {

            if (new_node)
                std::allocator_traits<NodeAllocator>::deallocate(alloc, new_node, 1);
            
            throw;
        }
    }

    void push_front(T&& value) {

        Node* new_node = nullptr;

        try {

            if (!head) {

                new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
                std::allocator_traits<NodeAllocator>::construct(alloc, new_node);

                head = tail = new_node;
            } 
            
            else if (head->size == NodeMaxSize) {

                new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
                std::allocator_traits<NodeAllocator>::construct(alloc, new_node);

                new_node -> next = head;
                head -> prev = new_node;

                head = new_node;
            } 
            
            else {

                for (size_t i = head -> size; i > 0; i--) {

                    try {
                        head -> elements[i].emplace(std::move(*(head -> elements[i - 1])));
                        head -> elements[i - 1].reset();
                    } 
                    
                    catch (...) {

                        for (size_t j = i; j < head -> size; j++)
                            head -> elements[j].reset();
                        
                        throw;
                    }
                }
            }

            head -> elements[0] = std::make_optional<T>(std::move(value));

            head->size++;
            all_size++;

        } 
        
        catch (...) {

            if (new_node)
                std::allocator_traits<NodeAllocator>::deallocate(alloc, new_node, 1);
            
            throw;
        }
    }

    void push_back(const T& value) {

        if (!head) {

            Node* new_node = nullptr;
            
            try {
                new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
                std::allocator_traits<NodeAllocator>::construct(alloc, new_node);
            } 
            
            catch (...) {

                if (new_node)
                    std::allocator_traits<NodeAllocator>::deallocate(alloc, new_node, 1);
                
                throw;
            }
    
            head = tail = new_node;
        } 

        else if (tail -> size == NodeMaxSize) {

            Node* new_node = nullptr;
    
            try {
                new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
                std::allocator_traits<NodeAllocator>::construct(alloc, new_node);
            } 
            
            catch (...) {

                if (new_node)
                    std::allocator_traits<NodeAllocator>::deallocate(alloc, new_node, 1);
                
                throw;
            }
    
            new_node -> prev = tail;
            tail -> next = new_node;
            tail = new_node;
        }
    
        try {
            tail->elements[tail->size].emplace(value);
        } 
        
        catch (...) {
            throw;
        }
    
        tail->size++;
        all_size++;
    }

    void push_back(T&& value) {

        if (!head) {

            Node* new_node = nullptr;
            
            try {
                new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
                std::allocator_traits<NodeAllocator>::construct(alloc, new_node);
            } 
            
            catch (...) {

                if (new_node)
                    std::allocator_traits<NodeAllocator>::deallocate(alloc, new_node, 1);
                
                throw;
            }
    
            head = tail = new_node;
        } 

        else if (tail -> size == NodeMaxSize) {

            Node* new_node = nullptr;
    
            try {
                new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
                std::allocator_traits<NodeAllocator>::construct(alloc, new_node);
            } 
            
            catch (...) {

                if (new_node)
                    std::allocator_traits<NodeAllocator>::deallocate(alloc, new_node, 1);
                
                throw;
            }
    
            new_node -> prev = tail;
            tail -> next = new_node;
            tail = new_node;
        }
    
        try {
            tail->elements[tail->size].emplace(std::move(value));
        } 
        
        catch (...) {
            throw;
        }
    
        tail->size++;
        all_size++;
    }



    void pop_front() noexcept {

        if (!head) return;

        else if (head -> size == 1 && all_size == 1) {

            std::allocator_traits<NodeAllocator>::destroy(alloc, head);
            std::allocator_traits<NodeAllocator>::deallocate(alloc, head, 1);

            head = nullptr;
            tail = nullptr;
        }

        else if (head -> size == 1 && all_size >= 2) {

            Node* temp = head -> next;

            std::allocator_traits<NodeAllocator>::destroy(alloc, head);
            std::allocator_traits<NodeAllocator>::deallocate(alloc, head, 1);

            head = temp;
            head -> prev = nullptr;
        }

        else if (head -> size >= 2) {

            head -> elements[0].reset();

            for (size_t i = 1; i < head -> size; i++) {
                
                head -> elements[i - 1].reset();
                head -> elements[i - 1] = std::move(head -> elements[i]);
            }

            head -> size--;
        }

        all_size--;
    }

    void pop_back() noexcept {

        if (!head) return;

        else if (tail -> size == 1 && all_size == 1) {

            std::allocator_traits<NodeAllocator>::destroy(alloc, tail);
            std::allocator_traits<NodeAllocator>::deallocate(alloc, tail, 1);

            head = nullptr;
            tail = nullptr;
        }

        else if (tail -> size == 1 && all_size >= 2) {

            Node* temp = tail -> prev;

            std::allocator_traits<NodeAllocator>::destroy(alloc, tail);
            std::allocator_traits<NodeAllocator>::deallocate(alloc, tail, 1);

            tail = temp;
            tail -> next = nullptr;
        }

        else if (tail -> size >= 2) {

            tail -> elements[tail -> size - 1].reset();

            tail -> size--;
        }

        all_size--;
    }



    T& front() {

        if (!head) throw std::out_of_range("front() called on empty container");

        return head -> elements[0].value();
    }
    
    const T& front() const{

        if (!head) throw std::out_of_range("front() called on empty container");

        return head -> elements[0].value();
    }

    T& back() {

        if (!tail) throw std::out_of_range("back() called on empty container");

        return tail -> elements[tail -> size - 1].value();
    }

    const T& back() const {

        if (!tail) throw std::out_of_range("back() called on empty container");

        return tail -> elements[tail -> size - 1].value();
    }
    
    T& at(size_t n) {

        if (n >= all_size) throw std::out_of_range("Index out of range");
        
        size_t count = 0;

        for (auto index = this -> begin(); index != this -> end(); index++) {

            if (n == count) return *index;
        
            count++;
        }

        throw std::out_of_range("Index out of range");
    }

    const T& at(size_t n) const {

        if (n >= all_size) throw std::out_of_range("Index out of range");
        
        size_t count = 0;

        for (auto index = this -> cbegin(); index != this -> cend(); index++) {

            if (n == count) return *index;
        
            count++;
        }

        throw std::out_of_range("Index out of range");
    }



    iterator erase(const_iterator first_1) noexcept {

        iterator first = const_cast<iterator>(first_1);

        if (first == this -> end()) return first;

        Node* current = first.node;
        size_t index = first.index;
        
        for (size_t i = index; i < current -> size - 1; i++)
            current -> elements[i] = std::move(current -> elements[i + 1].value());
        
        current -> elements[current -> size - 1].reset();

        --current -> size;
        --all_size;

        if (current -> size == 0) {

            if (current -> prev)
                current -> prev -> next = current -> next;

            else 
                head = current -> next;
            
            if (current -> next)
                current -> next -> prev = current -> prev;
            
            else
                tail = current -> prev;

            std::allocator_traits<NodeAllocator>::destroy(alloc, current);
            std::allocator_traits<NodeAllocator>::deallocate(alloc, current, 1);
        }

        return iterator(current, index);
    }

    iterator erase(const_iterator first_1, const_iterator second_1) noexcept {

        iterator first = const_cast<iterator>(first_1);
        iterator second = const_cast<iterator>(second_1);

        while (first != second) {

            iterator temp = first;
            ++first;

            erase(temp);
        }

        return second;
    }

    iterator erase(iterator first) noexcept {

        if (first == this -> end()) return first;
    
        Node* current = first.node;
        size_t index = first.index;
    
        for (size_t i = index; i < current -> size - 1; i++)
            current -> elements[i] = std::move(current -> elements[i + 1].value());
    
        current -> elements[current -> size - 1].reset();
        --current -> size;
        --all_size;
    
        if (current -> size == 0) {
            Node* nextNode = current -> next;
            Node* prevNode = current -> prev;
    
            if (prevNode)
                prevNode -> next = nextNode;

            else
                head = nextNode;
    
            if (nextNode)
                nextNode -> prev = prevNode;

            else
                tail = prevNode;
    
            std::allocator_traits<NodeAllocator>::destroy(alloc, current);
            std::allocator_traits<NodeAllocator>::deallocate(alloc, current, 1);
    
            return iterator(nextNode ? nextNode : tail, 0);
        }
    
        if (index >= current -> size)
            return iterator(current -> next, 0);
    
        return iterator(current, index);
    }

    iterator erase(iterator first, iterator second) noexcept {

        while (first != second) {

            iterator temp = first;
            erase(temp);
            
            ++first;
        }

        return second;
    }

    void clear() noexcept {

        while (head) {

            for (size_t i = 0; i < head -> size; ++i)
                head -> elements[i].reset();
    
            Node* temp = head;
            head = head->next;
    
            std::allocator_traits<NodeAllocator>::deallocate(alloc, temp, 1);
        }
    
        head = nullptr;
        tail = nullptr;
        all_size = 0;
    }

    void Shift_Right(iterator first) {

        Node* current = first.node;
        size_t index = first.index;
    
        T carry;
        bool flag = false;
    
        while (current) {

            bool flag_for_false = false;
            T last;
    
            try {

                last = current -> elements[current -> size - 1].value();

                for (size_t i = current -> size - 1; i > index; i--) {
                    current -> elements[i].emplace(std::move(current -> elements[i - 1].value()));
                    current -> elements[i - 1].reset();
                }
    
                if (flag) {
                    current -> elements[0].emplace(std::move(carry));
                }
    
                flag_for_false = true;
                carry = std::move(last);
            } 
            
            catch (...) {

                for (size_t i = index; i < current -> size - 1; i++) {
                    current -> elements[i].emplace(std::move(current -> elements[i + 1].value()));
                    current -> elements[i + 1].reset();
                }

                throw;
            }
    
            if (!current -> next) {

                try {
                    push_back(carry);
                } 
                
                catch (...) {

                    if (flag_for_false) {

                        for (size_t i = index; i < current -> size - 1; i++) {
                            current -> elements[i].emplace(std::move(current -> elements[i + 1].value()));
                            current -> elements[i + 1].reset();
                        }
                    }

                    throw;
                }

                return;
            }
    
            current = current -> next;
            index = 0;
            flag = true;
        }
    }

    iterator insert(const_iterator first_1, const T& value) {

        iterator first = const_cast<iterator>(first_1);

        if (first == this -> end()) {

            push_back(value);
            
            return iterator(tail, tail -> size - 1);
        } 
        
        Shift_Right(first);

        try {
            
            Node* current = first.node;
            current -> elements[first.index].emplace(value);
        }

        catch(...) {

            all_size--;
            first.node -> size--;

            throw;
        }

        return iterator(first.node, first.index);
    }

    iterator insert(iterator first, const T& value) { 

        if (first == this -> end()) {

            push_back(value);
            
            return iterator(tail, tail -> size - 1);
        } 
        
        Shift_Right(first);

        try {
            
            Node* current = first.node;
            current -> elements[first.index].emplace(value);
        }

        catch(...) {

            all_size--;
            first.node -> size--;

            throw;
        }

        return iterator(first.node, first.index);
    }

    iterator insert(iterator first, T&& value) {

        if (first == this -> end()) {

            push_back(value);
            
            return iterator(tail, tail -> size - 1);
        } 
        
        Shift_Right(first);

        try {
            
            Node* current = first.node;
            current -> elements[first.index].emplace(std::move(value));
        }

        catch(...) {

            all_size--;
            first.node -> size--;

            throw;
        }

        return iterator(first.node, first.index);
    }

    iterator insert(const_iterator first_1, size_t n, const T& value) {

        iterator first = const_cast<iterator>(first_1);

        iterator first_inserted = first;
        size_t count = 0;

        try {

            for (size_t i = 0; i < n; i++) {

                Shift_Right(first);

                Node* current = first.node;

                current -> elements[first.index].emplace(value);

                first++;
                count++;
            }
        }

        catch(...) {

            all_size -= count;

            throw;
        }

        return first_inserted;
    }

    template<typename iterator_for_fin>

    iterator insert(iterator first, iterator_for_fin i, iterator_for_fin j) {

        iterator first_int = first;

        try {
            
            while (i != j) {

                insert(first, *i);

                i++;
                first++;
            }
        }

        catch(...){
            throw;
        }

        return first_int;
    }

    template <typename Range>

    iterator insert_range(iterator first, const Range& rg) {

        iterator first_int = first;

        try {

            for (const auto& element : rg) {

                insert(first, element);
                
                first++;
            }
        }

        catch(...) {
            throw;
        }

        return first_int;
    }

    iterator insert(iterator first, std::initializer_list<T> array) {
        
        return insert(first, array.begin(), array.end());
    }
};
