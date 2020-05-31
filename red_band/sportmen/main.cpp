#include <iostream>
#include <map>
#include <stack>

using namespace std;

class List {
public:
    List() {
        head = nullptr;
    }

    void add(int k, int x) {
        if (idx.count(x) == 0) {
            Node *buf = new Node;
            buf->next = head;
            buf->key = k;
            head = buf;
            idx[k] = buf;
        } else {
            Node *cur = idx[x];
            Node *buf = new Node;
            buf->next = cur->next;
            buf->key = k;
            cur->next = buf;
            idx[k] = buf;
        }
    }

    void print() {
        stack<int> s;
        for (Node *n = head; n != nullptr; n = n->next) {
            s.push(n->key);
        }
        while (!s.empty()) {
            cout <<s.top()<<" ";
            s.pop();
        }
    }

private:
    struct Node {
        Node *next;
        int key;
    };
    Node *head;
    map<int, Node *> idx;
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin>>N;
    List l;
    for (int i =0; i<N; i++) {
        int k, x;
        cin>>k>>x;
        l.add(k, x);
    }
    l.print();
    return 0;
}
