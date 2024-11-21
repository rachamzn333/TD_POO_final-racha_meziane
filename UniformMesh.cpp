#include "UniformMesh.h"

UniformMesh::UniformMesh(double x_min, double x_max, double dx)
    : x_min(x_min), x_max(x_max), dx(dx) {
    int num_points = static_cast<int>((x_max - x_min) / dx) + 1;
    for (int i = 0; i < num_points; ++i) {
        points.push_back(x_min + i * dx);
    }
}

double UniformMesh::getXMin() const { return x_min; }

double UniformMesh::getXMax() const { return x_max; }

int UniformMesh::getNumPoints() const { return points.size(); }

double UniformMesh::getDeltaX() const { return dx; }

double UniformMesh::getPosition(int index) const { return points[index]; }

// Implémentation de la méthode x_size() pour retourner le nombre de points dans le maillage
int UniformMesh::x_size() const { 
    return points.size(); 
}
double UniformMesh::x_i(int i) const {
    return points[i];
}


