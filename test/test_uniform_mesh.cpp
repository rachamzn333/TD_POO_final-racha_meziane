#include <gtest/gtest.h>
#include "../UniformMesh.h"
#include "../IMesh.h"

// Test Unitaire pour la classe UniformMesh
TEST(UnitaryTest, MeshTest) {
    // Crée une instance de UniformMesh
    IMesh* mesh = new UniformMesh(0.0, 1.0, 0.2); 

    // Vérifie le nombre de points dans le maillage
    EXPECT_EQ(mesh->getNumPoints(), 6);

    // Vérifie les positions de quelques points du maillage
    EXPECT_DOUBLE_EQ(mesh->getPosition(0), 0.0);
    EXPECT_DOUBLE_EQ(mesh->getPosition(1), 0.2);
    EXPECT_DOUBLE_EQ(mesh->getPosition(2), 0.4);
    EXPECT_DOUBLE_EQ(mesh->getPosition(5), 1.0);

    // Vérifie les valeurs des bornes
    EXPECT_DOUBLE_EQ(mesh->getXMin(), 0.0);
    EXPECT_DOUBLE_EQ(mesh->getXMax(), 1.0);
    EXPECT_DOUBLE_EQ(mesh->getDeltaX(), 0.2);
}
