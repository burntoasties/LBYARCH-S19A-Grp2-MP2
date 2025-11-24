
# [GROUP 2] LBYARCH S19-A

**x86-C Interface Program - Dot Product**, the kernel is to perform a dot product between vector A and vector B and place the result in *sdot*.\
Scalar variable *n* (integer) contains the length of the vector;  Vectors A and B are both single-precision float. Scalar *sdot* is a single-precision float.\
\
**Process:** $sdot = \sum_{i=1}^{n} a_i b_i = a_1 b_1 + a_2 b_2 + \dots + a_n b_n$



## Authors

- Sophia Kylie G. Avelino [[@Gl1tch8](https://github.com/Gl1tch8)]
- Anton Miguel G. Borromeo [[@burntoasties](https://github.com/burntoasties)]


## Output and Analysis

*Run 1*:
![f414d51b-2464-46d5-9bf1-80613a8c794a](https://github.com/user-attachments/assets/b1363d6d-7beb-4259-8030-a67a5bc5b74e)

*Run 2*:

![a157bc6a-5b66-4eef-8fff-c82fab2b3e2f](https://github.com/user-attachments/assets/1a151f9d-f713-4d3c-a02d-6a6b38241381)

For the vector length of $2^{20}$ and $2^{24}$, it can be seen that *ASM* had a longer execution time in milliseconds compared to *C*. However, this difference is extremely small, and thus can be negligible. In the third case where the vector length is $2^{30}$, the time it takes for *ASM* to finish running is almost 200 milliseconds faster than C. It can be seen that with a bigger vector length, the difference in speed between the 2 kernels also becomes more significant, with ASM coming out as faster.

## Demo

[![Thumbnail](https://github.com/user-attachments/assets/412c0e47-1b72-4ee3-911e-474be28f83e6)](https://www.youtube.com/watch?v=T7Nu7VATpMo "LBYARCH MP")
