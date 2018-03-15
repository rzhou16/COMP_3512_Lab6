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
	static constexpr int FITNESS_SCALER = 10000.0; // Scales the fitness to move the decimal place to a reasonable spot
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
			cities_to_visit.push_back(City((char)(i + ASCII_OFFSET), rand() % (MAP_BOUNDARY + 1), rand() % (MAP_BOUNDARY + 1)));
		}

		for (int i = 0; i < POPULATION_SIZE; i++) {
			population.push_back(Tour(0, cities_to_visit));
		}
	}

	int determine_fitnessc(std::vector<Tour>& population, int poplulation_size) const {
		int index_of_shortest_tour = 0;
		double shortest_tour_in_population = (double)RAND_MAX; // Begin by assuming distance is enormous
		double candidate_distance = 0.0;
		for (int i = 0; i < poplulation_size; i++) {
			candidate_distance = population[i].get_tour_distance();
			population[i].set_fitness(FITNESS_SCALER / candidate_distance);
			if (candidate_distance <= shortest_tour_in_population) {
				index_of_shortest_tour = i;
				shortest_tour_in_population = candidate_distance;
			}
		}
		return index_of_shortest_tour;
	}
};