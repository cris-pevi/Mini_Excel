#ifndef __NODE_H__
#define __NODE_H__

#include <map>
#include <memory>

template<typename T>
class Node {
public:
    virtual ~Node() {}
    virtual T evaluate(const std::map<std::string, std::unique_ptr<Node<T>>> &cellExpressions) const = 0;
};

#endif