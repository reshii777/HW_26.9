#include <iostream>
#include <vector>
#include <thread>
#include <numeric> // ��� std::accumulate
#include <windows.h>

// �������, ������� ����� ��������� ������ �����
void calculateSum(const std::vector<int>& array, size_t start, size_t end, long long& result) {
    result = std::accumulate(array.begin() + start, array.begin() + end, 0LL);
}

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "ru_Ru");

    // ������� ������
    size_t N = 20;
    size_t M = 4;
    std::vector<int> array = { 5, 3, 2, 4, 8, 9, 6, 1, 1, 7, 9, 3, 8, 2, 6, 3, 5, 5, 4, 7 };

    // �������� ������� �������
    std::vector<std::thread> threads;

    // ������ ��� �������� ����������� ���������� ������� ������
    std::vector<long long> results(M);

    // ��������� ������ �� ����� � ��������� ������
    size_t chunkSize = N / M;
    size_t remainder = N % M;
    size_t start = 0;

    for (size_t i = 0; i < M; ++i) {
        size_t end = start + chunkSize + (i < remainder ? 1 : 0);
        threads.emplace_back(calculateSum, std::ref(array), start, end, std::ref(results[i]));
        start = end;
    }

    // ������� ���������� ���� �������
    for (auto& thread : threads) {
        thread.join();
    }

    // ��������� ���������� �������
    long long totalSum = std::accumulate(results.begin(), results.end(), 0LL);

    // ����� ����������
    std::cout << "���������: " << totalSum << std::endl;

    return 0;
}
