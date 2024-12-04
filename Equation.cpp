/*#include "Equation.h"

void Equation::compute(IMesh* mesh) {
    for (int i = 0; i < mesh->getNumPoints(); ++i) {
        double x_i = mesh->getPosition(i);
        std::cout << "-- at x_i = " << x_i << std::endl;
    }
}
*/
#include "Equation.h"

// Calcule les conditions initiales dans le domaine
void Equation::compute_initial_condition(Variable& variable, IMesh* mesh, double T1, double T2) {
    int midpoint = mesh->x_size() / 2;
    for (int i = 0; i < mesh->x_size(); ++i) {
        if (i < midpoint) {
            variable[i] = T1;  // Première moitié à T1
        } else {
            variable[i] = T2;  // Seconde moitié à T2
        }
    }
}

// Imposer les conditions aux limites de Dirichlet sur les bords
void Equation::compute_boundary_conditions(Variable& variable, double T1, double T2) {
    variable[0] = T1;                 // Bord gauche à T1
    variable[variable.size() - 1] = T2;  // Bord droit à T2
}

void Equation::compute(const Variable& u_k, Variable& u_kp1, IMesh* mesh) {
    // Itération pour tous les points internes, en excluant les bords
    for (int i = 1; i < mesh->x_size() - 1; ++i) {
        u_kp1[i] = 0.5 * (u_k[i - 1] + u_k[i + 1]);
    }
}
void Equation::compute_exact_solution(Variable& u_ref, IMesh* mesh, double T1, double T2) {
    for (int i = 0; i < mesh->x_size(); ++i) {
        double x = mesh->x_i(i);  // Position x_i dans le maillage
        u_ref[i] = (T2 - T1) * x + T1;  // Calcul de la solution exacte
    }
}



// Autres méthodes comme compute_initial_condition et compute_boundary_conditions...
