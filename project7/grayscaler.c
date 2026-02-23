#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "ppm.h"

struct slice_data {
    struct ppm *image;
    int start_y;
    int height; // slice height in pixels
    long sum_r;
    long sum_g;
    long sum_b;
};

void *run(void *args)
{
    struct slice_data *data = args;

    for (int j = 0; j < data->height; j++) {
        int y = data->start_y + j;
        for (int i = 0; i < data->image->width; i++) {
            // Each pixel in thread
            int x = i;
            int pixel = ppm_get_pixel(data->image, x, y);

            // Keeping the sum of each r, g, and b value.
            int r = PPM_PIXEL_R(pixel);
            int g = PPM_PIXEL_G(pixel);
            int b = PPM_PIXEL_B(pixel);
            data->sum_r += r;
            data->sum_g += g;
            data->sum_b += b;

            // Convert the current pixel into gray
            int gray = (299*r + 587*g + 114*b) / 1000;
            int gray_pixel = PPM_PIXEL(gray, gray, gray);
            ppm_set_pixel(data->image, x, y, gray_pixel);
        }
    }
    return NULL;

}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <threads> <input.ppm> <output.ppm>\n", argv[0]);
        return 1;
    }
    // argv[1] = thread_count, argv[2] = ppm_filename, argv[3] = output_file
    int thread_count = atoi(argv[1]);
    if (thread_count <= 0) {
        fprintf(stderr, "Thread count must be greater than 0.\n");
        return 1;
    }
    char *ppm_filename = argv[2];
    char *output_file = argv[3];

    struct ppm *image = ppm_read(ppm_filename);
    int w = image->width;   // width
    int h = image->height;  // height

    int n = w*h;     // total pixels

    int rows = h / thread_count;   // number of rows per thread
    int r = h % thread_count;     // Remainder to be added to last row




    pthread_t thread[thread_count];
    struct slice_data slices[thread_count];

    for (int i = 0; i<thread_count; i++) {
        // defining the structs for each thread
        slices[i].image = image;
        slices[i].start_y = i * rows;
        slices[i].height = rows;
        if(i == thread_count-1) {   // If last thread, remainder is part of height
            slices[i].height += r;
        }

        slices[i].sum_r = 0;
        slices[i].sum_g = 0;
        slices[i].sum_b = 0;
        
        pthread_create(&thread[i], NULL, run, &slices[i]);
        printf("Thread %d: %d %d\n", i, slices[i].start_y, slices[i].height);
    }

    long total_r = 0;
    long total_g = 0;
    long total_b = 0;

    for (int i = 0; i<thread_count; i++) {
        // Join threads
        pthread_join(thread[i], NULL);
        total_r += slices[i].sum_r;
        total_g += slices[i].sum_g;
        total_b += slices[i].sum_b;
    }

    // Calculate average RGB
    long av_r = total_r / n;
    long av_g = total_g / n;
    long av_b = total_b / n;

    printf("Average R: %ld\n", av_r);
    printf("Average G: %ld\n", av_g);
    printf("Average B: %ld\n", av_b);

    ppm_write(image, output_file);
    ppm_free(image);

}



