#include "PQ.h"

int main()
{   
    vector<string> tasks;
    vector<int> priorities;

    cout << "\n1) Heap Array of Strings Using Vectors Constructor" << endl;

    tasks.push_back("Brush");
    tasks.push_back("Shower");
    tasks.push_back("Eat");
    tasks.push_back("Study");
    tasks.push_back("Pray");
    tasks.push_back("Sleep");

    for (int i = 1; i <= 6; i++)
        priorities.push_back(i);
    
    PQ<string> kuta(tasks, priorities);

    cout << "\n- Heap array of priorities with their indices:" << endl;
    kuta.printHeap();

    cout << "\n- Array of AVL pointers:" << endl;
    kuta.printPointers();
    
    cout << "\n- AVL Tree of tasks with the heap array indices:" << endl;
    kuta.printTree();

    cout << endl;

    cout << "- Check heap size: " << kuta.size() << endl << endl;
    cout << "- Find and return min task: " << kuta.findMin() << endl << endl;

    cout << "- Test make empty and print heap:" << endl;
    kuta.makeEmpty();
    kuta.printHeap();
    cout << endl;


    cout << "\n2) Heap Array of Chars Using Empty Constructor" << endl;
    PQ<char> lodu;
    
    // insert one by one
    lodu.insert('a', 0);
    lodu.insert('b', 1);
    lodu.insert('c', 4);
    lodu.insert('d', 2);

    cout << "\n- Heap array of priorities with their indices:" << endl;
    lodu.printHeap();

    cout << "\n- Array of AVL pointers:" << endl;
    lodu.printPointers();
    
    cout << "\n- AVL Tree of tasks with the heap array indices:" << endl;
    lodu.printTree();
    cout << endl;

    cout << "- Heap after updating priority of task a to be 0:" << endl;
    lodu.updatePriority('a', 0);
    lodu.printHeap();

    cout << "\n- Find, return and delete min task: " << lodu.deleteMin() << endl;

    cout << "\nAfter one deletion:" << endl;
    cout << "- Heap array of priorities with their indices:" << endl;
    lodu.printHeap();

    cout << "\n- Array of AVL pointers:" << endl;
    lodu.printPointers();

    cout << "\n- AVL Tree of tasks with the heap array indices:" << endl;
    lodu.printTree();

    cout << "- Heap after updating priority of task c to be 7:" << endl;
    lodu.updatePriority('c', 7);
    lodu.printHeap();
    cout << endl;

    lodu.makeEmpty();

    return 0;
}
