#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <stack>

template<typename key_T>
class Node
{
public:

    Node();
    Node(key_T key);

    ~Node();

    int GetKey();
    void Insert(Node* node);
    Node* Search(key_T key);
    void Print();
    void Print(std::ostream &os);

    class Iterator
    {
    private:
        key_T m_key;
        Node<key_T>* m_root;
        Node<key_T>* m_position;
        std::stack<Node<key_T>*> s;

    public:
        Iterator(Node<key_T>* root)
        {
            m_root = m_position = root;
            m_key = root->GetKey();
            s.push(root);
        }

        Node<key_T>* getFirst()
        {
            while(s.top()->m_left) {
                s.push(s.top()->m_left);
            }
            m_key = s.top()->GetKey();
            return s.top();
        }


        Node<key_T>* getLast()
        {
            while(s.top()->m_right) {
                s.push(s.top()->m_right);
            }
            m_key = s.top()->GetKey();
            return s.top();
        }

        Node<key_T>* next()
        {
            if(s.size() == 0) {
                std::cout << "fail";
                return NULL;
            } else if(s.top()->m_right && s.top()->m_right->GetKey() != m_key) {
                s.push(s.top()->m_right);
                return getFirst();
            } else {
                s.pop();
                Iterator::next();
            }
            return NULL;
        }

        Node<key_T>* previous()
        {
            if(s.size() == 0) {
                std::cout << "fail";
                return NULL;
            } else if(s.top()->m_left && s.top()->m_left->GetKey() != m_key) {
                s.push(s.top()->m_left);
                return getLast();
            } else {
                s.pop();
                Iterator::next();
            }
            return NULL;
        }
    };

private:
    key_T m_key;
    Node* m_left;
    Node* m_right;

};



template<typename key_t>
Node<key_t>::Node()
{
    Node(0);
}

template<typename key_t>
Node<key_t>::Node(key_t key)
{
    m_key = key;
    m_left = NULL;
    m_right = NULL;
}

template<typename key_t>
Node<key_t>::~Node()
{
    m_left->~Node();
    m_right->~Node();
}

template<typename key_t>
int Node<key_t>::GetKey()
{
    return m_key;
}

template<typename key_t>
void Node<key_t>::Insert(Node *node)
{
    if(node->GetKey() < m_key) {
        if(!m_left) {
            m_left = node;
        } else {
            m_left->Insert(node);
        }
    } else {
        if(!m_right) {
            m_right = node;
        } else {
            m_right->Insert(node);
        }
    }
}

/// \brief Search the Node with has that key
/// \param key The Keyobject
template<typename key_t>
Node<key_t>* Node<key_t>::Search(key_t key)
{
    // check if to go lower
    if(key < m_key) {
        if(m_left) {
            return m_left->Search(key);
        }
    } else {
        if(m_right) {
            return m_right->Search(key);
        }
    }

    // is it the right Node?
    if(key == m_key) {
        return this;
    } else {
        return NULL;
    }
}

/// \brief Print Node in std::cout
template<typename key_t>
void Node<key_t>::Print() {
    Node<key_t>::Print(std::cout);
}

/// \brief Print Node in a given std::ostream
/// \param os The Outputstream
template<typename key_t>
void Node<key_t>::Print(std::ostream &os)
{
    // first print all left Nodes
    if(m_left) {
        m_left->Print(os);
    }

    // print myself
    os << m_key << " ";

    // now print all right Nodes
    if(m_right) {
        m_right->Print(os);
    }
}

#endif // NODE_H
