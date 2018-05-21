#include<bits/stdc++.h>

using namespace std;

int S, M, N;
vector<int> disks;

void set_the_variable();

void FCFS();

void SSTF();

void SCAN();

void CSCAN();

void LOOK();

void CLOOK();

int main() {
    set_the_variable();
    FCFS();
    SSTF();
    SCAN();
    CSCAN();
    LOOK();
    CLOOK();
}

void set_the_variable() {
    cin >> S;
    cin >> M;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int read_num;
        cin >> read_num;
        disks.push_back(read_num);
    }
}

void FCFS() {
    cout << "FCFS" << endl;
    int count = 0;
    int pointer = S;
    cout << pointer;
    for (auto &x : disks) {
        int sub = abs(pointer - x);
        cout << " -> " << x;
        pointer = x;
        count += sub;
    }
    cout << endl << count << endl;
}

void SSTF() {
    cout << "SSTF" << endl;
    int count = 0;
    int pointer = S;
    cout << pointer;

    vector<int> sort_disk(disks);
    sort(sort_disk.begin(), sort_disk.end());
    long index = lower_bound(sort_disk.begin(), sort_disk.end(), pointer) - sort_disk.begin();

    bool forward;
    while (!sort_disk.empty()) {
        if (index == 0)
            forward = true;
        else if (index >= sort_disk.size())
            forward = false;
        else
            forward = sort_disk[index] - 2 * pointer + sort_disk[index - 1] < 0;

        int disk_address;
        if (forward) {
            disk_address = sort_disk[index];
            sort_disk.erase(sort_disk.begin() + index);
        } else {
            disk_address = sort_disk[index - 1];
            sort_disk.erase(sort_disk.begin() + index - 1);
            index--;
        }
        int sub = abs(disk_address - pointer);
        cout << " -> " << disk_address;
        pointer = disk_address;
        count += sub;
    }
    cout << endl << count << endl;
}

void SCAN() {
    cout << "SCAN" << endl;
    int count = 0;
    int pointer = S;
    cout << pointer;

    vector<int> sort_disk(disks);
    sort(sort_disk.begin(), sort_disk.end());
    long index = lower_bound(sort_disk.begin(), sort_disk.end(), pointer) - sort_disk.begin();
    int min = sort_disk[0];

    bool forward = false;
    while (!sort_disk.empty()) {
        if (!forward && index == 0) {
            forward = true;
            cout << " -> " << 0;
            count += min;
            pointer = 0;
        }

        int disk_address;
        if (forward) {
            disk_address = sort_disk[index];
            sort_disk.erase(sort_disk.begin() + index);
        } else {
            disk_address = sort_disk[index - 1];
            sort_disk.erase(sort_disk.begin() + index - 1);
            index--;
        }
        int sub = abs(disk_address - pointer);
        cout << " -> " << disk_address;
        pointer = disk_address;
        count += sub;
    }

    cout << endl << count << endl;
}

void CSCAN() {
    cout << "C-SCAN" << endl;
    int count = 0;
    int pointer = S;
    cout << pointer;

    vector<int> sort_disk(disks);
    sort(sort_disk.begin(), sort_disk.end());
    long index = lower_bound(sort_disk.begin(), sort_disk.end(), pointer) - sort_disk.begin();
    int min = sort_disk[0];

    while (!sort_disk.empty()) {
        if (index == 0) {
            cout << " -> " << 0 << " -> " << (M-1);
            count += min;
            pointer = (M-1);
            index = sort_disk.size();
        }

        int disk_address = sort_disk[index - 1];
        sort_disk.erase(sort_disk.begin() + index - 1);
        index--;

        int sub = abs(disk_address - pointer);
        cout << " -> " << disk_address;
        pointer = disk_address;
        count += sub;
    }
    cout << endl << count << endl;
}

void LOOK() {
    cout << "LOOK" << endl;
    int count = 0;
    int pointer = S;
    cout << pointer;

    vector<int> sort_disk(disks);
    sort(sort_disk.begin(), sort_disk.end());
    long index = lower_bound(sort_disk.begin(), sort_disk.end(), pointer) - sort_disk.begin();

    bool forward = false;
    while (!sort_disk.empty()) {
        if (!forward && index == 0) {
            forward = true;
        }

        int disk_address;
        if (forward) {
            disk_address = sort_disk[index];
            sort_disk.erase(sort_disk.begin() + index);
        } else {
            disk_address = sort_disk[index - 1];
            sort_disk.erase(sort_disk.begin() + index - 1);
            index--;
        }
        int sub = abs(disk_address - pointer);
        cout << " -> " << disk_address;
        pointer = disk_address;
        count += sub;
    }

    cout << endl << count << endl;
}

void CLOOK() {
    cout << "C-LOOK" << endl;
    int count = 0;
    int pointer = S;
    cout << pointer;

    vector<int> sort_disk(disks);
    sort(sort_disk.begin(), sort_disk.end());
    long index = higher_bound(sort_disk.begin(), sort_disk.end(), pointer) - sort_disk.begin();

    while (!sort_disk.empty()) {
        if (index == 0) {
            index = sort_disk.size();
            pointer = sort_disk[sort_disk.size() - 1];
        }

        int disk_address = sort_disk[index - 1];
        sort_disk.erase(sort_disk.begin() + index - 1);
        index--;

        int sub = abs(disk_address - pointer);
        cout << " -> " << disk_address;
        pointer = disk_address;
        count += sub;
    }
    cout << endl << count << endl;
}