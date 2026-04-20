#include <stdio.h>
#include <stdlib.h>

void reverseArray(int *arr, int size) {
    // Pointer 'start' menunjuk ke awal array
    int *start = arr; 
    // Pointer 'end' menunjuk ke elemen terakhir array
    int *end = arr + size - 1; 
    int temp;

    while (start < end) {
        // Proses penukaran (swap) nilai
        temp = *start;
        *start = *end;
        *end = temp;

        // Gerakkan pointer ke arah tengah
        start++;
        end--;
    }
}

int main() {
    int N;
    // Membaca jumlah elemen (N)
    if (scanf("%d", &N) != 1) return 0;

    int *recovered = (int *)malloc(N * sizeof(int));

    // Membaca elemen array
    for (int i = 0; i < N; i++) {
        scanf("%d", &recovered[i]);
    }

    reverseArray(recovered, N);

    // Tahap 1: Pemulihan Data (RECOVERED)
    for (int i = 0; i < N; i++) {
        if (recovered[i] != -1) {
            recovered[i] = recovered[i]; // Data valid, tetap gunakan nilai asli
        } else {
            int left = -1, right = -1;

            // Cari tetangga valid di kiri 
            if (i>0){
                if (recovered[i - 1] != -1) {
                    left = recovered[i - 1];
                }
            }

            // Cari tetangga valid di kanan
            if (i < N - 1){
                if (recovered[i + 1] != -1) {
                    right = recovered[i + 1];
                }
            }

            // Aturan pemulihan berdasarkan ketersediaan tetangga
            if (left != -1 && right != -1) {
                recovered[i] = (left + right) / 2.0; // Floor division otomatis di int
            } else if (left != -1) {
                recovered[i] = left;
            } else if (right != -1) {
                recovered[i] = right;
            } else {
                recovered[i] = 0;
            }
        }
    }

    // Cetak hasil pemulihan
    printf("RECOVERED");
    reverseArray(recovered, N);
    for (int i = 0; i < N; i++) {
        printf(" %d", recovered[i]);
    }
    printf("\n");

    // Tahap 2: Mencari Maksimum Subarray (Kadane's Algorithm)
    long long max_so_far = recovered[0];
    long long current_max = recovered[0];

    for (int i = 1; i < N; i++) {
        // Pilih antara elemen saat ini atau (current_max + elemen saat ini)
        if ((long long)recovered[i] > current_max + recovered[i]) {
            current_max = recovered[i];
        } else {
            current_max = current_max + recovered[i];
        }

        // Update nilai tertinggi yang pernah dicapai
        if (current_max > max_so_far) {
            max_so_far = current_max;
        }
    }

    printf("MAX_SUM %lld\n", max_so_far);

    free(recovered);
    return 0;
}
