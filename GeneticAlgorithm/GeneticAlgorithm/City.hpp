#pragma once

class City {
private:
	char name;
	int  x_coordinate;
	int  y_coordinate;
public:
	City(char _name, int _x, int _y) {
		name = _name;
		x_coordinate = _x;
		y_coordinate = _y;
	}

	City(City& _city) {
		using std::swap;
		swap(name, _city.name);
		swap(x_coordinate, _city.x_coordinate);
		swap(y_coordinate, _city.y_coordinate);
	}
};