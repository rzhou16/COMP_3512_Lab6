#pragma once

class City {
private:
	char name;
	int  x_coordinate;
	int  y_coordinate;
public:
	City() {}

	~City() {}

	City(char _name, int _x, int _y) {
		name = _name;
		x_coordinate = _x;
		y_coordinate = _y;
	}

	City(const City& _city) {
		name = _city.name;
		x_coordinate = _city.x_coordinate;
		y_coordinate = _city.y_coordinate;
	}

	char get_name() const { return name; }
	int get_x() const { return x_coordinate; }
	int get_y() const { return y_coordinate; }
};