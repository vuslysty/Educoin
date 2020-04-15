#include <iostream>

    const int N = 10;

int *needed_place(int *start, int *end) {
    bool check_ringt = true;

    while (start != end) {
        if (check_ringt) {
            if (*start > *end) {
                // std::cout << *start << " > " << *end << std::endl;
                std::swap(*start, *end);
                check_ringt = false;
                end--;
            } else {
                start++;
            }
        } else {
            if (*end < *start) {
                // std::cout << *start << " > " << *end << std::endl;
                std::swap(*start, *end);
                check_ringt = true;
                start++;
            } else {
                end--;
            }
        }
    }
    return end;
}

void m_qsort(int *start, int *end) {
    int *center = needed_place(start, end - 1);

    std::cout << *center << std::endl;
    for (int i = 0; i < N; i++) {
        std::cout << start[i] << " ";
    }
    std::cout << std::endl;

    // if (start != center - 1)
        m_qsort(start, center);
    // if (center + 1 != end - 1);
        m_qsort(center + 1, end);
}


int main() {


    int max = 10;
    int data[N] = {3, 1, 6, 3, 6, 3, 7, 3, 8, 6};

    // for (int i = 0; (i < N -1); i++) {
    //     for (int j = 0; j < N - 1 - i; j++)
    //         if (data[j] > data[j + 1]) {
    //             std::swap(data[j], data[j + 1]);
    //         }
    // }

    m_qsort(data, data + N);

    // int *center = needed_place(data, data + N - 1);

    for (int i = 0; i < N; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}