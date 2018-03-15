#pragma once
#include "City.hpp"
#include <vector>
#include <algorithm>

class Tour {
private:
	static constexpr int CITIES_IN_TOUR = 20;
	double fitness; // Fitness rating
	std::vector<City> permutation; // An array of CITIES_IN_TOUR cities 

public:
	Tour() {}

	Tour(double _fitness, std::vector<City>& _permutation) {
		using std::swap;
		swap(fitness, _fitness);
		swap(permutation, _permutation);
		std::random_shuffle(permutation.begin(), permutation.end());
	}
	
	Tour(Tour& _tour) {
		using std::swap;
		swap(fitness, _tour.fitness);
		swap(permutation, _tour.permutation);
	}

	/*
	* Returns the total distance traveled on the
	* specified array (tour) of cities.
	* PARAM:  tour contains a set of CITIES_IN_TOUR cities
	* PRE:    NULL
	* POST:   NULL
	* RETURN: the total distance, a double
	*/
	double get_tour_distance() {
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
	double get_distance_between_cities(City& a, City& b)
	{
		return sqrt(pow((double)(a.get_x() - b.get_x()), 2.0) +
			pow((double)(a.get_y() - b.get_y()), 2.0));
	}

	void set_fitness(double _fitness) {
		fitness = _fitness;
	}
};