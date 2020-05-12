#include <bits/stdc++.h>
using namespace std;

/* Copy this */
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
namespace __gnu_pbds{
typedef tree<
int, // fix this
null_type,
std::less<int>, // fix this
rb_tree_tag,
tree_order_statistics_node_update>
set_t;
}
using __gnu_pbds::set_t;

int main() {
	set_t S;
	S.insert(5);
	S.insert(7);
	S.insert(10);
	cout << S.order_of_key(4) << '\n'; // 0, How many smaller
	cout << S.order_of_key(5) << '\n'; // 0
	cout << S.order_of_key(6) << '\n'; // 1
	cout << *S.find_by_order(0) << '\n'; // 5
	cout << *S.find_by_order(2) << '\n'; // 10
	return 0;
}
