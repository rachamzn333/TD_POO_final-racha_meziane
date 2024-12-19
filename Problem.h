#ifndef PROBLEM_H
#define PROBLEM_H

#include "Equation.h"
#include "IMesh.h"
#include "Variable.h"  // Assurez-vous que la classe Variable est incluse
#include <iostream>

class Problem {
public:
    Problem(IMesh* mesh, int max_iterations, double epsilon);  // Ajout de epsilon
    ~Problem();

    void solve();
    void solve_parallel();  // Déclaration de la méthode parallèle


private:
    IMesh* mesh;
    int max_iterations;
    double epsilon;  // Stocke epsilon pour la convergence
    Equation equation;

 bool has_converged(const Variable& u_k, const Variable& u_kp1);

};

#endif // PROBLEM_H


