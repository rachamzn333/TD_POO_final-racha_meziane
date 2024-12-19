#include "Problem.h"
#include "UniformMesh.h"

int main() {
    // Crée un maillage uniforme pour l'intervalle [0, 1] avec dx = 0.01
    IMesh* mesh = new UniformMesh(0.0, 1.0, 0.01);

    // Initialise le problème avec un nombre d'itérations maximal de 100 et un seuil de convergence
    int max_iterations = 100;
    double epsilon = 1e-5;
    Problem problem(mesh, max_iterations, epsilon);

    // Résolution séquentielle
    std::cout << "--- Résolution séquentielle ---" << std::endl;
    problem.solve();

    // Résolution parallèle
    std::cout << "\n--- Résolution parallèle ---" << std::endl;
    problem.solve_parallel();


    return 0;
}
