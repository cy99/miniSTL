#include <iostream>
#include "../mini_vector.h"
#include "../mini_algo.h"

using std::cout;
using std::endl;

int main() {
	using namespace ministl;
	int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
	vector<int> ivec(ia, ia + 9);

	make_heap(ivec.begin(), ivec.end());
	for (unsigned i = 0; i < ivec.size(); ++i) {
		cout << ivec[i] << ' ';
	} cout << endl << endl;

	ivec.push_back(7);
	push_heap(ivec.begin(), ivec.end());
	for (unsigned i = 0; i < ivec.size(); ++i) {
		cout << ivec[i] << ' ';
	} cout << endl << endl;

	pop_heap(ivec.begin(), ivec.end());
	cout << ivec.back() << endl;
	ivec.pop_back();

	for (unsigned i = 0; i < ivec.size(); ++i) {
		cout << ivec[i] << ' ';
	} cout << endl << endl;

	sort_heap(ivec.begin(), ivec.end());
	for (unsigned i = 0; i < ivec.size(); ++i) {
		cout << ivec[i] << ' ';
	} cout << endl << endl;

	return 0;
}