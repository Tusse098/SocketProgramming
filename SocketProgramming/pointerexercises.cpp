//#include <stdio.h>
//
//int sum(int* arr, int n) {
//    int total = 0;
//    for (int i = 0; i < n; i++) {
//        total += *(arr + i);
//    }
//    return total;
//}
//
//void fill(int* arr, int n, int value) {
//    for (int i = 0; i < n; i++) {
//        arr[i] = value;
//    }
//}
//
//int main(void) {
//    int nums[5] = { 10, 20, 30, 40, 50 };
//    int* p = nums;
//
//    printf("1: %d %d\n", nums[0], *p); // 10, 10
//    printf("2: %d %d\n", nums[2], *(p + 2)); // 30, 30
//    printf("3: %d\n", p[3]); // 40
//
//    p++;
//    printf("4: %d\n", *p); //20
//
//    printf("5: %d\n", sum(nums, 5));
//    printf("6: %d\n", sum(nums + 2, 3));
//
//    fill(nums, 5, 7);
//    printf("7: %d %d\n", nums[0], nums[4]);
//
//    printf("8: %d\n", (int)(&nums[4] - &nums[0]));
//    printf("9: %zu %zu\n", sizeof(nums), sizeof(p));
//
//    return 0;
//}