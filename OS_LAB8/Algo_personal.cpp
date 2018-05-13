//
// Created by cat on 18-5-5.
//
#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;

#define DEFAULT_CACHE_SIZE 512
#define DEFAULT_ALGORITHM 2

int cache_size, working_algorithm, hit, miss, page_max_size;

typedef void (*pf)();

vector<int> pages;
map<int, pf> algorithms;

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
    while (true) {
        bool flag = false;

//        cin >> cache_size;
//        if (cache_size > 2048 || cache_size < 0)
//            flag = true;
//
//        cin >> working_algorithm;
//        if (working_algorithm > 4 || working_algorithm < 0)
//            flag = true;

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

void FIFO_algorithm() {
    hit = miss = 0;
    unordered_map<int, int> mymap((unsigned long) cache_size);
    pair<int, int> first;
    for (int i = 0; i < pages.size(); ++i) {
        int address = pages[i];


        if (mymap.empty()) {
            miss++;
            mymap[address] = i;
            first = make_pair(address, i);
            continue;
        }


        if (mymap[address] != NULL) {
            mymap[address] = i;
            continue;
        } else {
            miss++;
            mymap[address] = i;
        }

        if (mymap.size() == cache_size + 1) {
            mymap.erase(first.second);
            int new_index = first.first + 1;
            while (true) {
                int next_address = pages[new_index];
                if (mymap[next_address] == new_index) {
                    first = make_pair(next_address, new_index);
                    break;
                }
                new_index++;
            }
        }
    }

    cout << miss << endl;
}

void FIFO_algorithm_origin() {
    hit = miss = 0;
    list<int> l;
    l.clear();
    for (auto &x:pages) {
        if (l.empty()) {
            miss++;
            l.push_front(x);
            continue;
        }
        bool flag = false;
        for (auto &y : l) {
            if (y == x) {
                flag = true;
                l.remove(y);
                l.push_front(x);
                break;
            }
        }
        if (flag) {
            hit++;
            continue;
        }
        miss++;
        if (l.size() == cache_size) {
            l.pop_back();
        }
        l.push_front(x);
    }
}

void MIN_algorithm() {
    unordered_map<int, vector<int>> map;
    for (int i = 0; i < pages.size(); ++i) {
        map[pages[i]].push_back(i);
    }

    unordered_map<int, int> storage;
    hit = miss = 0;
    for (int i = 0; i < pages.size(); ++i) {
        int address = pages[i];

        if (storage[address] != NULL) {
            int back = storage[address];
            while (map[address][back] <= i) {
                back++;
            }
            back++;
            storage[address] = back;
            continue;
        }

        miss++;
        if (storage.size() < cache_size) {
            int back = storage[address];
            while (map[address][back] <= i) {
                back++;
            }
            back++;
            storage[address] = back;
            continue;
        }

        pair<int, int> count;
        for (auto &element:storage) {
            if (element.second - i > count.second) {
                count = element;
            }
        }
        storage.erase(count.first);
        int back = storage[address];
        while (map[address][back] <= i) {
            back++;
        }
        back++;
        storage[address] = back;
    }

    cout << miss << endl;
}

void LRU_algorithm() {
    unordered_map<int, vector<int>> map;
    for (int i = 0; i < pages.size(); ++i) {
        map[pages[i]].push_back(i);
    }

    unordered_map<int, int> storage;
    hit = miss = 0;
    for (int i = 0; i < pages.size(); ++i) {
        int address = pages[i];

        if (storage[address] != NULL) {
            int back = storage[address];
            while (map[address][back] <= i) {
                back--;
            }
            back--;
            storage[address] = back;
            continue;
        }

        miss++;
        if (storage.size() < cache_size) {
            int back = storage[address];
            while (map[address][back] <= i) {
                back--;
            }
            back--;
            storage[address] = back;
            continue;
        }

        pair<int, int> count;
        for (auto &element:storage) {
            if (i - element.second > count.second) {
                count = element;
            }
        }
        storage.erase(count.first);
        int back = storage[address];
        while (map[address][back] <= i) {
            back--;
        }
        back--;
        storage[address] = back;
    }
    cout << miss << endl;
}

void CLOCK_algorithm() {
    vector<pair<int,int>> clock;
    hit = miss = 0;
    int index = 0;
    for (int i = 0; i < pages.size(); ++i) {
        if (clock.empty()){
            miss++;
            clock.push_back(make_pair(pages[i], 1));
            index++;
            continue;
        }

        bool flag = false;
        for(auto &counter : clock){
            if(counter.first== pages[i]){
                counter.second = 1;
                flag = true;
                index++;
                break;
            }
        }

        if(flag){
            continue;
        }

        miss++;
        if(clock.size() < cache_size){
            clock.push_back(make_pair(pages[i], 1));
            index++;
            if(index == cache_size-1)
                index = 0;
            continue;
        }

        bool flag_for_replace = false;
        for (int j = 0; j < cache_size; ++j) {
            if(clock[index].second == 0){
                flag_for_replace= true;
            } else{
                clock[index].second = 0;
            }
            index++;
            if(index == cache_size-1)
                index = 0;
            if(flag_for_replace)
                break;
        }

        if(!flag_for_replace){
            clock[index] = make_pair(pages[i],1);
        }
    }
    cout << miss << endl;
}

void SECOND_CHANCE_algorithm() {
    hit = miss = 0;
    list<pair<int,int>> l;
    l.clear();
    for (auto &x:pages){
        if(l.empty()){
            miss++;
            l.push_front(make_pair(x,1));
            continue;
        }
        bool flag = false;
        for (auto &y : l){
            if(y==x){
                flag = true;
                l.remove(y);
                l.push_front(make_pair(x,1));
                break;
            }
        }
        if(flag){
            hit++;
            continue;
        }
        miss++;
        if(l.size() == cache_size){
            while (true){
                
            }


            l.pop_back();
        }
        l.push_front(make_pair(x,1));
    }
}