#include <iostream>
using namespace std;
struct Node {
    int x;
    Node *next;
    Node(int val = 0, Node *next = nullptr) : x(val), next(next) {}
};
Node *create_c(int n)
{
    Node *head;
    head = new Node(1, nullptr);
    if (n == 1) {
        return head;
    }
    Node *tail;
    tail = new Node(n, head);
    Node *cur;
    for (int i = 0; i < n - 2; i++) {
        cur = new Node(n - i - 1, tail);
        tail = cur;
    }
    head->next = cur;
    return head;
}
void del_c(Node &h, int m)
{
    Node *cur = &h;
    while (cur->next != nullptr && cur->next != cur) {
        Node *pre;
        for (int i = 1; i <= m; i++) {
            if (i == m - 1) {
                pre = cur;
            }
            if (i == m) {
                cout << cur->x << endl;
                pre->next = cur->next;
                cur->next = nullptr;
                cur = pre->next;
                break;
            }
            cur = cur->next;
        }
    }
    cur->next = nullptr;
    h = *cur;
}

int main()
{
    int n, m;
    cin >> n >> m;
    Node *head = create_c(n);
    del_c(*head, m);
    cout << "Last: " << head->x << endl;
    return 0;
}