#pragma once 
template <typename T, typename F>
void merge(T* arr, int start, int middle, int end, F func) {
	T* temp1 = new T[middle - start + 1];
	T* temp2 = new T[end - middle];
	int size1 = middle - start + 1;
	int size2 = end - middle;
	for (int i = 0; i < middle - start + 1; i++) {
		temp1[i] = arr[i + start];
	}
	for (int i = 0; i < end - middle; i++) {
		temp2[i] = arr[i + middle + 1];
	}


	int cnt1 = 0, cnt2 = 0;
	for (int i = start; i <= end; i++) {
		if (cnt1 == size1) {
			arr[i] = temp2[cnt2];
			cnt2++;
		}
		else if (cnt2 == size2) {
			arr[i] = temp1[cnt1];
			cnt1++;
		}
		else {
			if (func(temp1[cnt1]) < func(temp2[cnt2])) {
				arr[i] = temp1[cnt1];
				cnt1++;
			}
			else {
				arr[i] = temp2[cnt2];
				cnt2++;
			}

		}

	}


}
template<typename T, typename F>
void mainMergeSort(T* arr, int start, int end, F func) {
	if (start >= end)
		return;
	mainMergeSort(arr, start, (start + end) / 2, func);
	mainMergeSort(arr, (start + end) / 2 + 1, end, func);
	merge(arr, start, (start + end) / 2, end, func);

}
template<typename T, typename F>
void mergeSort(T* arr, int size, F func) {

	mainMergeSort(arr, 0, size - 1, func);
}