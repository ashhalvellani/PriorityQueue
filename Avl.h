#include "dsexceptions.h"
#include <iostream>
using namespace std;

template <typename Comparable>

class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
    { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    void displayLinks( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            displayLinks( root, 0 );
    }

    void makeEmpty( )
    {
        makeEmpty( root );
    }

    void* insert( const Comparable & x, int i )
    {
        return insert( x, i, root );
    }

    int remove( const Comparable & x )
    {
        return remove( x, root );
    }

    void swapIndex( void *x, void *y ) 
    {
        swapInd( x, y );
    }

    const Comparable & getID(const void* x) const
    {
        return element(x);
    }

    int getIndex(const Comparable & x) const
    {
        return getInd(x, root);
    }

    void setIndex(void* x, int i)
    {
        return setInd(x, i);
    }


  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode    *left;
        AvlNode    *right;
        int        height;
        int        index;

        AvlNode( const Comparable & ele, int ind, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, index{ ind }, left{ lt }, right{ rt }, height{ h } { }
    };
    
    AvlNode *root;

    void* insert( const Comparable & x, int i, AvlNode * & t )
    {   
        void * result;
        if( t == nullptr ) {
            t = new AvlNode{ x, i, nullptr, nullptr };
            result = (void *) t;
        }
        else if( x < t->element )
            result = insert( x, i, t->left );
        else if( t->element < x )
            result = insert( x, i, t->right );        
        balance( t );

        return result;
    }

    void swapInd( void* x, void* y ) 
    {
        AvlNode *s = (struct AvlNode *) x;
        AvlNode *t = (struct AvlNode *) y;

        int temp = s->index;
        s->index = t->index;
        t->index = temp;
    }

    const Comparable & element(const void* x) const
    {
        AvlNode *t = (struct AvlNode *) x;
        return t->element;
    }

    int getInd(const Comparable & x, AvlNode *t ) const 
    {
        if (t->element == x)
            return t->index;
        if (x < t->element && t->left != nullptr)
            return getInd(x, t->left);
        if (x > t->element && t->right != nullptr)
            return getInd(x, t->right);
        return 0;
    }
     
    int remove( const Comparable & x, AvlNode * & t )
    {
        int index;
        if( x < t->element )
            index = remove( x, t->left );
        else if( t->element < x )
            index = remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            index = t->index;
            t->element = findMin( t->right )->element;
            index = remove( t->element, t->right );
        }
        else
        {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        balance( t );
        return index;
    }

    void setInd(void* x, int i){
        AvlNode* t = (struct AvlNode *) x;
        t->index = i;
    }

    
    static const int ALLOWED_IMBALANCE = 1;

    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE ) {
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        }
        else if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE ) {
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
        }
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

    bool contains( const Comparable & x, AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
    
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {   
            printTree( t->left );
            cout << "Task: " << t->element << ",   Index: " << t->index <<endl;
            printTree( t->right );
        }
    }

    void displayLinks( AvlNode *t, int depth) const
    {
        const int SHIFT = 4 ;
        if( t != nullptr )
        {
            for( int i = 0 ; i < SHIFT*depth ; i++ ){ cout << " " ; }
            
            cout << t->element;
            cout << ") @: " << t;

            if (t->left == nullptr) cout << " L:0";
            else cout << " L:" << t->left;

            if (t->right == nullptr) cout << " R:0" << endl;
            else cout << " R:" << t->right << endl;

            displayLinks( t->left, depth+1 );
            displayLinks( t->right, depth+1 );
        }
    }

    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }

    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

};