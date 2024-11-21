/*#include "Problem.h"

Problem::Problem(IMesh* mesh, int max_iterations)
    : mesh(mesh), max_iterations(max_iterations) {}  // Définition du constructeur

Problem::~Problem() {
    delete mesh;  // Définition du destructeur
}

void Problem::solve() {  // Définition de la méthode solve
    std::cout << "--- Solve problem ---" << std::endl;
    for (int iteration = 1; iteration <= max_iterations; ++iteration) {
        std::cout << "--- Iterative method iteration : " << iteration << " ---" << std::endl;
        equation.compute(mesh);
        if (hasConverged()) {
            break;
        }
    }
}

bool Problem::hasConverged() {
    return true;  // Simule la convergence pour l'instant
}
*/
#include "Problem.h"
#include "Variable.h"
#include <iostream>
#include <iomanip>  // Pour le formatage des affichages

Problem::Problem(IMesh* mesh, int max_iterations, double epsilon)
    : mesh(mesh), max_iterations(max_iterations), epsilon(epsilon) {}

Problem::~Problem() {
    delete mesh;
}

bool Problem::has_converged(const Variable& u_k, const Variable& u_kp1) {
    double max_diff = 0.0;

    for (int i = 0; i < u_k.size(); ++i) {
        double diff = std::abs(u_kp1[i] - u_k[i]);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }

    return max_diff < epsilon;
}

void Problem::solve() {
    std::cout << "--- Solve problem ---" << std::endl;

    Variable u_k(mesh);
    Variable u_kp1(mesh);

    Equation equation;
    double T1 = 30.0;
    double T2 = 15.0;

    equation.compute_initial_condition(u_k, mesh, T1, T2);
    int iteration = 0;

    while (iteration < max_iterations) {
        ++iteration;
        
        equation.compute_boundary_conditions(u_kp1, T1, T2);
        equation.compute(u_k, u_kp1, mesh);

        // Affichage des valeurs de u_kp1 pour chaque point
        std::cout << "Itération " << iteration << ":" << std::endl;
        for (int i = 0; i < mesh->x_size(); ++i) {
            std::cout << "u(" << mesh->x_i(i) << ") = " << std::fixed << std::setprecision(5) << u_kp1[i] << std::endl;
        }

        if (has_converged(u_k, u_kp1)) {
            std::cout << "Convergence atteinte après " << iteration << " itérations." << std::endl;
            break;
        }

        // Copier u_kp1 dans u_k pour la prochaine itération
        for (int i = 0; i < mesh->x_size(); ++i) {
            u_k[i] = u_kp1[i];
        }
    }

    if (iteration == max_iterations) {
        std::cout << "Nombre maximum d'itérations atteint sans convergence." << std::endl;
    }
}
