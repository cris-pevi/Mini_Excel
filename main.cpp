#include <iostream>
#include "Node.h"

int main() {
    // Nodo que contiene un número
    NumberNode<double> numNode(42.5);

    // Mapa vacío
    std::map<std::string, std::unique_ptr<Node<double>>> cellExpressions;

    // Evaluación del nodo
    std::cout << "El valor del nodo es: " << numNode.evaluate(cellExpressions) << std::endl;

    return 0;
}