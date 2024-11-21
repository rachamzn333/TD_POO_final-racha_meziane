# CMake generated Testfile for 
# Source directory: /home/racha/TD2_POO
# Build directory: /home/racha/TD2_POO/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/racha/TD2_POO/build/UnitTests[1]_include.cmake")
add_test(structure_test "/home/racha/TD2_POO/build/SimulateurDiffusion")
set_tests_properties(structure_test PROPERTIES  _BACKTRACE_TRIPLES "/home/racha/TD2_POO/CMakeLists.txt;14;add_test;/home/racha/TD2_POO/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
