#pragma once
#include "City.hpp"
#include <vector>

class Tour {
private:
	static constexpr int CITIES_IN_TOUR = 20;
	double fitness; // Fitness rating
	std::vector<City> permutation; // An array of CITIES_IN_TOUR cities 

public:
	Tour() { fitness = 0; }
};