// map test
#include <iostream>
#include "../mini_map.h"
#include <string>

using std::cout;
using std::endl;
using std::string;

int main() {
    using namespace ministl;
    map<string, int> simap;
    simap[string("jjhou")] = 1;
    simap[string("jerry")] = 2;
    simap[string("jason")] = 3;
    simap[string("jimmy")] = 4;

    pair<string, int> value(string("david"), 5);
    simap.insert(value);

    map<string, int>::iterator simap_iter = simap.begin();
    for (; simap_iter != simap.end(); ++simap_iter)
        cout << simap_iter->first << " => "
            << simap_iter->second << endl;

    simap["jjhou"] = 9;

#if 1
    cout << endl << endl << "---- reverse ----" << endl;
    for (simap_iter = simap.end(); simap_iter != simap.begin(); ) {
        --simap_iter;
        cout << simap_iter->first << " => "
            << simap_iter->second << endl;
    }

    cout << "reverse_iterator" << endl;
    for (auto it = simap.rbegin(); it != simap.rend(); ++it) {
        cout << it->first << " => "
            << it->second << endl;
    }
    cout << "------ over ------\n" << endl;
#endif // 1



    int number = simap[string("jjhou")];
    cout << "jjhou number is " << number << endl;

    map<string, int>::iterator ite1;

    ite1 = simap.find("jjhou");
    if (ite1 != simap.end())
        cout << "jjhou found" << endl;
    //*ite1 = pair<string, int>("mchen", 9); // error
    simap["mchen"] = 12;

    for (auto &x : simap)
        cout << x.first << " => " << x.second << endl;

    cout << "If I erase jerry, then " << endl;
    simap.erase("jerry");
    for (auto &x : simap)
        cout << x.first << " => " << x.second << endl;

    cout << "map size is " << simap.size() << endl;
}


int main1() {
	using namespace ministl;
	map<int, int> m;
	// m.insert(pair<int, int>(1, 2));
	for (unsigned i = 0; i < 10; ++i) {
        m[i] = i * i;
	}
	for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
	}
	return 0;
}
