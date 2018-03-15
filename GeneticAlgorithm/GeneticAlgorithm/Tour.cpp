#include "Tour.hpp"

Tour::Tour() {}

Tour::~Tour() {}

Tour::Tour(double _fitness, std::vector<City>& _permutation) {
	fitness = _fitness;
	for (int i = 0; i < permutation.size(); i++) {
		permutation[i] = _permutation[i];
	}
	std::random_shuffle(permutation.begin(), permutation.end());
}

Tour::Tour(const Tour& _tour) {
	fitness = _tour.fitness;
	for (int i = 0; i < permutation.size(); i++) {
		permutation[i] = _tour.permutation[i];
	}
}

std::vector<City>& Tour::get_permutation() {
	return permutation;
}

/*
* Returns 1 if the specified tour contains the specified city, else 0.
* PARAM:  pointer to a candidate_tour
* PARAM:  length of the candidate tour
* PARAM:  struct city, the city being sought
* PRE:    NULL
* POST:   NULL
* RETURN: IF candidate_tour CONTAINS city_name
*         THEN 1
*         ELSE 0
*/
int Tour::contains_city(int length, City& candidate_city)
{
	int i = 0;
	for (i = 0; i < length; ++i) {
		if (permutation[i].get_name() == (char)candidate_city.get_name() &&
			permutation[i].get_x() == (int)candidate_city.get_x() &&
			permutation[i].get_y() == (int)candidate_city.get_y()) {
			return 1;
		}
	}
	return 0;
}

/*
* Swaps the cities at the specified indices in the
* specified array (tour) of cities.
* PARAM:  int index
* PARAM:  int index
* PARAM:  pointer to an array of struct city
* PRE:    both indices >= 0
* PRE :   both indices < CITIES_IN_TOUR
* POST:   the cities at the specified indices in the
*         specified tour have been swapped.
*/
void Tour::swap_cities(int index_one, int index_two)
{
	City temp = permutation[index_one];
	permutation[index_one] = permutation[index_two];
	permutation[index_two] = temp;
	return;
}

/*
* Returns the total distance traveled on the
* specified array (tour) of cities.
* PARAM:  tour contains a set of CITIES_IN_TOUR cities
* PRE:    NULL
* POST:   NULL
* RETURN: the total distance, a double
*/
double Tour::get_tour_distance() {
	double distance = 0;
	for (int i = 0; i < permutation.size(); i++) {
		distance += get_distance_between_cities(permutation[i], permutation[(i + 1) % CITIES_IN_TOUR]);
	}
	return distance;
}

/*
* Returns the distance between the two specified cities.
* PARAM:  a struct city
* PARAM:  a struct city
* PRE:    NULL
* POST:   NULL
* RETURN: the total distance, a double
*/
double Tour::get_distance_between_cities(City& a, City& b)
{
	return sqrt(pow((double)(a.get_x() - b.get_x()), 2.0) +
		pow((double)(a.get_y() - b.get_y()), 2.0));
}

void Tour::set_fitness(double _fitness) {
	fitness = _fitness;
}

double Tour::get_fitness() const {
	return fitness;
}