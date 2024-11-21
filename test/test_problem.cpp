#include <gtest/gtest.h>
#include "../Problem.h"
#include "../UniformMesh.h"

// Test Unitaire pour la classe Problem
TEST(UnitaryTest, ProblemTest) {
    // Crée un maillage
    UniformMesh* mesh = new UniformMesh(0.0, 1.0, 0.2);

    // Crée une instance de Problem avec le maillage, le nombre d'itérations et epsilon
    double epsilon = 1e-5;
    Problem problem(mesh, 100, epsilon);  // Ajout de epsilon

    // Vérifie que l'objet Problem est bien initialisé et que la méthode solve s'exécute sans exception
    EXPECT_NO_THROW(problem.solve());

    // Supprimez `delete mesh;` car Problem prend en charge la libération de `mesh`
}
