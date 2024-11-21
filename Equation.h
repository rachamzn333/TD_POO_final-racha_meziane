/*#ifndef EQUATION_H
#define EQUATION_H

#include "IMesh.h"
#include <iostream>

class Equation {
public:
    Equation() = default;
    void compute(IMesh* mesh);  // Déclaration de la méthode compute
};

#endif // EQUATION_H
*/
#ifndef EQUATION_H
#define EQUATION_H

#include "IMesh.h"
#include "Variable.h"  // Assurez-vous d'inclure la classe Variable
#include <iostream>

class Equation {
public:
    Equation() = default;

   void compute(const Variable& u_k, Variable& u_kp1, IMesh* mesh);


    // Méthode pour initialiser les conditions initiales
    void compute_initial_condition(Variable& variable, IMesh* mesh, double T1, double T2);

    // Méthode pour imposer les conditions aux limites
    void compute_boundary_conditions(Variable& variable, double T1, double T2);
};

#endif // EQUATION_H

