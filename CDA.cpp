#include <iostream>
#include <string.h>
using namespace std;

template <class elmtype>

class CDA {

  public:
    CDA();
    CDA(int s);
    ~CDA();
    elmtype& operator[](int i);
    void AddEnd(elmtype v);
    void AddFront(elmtype v);
    void DelEnd();
    void DelFront();
    int Length();
    int Capacity();
    void Clear();
    bool Ordered();
    int SetOrdered();
    elmtype Select(int k);
    void InsertionSort();
    void QuickSort();
    void CountingSort(int m);
    int Search(elmtype e);
    CDA(const CDA<elmtype> &obj);
    CDA<elmtype> &operator=(const CDA<elmtype> &obj);

  private:
    int size, capacity, front, rear;
    elmtype *arr;
    elmtype ret;
    bool flag;
    void deepCopy(const CDA<elmtype> &obj);

};

template <typename elmtype>
CDA<elmtype>::CDA() {
  size = 0;
  capacity = 1;
  arr = new elmtype[capacity];
  flag = false;
  front = -1;
  rear = 0;
}

template <typename elmtype>
CDA<elmtype>::CDA(int s) {
  capacity = size = s;
  arr = new elmtype[s];
  flag = false;
  front = 0;
  rear = s - 1;
}

template <typename elmtype>
CDA<elmtype>::~CDA() {
  delete[] arr;
}

template <typename elmtype>
elmtype& CDA<elmtype>::operator[](int i) {
  if (i >= size || i < 0) {
    cout << "Out of bounds reference : " << i << endl;
    return ret;
  }
  else return arr[(front + i) % capacity];
}

template <typename elmtype>
void CDA<elmtype>::AddEnd(elmtype v) {
  if (size == capacity) {
    int cap = capacity;
    capacity *= 2;
    elmtype *temp = arr;
    arr = new elmtype[capacity];
    for (int i = 0; i < size; i++) {
      arr[i] = temp[(front+i) % cap];
    }
    size++;
    arr[size-1] = v;
    front = 0;
    rear = size - 1;
    delete[] temp;
  }
  else {
    if (front == -1) front = 0;
    else if (rear == (capacity - 1)) rear = 0;
    else rear += 1;
    size++;
    arr[rear] = v;
  }
}

template <typename elmtype>
void CDA<elmtype>::AddFront(elmtype v) {
  if (size == capacity) {
    int cap = capacity;
    capacity *= 2;
    elmtype *temp = arr;
    arr = new elmtype[capacity];
    arr[0] = v;
    for (int i = 0; i < size; i++) {
      arr[i+1] = temp[(front+i) % cap];
    }
    size++;
    front = 0;
    rear = size - 1;
    delete[] temp;
  }
  else {
    if (front == -1) front = 0;
    else if (front == 0) front = capacity - 1;
    else front = front - 1;
    size++;
    arr[front] = v;
  }
}

template <typename elmtype>
void CDA<elmtype>::DelEnd() {
  if (size == 0) {
    return;
  }
  size--;
  if (4*size <= capacity) {
    int cap = capacity;
    capacity /= 2;
    if (capacity < 1) return;
    elmtype *temp = arr;
    arr = new elmtype[capacity];
    for (int i = 0; i < (size-1); i++) {
      arr[i] = temp[(front+i) % cap];
    }
    front = 0;
    rear = size - 1;
    delete[] temp;
  }
  else {
    if (front == rear) {
      front = -1;
      rear = 0;
    }
    else if (rear == 0) {
      rear = capacity - 1;
    }
    else rear -= 1;
  }
}

template <typename elmtype>
void CDA<elmtype>::DelFront() {
  if (size == 0) {
    return;
  }
  size--;
  if (4*size <= capacity) {
    int cap = capacity;
    capacity /= 2;
    if (capacity < 1) return;
    elmtype *temp = arr;
    arr = new elmtype[capacity];
    for (int i = 0; i < size; ++i) {
      arr[i] = temp[(front+i+1) % cap];
    }
    front = 0;
    rear = size - 1;
    delete[] temp;
  }
  else {
    if (front == rear) {
      front = -1;
      rear = 0;
    }
    else if (front == (capacity - 1)) front = 0;
    else front += 1;
  }
}

template <typename elmtype>
int CDA<elmtype>::Length() {
  return size;
}

template <typename elmtype>
int CDA<elmtype>::Capacity() {
  return capacity;
}

template <typename elmtype>
void CDA<elmtype>::Clear() {
  delete arr;
  arr = new elmtype[capacity=1];
  size = 0;
  flag = false;
  front = -1;
  rear = 0;
}

template <typename elmtype>
CDA<elmtype>::CDA(const CDA<elmtype> &obj) {
  deepCopy(obj);
}

template <typename elmtype>
CDA<elmtype> &CDA<elmtype>::operator=(const CDA<elmtype> &obj)
{
  if (this != &obj) {
    delete[] arr;
    deepCopy(obj);
  }
  return *this;
}

template <typename elmtype>
void CDA<elmtype>::deepCopy(const CDA<elmtype> &obj) {
  capacity = obj.capacity;
  size = obj.size;
  front = obj.front;
  rear = obj.rear;
  arr = new elmtype[capacity];
  for (int i = 0; i < obj.size; i++) {
    arr[(front + i) % capacity] = obj.arr[(front + i) % capacity];
  }
}

template <typename elmtype>
bool CDA<elmtype>::Ordered() {
  SetOrdered();
  return flag;
}

template <typename elmtype>
int CDA<elmtype>::SetOrdered() {
  if (size == 0 || size == 1) {
    flag = true;
    return 1;
  }
  for (int i = 1; i < size; i++) {
    if (arr[i - 1] > arr[i]) {
      flag = false;
      return -1;
    }
  }
  flag = true;
  return 1;
}

template <typename elmtype>
int partition(elmtype arr[], int l, int r) {
  int i = l;
  elmtype x = arr[r];
  for (int j = l; j <= r - 1; j++) {
    if (arr[j] <= x) {
      swap(arr[i], arr[j]);
      i++;
    }
  }
  swap(arr[i], arr[r]);
  return i;
}

template <typename elmtype>
elmtype kthSmallest(elmtype arr[], int l, int r, int k) {
  if (k > 0 && k <= r - l + 1) {
    int index = partition(arr, l, r);
    if (index - l == k - 1) return arr[index];
    if (index - l > k - 1) return kthSmallest(arr, l, index - 1, k);
    return kthSmallest(arr, index + 1, r, k - index + l - 1);
  }
}

template <typename elmtype>
elmtype CDA<elmtype>::Select(int k) {
  if (Ordered() == true) return arr[k-1];
  else {
    elmtype *temp = arr;
    arr = new elmtype[capacity];
    for (int i = 0; i < size; i++) {
      arr[i] = temp[(front+i) % capacity];
    }
    front = 0;
    rear = size - 1;
    delete[] temp;
    return kthSmallest(arr, front, rear, k);
  }
}

template <typename elmtype>
void CDA<elmtype>::InsertionSort() {
  elmtype *temp = arr;
  arr = new elmtype[capacity];
  for (int i = 0; i < size; i++) {
    arr[i] = temp[(front+i) % capacity];
  }
  front = 0;
  rear = size - 1;
  delete[] temp;
  int n = sizeof(arr) / sizeof(arr[0]);
  int i, j, key;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
  Ordered();
}

void quickSort(int arr[], int front, int rear) {
  if (front < rear) {
    int pi = partition(arr, front, rear);
    quickSort(arr, front, pi - 1);
    quickSort(arr, pi + 1, rear);
  }
}

template <typename elmtype>
void CDA<elmtype>::QuickSort() {
  elmtype *temp = arr;
  arr = new elmtype[capacity];
  for (int i = 0; i < size; i++) {
    arr[i] = temp[(front+i) % capacity];
  }
  front = 0;
  rear = size - 1;
  delete[] temp;
  quickSort(arr, front, rear);
}

template <typename elmtype>
void CDA<elmtype>::CountingSort(int m) {
  elmtype *temp = arr;
  arr = new elmtype[capacity];
  for (int i = 0; i < size; i++) {
    arr[i] = temp[(front+i) % capacity];
  }
  front = 0;
  rear = size - 1;
  delete[] temp;

  int output[size*m];
  int count[m+1];
  int max = arr[0];
  for (int i = 1; i < size; i++) {
    if (arr[i] > max) max = arr[i];
  }
  if (max > m) max = m;
  for (int i = 0; i <= max; ++i) {
    count[i] = 0;
  }
  for (int i = 0; i < size; i++) {
    count[arr[i]]++;
  }
  for (int i = 1; i <= max; i++) {
    count[i] += count[i - 1];
  }
  for (int i = size - 1; i >= 0; i--) {
    output[count[arr[i]] - 1] = arr[i];
    count[arr[i]]--;
  }
  for (int i = 0; i < size; i++) {
    arr[i] = output[i];
  }
}

template <typename elmtype>
int binarySearch(elmtype arr[], int l, int r, elmtype x) {
  if (r >= l) {
    int m = l + (r - l) / 2;
    if (arr[m] == x) return m;
    if (arr[m] > x) return binarySearch(arr, l, m - 1, x);
    return binarySearch(arr, m + 1, r, x);
  }
  return -1;
}

template <typename elmtype>
int linearSearch(elmtype arr[], int n, elmtype x) {
  for (int i = 0; i < n; i++) {
    if (arr[i] == x) return i;
  }
  return -1;
}

template <typename elmtype>
int CDA<elmtype>::Search(elmtype e) {
  if (Ordered() == true) {
    return binarySearch(arr, front, rear, e);
  }
  else {
    return linearSearch(arr, size, e);
  }
}
