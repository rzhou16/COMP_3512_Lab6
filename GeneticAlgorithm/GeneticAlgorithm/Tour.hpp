#pragma once
#include "City.hpp"

class Tour {
private:
	static constexpr int CITIES_IN_TOUR = 20;
	double fitness; // Fitness rating
	City permutation[CITIES_IN_TOUR]; // An array of CITIES_IN_TOUR cities 

public:
	Tour() {}
	~Tour() { delete permutation; }
	static int get_tour_size() { return CITIES_IN_TOUR; }

};