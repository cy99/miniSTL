#include "../mini_vector.h"
#include "../mini_priority_queue.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
	using namespace ministl;

	int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
	priority_queue<int> ipq(ia, ia + 9);
	cout << "size = " << ipq.size() << endl;

	for (unsigned i = 0; i < ipq.size(); ++i) {
		cout << ipq.top() << ' ';
	} cout << endl << endl;

	while (!ipq.empty()) {
		cout << ipq.top() << ' ';
		ipq.pop();
	}

	cout << endl << endl;

	return 0;
}