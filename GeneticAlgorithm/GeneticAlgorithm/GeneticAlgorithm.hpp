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
	static constexpr double MUTATION_RATE = 0.15;    // Chance of being mutated
	static constexpr double FITNESS_SCALER = 10000.0; // Scales the fitness to move the decimal place to a reasonable spot
	static constexpr int MAP_BOUNDARY = 1000;   // Size of the map (X and Y)
	static constexpr int ITERATIONS = 1000;    // Number of loops for the algorithm
	static constexpr int NUMBER_OF_PARENTS = 2;     // Number of 'parents' for each cross
	static constexpr int PARENT_POOL_SIZE = 5;     // Number of members randomly selected from the population, from which the fittest is made a 'parent'

	std::vector<Tour> population{ POPULATION_SIZE };      // Holds our candidate population

public:
	GeneticAlgorithm();
	void init();
	int determine_fitness(std::vector<Tour>& population, int poplulation_size) const;
	std::vector<Tour>& select_parents(std::vector<Tour>& population);
	Tour& crossover(std::vector<Tour>& parents);
	void mutate(std::vector<Tour>& population);
	void run();
};