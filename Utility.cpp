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
