set terminal pngcairo enhanced font "Arial,10" size 800,600
set output 'plot.png'

# Titre et étiquettes des axes
set title "Évolution de la température - Méthode de Jacobi vs Solution exacte"
set xlabel "Position x"
set ylabel "Température u(x)"

# Grille
set grid

# Tracer les courbes
plot "../build/initial_condition.dat" using 1:2 with lines title "Initial Condition" lt rgb "cyan", \
     "../build/jacobi_solution.dat" using 1:2 with lines title "Computed Jacobi Solution" lt rgb "magenta", \
     "../build/exact_solution.dat" using 1:2 with lines title "Exact Solution" lt rgb "green"

