// #include "stdio.h"
// #include "stdlib.h"
// #include "stdint.h"
// #include "math.h"

// #define M_PI 3.14159265358979323846

// double cos_core (double x)
// {
//   double x8, x4, x2;
//   x2 = x * x;
//   x4 = x2 * x2;
//   x8 = x4 * x4;
//   /* evaluate polynomial using Estrin's scheme */
//   return (-2.7236370439787708e-7 * x2 + 2.4799852696610628e-5) * x8 +
//          (-1.3888885054799695e-3 * x2 + 4.1666666636943683e-2) * x4 +
//          (-4.9999999999963024e-1 * x2 + 1.0000000000000000e+0);
// }

// double sin_core (double x)
// {
//   double x4, x2, t;
//   x2 = x * x;
//   x4 = x2 * x2;
//   /* evaluate polynomial using a mix of Estrin's and Horner's scheme */
//   return ((2.7181216275479732e-6 * x2 - 1.9839312269456257e-4) * x4 + 
//           (8.3333293048425631e-3 * x2 - 1.6666666640797048e-1)) * x2 * x + x;
// }

// double mod_2pi(double value)
// {
//     double new_val = value;
//     while (new_val > 2 * M_PI || new_val < -2 * M_PI)
//     {
//         if (new_val > 2 * M_PI)
//         {
//             new_val -= 2 * M_PI;
//         }
//         else if (new_val < -2 * M_PI)
//         {
//             new_val += 2 * M_PI;
//         }
//     }
//     return new_val;
// }

// double conv_value(double value)
// {
//     double new_val = mod_2pi(value);
//     if (value > 3* M_PI / 2)
//     {
//         new_val = new_val - 2*M_PI;
//     }
//     else if (3* M_PI /2 > new_val && new_val > M_PI / 2)
//     {
//         new_val = M_PI - new_val;
//     }
//     if (new_val >= -M_PI/4 && new_val <= M_PI/4)
//     {
//         return cos_core(new_val);
//     }
//     else
//     {
//         return sin_core(M_PI/2 - new_val);
//     }
// }

// int main(int argc, char* argv[])
// {
//     int32_t value_init = (int32_t)atoi(argv[1]);
//     int32_t compteur = -value_init;
//     double value = M_PI * compteur / (4*value_init);
//     float value_cos = 0;
//     while (compteur < value_init)
//     {
//         compteur++;
//         // value_cos = cos_core(value);
//         // printf("cos(%f) = %f\n", value, value_cos);
//         value_cos = conv_value(value);
//         printf("cos(%f) = %f\t", value, value_cos);
//         printf("cos(%f) = %f\n", value, cos(value));
//         value = compteur;
//         // value = M_PI * compteur / (4 * value_init);
//     }
// }