#include "Problem.h"
#include "UniformMesh.h"

int main() {
    // Crée un maillage uniforme pour l'intervalle [0, 1] avec dx = 0.2
    IMesh* mesh = new UniformMesh(0.0, 1.0, 0.2);
    
    // Initialise le problème avec un nombre d'itérations maximal de 100 et un seuil de convergence
    int max_iterations = 100;
    double epsilon = 1e-5;  // Seuil de convergence
    Problem problem(mesh, max_iterations, epsilon);  // Transmet epsilon au constructeur de Problem

    // Appelle la méthode solve pour résoudre le problème
    problem.solve();

    return 0;
}
