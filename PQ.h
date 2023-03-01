#ifndef PQ_H
#define PQ_H

#include <vector>
#include "Avl.h"

// PQ class
//
// Template parameter: ID
// Constructors:
// PQ --> constructs a new empty queue
// PQ( tasks, priorities ) --> constructs a new queue with a given set of task IDs and priorities 
// ******************PUBLIC OPERATIONS*********************
// void insert( x, p )       --> Insert task ID x with priority p 
// ID findMin( )  --> Return a task ID with smallest priority, without removing it 
// ID deleteMin( )   --> Remove and return a task ID with smallest priority 
// void updatePriority( x, p )   --> Changes priority of ID x to p (if x not in PQ, inserts x);
// bool isEmpty( )   --> Return true if empty; else false
// int size() --> return the number of task IDs in the queue 
// void makeEmpty( )  --> Remove all task IDs (and their priorities)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename ID>
class PQ
{
  public:

    // Constructor
    // Initializes a new empty PQ
    PQ() : heapSize {0}, min {}
    { }

    // Constructor
    // Initializes a new PQ with a given set of tasks IDs and priorities  
    //      priority[i] is the priority for ID task[i] 
    PQ( const vector<ID> & tasks, const vector<int> & priorities ) : heapSize {0}, min {}
    {
      for(int i = 0; i < tasks.size(); i++) {
        insert( tasks[i], priorities[i] );
      } 
    }
						     
    // Emptiness check 
    bool isEmpty( ) const
    {
      return heapSize == 0;
    }

    // Deletes and Returns a task ID with minimum priority
    //    Throws exception if queue is empty
    const ID & deleteMin()
    {
      if (isEmpty())
        throw UnderflowException{ };
        
      min = tree.getID(avlPointers[0]);

      heapArr[0] = heapArr[heapSize - 1];

      int i = tree.remove(min);
      avlPointers[i - 1] = avlPointers[0];

      tree.swapIndex(avlPointers[0], avlPointers[heapSize - 1]);
      
      avlPointers[0] = avlPointers[heapSize - 1];
      
      heapSize--;

      percolateDown(0);
    
      return min;
    }

    // Returns an ID with minimum priority without removing it
    //     Throws exception if queue is empty
    const ID & findMin() const
    {
      if (isEmpty())
        throw UnderflowException{ };
      return tree.getID(avlPointers[0]);
    }

    // Insert ID x with priority p.
    void insert( const ID & x, int p )
    {
      heapSize++;
      heapArr.push_back(p);
    
      void* ptr = tree.insert(x, heapSize - 1); 
      
      avlPointers.push_back(ptr);

      percolateUp(heapSize-1);
    }

    // Update the priority of ID x to p
    // Inserts x with p if s not already in the queue
    void updatePriority( const ID & x, int p )
    {
      if (!tree.contains(x))
        insert(x, p);
      int index = tree.getIndex(x);

      int oldP = heapArr[index];
      heapArr[index] = p;

      if (oldP < p)
        percolateDown(index);
      if (oldP > p)
        percolateUp(index);
    } 

    // Return the number of task IDs in the queue
    int size( ) const 
    {
      return heapSize;
    }

    // Delete all IDs from the PQ
    void makeEmpty( )
    {
      heapArr.clear();
      avlPointers.clear();
      tree.makeEmpty();
      heapSize = 0;
    }

    void printHeap( ) {
      if (heapSize == 0)
        cout << "Empty heap" << endl;
      else {
        cout << "Priorities: ";
        for (int i = 0; i < heapSize; i++)
          cout << heapArr[i] << ", "; 
        cout << endl;
        cout << "Indices:    ";
        for (int i = 0; i < heapSize; i++)
          cout << i << ", "; 
        cout << endl;
      }
    }

    void printPointers() {
      for (int i = 0; i < heapSize; i++)
        cout << avlPointers[i] << ", ";
      cout << endl;
    }

    void printTree( ) {
      tree.printTree();
      cout << endl;
      cout << "Display links:" << endl;
      tree.displayLinks();
    }

  private:
    int heapSize;
    vector<int> heapArr;
    vector<void*> avlPointers;
    AvlTree<ID> tree;
    ID min;

    void percolateDown(int index) {
      int left = 2*index + 1;
      int right = 2*index + 2;
      int smallest = index;

      if(left <= heapSize && heapArr[index] > heapArr[left])
        smallest = left;

      if (right <= heapSize && heapArr[smallest] > heapArr[right])
        smallest = right;
      
      if (smallest != index) {
        swap(heapArr[index], heapArr[smallest]);
        
        tree.swapIndex(avlPointers[index], avlPointers[smallest]);

        swap(avlPointers[index], avlPointers[smallest]);
        
        percolateDown(smallest);
      }
    }

    void percolateUp(int index) {
      int i = index;

      while (i >= 0 && heapArr[(i-1)/2] > heapArr[i]) {
        swap(heapArr[i], heapArr[(i-1)/2]);

        tree.swapIndex(avlPointers[i], avlPointers[(i-1)/2]);

        swap(avlPointers[i], avlPointers[(i-1)/2]);

        i = (i-1)/2;
      }
    }
};


#endif
