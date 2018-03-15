#pragma once
#include "City.hpp"
#include <vector>
#include <algorithm>

class Tour {
private:
	static constexpr int CITIES_IN_TOUR = 20;
	double fitness; // Fitness rating
	std::vector<City> permutation{ CITIES_IN_TOUR }; // An array of CITIES_IN_TOUR cities 

public:
	Tour();
	~Tour();
	Tour(double _fitness, std::vector<City>& _permutation);
	Tour(const Tour& _tour);
	std::vector<City> get_permutation();
	int contains_city(int length, City& candidate_city);
	void swap_cities(int index_one, int index_two);
	double get_tour_distance();
	double get_distance_between_cities(City& a, City& b);
	void set_fitness(double _fitness);
	double get_fitness() const;
};
