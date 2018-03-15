#pragma once
#include "Tour.hpp"
#include <cstdlib>
#include <ctime>

class GeneticAlgorithm {
private:
	static constexpr int CITIES_IN_TOUR = 20;
	static constexpr int ASCII_OFFSET = 65;
	static constexpr int NUMBER_OF_ELITES = 1;
	static constexpr int POPULATION_SIZE = 30;
	static constexpr int MAP_BOUNDARY = 1000;   // Size of the map (X and Y)
	std::vector<Tour> population;      // Holds our candidate population
	std::vector<Tour> parents;         // Used during crossover
	std::vector<Tour> crosses;         // Used during calculations
	Tour temporary_tour;  // Used during calculations
	std::vector<City> cities_to_visit; // Stores master list of cities
	Tour child;
public:
	GeneticAlgorithm() { init(); }

	void init() {
		srand(time(NULL));
		for (int i = 0; i < CITIES_IN_TOUR; i++) {
			
		}
	}
};