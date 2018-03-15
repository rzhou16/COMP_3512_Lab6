#pragma once
#include "Tour.hpp"

class GeneticAlgorithm {
private:
	static constexpr int NUMBER_OF_ELITES = 1;
	static constexpr int POPULATION_SIZE = 30;
	Tour * population;      // Holds our candidate population
	Tour * parents;         // Used during crossover
	Tour * crosses;         // Used during calculations
	Tour temporary_tour;  // Used during calculations
	City * cities_to_visit; // Stores master list of cities
	Tour * child;
public:
	GeneticAlgorithm() {
		population = new Tour[POPULATION_SIZE];
		crosses = new Tour[POPULATION_SIZE - NUMBER_OF_ELITES];
		temporary_tour = Tour();
		cities_to_visit = new City[Tour::get_tour_size()];
		parents = NULL;
		child = NULL;
	}

	void init() {
		for (int i = 0; i < Tour::get_tour_size(); i++) {
			cities_to_visit[i].
		}
	}
};