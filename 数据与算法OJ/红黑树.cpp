#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const int BUF_SIZE = 1 << 20;
char buf[BUF_SIZE];
int ptr = 0;

unsigned int readInt() {
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    unsigned int val = 0;
    while (c >= '0' && c <= '9') {
        val = val * 10 + c - '0';
        c = getchar();
    }
    return val;
}

void writeInt(unsigned int num) {
    if (ptr > BUF_SIZE - 20) {
        fwrite(buf, 1, ptr, stdout);
        ptr = 0;
    }
    if (num == 0) {
        buf[ptr++] = '0';
    } else {
        char tmp[20];
        int tmpPtr = 0;
        while (num > 0) {
            tmp[tmpPtr++] = (num % 10) + '0';
            num /= 10;
        }
        while (tmpPtr > 0) {
            buf[ptr++] = tmp[--tmpPtr];
        }
    }
    buf[ptr++] = ' ';
}

void flushBuf() {
    fwrite(buf, 1, ptr, stdout);
    ptr = 0;
}

int main() {
    unsigned int n = readInt(), m = readInt();
    set<unsigned int> seg;

    for (int i = 0; i < n; ++i) {
        unsigned int x = readInt();
        seg.insert(x);
    }

    unsigned int ops = 0;
    char opType;
    while (ops < m) {
        cin>>opType;

        if (opType == '0') {
            unsigned int q1 = readInt();
            for (int j = 0; j < q1; ++j) {
                unsigned int query = readInt();
                if (!seg.empty()) {
                    auto it = seg.upper_bound(query);
                    if (it == seg.begin()) {
                        writeInt(*it);
                    } else {
                        --it;
                        writeInt(*it);
                    }
                }
            }
            buf[ptr - 1] = '\n';
            ops++;

        } else if (opType == '1') {
            unsigned int q1 = readInt();
            for (int j = 0; j < q1; ++j) {
                seg.insert(readInt());
            }
            ops++;

        } else if (opType == '2') {
            unsigned int q1 = readInt();
            vector<unsigned int> mergePts(q1);
            for (int j = 0; j < q1; ++j) {
                mergePts[j] = readInt();
            }

            sort(mergePts.begin(), mergePts.end());
            vector<unsigned int> markPts;
            unsigned int lastMark = -1;

            for (unsigned int mergePt : mergePts) {
                auto it = seg.upper_bound(mergePt);
                if (it != seg.begin()) {
                    --it;
                    unsigned int st = *it;
                    if (st != lastMark) {
                        markPts.push_back(st);
                        lastMark = st;
                    }
                }
            }

            for (unsigned int st : markPts) {
                auto nextIt = seg.upper_bound(st);
                if (nextIt != seg.end()) {
                    seg.erase(nextIt);
                }
            }
            ops++;

        } else if (opType == '3') {
            if (!seg.empty()) {
                for (auto it = seg.begin(); it != seg.end(); ++it) {
                    writeInt(*it);
                }
                buf[ptr - 1] = '\n';
            }
            ops++;
        }
    }

    flushBuf();
    return 0;
}
