class heap {
	vector<int> arr;
	int size;

public:
	heap(int c) {
		size = c;
	}

	void heapify(int i, int n) {
		int l = 2 * i + 1;
		int r = 2 * i + 2;

		int s = i;

		if (l < n && arr[l] < arr[s])
			s = l;
		if (r < n && arr[r] < arr[s])
			s = r;

		if (s != i) {
			swap(arr[s], arr[i]);
			heapify(s);
		}
	}

	void decreaseKey(int i, int new_val) {
		int val = new_val;
		int parent = (i - 1) / 2;

		while (i > 0 && arr[parent] > arr[i]) {
			swap(arr[parent], arr[i]);
			i = parent;
			parent = (i - 1) / 2;
		}
	}

	int extractMin() {
		if (arr.size() == 0)
			return -1;

		int top = arr[0];
		arr[0] = arr[arr.size() - 1];
		arr.pop_back();

		heapify(0);

		return top;
	}

	void deleteKey(i) {
		decreaseKey(i, INT_MIN);
		extractMin();
	}

	void insertKey(int val) {
		if (arr.size() == size)
			return;

		arr.push_back(val);
		decreaseKey(arr.size() - 1, val);
	}

	bool isHeap(int i, vector<int> &h) {
		if (i >= (h.size() - 2) / 2)
			return true;

		return (h[i] >= h[2 * i + 1] && h[i] >= h[2 * i + 2]) && isHeap(2 * i + 1, h) && isHeap(2 * i + 2, h);
	}

	bool isBTaHeap(TreeNode* root) {
		if (root == NULL)
			return true;


		queue<Node*> q;
		q.push(root);
		bool null = false;

		while (q.size() > 0) {
			Node *cur = q.front(); q.pop();

			if (cur == NULL) {
				null = true;
			}

			else {
				if (null == true)
					return false;

				if (cur->left && cur->left->data > cur->data)
					return false;

				if (cur->right && cur->right->data > cur->data)
					return false;


				q.push(cur->left);
				q.push(cur->right);

			}
		}

		return true;
	}

	void heapSort() {

		// n-2 / 2 last internal node with children
		for (int i = n / 2 - 1; i >= 0; i--) {
			heapify(i, n);
		}

		// sort
		// extractMin from top and place it at end
		// reduce size with each iteration so the sorted values aren't affected

		for (int i = n - 1; i >= 0; i++) {
			swap(arr[0], arr[i]);

			heapify(0, i);
		}

	}

};