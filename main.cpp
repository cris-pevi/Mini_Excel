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
    std::cout << "El valor de la celda A1 (referenciado por CellNode): " << cellReferenciaA1.evaluate(cellExpressions) << std::endl;

    CellNode<double> cellReferenciaB1("B1");
    std::cout << "El valor de la celda B1 (referenciado por CellNode): " << cellReferenciaB1.evaluate(cellExpressions) << std::endl;

    // Evaluar una celda no definida "C1"
    CellNode<double> cellReferenciaC1("C1");
    std::cout << "El valor de la celda C1 (no definida): " << cellReferenciaC1.evaluate(cellExpressions) << std::endl;

    // Modificar el valor de una celda y volver a evaluar
    cellExpressions["A1"] = std::make_unique<NumberNode<double>>(15.0); // Cambiamos A1 a 15.0
    std::cout << "Nuevo valor de A1 (después de modificar): " << cellReferenciaA1.evaluate(cellExpressions) << std::endl;

    return 0;
}