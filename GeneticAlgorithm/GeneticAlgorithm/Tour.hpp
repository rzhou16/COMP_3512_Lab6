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
};