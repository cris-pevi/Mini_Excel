#ifndef __NODE_H__
#define __NODE_H__

#include <map>
#include <memory>
#include <functional>

template<typename T>
class Node {
    public:
        virtual ~Node() {}
        virtual T evaluate(const std::map<std::string, std::unique_ptr<Node<T>>> &cellExpressions) const = 0;
};

template<typename T>
class NumberNode : public Node<T> {
    T value;
    
    public:
        NumberNode(T v) : value(v) {}
        T evaluate(const std::map<std::string, std::unique_ptr<Node<T>>> &) const override {
            return value;
        }
};

template<typename T>
class CellNode : public Node<T> {
    std::string cellName;
    
    public:
    CellNode(const std::string &c) : cellName(c) {}
    T evaluate(const std::map<std::string, std::unique_ptr<Node<T>>> &cellExpressions) const override {
        auto it = cellExpressions.find(cellName);
        if (it == cellExpressions.end() || !it->second) {
            return T(); // Celda vacía
        }
        return it->second->evaluate(cellExpressions);
    }
};

template<typename T>
class OpNode : public Node<T> {
    std::unique_ptr<Node<T>> left;  // Operando izquierdo
    std::unique_ptr<Node<T>> right; // Operando derecho
    std::function<T(T, T)> opFunc;  // Función de la operación (e.g., +, -, *, /)

public:
    OpNode(std::unique_ptr<Node<T>> l, std::unique_ptr<Node<T>> r, std::function<T(T, T)> f)
    : left(std::move(l)), right(std::move(r)), opFunc(f) {}

    T evaluate(const std::map<std::string, std::unique_ptr<Node<T>>> &cellExpressions) const override {
        T lv = left->evaluate(cellExpressions);
        T rv = right->evaluate(cellExpressions);
        return opFunc(lv, rv);
    }
};

#endif