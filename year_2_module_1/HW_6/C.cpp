#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")

using namespace std;

struct PersistentStack {
    int val = 0;
    PersistentStack *parent = nullptr;
    int count;

    PersistentStack(PersistentStack *p, int new_val) {
        val = new_val;
        count = p->count + 1;
        parent = p;
    }

    PersistentStack() {
        count = 0;
    }

    PersistentStack *Push(int new_val) {
        return new PersistentStack(this, new_val);
    }

    PersistentStack *Pop() {
        return parent;
    }

    int Top() {
        return val;
    }
};

struct PersistentQueue {
    PersistentStack *R, *L, *R1, *L1, *buf;
    bool recopy, copied;
    int to_copy;

    PersistentQueue(PersistentStack *newL, PersistentStack *newL1, PersistentStack *newR, PersistentStack *newR1,
                    PersistentStack *new_buf, bool new_recopy, bool new_copied, int new_to_copy) {
        L = newL;
        L1 = newL1;
        R = newR;
        R1 = newR1;
        buf = new_buf;
        recopy = new_recopy;
        copied = new_copied;
        to_copy = new_to_copy;
    }

    PersistentQueue() {
        L = new PersistentStack();
        L1 = new PersistentStack();
        R = new PersistentStack();
        R1 = new PersistentStack();
        buf = new PersistentStack();
        recopy = false;
        copied = false;
        to_copy = 0;
    }

    PersistentQueue *Push(int new_val) {
        if (!recopy) {
            PersistentStack *Lc = L->Push(new_val);
            PersistentQueue *Q = new PersistentQueue(Lc, L1, R, R1, buf, recopy, copied, to_copy);
            return Q->CheckRecopy();
        } else {
            PersistentStack *Lc1 = L1->Push(new_val);
            PersistentQueue *Q = new PersistentQueue(L, Lc1, R, R1, buf, recopy, copied, to_copy);
            return Q->CheckNormal();
        }
    }

    PersistentQueue *Pop() {
        if (!recopy) {
            PersistentStack *Rc = R->Pop();
            PersistentQueue *Q = new PersistentQueue(L, L1, Rc, R1, buf, recopy, copied, to_copy);
            return Q->CheckRecopy();
        } else {
            PersistentStack *Rc1 = R1->Pop();
            PersistentStack *Rc = R;
            int cur_copy = to_copy;
            if (to_copy > 0) {
                --cur_copy;
            } else {
                Rc = Rc->Pop();
            }
            PersistentQueue *Q = new PersistentQueue(L, L1, Rc, Rc1, buf, recopy, copied, cur_copy);
            return Q->CheckNormal();
        }
    }

    int Top() {
        if (!recopy) {
            return R->Top();
        } else {
            return R1->Top();
        }
    }

    PersistentQueue *CheckRecopy() {
        if (L->count > R->count) {
            PersistentQueue *Q = new PersistentQueue(L, L1, R, R, buf, true, false, R->count);
            return Q->CheckNormal();
        } else {
            return new PersistentQueue(L, L1, R, R1, buf, false, copied, to_copy);
        }
    }

    PersistentQueue *CheckNormal() {
        PersistentQueue *Q = AdditionalOperations();
        return new PersistentQueue(Q->L, Q->L1, Q->R, Q->R1, Q->buf, Q->buf->count != 0, Q->copied, Q->to_copy);
    }

    PersistentQueue *AdditionalOperations() {
        int toDo = 3;
        PersistentStack *Lc = L;
        PersistentStack *Lc1 = L1;
        PersistentStack *Rc = R;
        PersistentStack *bufc = buf;
        bool cur_copied = copied;
        int cur_copy = to_copy;
        while (!cur_copied && toDo > 0 && Rc->count > 0) {
            int x = Rc->Top();
            Rc = Rc->Pop();
            bufc = bufc->Push(x);
            --toDo;
        }
        while (toDo > 0 && Lc->count > 0) {
            cur_copied = true;
            int x = Lc->Top();
            Lc = Lc->Pop();
            Rc = Rc->Push(x);
            --toDo;
        }
        while (toDo > 0 && bufc->count > 0) {
            int x = bufc->Top();
            bufc = bufc->Pop();
            if (cur_copy > 0) {
                Rc = Rc->Push(x);
                --cur_copy;
            }
            --toDo;
        }
        if (bufc->count == 0) {
            PersistentStack *t = Lc;
            Lc = Lc1;
            Lc1 = t;
        }
        return new PersistentQueue(Lc, Lc1, Rc, R1, bufc, recopy, cur_copied, cur_copy);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    cin >> n;
    vector<PersistentQueue *> q;
    q.push_back(new PersistentQueue());
    vector<vector<int>> queries(n);
    for (int i = 0; i < n; ++i) {
        int a, t, m;
        cin >> a >> t;
        queries[i].push_back(a);
        queries[i].push_back(t);
        if (a == 1) {
            cin >> m;
            queries[i].push_back(m);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (queries[i][0] == 1) {
            int t = queries[i][1], m = queries[i][2];
            q.push_back(q[t]->Push(m));
        } else {
            int t = queries[i][1];
            cout << q[t]->Top() << endl;
            q.push_back(q[t]->Pop());
        }
    }
    return 0;
}