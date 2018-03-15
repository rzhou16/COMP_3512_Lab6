#pragma once
#include "City.hpp"
#include <vector>

class Tour {
private:
	static constexpr int CITIES_IN_TOUR = 20;
	double fitness; // Fitness rating
	std::vector<City> permutation; // An array of CITIES_IN_TOUR cities 

public:
	Tour(double _fitness, std::vector<City>& _permutation) {
		using std::swap;
		swap(fitness, _fitness);
		swap(permutation, _permutation);
	}
	
	Tour(Tour& _tour) {
		using std::swap;
		swap(fitness, _tour.fitness);
		swap(permutation, _tour.permutation);
	}
};