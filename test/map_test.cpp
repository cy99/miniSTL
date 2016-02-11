// map test
#include <iostream>
#include "../mini_map.h"
#include "../mini_multimap.h"
#include <string>
#include <map>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "../mini_vector.h"


using std::cout;
using std::endl;
using std::string;

int main1() {
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
    return 0;
}




int main2() {
	using namespace ministl;
	multimap<int, int> m;
	std::multimap<int, int> mm;
	// m.insert(pair<int, int>(1, 2));

	#if 1
	for (int i = 0; i < 10; ++i) {
        m.insert(pair<int, int>(i, i * i));
        mm.insert(std::pair<int, int>(i, i * i));
	}

	for (int i = 3; i < 8; ++i) {
        m.insert(pair<int, int>(i, i));
        mm.insert(std::pair<int, int>(i, i));
	}

    cout << endl << "std::map : " << endl;
	for (multimap<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
	}

	cout << endl << "std::multimap : " << endl;
	for (auto it = mm.begin(); it != mm.end(); ++it) {
        cout << it->first << " => " << it->second << endl;
	}
	#endif
	return 0;
}




#define SCALE 12345678
#define __SHOW 0

long long random_long_long_number() {
    // srand(time(0));
    static bool is_odd = false;
    long long ret = 0;
    // if (is_odd) ret = (long long)sqrt(std::rand() * std::rand());
    // else ret = std::rand();

    if (is_odd) ret = (std::rand() * std::rand());
    else ret = (long long)(pow(std::rand(), 2) * 3.14);

    is_odd = !is_odd;
    return ret;
}

void test_efficiency() {
    using namespace ministl;
    clock_t start, finish;

    vector<long long> sz, test_list;
    for (unsigned i = 0; i < SCALE; ++i) {
        sz.push_back(random_long_long_number());
        test_list.push_back(random_long_long_number());
    }
#if __SHOW
    cout << "----------------- Random list ------------------\n";
    for (auto &x : sz) {
        cout << x << " ";
    } cout << endl << endl;
#endif
    start = clock();
    vector<pair<long long, long long> > ss;
    vector<std::pair<long long, long long> > sb;
    for (auto &x : sz) {
        ss.push_back(pair<long long, long long>(x, x));
        sb.push_back(std::pair<long long, long long>(x, x));
    }
    finish = clock();
    cout << "vector push_back " << 2 * SCALE << " elements : " << endl;
    cout << "Time Waste : " << double(finish - start) / CLOCKS_PER_SEC << endl << endl;
    cout << "--------------" << endl;

    cout << "------------------------------ ministl::map -------------------------------------\n";
    start = clock();
    map<int, int> m(ss.begin(), ss.end());
    finish = clock();
    cout << "map insert " << SCALE << " elements : " << endl;
    cout << "Time Waste : " << double(finish - start) / CLOCKS_PER_SEC << endl;
    cout << "ministl::map Size is " << m.size() << endl << endl;

    cout << "[Find]" << endl;
    start = clock();
    for (auto &x : test_list)
        m.find(x);
    finish = clock();
    cout << "ministl::map find " << SCALE << " elements : " << endl;
    cout << "Time Waste : " << double(finish - start) / CLOCKS_PER_SEC << endl;

    cout << "------------------------------ std::map -------------------------------------\n";
    start = clock();
    std::map<int, int> mm(sb.begin(), sb.end());
    finish = clock();
    cout << "map insert " << SCALE << " elements : " << endl;
    cout << "Time Waste : " << double(finish - start) / CLOCKS_PER_SEC << endl;
    cout << "std::map Size is " << mm.size() << endl << endl;

    cout << "[Find]" << endl;
    start = clock();
    for (auto &x : test_list)
        mm.find(x);
    finish = clock();
    cout << "std::map find " << SCALE << " elements : " << endl;
    cout << "Time Waste : " << double(finish - start) / CLOCKS_PER_SEC << endl;




#if __SHOW
    cout << "\n\n---- Show ----\n";
    for (auto &x : m) {
        cout << x.first << " => "
            << x.second << endl;
    }
#endif
}

int main() {
    test_efficiency();
    return 0;
}
