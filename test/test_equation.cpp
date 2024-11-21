/*#include <gtest/gtest.h>
#include "/home/racha/TD2_POO/Equation.h"
#include "/home/racha/TD2_POO/UniformMesh.h"

// Test Unitaire pour la classe Equation
TEST(MainFunctionTest, EquationTest) {
    // Crée une instance de Equation avec le constructeur par défaut
    Equation equation;

    // Crée un maillage pour le test
    UniformMesh mesh(0.0, 1.0, 0.2);

    // Exécute le calcul sur une itération et vérifie qu'il se passe sans erreur
    EXPECT_NO_THROW(equation.compute(&mesh));

    // Ajoutez d'autres vérifications ici si nécessaire, par exemple vérifier si les valeurs de l'équation
    // sont correctement modifiées dans une prochaine itération ou observer les sorties via des affichages.
}
*/
#include <gtest/gtest.h>
#include "/home/racha/TD2_POO/Equation.h"
#include "/home/racha/TD2_POO/UniformMesh.h"
#include "/home/racha/TD2_POO/Variable.h"  // Assurez-vous que la classe Variable est incluse

// Test Unitaire pour la classe Equation
TEST(MainFunctionTest, EquationTest) {
    // Crée une instance de Equation
    Equation equation;

    // Crée un maillage pour le test
    UniformMesh mesh(0.0, 1.0, 0.2);

    // Crée deux instances de Variable pour les itérations u_k et u_kp1
    Variable u_k(&mesh);
    Variable u_kp1(&mesh);

    // Exécute le calcul et vérifie qu'il se passe sans exception
    EXPECT_NO_THROW(equation.compute(u_k, u_kp1, &mesh));

    // Optionnel : ajoutez des assertions pour vérifier les valeurs si nécessaire
}
