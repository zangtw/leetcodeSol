#include <iostream>
#include <unordered_map>
using namespace std;

typedef struct LinkListNode {
  int key = INT_MAX;
  int val = INT_MAX;
  struct LinkListNode* prev;
  struct LinkListNode* next;
} LinkListNode;

class LRUCache{
private:
  int cpty;
  LinkListNode *head;
  unordered_map<int, LinkListNode*> key2Address;
public:
  LRUCache(int capacity) {
    cpty = capacity;
    if (cpty < 1) return;

    head = new LinkListNode();
    LinkListNode* p = head;

    for (int i = 1; i < capacity; i++)
    {
      LinkListNode* p_prev = p;

      p = new LinkListNode();
      p->prev = p_prev;
      p_prev->next = p;
    }

    head->prev = p;
    p->next = head;

    // from now on, head always points to the oldest node
    head = head->prev; 
  }

  int get(int key) {
    if (cpty < 1 || key2Address.find(key) == key2Address.end())
      return -1;
    else
    {
      set(key, key2Address[key]->val);
      return key2Address[key]->val;
    }
  }

  void set(int key, int value) {
    if (cpty < 1) return;

    // new key
    if (key2Address.find(key) == key2Address.end() 
        || key2Address[key] == head)
    {
      key2Address.erase(head->key);
      head->key = key;
      head->val = value;
      key2Address.insert(make_pair(key, head));
      head = head->prev;
    }
    else
    {
      LinkListNode* keyLoc = key2Address[key];
      keyLoc->prev->next = keyLoc->next;
      keyLoc->next->prev = keyLoc->prev; 

      keyLoc->next = head->next;
      head->next->prev = keyLoc;
      head->next = keyLoc;
      keyLoc->prev = head;
 
      keyLoc->val = value;
    }
  }
};

int main()
{
  int cap = 2;
  
  LRUCache sol(cap);
  sol.set(2,1);
  sol.set(1,1);
  cout << sol.get(2) << endl;
  //sol.set(1,1);
  sol.set(4,1);
  cout << sol.get(1) << endl;
  cout << sol.get(2) << endl;
  
  return 0;
}
