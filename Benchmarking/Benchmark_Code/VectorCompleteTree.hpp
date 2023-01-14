// Adapted from Goodrich
#pragma once
#include <vector>

//functor
template <class NodeType>
class Compare {
public:
    bool operator () (NodeType x, NodeType y) const {
        return x < y;
    }
};

template <class NodeType>
class VectorCompleteTree {
public:
    VectorCompleteTree() : sorted(1) {} // ctor

    // iterator
    typedef typename std::vector<NodeType>::iterator Position;

    int size() const { return sorted.size() - 1; }
    Position left(const Position& p) { return pos(2 * idx(p)); }
    Position right(const Position& p) { return pos(2 * idx(p) + 1); }
    Position parent(const Position& p) { return pos(idx(p) / 2); }
    bool hasLeft(const Position& p) const { return 2 * idx(p) <= size(); }
    bool hasRight(const Position& p) const { return 2 * idx(p) + 1 <= size(); }
    bool isRoot(const Position& p) const { return idx(p) == 1; }
    Position root() { return pos(1); }
    Position last() { return pos(size()); }
    void addLast(const NodeType& e) { sorted.push_back(e); }
    void removeLast() { sorted.pop_back(); }
    void swap(const Position& p, const Position& q)
    {
        NodeType e = *q;
        *q = *p;
        *p = e;
    }
    void display()
    {
        size_t sz = size();
        for (size_t i = 1; i <= sz; i++) {
            std::cout << "Elem[" << i << "]: " << sorted[i];
            if (i < sz)
                std::cout << ", ";
        }
    }
protected:
    Position pos(int i) { return sorted.begin() + i; }
    int idx(const Position& p) const { return p - sorted.begin(); }

private:
    std::vector<NodeType> sorted;
};