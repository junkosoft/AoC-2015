#include "../days.h"

#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Wrap {
public:
	int l, w, h;

	Wrap(int l, int w, int h) {
		this->l = l;
		this->w = w;
		this->h = h;		
	}

	int findArea() {
		int s1 = l*w;
		int s2 = w*h;
		int s3 = h*l;
		int area = 2*s1 + 2*s2 + 2*s3;
		int extra = min(s1, min(s2, s3));

		return area + extra;
	}

	int getRibbonLength() {
		std::vector<int> v = {l, w, h};
		std::sort(v.begin(), v.end());
		
		int ribbon_ = (2*v[0]) + (2*v[1]);
		int bow_ = l*w*h;

		return ribbon_ + bow_;
	}
};

std::vector<Wrap*> wraps;

void day_two() {
	std::fstream input("days/day_two_input.txt");

	int currentLine = 0;
	std::string line;
	while (std::getline(input, line)) {
		line[line.find_first_of('x', 0)] = ' ';
		line[line.find_last_of('x', line.length()-1)] = ' ';

		std::string lcopy = line;
		wraps.push_back(new Wrap(0, 0, 0));
		
		wraps[currentLine]->l = atoi(lcopy.c_str());
		
		if (to_string(wraps[currentLine]->l).length() >= 2) {
			lcopy.erase(0, 3);
		} else {
			lcopy.erase(0, 2);
		}

		wraps[currentLine]->w = atoi(lcopy.c_str());
		
		if (to_string(wraps[currentLine]->w).length() == 2) {
			lcopy.erase(0, 3);
		} else {
			lcopy.erase(0, 2);
		}

		wraps[currentLine]->h = atoi(lcopy.c_str());
		currentLine++;
	}

	int wrapping_size = 0, ribbon_size = 0;

	for (auto w : wraps) {
		wrapping_size += w->findArea();
		ribbon_size += w->getRibbonLength();
	}

	cout << "size needed: " << wrapping_size << "\n";
	cout << "ribbon needed: " << ribbon_size << "\n";

	input.close();
}