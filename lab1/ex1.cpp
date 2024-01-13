#include <iostream>
#include <stdint.h>
using namespace std;

struct Vehicle
{
	int price;
	int capacity;
}vehicle;

int compareDistances(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

int compareRelativeDistances(const void* a, const void* b)
{
	return (*(int*)b - *(int*)a);
}

int compareCars(const void* a, const void* b)
{
	const struct Vehicle* v1 = (const struct Vehicle *)a;
	const struct Vehicle* v2 = (const struct Vehicle*)b;
	return (v1->capacity - v2->capacity);
}

bool isCarViable(Vehicle car, int K , int *distance , int Cf, int Cs, int T, int Tf, int Ts)
{
	unsigned int totalTime = 0;
	for (int i=0;i<K+1;i++)
	{
		float a = (float)(car.capacity - distance[i] * Cs) / (float)(Cf - Cs);
		if (a > distance[i]) a = distance[i];
		if (a * Cf + (distance[i] - a) * Cs > car.capacity || a < 0) return false;
		totalTime += a * Tf + (distance[i] - a) * Ts;
		if (totalTime > T) return false;
	}
	return (totalTime<=T);
}


int binary_search(int left, int right, int index, Vehicle cars[], int K , int distance[], int Cf, int Cs, int T, int Tf, int Ts) {
	if (left >= right)
		return index;
	else {
		int mid = (left + right) / 2;
		if (isCarViable(cars[mid] , K , distance, Cf, Cs, T, Tf, Ts)) {
			return binary_search(left, mid - 1, mid, cars, K , distance, Cf, Cs, T, Tf, Ts);
		}
		else {
			return binary_search(mid + 1, right, index, cars, K , distance, Cf, Cs, T, Tf, Ts);
		}

	}
}

int main()
{
	int N = 0, K, D, T;
	int Ts, Cs, Tf, Cf;
	scanf("%d %d %d %d", &N, &K, &D, &T);

	Vehicle *cars = new Vehicle[N];

	for (int i = 0; i < N; i++) 
		scanf("%d %d", &cars[i].price, &cars[i].capacity);
	

	int *distance = new int[K];
	for (int i = 0; i < K; i++)
		scanf("%d", &distance[i]);

	scanf("%d %d %d %d", &Ts, &Cs, &Tf, &Cf);

	qsort(cars, N, sizeof(Vehicle), compareCars);
	qsort(distance, K , sizeof(int), compareDistances);

	int *relativeDistance = new int[K+1];
	relativeDistance[0] = distance[0];

	for (int i = 1; i < K ; i++)
	{
		relativeDistance[i] = distance[i] - distance[i - 1];
	}
	relativeDistance[K] = D - distance[K - 1];
	
	qsort(relativeDistance, K + 1, sizeof(int), compareRelativeDistances);

	int final_index = binary_search(0, N, -1, cars, K , relativeDistance, Cf, Cs, T, Tf, Ts);

	if (final_index == -1) cout << "-1\n";
	else
	{
		int bestPrice = cars[final_index].price;
		for (int i = final_index; i < N; i++)
		{
			if (cars[i].price < bestPrice) bestPrice = cars[i].price;
		}
		cout << bestPrice << "\n";
	}

	return 0;

}
