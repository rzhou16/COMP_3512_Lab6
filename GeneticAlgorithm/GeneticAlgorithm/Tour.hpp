#pragma once
class City;

class Tour {
private:
	static constexpr CITIES_IN_TOUR = 20;
	double fitness;
	City* permutation;
};