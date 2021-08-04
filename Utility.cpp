pair<map<int, int>, vector<int>> number_to_order(vector<int> vec) {
	// 0-based, map: number->order, modify the type for number by yourself
	map<int, int> trans;
	sort(vec.begin(), vec.end());
	vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
	for (int i = 0; i < vec.size(); i++) {
		trans[vec[i]] = i;
	}
	return {trans, vec};
}

ll ifloor(ll a, ll b){
    if(b < 0) a *= -1, b *= -1;
    if(a < 0) return (a - b + 1) / b;
    else return a / b;
}
 
ll iceil(ll a, ll b){
    if(b < 0) a *= -1, b *= -1;
    if(a > 0) return (a + b - 1) / b;
    else return a / b;
} 

auto add = [&](int& a, int b) -> void {
	a += b;
	a = (a >= MOD ? a - MOD : a);
};
auto sub = [&](int& a, int b) -> void {
	a -= b;
	a = (a < 0 ? a + MOD : a);
};

