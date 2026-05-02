#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *reverseList(ListNode *head)
{
    if (head == nullptr) {
        return nullptr;
    }
    ListNode *pre = nullptr;
    ListNode *nxt = head->next;
    while (nxt != nullptr) {
        head->next = pre;
        pre = head;
        head = nxt;
        nxt = nxt->next;
    }
    head->next = pre;
    return head;
}

int main()
{
    // 测试函数
    ListNode n5(50);
    ListNode n4(49, &n5);
    ListNode n3(45, &n4);
    ListNode n2(38, &n3);
    ListNode n1(27, &n2);
    ListNode *head = &n1;
    cout << "原链表：";
    while (head != nullptr) {
        cout << head->val << "\t";
        head = head->next;
    }
    cout << endl;
    head = reverseList(&n1);
    cout << "反转后：";
    while (head != nullptr) {
        cout << head->val << "\t";
        head = head->next;
    }
    cout << endl;
    return 0;
}
