#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_pbds;

/*
	Order Statistics Tree ( OST )
	
	find_by_order()
		takes an integer k and returns an iterator to the k'th largest element counting from zero
	order_of_key()
		takes an element, here an integer and returns the number of elements strictly smaller than input
*/

typedef tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>
ordered_set;

int main() {
	ordered_set X;
	X.insert(1);
	X.insert(2);
	X.insert(4);
	X.insert(8);
	X.insert(16);

	cout << *X.find_by_order(1) << '\n';	// 2
	cout << *X.find_by_order(2) << '\n';	// 4
	cout << *X.find_by_order(4) << '\n';	// 16
	cout << boolalpha << (X.end() == X.find_by_order(6)) << '\n';	// true
	cout << boolalpha << (X.begin() == X.find_by_order(1)) << '\n';	// false

	cout << X.order_of_key(-5) << '\n';		// 0
	cout << X.order_of_key(1) << '\n';		// 0
	cout << X.order_of_key(3) << '\n';		// 2
	cout << X.order_of_key(4) << '\n';		// 2
	cout << X.order_of_key(400) << '\n';	// 5

	return 0;
}
