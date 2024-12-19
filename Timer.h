#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>
#include <string>

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop_time;

public:
    void start();  // Méthode pour démarrer le chronomètre
    void stop();   // Méthode pour arrêter le chronomètre
    void print(const std::string& label = "Timer") const;  // Afficher le temps écoulé
    double elapsed_ms() const;  // Retourne le temps écoulé en millisecondes
};

#endif // TIMER_H
