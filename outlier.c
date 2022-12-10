#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "assert.h"

/* Function that compares two elements.*/
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
/*To calculte median of the elemnts of an array*/
int calculate_median(const size_t n, const int *list)
{
    if (n % 2 == 0) /*if length is even*/
    {
        return ((list[(n / 2) - 1] + list[(n / 2)]) / 2.0);
    }
    else
    {
        return (list[(n / 2)]);
    }
}

/*Finding the quartile */
static double quartile(int n, int q, const int *list)
{
    return (((list[((n / 4) * q) - 1]) + (list[(n / 4) * q])) / 2);
}
/*To detect and replace the outlier.*/
int calculate(int const *const input_data, int *output_data, int input_data_length, int max_change_rate)
{
    int median, errors_detected = 0;
    double q1, q3, iqr, low_lim, up_lim;
    float whisker_width = 1.5;

    memcpy(output_data, input_data, input_data_length * sizeof(int)); // copy the data to  output data from the input data
    qsort(input_data, input_data_length, sizeof(int), compare);       // sort the input_data
    median = calculate_median(input_data_length, input_data);         // calculate the median

    if (input_data_length > 4)
    {
        q1 = quartile(input_data_length, 1, input_data); // find 25th quartile
        q3 = quartile(input_data_length, 3, input_data); // find 75th quartile
        iqr = (q3 - q1);                                 // calculate iqr from q3 and q1
        /* calculate upper and low limits using whisker width to identify outliers */
        low_lim = q1 - whisker_width * iqr;
        up_lim = q3 + whisker_width * iqr;
        /*identify and replace the outlier with median value*/
        for (int index = 0; index < input_data_length; index++)
        {
            if (((output_data[index] > up_lim) || (output_data[index] < low_lim)) && max_change_rate > 0)
            {
                errors_detected++;
                output_data[index] = median;
                max_change_rate--;
            }
        }
    }
    else
    {
        return -1;
    }
    return errors_detected;
}

int main()
{
    int output1[7];
    int input1[7] = {1, 2, 3, 4, 5, 51, 6};
    int len = (sizeof(input1) / sizeof(input1[0]));
    assert(1 == calculate(input1, output1, len, 3));
    assert(output1[5] == calculate_median(len, input1));
    printf("2/5 passed\n");

    int output2[4];
    int input2[4] = {1, 2, 6500, 4};
    len = (sizeof(input2) / sizeof(input2[0]));
    assert(-1 == calculate(input2, output2, len, 3));
    printf("3/5 passed\n");

    int output3[8];
    int input3[8] = {25,29,3,32,85,33,27,28};
    len = (sizeof(input3) / sizeof(input3[0]));
    assert( 1 == calculate(input3, output3, len, 1));
    assert( 85 == output3[4]);
    calculate(input3, output3, len, 3);
    printf("5/5 passed\n");
    return (0);
}