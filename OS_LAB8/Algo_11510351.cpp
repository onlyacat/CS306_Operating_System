#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

#define DEFAULT_CACHE_SIZE 123
#define DEFAULT_ALGORITHM 1

int cache_size, working_algorithm, hit, miss, page_max_size;

typedef void (*pf)();

vector<int> pages;
map<int, pf> algorithms;

struct Node {
    int order;
    int address;
    Node *prev, *next;
};

void init_algorithm();

void set_the_variable();

void select_function(pf);

void FIFO_algorithm();

void MIN_algorithm();

void LRU_algorithm();

void CLOCK_algorithm();

void SECOND_CHANCE_algorithm();

int main() {
    init_algorithm();
    set_the_variable();
    select_function(algorithms[working_algorithm]);
}

void init_algorithm() {
    cache_size = DEFAULT_CACHE_SIZE;
    working_algorithm = DEFAULT_ALGORITHM;

    algorithms[0] = FIFO_algorithm;
    algorithms[1] = MIN_algorithm;
    algorithms[2] = LRU_algorithm;
    algorithms[3] = CLOCK_algorithm;
    algorithms[4] = SECOND_CHANCE_algorithm;
}

void set_the_variable() {

    cout <<setprecision (2);
    cout.setf(ios::fixed,ios::floatfield);
    while (true) {
        bool flag = false;

        cin >> cache_size;
        if (cache_size > 2048 || cache_size < 0)
            flag = true;

        cin >> working_algorithm;
        if (working_algorithm > 4 || working_algorithm < 0)
            flag = true;

        cin >> page_max_size;
        if (page_max_size > 10000000)
            flag = true;

        if (flag) {
            cout << "Invalid Input" << endl;
            continue;
        }

        for (int i = 0; i < page_max_size; ++i) {
            int x;
            cin >> x;
            pages.push_back(x);
        }

        break;
    }
}

void select_function(pf p) {
    p();
}

void initial_node(Node &node, int address, int order, Node *next, Node *prev) {
    node.address = address;
    node.order = order;
    node.next = next;
    node.prev = prev;
}

void FIFO_algorithm() {
    hit = miss = 0;
    unordered_map<int, Node *> mymap((unsigned long) cache_size);
    auto head = (Node *) malloc(sizeof(Node));
    auto tail = (Node *) malloc(sizeof(Node));
    initial_node(*head, NULL, NULL, tail, nullptr);
    initial_node(*tail, NULL, NULL, nullptr, head);

    for (int i = 0; i < pages.size(); ++i) {

        int address = pages[i];

        if (mymap.empty()) {
            auto node = (Node *) malloc(sizeof(Node));
            initial_node(*node, pages[i], i, tail, head);
            tail->prev = node;
            head->next = node;
            mymap[node->address] = node;
            continue;
        }

        if (mymap.count(address) == 1) {
            hit++;
            continue;
        }

        auto node = (Node *) malloc(sizeof(Node));
        initial_node(*node, pages[i], i, tail, tail->prev);
        tail->prev->next = node;
        tail->prev = node;
        mymap[node->address] = node;

        if (mymap.size() == cache_size + 1) {
            mymap.erase(head->next->address);
            Node *pointer = head->next;
            head->next->next->prev = head;
            head->next = head->next->next;
            free(pointer);
        }
    }
    cout << "Hit ratio = "<<float(hit) / pages.size()*100<<"%" << endl;
}

//void MIN_algorithm() {
//    vector<int> min;
//    hit = miss = 0;
//
//    min.emplace_back(pages[0]);
//
//    for (int i = 1; i < pages.size(); ++i) {
//
//        bool flag = false;
//
//        for(auto &counter : min){
//            if(counter== pages[i]){
//                hit++;
//                flag = true;
//                break;
//            }
//        }
//
//        if(flag){
//            continue;
//        }
//
//        if(min.size() < cache_size){
//            min.emplace_back(pages[i]);
//            continue;
//        }
//
//
//        int index = 0;
//        int last = 0;
//        for (int j = 0; j < min.size(); ++j) {
//
//        }
//    }
//    cout << float(hit)/pages.size() << endl;
//}


void MIN_algorithm() {
    unordered_map<int, vector<int>> map;
    for (int i = 0; i < pages.size(); ++i) {
        map[pages[i]].push_back(i);
    }

    for (auto &element : map){
        element.second.push_back(pages.size());
    }

    unordered_map<int, int> storage;
    hit = miss = 0;
    for (int i = 0; i < pages.size(); ++i) {
        int address = pages[i];

        if (storage.count(address) == 1) {
            hit++;
            continue;
        }

        if (storage.size() < cache_size) {
            storage[address] = i;
            continue;
        }
        int addre = -1;
        int count = -1;
        for (auto &element:storage) {
            if (address == -1){
                address = element.first;
                continue;
            }
            int back = 0;
            while (map[element.first][back] <= i) {
                back++;
            }

            if (back == pages.size()){
                addre = element.first;
                count = map[element.first][back] - i;
                break;
            }

            if (map[element.first][back] - i > count){
                addre = element.first;
                count = map[element.first][back] - i;
            }
        }
        storage.erase(addre);
        storage[address] = i;
    }

    cout << "Hit ratio = "<<float(hit) / pages.size()*100<<"%" << endl;
}

void MIN_algorithm1() {
    unordered_map<int, vector<int>> map;
    for (int i = 0; i < pages.size(); ++i) {
        map[pages[i]].push_back(i);
    }

    for (auto &element : map){
        element.second.push_back(page_max_size+1);
    }

    unordered_map<int, int> storage;
    hit = miss = 0;
    for (int i = 0; i < pages.size(); ++i) {
        int address = pages[i];

        if (storage.count(address) == 1) {
            hit++;
            int back = storage[address];
            while (map[address][back] <= i) {
                back++;
            }
            storage[address] = back;
            continue;
        }

        if (storage.size() < cache_size) {
            int back = 0;
            while (map[address][back] <= i) {
                back++;
            }
            storage[address] = back;
            continue;
        }
        pair<int, int> count = make_pair(-1,-1);
        for (auto &element:storage) {
            if (count.first == -1){
                count = element;
                continue;
            }
            if(element.second == page_max_size+1){
                count = element;
                break;
            }
            if (map[element.first][element.second] - i > map[count.first][count.second]) {
                count = element;
            }
        }
        storage.erase(count.first);
        int back = 0;
        while (map[address][back] <= i) {
            back++;
        }
        storage[address] = back;
    }

    cout << "Hit ratio = "<<float(hit) / pages.size()*100<<"%" << endl;
}

void LRU_algorithm() {

    hit = miss = 0;
    unordered_map<int, Node *> mymap((unsigned long) cache_size);
    Node *head = (Node *) malloc(sizeof(Node));
    Node *tail = (Node *) malloc(sizeof(Node));
    initial_node(*head, NULL, NULL, tail, nullptr);
    initial_node(*tail, NULL, NULL, nullptr, head);

    for (int i = 0; i < pages.size(); ++i) {

        int address = pages[i];

        if (mymap.empty()) {
            Node *node = (Node *) malloc(sizeof(Node));
            initial_node(*node, pages[i], i, tail, head);
            tail->prev = node;
            head->next = node;
            mymap[node->address] = node;
            continue;
        }

        if (mymap.count(address) == 1) {
            hit++;
            Node *n2 = mymap[address];
            n2->prev->next = n2->next;
            n2->next->prev = n2->prev;
            n2->prev = tail->prev;
            n2->next = tail;
            tail->prev->next = n2;
            tail->prev = n2;
            continue;
        }

        Node *node = (Node *) malloc(sizeof(Node));
        initial_node(*node, pages[i], i, tail, tail->prev);
        tail->prev->next = node;
        tail->prev = node;
        mymap[node->address] = node;

        if (mymap.size() == cache_size + 1) {
            mymap.erase(head->next->address);
            Node *pointer = head->next;
            head->next->next->prev = head;
            head->next = head->next->next;
            free(pointer);
        }
    }
    cout << "Hit ratio = "<<float(hit) / pages.size()*100<<"%" << endl;
}

void CLOCK_algorithm() {
    vector<pair<int, int>> clock;
    hit = miss = 0;
    int index = 1;

    clock.emplace_back(pages[0], 1);

    for (int i = 1; i < pages.size(); ++i) {

        bool flag = false;

        for (auto &counter : clock) {
            if (counter.first == pages[i]) {
                hit++;
                counter.second = 1;
                flag = true;
                break;
            }
        }

        if (flag) {
            continue;
        }

        if (clock.size() < cache_size) {
            clock.emplace_back(pages[i], 1);
            index++;
            if (index == cache_size)
                index = 0;
            continue;
        }

        bool flag_for_replace = false;
        for (int j = 0; j <= cache_size; ++j) {
            if (clock[index].second == 0) {
                clock[index] = make_pair(pages[i], 1);
                index++;
                if (index == cache_size)
                    index = 0;
                break;
            } else {
                clock[index].second = 0;
            }
            index++;
            if (index == cache_size)
                index = 0;
        }
    }
    cout << "Hit ratio = "<<float(hit) / pages.size()*100<<"%" << endl;
}

void SECOND_CHANCE_algorithm() {
    hit = miss = 0;
    list<pair<int, int>> l;
    l.clear();
    for (auto &x:pages) {
        if (l.empty()) {
            miss++;
            l.push_back(make_pair(x, 1));
            continue;
        }
        bool flag = false;
        for (auto &y : l) {
            if (y.first == x) {
                y.second = 1;
                flag = true;
//                l.remove(y);
//                l.push_front(make_pair(x,1));
                break;
            }
        }
        if (flag) {
            hit++;
            continue;
        }
        miss++;

        if (l.size() == cache_size-1) {
            while (true) {
                pair<int, int> first = l.front();
                l.pop_front();
                if (first.second == 1) {
                    first.second = 0;
                    l.push_back(first);
                    continue;
                }
                break;
            }
        }
        l.push_back(make_pair(x, 1));
    }
    cout << "Hit ratio = "<<float(hit) / pages.size()*100<<"%" << endl;
}