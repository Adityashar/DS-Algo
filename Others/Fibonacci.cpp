// 1. Nearest fibonacci number to K;

int nearestFibonacci(int k) {
	if (k == 0)
		return 0;

	int first = 0, second = 1;
	int third = first + second;

	while (third <= k) {
		first = second, second = third;
		third = second + first;
	}

	return abs(k - third) > abs(k - second) ? second : third;
}



/*

2. Minimum fibonacci numbers that sum to K;

Given an integer k, return the minimum number of Fibonacci numbers whose sum is equal to k;
The same Fibonacci number can be used multiple times;

The Fibonacci numbers are defined as:

F1 = 1;
F2 = 1;
Fn = Fn - 1 + Fn - 2 where n > 2;

*/

// O(LogK) + O(LogK)

class Solution {
public:
	vector<int> fibo;

	int count;

	void fibonacci(int k) {
		fibo.push_back(0);
		fibo.push_back(1);

		while (fibo.back() <= k) {
			int n = fibo.size();
			fibo.push_back(fibo[n - 1] + fibo[n - 2]);
		}

		if (fibo.back() > k)
			fibo.pop_back();
	}

	bool memo(int k, int steps) {
		if (k == 0) {
			count = steps;
			return true;
		}

		auto it = lower_bound(fibo.begin(), fibo.end(), k);

		if (*it == k) {
			count = steps;
			return true;
		}

		int start = (it - fibo.begin() - 1);

		for (int i = start; i > 0; i--) {
			if (memo(k - fibo[i], steps + 1))
				return true;
		}

		return false;
	}

	int iterativeSimple(int k) {
		int cnt = 0, j = fibo.size() - 1;

		while (k > 0) {
			cnt += k / fibo[j];
			k %= fibo[j];
			j--;
		}

		return cnt;
	}

	int findMinFibonacciNumbers(int k) {

		if (k == 1)
			return k;

		fibonacci(k);
		count = 0;
		memo(k, 1);

		return count;
	}
};


/*

3. Nth Fibonacci Number using Matrix-Chain Multiplication


*/