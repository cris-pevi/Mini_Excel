#include <iostream>
#include "Node.h"

int main() {
    // Mapa vacío
    std::map<std::string, std::unique_ptr<Node<double>>> cellExpressions;

    // Agregar celdas al mapa con NumberNode
    cellExpressions["A1"] = std::make_unique<NumberNode<double>>(10.5); // A1 = 10.5
    cellExpressions["B1"] = std::make_unique<NumberNode<double>>(20.0); // B1 = 20.0

    // Crear un CellNode que referencia a "A1", "B1"
    CellNode<double> cellReferenciaA1("A1");
    CellNode<double> cellReferenciaB1("B1");
    
    std::cout << "El valor de la celda A1 (referenciado por CellNode): " << cellReferenciaA1.evaluate(cellExpressions) << std::endl;
    std::cout << "El valor de la celda B1 (referenciado por CellNode): " << cellReferenciaB1.evaluate(cellExpressions) << std::endl;

    // Crear un OpNode que suma A1 y B1
    auto sumNode = std::make_unique<OpNode<double>>(
        std::make_unique<CellNode<double>>("A1"), // Variable izquierda (A1)
        std::make_unique<CellNode<double>>("B1"), // Variable derecha (B1)
        [](double a, double b) { return a + b; }  // Operación: suma
    );

    // Evaluar la operación --> A1 + B1
    std::cout << "Resultado de A1 + B1: " << sumNode->evaluate(cellExpressions) << std::endl;

    // Guardar el resultado en la celda "C1"
    cellExpressions["C1"] = std::move(sumNode);
    std::cout << "El valor de la celda C1: " << cellExpressions["C1"]->evaluate(cellExpressions) << std::endl;

    // Evaluar una celda no definida (C2)
    CellNode<double> cellReferenciaC2("C2");
    std::cout << "El valor de la celda C2 (no definida): " << cellReferenciaC2.evaluate(cellExpressions) << std::endl;

    // Modificar el valor de una celda y volver a evaluar
    cellExpressions["A1"] = std::make_unique<NumberNode<double>>(15.0); // Cambiamos A1 a 15.0
    std::cout << "Nuevo valor de A1: " << cellReferenciaA1.evaluate(cellExpressions) << std::endl;
    std::cout << "Nuevo resultado de C1 (re-evaluado como A1 + B1): " << cellExpressions["C1"]->evaluate(cellExpressions) << std::endl;

    return 0;
}