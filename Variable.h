#ifndef VARIABLE_H
#define VARIABLE_H

#include "IMesh.h"
#include <vector>

class Variable {
public:
    // Constructeur qui initialise le vecteur en fonction de la taille du maillage
    Variable(IMesh* mesh) : mesh(mesh), values(mesh->x_size(), 0.0) {}

    // Surcharge de l'opérateur [] pour accéder aux éléments du vecteur
    double& operator[](int i) {
        return values[i];
    }

    // Surcharge de l'opérateur [] pour un accès en lecture
    const double& operator[](int i) const {
        return values[i];
    }

    // Méthode pour obtenir la taille du vecteur
    int size() const {
        return values.size();
    }

private:
    IMesh* mesh;                 // Pointeur vers le maillage
    std::vector<double> values;  // Vecteur pour stocker les valeurs de u_i
};

#endif // VARIABLE_H
