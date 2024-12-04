#include "Problem.h"
#include "Variable.h"
#include <iostream>
#include <iomanip>  // Pour le formatage des affichages
#include <fstream>  // Pour écrire dans un fichier

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

/*void Problem::solve() {
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
} */
void Problem::solve() {
    std::cout << "--- Solve problem ---" << std::endl;

    Variable u_k(mesh);
    Variable u_kp1(mesh);
    Variable u_ref(mesh);

    Equation equation;
    double T1 = 30.0;  // Température au bord gauche
    double T2 = 15.0;  // Température au bord droit

    // Calcul de la solution exacte
    equation.compute_exact_solution(u_ref, mesh, T1, T2);

 std::ofstream file_initial("./initial_condition.dat");
std::ofstream file_exact("./exact_solution.dat");
std::ofstream file_jacobi("./jacobi_solution.dat");

if (!file_initial.is_open() || !file_exact.is_open() || !file_jacobi.is_open()) {
    std::cerr << "Erreur : impossible de créer ou d'ouvrir les fichiers de résultats !" << std::endl;
    return;
}


    // En-têtes des fichiers
    file_initial << "# x u_initial\n";
    file_exact << "# x u_exact\n";
    file_jacobi << "# x u_jacobi\n";

    // Initialisation des conditions initiales
    equation.compute_initial_condition(u_k, mesh, T1, T2);

    // Sauvegarder la condition initiale
    for (int i = 0; i < mesh->x_size(); ++i) {
        file_initial << mesh->x_i(i) << " " << u_k[i] << "\n";
    }

    int iteration = 0;

    // Méthode de Jacobi
    while (iteration < max_iterations) {
        ++iteration;

        equation.compute_boundary_conditions(u_kp1, T1, T2);
        equation.compute(u_k, u_kp1, mesh);

        if (has_converged(u_k, u_kp1)) {
            std::cout << "Convergence atteinte après " << iteration << " itérations." << std::endl;
            break;
        }

        for (int i = 0; i < mesh->x_size(); ++i) {
            u_k[i] = u_kp1[i];
        }
    }

    // Sauvegarder la solution Jacobi finale
    for (int i = 0; i < mesh->x_size(); ++i) {
        file_jacobi << mesh->x_i(i) << " " << u_kp1[i] << "\n";
    }

    // Sauvegarder la solution exacte
    for (int i = 0; i < mesh->x_size(); ++i) {
        file_exact << mesh->x_i(i) << " " << u_ref[i] << "\n";
    }

    // Fermer les fichiers
    file_initial.close();
    file_exact.close();
    file_jacobi.close();

    if (iteration == max_iterations) {
        std::cout << "Nombre maximum d'itérations atteint sans convergence." << std::endl;
    }
}
