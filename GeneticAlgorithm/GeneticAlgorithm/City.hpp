#pragma once
#include <string>

class City {
private:
	std::string name;
	int  x_coordinate;
	int  y_coordinate;
public:
	void set_name(std::string& _name) {
		name = _name;
	}

	void set_x_coordinate(int _x_coordinate) {
		x_coordinate = _x_coordinate;
	}

	void set_y_coordinate(int _y_coordinate) {
		y_coordinate = _y_coordinate;
	}
};