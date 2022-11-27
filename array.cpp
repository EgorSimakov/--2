//функция createArray заполняет целочисленный массив размерности N = 100 случайными значениями в диапазоне от –99 до 99.
//функция sort сортирует элементы массива. Определяется время, затраченное на сортировку, используетсябиблиотека chrono.
//функция quicksort сортирует элементы массива. Определяется время, затраченное на сортировку, используетсябиблиотека chrono.
//функция findMaxMin находит макс. и мин. элементы массива. Определяется время поиска этих элементов в отсортированном и неотсортированном массиве.
//функция findAvarege выводит СрЗнач макс. и мин. значения и выводит индексы всех элементов, которые равны этому значению, и их количество.
//функция findSmaller выводит количество элементов в отсортированном массиве, которые меньше числа a, которое инициализируется пользователем.
//функция findBigger выводит количество элементов в отсортированном массиве, которые больше числа b, которое инициализируется пользователем.
//функция binSearch выводит информацию о том, есть ли введенное пользователем число в отсортированном массиве. Реализуется алгоритм бинарного поиска. Сравнивается скорость его работы с обычным перебором.
//функция replaceElements меняет местами элементы массива,индексы которых вводит пользователь. Выводится скорость обмена.

#include<iostream>
#include<ctime>
#include<chrono>
using namespace std;
using namespace chrono;

const int N = 100;
int arr[N];
int arr_sort[N];

void createArray()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));
	cout << "Входной массив:" << endl;
	for (int i = 0; i < N; i++) {
		arr[i] = rand() % 199 - 99;
		arr_sort[i] = arr[i];
		cout << arr[i] << " ";
	}
	cout << endl;
}
void sort()
{
	setlocale(0, "rus");
	cout << "\nBubble sort" << "\n";
	auto start = high_resolution_clock::now();
	for (int i = 0; i < N - 1; i++) {
		bool flag = true;
		for (int j = 0; j < N - (i + 1); j++) {
			if (arr_sort[j] > arr_sort[j + 1]) {
				flag = false;
				swap(arr_sort[j], arr_sort[j + 1]);
			}
		}
		if (flag) {
			break;
		}
	}
	cout << "Отсортированный массив:\n";
	for (int i = 0; i < N; i++) {
		cout << arr_sort[i] << ' ';
		arr_sort[i] = arr[i];
	}
	auto end = steady_clock::now();
	auto result = duration_cast<nanoseconds>(end - start);
	cout << "\nВремя сортировки:" << result.count() << " ns" << endl;
	
	cout << "\nComb sort\n";
	float k = 1.247, S = N - 1;
	int count = 0;
	auto start1 = high_resolution_clock::now();
	while (S >= 1)
	{
		for (int i = 0; i + S < N; i++)
		{
			if (arr_sort[i] > arr_sort[int(i + S)])
			{
				swap(arr_sort[i], arr_sort[int(i + S)]);

			}
		}
		S /= k;
	}
	while (true)
	{
		for (int i = 0; i < N - 1; i++)
		{
			if (arr_sort[i] > arr_sort[i + 1])
			{
				swap(arr_sort[i + 1], arr_sort[i]);
			}
			else count++;
		}
		if (count == N - 1)
			break;
		else
			count = 0;
	}
	cout << "Отсортированный массив:\n";
	for (int i = 0; i < N; i++)
	{
		cout << arr_sort[i] << ' ';
		arr_sort[i] = arr[i];
	}
	auto end1 = steady_clock::now();
	auto result1 = duration_cast<nanoseconds>(end1 - start1);
	cout << "\nВремя сортировки:" << result1.count() << " ns" << endl;

	cout << "\nShaker sort\n";
	auto start3 = high_resolution_clock::now();
	bool sort_or_not = true;
	do {
		sort_or_not = true;
		for (int i = 0; i < N; i++) {
			if (arr_sort[i] > arr_sort[i + 1]) {
				swap(arr_sort[i], arr_sort[i + 1]);
				sort_or_not = false;
			}
		}
		for (int i = 99; i >= 1; i--) {
			if (arr_sort[i] < arr_sort[i - 1]) {
				swap(arr_sort[i], arr_sort[i - 1]);
				sort_or_not = false;
			}
		}
	} while (sort_or_not == false);
	cout << "Отсортированный массив:\n";
	for (int i = 0; i < N; i++)
	{
		cout << arr_sort[i] << " ";
		arr_sort[i] = arr[i];
	}
	auto end3 = steady_clock::now();
	auto result3 = duration_cast<nanoseconds>(end3 - start3);
	cout << "\nВремя сортировки:" << result3.count() << " ns" << endl;

	cout << "\nInsert sort\n";
	auto start2 = high_resolution_clock::now();
	for (int j = 1; j < N; j++)
	{
		int x = arr_sort[j];
		int i = j - 1;
		while ((i >= 0) && (x < arr_sort[i]))
		{
			arr_sort[i + 1] = arr_sort[i];
			i--;
		}
		arr_sort[++i] = x;
	}
	cout << "Отсортированный массив:\n";
	for (int i = 0; i < N; i++)
	{
		cout << arr_sort[i] << " ";
	}
	auto end2 = steady_clock::now();
	auto result2 = duration_cast<nanoseconds>(end2 - start2);
	cout << "\nВремя сортировки:" << result2.count() << " ns" << endl;
}
void quicksort(int* arr_sort, int  end, int begin)
{
	int mid;
	int f = begin;
	int l = end;
	mid = arr_sort[(f + l) / 2];
	while (f < l)
	{
		while (arr_sort[f] < mid) f++;
		while (arr_sort[l] > mid) l--;
		if (f <= l)
		{
			swap(arr_sort[f], arr_sort[l]);
			f++;
			l--;
		}
	}
	if (begin < l) quicksort(arr_sort, l, begin);
	if (f < end) quicksort(arr_sort, end, f);

}
void findMaxMin()
{
	setlocale(0, "rus");
	cout << "Arr_unsort" << "\nMaxMin:";
	int max = -100;
	int min = 199;
	auto start4 = high_resolution_clock::now();
	for (int i = 0; i < N; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	cout << max << " " << min;
	auto end4 = steady_clock::now();
	auto result4 = duration_cast<nanoseconds>(end4 - start4);
	cout << "\nВремя поиска Max_min:" << result4.count() << " ns" << endl;


	cout << "\nArr_sort" << "\nMaxMin_sort:";
	int max_sort = arr_sort[0];
	int min_sort = 199;
	auto start2 = high_resolution_clock::now();
	for (int i = 0; i < N; i++) {
		if (arr_sort[i] > max_sort) {
			max_sort = arr_sort[i];
		}
		if (arr_sort[i] < min_sort) {
			min_sort = arr_sort[i];
		}
	}
	cout << max_sort << " " << min_sort;
	auto end2 = steady_clock::now();
	auto result2 = duration_cast<nanoseconds>(end2 - start2);
	cout << "\nВремя поиска MaxMin_sort:" << result2.count() << " ns" << endl;
}
void findAvarege()
{
	setlocale(LC_ALL, "ru");
	int max_sort = arr_sort[0];
	int min_sort = 199;
	int n;
	for (int i = 0; i < N; i++) {
		if (arr_sort[i] > max_sort) {
			max_sort = arr_sort[i];
		}
		if (arr_sort[i] < min_sort) {
			min_sort = arr_sort[i];
		}
	}
	int max = -100;
	int min = 199;
	for (int i = 0; i < N; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
		if (arr[i] < min) {
			min = arr[i];
		}
	}

	cout << "Arr_sort\n";
	auto start3 = high_resolution_clock::now();
	n = (max_sort + min_sort) / 2;
	int cnt1 = 0;
	cout << "СрЗнач:" << " " << n << endl;
	cout << "Индексы:" << " ";
	for (int i = 0; i < N; i++) {
		if (arr_sort[i] == n) {
			cnt1++;
			cout << i << " ";
		}
	}
	cout << "\nКоличество:" << " " << cnt1;
	auto end3 = steady_clock::now();
	auto result3 = duration_cast<nanoseconds>(end3 - start3);
	cout << "\nВремя выполнения:" << result3.count() << " ns" << endl;

	cout << "\n\nArr_unsort\n";
	auto start5 = high_resolution_clock::now();
	n = (max + min) / 2;
	int cnt2 = 0;
	cout << "СрЗнач:" << " " << n << endl;
	cout << "Индексы:" << " ";
	for (int i = 0; i < N; i++) {
		if (arr[i] == n) {
			cnt2++;
			cout << i << " ";
		}
	}
	cout << "\nКоличество:" << " " << cnt2;
	auto end5 = steady_clock::now();
	auto result5 = duration_cast<nanoseconds>(end5 - start5);
	cout << "\nВремя выполнения:" << result5.count() << " ns" << endl;

}
void findSmaller()
{
	setlocale(LC_ALL, "ru");
	int a;
	int cnt3 = 0;
	cout << "\nВведите число a:";
	cin >> a;
	cout << "кол-во элементов меньше а:";
	for (int i = 0; i < N; i++) {
		if (arr_sort[i] < a) {
			cnt3++;
		}
	}
	cout << cnt3 << endl;
}
void findBigger()
{
	setlocale(LC_ALL, "ru");
	int b;
	int cnt3 = 0;
	cout << "\nВведите число b:";
	cin >> b;
	cout << "кол-во элементов больше b:";
	for (int i = 0; i < N; i++) {
		if (arr_sort[i] > b) {
			cnt3++;
		}
	}
	cout << cnt3 << endl;
}
void binSearch()
{
	setlocale(LC_ALL, "ru");
	int l = 0;
	int r = N; // в этом случае присваивается именно n
	int mid;
	int key;
	cout << "Бинарный поиск\n";
	cout << "Введите ключ:";
	cin >> key;
	auto start6 = high_resolution_clock::now();
	while (l < r) {
		mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]
		if (arr_sort[mid] > key) r = mid; // проверяем, какую часть нужно отбросить с поиска
		else l = mid + 1;
	}
	r--; // уменьшаем на один 

	if (arr_sort[r] == key) cout << "Индекс элемента " << key << " в массиве равен: " << r;
	else cout << "Извините, но такого элемента в массиве нет";
	auto end6 = steady_clock::now();
	auto result6 = duration_cast<nanoseconds>(end6 - start6);
	cout << "\nВремя поиска:" << result6.count() << " ns" << endl;

	cout << "\nПеребор\n";
	auto start7 = high_resolution_clock::now();
	int cnt5 = 0;
	for (int i = 0; i < N; i++) {
		if (arr_sort[i] == key)
			cnt5++;
	}
	if (cnt5 > 0)
		cout << "элемент найден";
	else cout << "Извините, но такого элемента в массиве нет";

	auto end7 = steady_clock::now();
	auto result7 = duration_cast<nanoseconds>(end7 - start7);
	cout << "\nВремя поиска:" << result7.count() << " ns" << endl;

	if (result6.count() < result7.count()) cout << "\nБинарынй поиск быстрее перебора";
	else cout << "\nПеребор быстрее бинарного поиска\n";
}
void replaceElements()
{
	setlocale(LC_ALL, "ru");
	cout << "Ведите индексы от 0 до 99:" << ' ';
	int z;
	int y;
	int temp;
	cin >> z >> y;
	auto start6 = high_resolution_clock::now();
	if (z < N && z >= 0 && y < N && y >= 0) {
		swap(arr_sort[z], arr_sort[y]);
		for (int i = 0; i < N; i++) {
			cout << arr_sort[i] << " ";
		}
		cout << endl;
	}
	else cout << "Индекс не найден" << endl;
	auto end6 = steady_clock::now();
	auto result6 = duration_cast<nanoseconds>(end6 - start6);
	cout << "\nВремя выполнения:" << result6.count() << " ns" << endl;
}


//функция меню

int main() {
	int end = N - 1, begin = 0;
	for (; ; ) {
		setlocale(LC_ALL, "rus");
		int choice;
		cout << "\nWat du you want?\n";
		cout << "1 - Create an arrey.\n";
		cout << "2 - Sort arrey.\n";
		cout << "3 - Find the maximum and minimum.\n";
		cout << "4 - Output the avarage value.\n";
		cout << "5 - Print the number smaller than the entered value.\n";
		cout << "6 - Print the number bigger than the entered value.\n";
		cout << "7 - Find out if ther is a number in the arrey.\n";
		cout << "8 - Change arrey elements.\n";
		cout << "9 - Exit.\n";
		cout << "\nEnter the option number:";

		cin >> choice;

		switch (choice)
		{
		case 1:
			createArray();
			break;

		case 2:
			sort();
			quicksort(arr_sort, end, begin);
			cout << endl << "Quick sort" "\nОтсортированный массив:\n";
			for (int i = 0; i < N; i++)
				cout << arr_sort[i] << " ";
			break;

		case 3:
			findMaxMin();
			break;

		case 4:
			findAvarege();
			break;

		case 5:
			findSmaller();
			break;

		case 6:
			findBigger();
			break;

		case 7:
			binSearch();
			break;

		case 8:
			replaceElements();
			break;

		case 9:
			cout << "Выход из программы...";
			return 0; break;

		default:
			cout << "\nТакого пункта в меню нет.";
			return 0; break;
		}
	}

}