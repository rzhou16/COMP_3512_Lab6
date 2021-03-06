#include "GeneticAlgorithm.hpp"

/* default ctor. calls run() to perform algorithm. */
GeneticAlgorithm::GeneticAlgorithm() {
	run();
}

/* populates population */
void GeneticAlgorithm::init() {
	std::vector<City> cities_to_visit( CITIES_IN_TOUR );
	srand((unsigned int) time(NULL));

	for (int i = 0; i < CITIES_IN_TOUR; i++) {
		cities_to_visit[i] = City((char)(i + ASCII_OFFSET), rand() % (MAP_BOUNDARY + 1), rand() % (MAP_BOUNDARY + 1));
	}
	
	for (int i = 0; i < POPULATION_SIZE; i++) {
		population[i] = Tour(0, cities_to_visit);
	}
}


/*
* Calculates the fitness of each tour in the specifed population
* and stores it in its class.  Also determines which tour has
* the best fitness.
* PARAM:  population a vector of class tour
* PARAM:  population_size of the vector
* PRE:    population_size is the length of population
* POST:   the class tour elements in the population vector have
*         been updated with their correct fitness ratings
* RETURN: the index of the 'fittest' tour in the population vector
*/
int GeneticAlgorithm::determine_fitness(std::vector<Tour>& population, int poplulation_size) const {
	int index_of_shortest_tour = 0;
	double shortest_tour_in_population = (double)RAND_MAX; // Begin by assuming distance is enormous
	double candidate_distance = 0.0;
	for (int i = 0; i < poplulation_size; i++) {
		candidate_distance = population[i].get_tour_distance(); // get total distance of the tour
		population[i].set_fitness(FITNESS_SCALER / candidate_distance); // sets fitness score based on the distance returned
		if (candidate_distance <= shortest_tour_in_population) {
			index_of_shortest_tour = i;
			shortest_tour_in_population = candidate_distance;
		}
	}
	return index_of_shortest_tour;
}

/*
* Selects NUMBER_OF_PARENTS parent tours.  Each parent
* is fittest of a subset of size PARENT_POOL_SIZE of the
* population, randomly selected,.
* PARAM:  pointer to a population of class tour
* PRE:    PARENT_POOL_SIZE > POPULATION_SIZE
* POST:   NULL
* RETURN: pointer to a class tour which points to
*/

/*
* Selects NUMBER_OF_PARENTS parent tours.  Each parent
* is fittest of a subset of size PARENT_POOL_SIZE of the
* population, randomly selected,.
* PARAM:  pointer to a population of class tour
* PRE:    PARENT_POOL_SIZE > POPULATION_SIZE
* POST:   NULL
* RETURN: pointer to a class tour which points to
*/
std::vector<Tour> GeneticAlgorithm::select_parents(std::vector<Tour>& population)
{
	int parent_index = 0;

	std::vector<Tour> parents(NUMBER_OF_PARENTS);
	std::vector<Tour> parent_pool(PARENT_POOL_SIZE);

	/* Chooses the best parents from a randomly selected parent pool */
	for (int i = 0; i < NUMBER_OF_PARENTS; ++i) {
		for (int j = 0; j < PARENT_POOL_SIZE; ++j) {
			int k = rand() % POPULATION_SIZE;
			parent_pool[j] = population[k];
		}
		parent_index = determine_fitness(parent_pool, PARENT_POOL_SIZE);
		parents[i] = parent_pool[parent_index];
	}
	return parents;
}

/*
* Mixes the contents of the NUMBER_OF_PARENTS tours pointed to by
* the parents pointer, and returns a pointer to the mixture.
*
* How are we mixing them?  Not very well, yet.  This method has
* been hard-coded for 2 parents.  Can you see how we can extend the
* code to incorporate cities from > 2 parents?  Do we need any
* preconditions (i.e. NUMBER_OF_PARENTS < POPULATION )?
*
* We select a random index and use the cities from one parent
* to populate the mixed tour up to and including that index, and then
* the cities from the second parent to top up the tour, making sure we
* don't add cities that are already in the mixed tour.
*
* Can you think of ways to improve the way we cross the 'parents'?
*
* PARAM:  parents, a pointer to a class tour
* PRE:    parents is a valid pointer to NUMBER_OF_PARENTS class tours
* RETURN: a pointer to a class tour combination of the parents
*/
Tour GeneticAlgorithm::crossover(std::vector<Tour>& parents)
{
	Tour child;

	/* Here's how we use rand again.  We invoke the rand() function, and since
	we want the result to be between 0 and (CITIES_IN_TOUR - 1), we use the
	modulus operator */
	int boundary_index = rand() % CITIES_IN_TOUR;

	/* Sets the index of the mixed result to 0.0 */
	child.set_fitness(0);

	/* Copies the first 'boundary_index' cities in order from parent 1 to the mixed
	result */
	for (int i = 0; i < boundary_index; i++) {
		child.get_permutation()[i] = parents[0].get_permutation()[i];
	}

	/* Fills the rest of the cells with cities from parent 2 */
	while (boundary_index < CITIES_IN_TOUR) {
		for (int i = 0; i < CITIES_IN_TOUR; ++i) {
			/* If the mixed tour doesn't already contain the city at that index in parent two... */
			if (!child.contains_city(boundary_index, parents[1].get_permutation()[i])) {

				/* ...then we add it from the second parent to the child... */
				child.get_permutation()[boundary_index] = parents[1].get_permutation()[i];
				/* And increment the boundary_index */
				boundary_index++;
			}
		}
	}

	return child;
}

/*
* Mutates the tour at the specified index of tours.
*
* Calculates a random mutation value for each city in the
* specified tour.  If this value < MUTATION_RATE, then the
* city is swapped with a randomly chosen city from the
* same vector (tour).
*
* There could be better ways to mutate a tour of cities.
* Can you think of any?
*
* PARAM:  permutation, a vector of class tour
* PARAM:  int index
* PRE:    index is a valid index for permutation
* POST:   some of population's tours may have been mutated.
* RETURN: VOID
*/
void GeneticAlgorithm::mutate(std::vector<Tour>& population)
{
	int k = 0;
	double mutates = 0.0;
	for (int i = 0 + NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
		for (int j = 0; j < CITIES_IN_TOUR; ++j) {
			mutates = (double)rand() / (double)RAND_MAX;
			if (mutates <= MUTATION_RATE) {
				k = rand() % CITIES_IN_TOUR;
				
				population[i].swap_cities(j, k);
			}
		}
	}
}


void GeneticAlgorithm::run() {
	std::vector<Tour> crosses{ POPULATION_SIZE - NUMBER_OF_ELITES };
	std::vector<Tour> parents;
	double best_distance = 0;
	double best_iteration_distance = 0;

	/* populate cities_to_visit and population*/
	init();

	/* Determines the fitness of each tour, and notes which tour is the fittest.  The
	determine_fitness function returns the index of the fittest individual. */
	int index_of_shortest_tour = determine_fitness(population, POPULATION_SIZE);
	printf("Index of shortest tour: %d\n", index_of_shortest_tour);

	/* Sets the base distance.  This is our starting point. We'll use the best
	distance from our initial random population of size POPULATION_SIZE */
	best_distance = FITNESS_SCALER / population[index_of_shortest_tour].get_fitness();
	printf("Shortest distance in initial population: %8.3f\n", best_distance);

	/* And now we loop until we find what we want--the population "evolves"!
	We can loop a certain number of times like:
	for (iterations = 0; iterations < ITERATIONS; ++iterations) { ... }

	OR
	
	We can loop until we observe a predetermined improvement:
	while ( best_distance / base_distance > improvement_factor) { ... } */
	for (int iterations = 0; iterations < ITERATIONS; iterations++) {

		/* 1. Selection: keep the best route by moving the fittest to the front of
		the population.  We won't  change it in this iteration, and we will
		call it an 'elite' individual) */
		if (index_of_shortest_tour != 0) {
			Tour temporary_tour = population[0];
			population[0] = population[index_of_shortest_tour];
			population[index_of_shortest_tour] = temporary_tour;
		}

		/* 2. Crossover (mix the rest of the routes and create new routes).  First
		we create a separate collection of POPULATION_SIZE - 1.  We store this
		in one of our utility buffers.  We choose parents by selecting the
		fittest tour from PARENT_POOL_SIZE randomly selected tours.  We do
		this NUMBER_OF_PARENTS times.  We cross the NUMBER_OF_PARENTS parents
		and store the result in our utility buffer
		*/
		for (int j = 0; j < (POPULATION_SIZE - NUMBER_OF_ELITES); ++j) {
			parents = select_parents(population);
			Tour child(crossover(parents));
			crosses[j] = child;
		}

		/* Then we copy the POPULATION_SIZE - NUMBER_OF_ELITES crosses from the utility buffer
		to our population vector, making sure not to overwrite the elite tour */
		for (int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i) {
			population[i] = crosses[i - NUMBER_OF_ELITES];
			population[i].set_fitness(0.0);
		}

		/* 3. Mutation (randomly mess a few up. excluding the elite tour[s]) */
		mutate(population);

		/* 4. Evaluation (assign each one a fitness aka FITNESS_SCALER * the inverse
		of the total distance traveled) */
		index_of_shortest_tour = determine_fitness(population, POPULATION_SIZE);

		/* At the end of this iteration, if we have made it further to our goal,
		we print some helpful information to standard output, and keep track */
		best_iteration_distance = population[index_of_shortest_tour].get_tour_distance();
		if (best_iteration_distance < best_distance) {
			best_distance = best_iteration_distance;
			printf("New distance: %8.3f\n", best_iteration_distance);
		}
	}

	/* Prints summary information */
	printf("Shortest distance %8.3f\n",
		(FITNESS_SCALER / population[index_of_shortest_tour].get_fitness()));

	/* And that's it! */
	system("pause");
}
