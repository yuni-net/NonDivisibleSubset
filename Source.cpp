// https://www.hackerrank.com/challenges/non-divisible-subset

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

#define element_it_type list<Data>::iterator

struct Data{
	int value;
	list<element_it_type> iterators_I_cant_coexist;
	Data(const int value_){
		value = value_;
	}
};

int main() {
	// receive input
	int subset_qty, div_value;
	cin >> subset_qty >> div_value;
	if (subset_qty == 1){
		cout << "1" << endl;
		return 0;
	}

	list<Data> subset;
	//subset.(subset_qty);
	for (int i = 0; i<subset_qty; ++i){
		int value;
		cin >> value;
		subset.push_back(Data(value));
	}

	// analyze all dependencies
	element_it_type one = subset.begin();
	while (true){
		element_it_type another = one;
		++another;
		while (another != subset.end()){
			if ((one->value + another->value) % div_value == 0){
				one->iterators_I_cant_coexist.push_back(another);
				another->iterators_I_cant_coexist.push_back(one);
			}
			++another;
		}
		++one;
		auto next = one;
		++next;
		if ((next) == subset.end()){
			break;
		}
	}

	while (true){
		element_it_type most_dependented = subset.begin();
		{
			element_it_type it = subset.begin();
			++it;
			while (it != subset.end()){
				if (it->iterators_I_cant_coexist.size() > most_dependented->iterators_I_cant_coexist.size()){
					most_dependented = it;
				}
				++it;
			}
		}
		const int qty_most_dependented = most_dependented->iterators_I_cant_coexist.size();
		if (qty_most_dependented == 0){
			cout << subset.size() << endl;
			break;
		}

		element_it_type element_it = subset.begin();
		while (element_it != subset.end()){
			Data & element = *element_it;
			auto dependented_it = element.iterators_I_cant_coexist.begin();
			while (dependented_it != element.iterators_I_cant_coexist.end()){
				if (*dependented_it == most_dependented){
					element.iterators_I_cant_coexist.erase(dependented_it);
					break;
				}
				++dependented_it;
			}
			++element_it;
		}
		subset.erase(most_dependented);
	}

	return 0;
}
