#include "Problem.h"
#include "Variable.h"
#include <iostream>
#include <iomanip>  // Pour le formatage des affichages
#include <fstream>  // Pour écrire dans un fichier
#include "Timer.h"
#include <thread>
#include <mutex>


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

    // Chronomètres
    Timer total_timer;
    Timer iteration_timer;

    // Démarrage du chronomètre global
    total_timer.start();

    int iteration = 0;

    while (iteration < max_iterations) {
        // Démarrer le chronomètre pour l'itération
        iteration_timer.start();

        ++iteration;

        equation.compute_boundary_conditions(u_kp1, T1, T2);
        equation.compute(u_k, u_kp1, mesh);

        // Arrêter le chronomètre pour l'itération
        iteration_timer.stop();

        // Afficher le temps pour l'itération
        iteration_timer.print("Temps pour l'itération " + std::to_string(iteration));

        if (has_converged(u_k, u_kp1)) {
            std::cout << "Convergence atteinte après " << iteration << " itérations." << std::endl;
            break;
        }

        // Copier u_kp1 dans u_k
        for (int i = 0; i < mesh->x_size(); ++i) {
            u_k[i] = u_kp1[i];
        }
    }

    // Arrêter le chronomètre global
    total_timer.stop();

    // Afficher le temps total
    total_timer.print("Temps total du calcul");

    if (iteration == max_iterations) {
        std::cout << "Nombre maximum d'itérations atteint sans convergence." << std::endl;
    }}
 


void Problem::solve_parallel() {
    std::cout << "--- Solve problem in parallel ---" << std::endl;

    // Variables pour Jacobi et Gauss-Seidel
    Variable u_k_jacobi(mesh);
    Variable u_kp1_jacobi(mesh);
    Variable u_k_gs(mesh);
    Variable u_kp1_gs(mesh);

    Equation equation;

    double T1 = 30.0;  // Température au bord gauche
    double T2 = 15.0;  // Température au bord droit

    Timer total_timer;
    total_timer.start();

    int max_iterations = 100;

    // Mutex pour protéger les accès concurrents (si nécessaire)
    std::mutex mtx;

    // Thread pour Jacobi
    std::thread jacobi_thread([&]() {
        for (int iteration = 0; iteration < max_iterations; ++iteration) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                equation.compute_boundary_conditions(u_kp1_jacobi, T1, T2);
            }
            equation.compute(u_k_jacobi, u_kp1_jacobi, mesh);
            for (int i = 0; i < mesh->x_size(); ++i) {
                u_k_jacobi[i] = u_kp1_jacobi[i];
            }
        }
        std::cout << "Jacobi terminé après " << max_iterations << " itérations." << std::endl;
    });

    // Thread pour Gauss-Seidel
    std::thread gs_thread([&]() {
        for (int iteration = 0; iteration < max_iterations; ++iteration) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                equation.compute_boundary_conditions(u_kp1_gs, T1, T2);
            }
            equation.compute(u_k_gs, u_kp1_gs, mesh);
            for (int i = 0; i < mesh->x_size(); ++i) {
                u_k_gs[i] = u_kp1_gs[i];
            }
        }
        std::cout << "Gauss-Seidel terminé après " << max_iterations << " itérations." << std::endl;
    });

    // Attendre la fin des threads
    jacobi_thread.join();
    gs_thread.join();

    total_timer.stop();
    total_timer.print("Temps total en parallèle");
}
