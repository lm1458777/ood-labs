#include <algorithm>
#include <functional>

using namespace std;

void main()
{
	int numbers[] = {6, 3, 2, 1, 3, 4};
	sort(begin(numbers), end(numbers), [](int x, int y) { return x < y; });
	
	sort(begin(numbers), end(numbers), less<int>());

	function<bool(int, int)> compare = [](int x, int y) { return x < y; };
	sort(begin(numbers), end(numbers), compare);
}
