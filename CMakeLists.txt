cmake_minimum_required(VERSION 3.10)
project(SimulateurDiffusion)

# Utilisation de C++11
set(CMAKE_CXX_STANDARD 11)

# Activation des tests
enable_testing()

# Ajout de l'exécutable principal
add_executable(SimulateurDiffusion main.cpp Problem.cpp Equation.cpp UniformMesh.cpp)

# Ajout du test d'intégration
add_test(NAME structure_test COMMAND SimulateurDiffusion)

# Téléchargement et ajout de GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Création de l'exécutable pour les tests unitaires avec tous les fichiers nécessaires
add_executable(UnitTests 
    test/test_uniform_mesh.cpp 
    test/test_problem.cpp 
    test/test_equation.cpp
    Problem.cpp            # Ajout de Problem.cpp
    Equation.cpp           # Ajout de Equation.cpp
    UniformMesh.cpp        # Ajout de UniformMesh.cpp
)

# Lier GTest et les bibliothèques nécessaires à UnitTests
target_link_libraries(UnitTests gtest gtest_main pthread)

# Ajout de gtest_discover_tests pour détecter les tests avec ctest
include(GoogleTest)
gtest_discover_tests(UnitTests)

