// Author: Christine Mahler
// MCT Assignment 5 - Question 1

// Select two of the sort algorithms we have discussed in class.
// 1. Code the selected algorithms.
// 2. Instrument your sort algorithms to calculate efficiency by gathering data on:
//    a. Time for algorithm to run.
//    b. Number of swaps.
//    c. Number of comparisons.
// 3. Download the Peak Wind speed at 80meter data for your birthday in 2013...
// 4. Copy and paste the data into a file.
// 5. Working from this data file, load the last column (wind speeds) of the comma delimited
// file into a one-dimensional array.
// 6. Run both of your instrumented algorithms again with the wind speed data you created.
// 7. Save the sorted data in a new file to be used in Question 2.
// 8. Display your results and discuss which algorithm performed better on your data set.

// ******************************************** INSERTION SORT ********************************************

#include <stdio.h> // standard input/output header
#include <time.h> // time header for clock() function

#define SIZE 1440 // define SIZE constant for us in array length

int main()
{
	double array[SIZE] = { 6.4296, 6.9721, 6.4947, 6.4513, 6.69, 6.5815, 6.1909, 5.9739, 5.9522, 6.039, 5.9956, 4.7587, 5.2795, 5.3663, 4.5851, 4.6068, 4.4115, 4.6502, 4.8021, 4.2596, 3.7388, 3.0878, 3.2831, 3.4784, 3.435, 3.2397, 2.1764, 2.0896, 2.4151, 2.8491, 3.0444, 1.9377, 3.0661, 3.0878, 3.0661, 2.8708, 2.9142, 2.8274, 2.8274, 3.7171, 3.8256, 3.1529, 3.7605, 3.7822, 3.4133, 4.5417, 4.3681, 4.3464, 3.3482, 3.2614, 3.8473, 3.4133, 3.1312, 5.0625, 7.2542, 5.9956, .1475, 6.256, 8.0571, 7.3193, 7.4712, 5.9088, 5.7352, 5.0625, 5.2144, 6.9938, 7.4061, 9.1421, 7.6882, 7.6665, 8.1222, 8.1005, 5.5833, 4.8455, 5.1493, 4.9323, 4.8455, 5.1927, 5.9522, 6.4296, 6.69, 6.9504, 10.032, 10.053, 9.9016, 8.9034, 7.8184, 7.2325, 5.7569, 6.69, 7.2325, 5.605, 5.0191, 4.6285, 4.4115, 3.9558, 2.784, 2.6755, 2.6104, 3.218, 3.652, 4.1294, 4.7804, 5.3446, 3.3048, 3.7171, 4.303, 3.9124, 2.8708, 2.1547, 3.435, 3.7171, 3.4133, 3.6954, 3.6086, 3.4784, 2.7623, 3.0444, 3.4784, 4.2596, 4.4549, 4.737, 5.0408, 3.8039, 3.869, 3.3916, 2.8491, 2.6321, 2.4151, 2.6538, 2.9359, 2.7406, 3.5652, 3.1095, 3.3699, 3.6303, 3.3048, 2.8925, 2.5019, 2.1547, 2.0028, 2.1981, 2.2415, 2.6538, 2.5236, 2.7623, 3.0444, 2.9793, 3.0227, 2.8925, 3.0878, 2.8925, 2.6104, 2.5453, 2.5453, 2.4585, 2.7406, 2.8708, 2.8925, 3.1095, 3.2614, 3.4784, 2.8708, 2.3717, 2.2632, 2.6972, 2.3934, 2.1113, 2.0245, 1.3301, 1.8509, 2.1113, 1.9594, 2.3934, 1.9594, 1.8292, 2.3717, 2.2198, 2.3717, 2.0028, 1.5905, 1.5688, 1.2433, 1.9594, 1.8075, 1.5037, 1.2433, 1.8292, 1.8509, 1.9594, 1.8075, 1.5254, 1.6339, 1.8075, 1.916, 2.0245, 1.8943, 1.699, 1.8943, 1.8075, 1.7858, 1.482, 1.1348, 1.0046, 1.0263, 0.7442, 0.3536, 0.4621, 0.3102, 0.3102, 0.5489, 0.8093, 0.9178, 0.7008, 0.8961, 1.0263, 1.1999, 1.265, 1.265, 1.3735, 1.3952, 1.2867, 1.1348, 1.5905, 1.5471, 1.6339, 1.5037, 1.482, 1.699, 1.7424, 1.6773, 1.6556, 1.4386, 1.5905, 1.4169, 1.3084, 1.265, 1.0046, 1.048, 1.3301, 1.3735, 1.4603, 1.699, 1.5905, 1.5905, 1.4603, 1.3301, 1.2216, 1.265, 1.3084, 1.3084, 1.4169, 1.2433, 1.1782, 1.5254, 1.482, 1.4169, 1.3952, 1.916, 1.8075, 2.1981, 2.1113, 2.0679, 2.0679, 2.133, 2.133, 2.1981, 2.1547, 2.1113, 2.1547, 2.2415, 2.1981, 2.0896, 2.133, 2.0245, 2.0679, 2.0679, 2.0896, 2.0245, 1.9377, 1.9377, 2.0462, 2.0028, 2.1764, 2.1547, 2.1981, 2.2415, 2.2198, 2.2632, 2.3934, 2.4151, 2.4585, 2.8491, 3.0878, 3.1529, 3.2614, 3.2397, 3.3699, 3.0878, 3.0661, 3.1312, 3.1529, 2.8925, 2.9576, 2.784, 2.8274, 2.8708, 2.784, 2.7189, 2.7623, 2.784, 3.0444, 3.5218, 3.6954, 3.7605, 3.7388, 3.7605, 3.7171, 3.5652, 3.5218, 3.1746, 2.8925, 2.8274, 2.8491, 2.7623, 2.6321, 2.567, 2.6104, 2.6538, 2.8491, 2.8708, 2.8057, 2.784, 2.7406, 2.4368, 2.4585, 2.4368, 2.4151, 2.3934, 2.2632, 2.2415, 2.2632, 2.3283, 2.3717, 2.35, 2.3934, 2.3717, 2.2198, 2.2632, 2.2415, 2.2632, 2.1547, 2.0679, 2.1113, 2.1547, 2.1764, 2.1981, 2.1764, 2.2415, 2.1547, 2.1113, 1.9811, 1.8943, 1.8943, 1.8943, 1.916, 1.8509, 1.8943, 1.916, 1.8075, 2.1764, 2.133, 2.2198, 2.2632, 2.3283, 2.2632, 2.1547, 2.3717, 2.3717, 2.5236, 2.2632, 2.0896, 2.1113, 2.2849, 2.1764, 2.1113, 2.0028, 1.8075, 2.2632, 2.3934, 2.3717, 2.1764, 2.1113, 2.2198, 2.3717, 2.5453, 2.6321, 2.2632, 2.3283, 2.0028, 2.2198, 2.2415, 2.0028, 2.0896, 1.7641, 1.7207, 1.8292, 1.7424, 1.6339, 1.5905, 1.5688, 1.5471, 1.6122, 1.7424, 1.9594, 1.9811, 1.9811, 1.9811, 1.9811, 1.9594, 2.0028, 1.916, 1.9377, 1.7424, 1.699, 1.916, 1.916, 1.916, 1.8726, 1.8943, 1.9811, 2.0245, 2.0028, 2.0028, 1.916, 1.9594, 1.9377, 2.0245, 2.4802, 2.4368, 2.3717, 2.2632, 2.5019, 2.0679, 2.0245, 2.5019, 2.5453, 2.8925, 2.7189, 2.6972, 2.9142, 2.5019, 2.1113, 2.0245, 2.35, 2.5019, 2.4585, 2.4802, 2.8274, 2.7189, 2.6538, 2.8274, 2.4802, 2.5236, 2.8274, 3.1095, 2.6755, 2.4368, 2.567, 2.5236, 2.5019, 2.5019, 2.5887, 2.6538, 2.2849, 2.1547, 2.3934, 2.0462, 2.133, 2.2198, 2.3283, 2.1981, 2.2198, 2.3934, 2.35, 2.3066, 2.2415, 2.1547, 2.1547, 2.0896, 2.2198, 2.3066, 2.5236, 2.6538, 2.5453, 2.6104, 2.7406, 2.5453, 2.3717, 2.3717, 2.2849, 2.4151, 2.4368, 2.4151, 2.4368, 2.3934, 2.4802, 2.4802, 2.5019, 2.5236, 2.7189, 2.567, 2.567, 2.6104, 2.6321, 2.6321, 2.6755, 2.7623, 2.7189, 3.001, 2.5236, 2.5019, 2.6755, 2.5453, 2.4368, 2.5236, 2.5453, 2.4368, 2.6538, 2.6755, 2.8057, 2.9359, 2.8491, 2.6321, 2.2415, 2.3717, 2.3283, 2.4802, 2.1113, 2.0462, 2.567, 2.1547, 2.3066, 1.8726, 1.8726, 2.0462, 2.4151, 1.9811, 2.2632, 2.567, 1.916, 1.8726, 2.2198, 2.1547, 3.3916, 3.001, 2.4368, 2.5019, 2.7189, 2.6755, 2.2849, 3.0444, 3.0661, 2.8708, 3.3482, 3.3048, 3.3482, 2.6755, 3.3699, 3.2614, 4.4115, 3.5652, 3.5652, 3.2614, 3.2831, 3.4784, 3.8256, 3.5218, 3.5869, 3.652, 4.303, 3.4784, 4.1077, 4.0643, 3.5218, 3.2397, 3.7171, 3.8473, 3.8256, 3.6737, 3.3699, 3.6303, 4.8889, 4.8455, 4.52, 3.9992, 3.8039, 3.8256, 3.4567, 3.9558, 3.5652, 3.8256, 3.6737, 4.2813, 4.4115, 3.6303, 4.2162, 4.3464, 4.0209, 3.9992, 3.3048, 4.1077, 4.0426, 4.3681, 4.0643, 4.3464, 4.2379, 4.6719, 3.8907, 4.2596, 3.8473, 4.7587, 5.0408, 5.3012, 4.7804, 4.4332, 4.6502, 4.5417, 4.0643, 3.6954, 4.2813, 4.8455, 4.5851, 4.8455, 3.9775, 4.3247, 3.9992, 4.8021, 4.086, 4.0426, 3.9124, 3.3482, 3.7605, 4.7587, 4.4983, 5.1927, 3.6954, 3.3048, 4.7587, 4.3464, 4.9106, 3.9341, 3.9775, 4.1294, 4.2596, 4.8021, 4.6285, 4.4332, 4.4549, 5.0191, 4.954, 5.0408, 4.7587, 4.8889, 5.0408, 6.5815, 5.9739, 4.7804, 5.1059, 4.7587, 5.1493, 5.7352, 6.1692, 4.2162, 5.1927, 6.3645, 5.9522, 4.4332, 4.8021, 5.8871, 6.1475, 6.4947, 5.5182, 5.3012, 5.4314, 6.3428, 6.2994, 7.1891, 5.7352, 5.9522, 5.0191, 5.0625, 5.7786, 6.3428, 5.9088, 5.9088, 5.4748, 5.4748, 5.4748, 6.6683, 7.3627, 6.2777, 6.1692, 6.256, 5.9305, 7.341, 6.6683, 8.1873, 6.9504, 6.039, 6.4513, 6.2994, 6.3645, 6.5164, 8.7081, 7.7967, 7.2325, 7.2108, 7.6231, 7.558, 7.4278, 6.8202, 8.1656, 9.1638, 7.2976, 7.1023, 7.7316, 8.1439, 8.1439, 7.9269, 8.2524, 7.124, 6.7334, 6.0173, 6.9938, 7.2759, 7.9486, 7.4712, 7.6231, 9.4242, 6.69, 7.8401, 7.2108, 7.3627, 7.0806, 7.124, 6.7768, 8.7298, 8.426, 7.7316, 8.3609, 7.2108, 8.3826, 7.9486, 7.5363, 8.643, 7.1891, 6.8202, 7.5363, 8.0571, 9.945, 7.6014, 8.1656, 8.0788, 7.1674, 8.5128, 7.7967, 8.2958, 7.8835, 7.4929, 7.6882, 7.7316, 9.1421, 7.8835, 6.5815, 7.775, 9.4676, 7.5363, 6.4513, 7.2759, 9.511, 9.0336, 7.6665, 6.8419, 6.3645, 7.992, 8.209, 7.0155, 7.2759, 7.7099, 6.5164, 6.907, 7.8401, 8.2524, 7.558, 7.6014, 7.6882, 8.8166, 6.7768, 7.2976, 6.6466, 7.0589, 8.4477, 6.8853, 6.6032, 5.388, 7.1457, 7.4495, 7.0589, 6.256, 6.256, 6.6466, 5.8654, 6.2777, 6.2994, 6.7334, 6.8419, 6.1909, 7.1674, 6.7551, 6.9721, 7.7967, 6.9287, 8.86, 7.5797, 7.6882, 6.4079, 7.1674, 6.7334, 8.5996, 7.9486, 7.9269, 6.8419, 7.3844, 7.2976, 7.558, 7.2325, 6.8202, 7.0372, 6.3645, 7.3193, 8.1656, 7.1457, 6.9721, 7.2542, 7.1891, 6.7768, 6.1475, 6.4947, 7.1023, 7.124, 7.6665, 6.3862, 6.1258, 7.0155, 6.5815, 5.6267, 7.4712, 6.2994, 6.4079, 6.5164, 7.4929, 8.1222, 6.5164, 6.0824, 6.1041, 7.2108, 7.8835, 9.1638, 7.7316, 7.341, 7.4495, 7.4712, 6.3862, 7.3844, 8.7515, 7.8835, 6.5815, 6.5164, 7.558, 7.7316, 7.1023, 6.2343, 6.1258, 6.256, 6.9287, 6.7985, 6.1258, 6.1692, 5.4748, 5.4965, 6.6249, 7.4278, 6.9938, 6.1475, 6.6683, 5.5399, 5.6701, 6.5381, 6.8419, 5.7786, 6.5598, 6.0173, 6.9504, 6.2343, 6.2343, 5.9739, 5.7786, 6.3645, 7.2542, 6.8853, 6.69, 6.6249, 6.9721, 6.3862, 6.7551, 6.9504, 6.039, 6.4079, 6.4947, 7.0589, 6.5381, 6.0607, 6.9938, 6.7768, 6.5381, 6.69, 5.7569, 6.8636, 6.0824, 6.2126, 6.4513, 7.4712, 6.473, 5.8003, 5.9956, 6.0607, 5.605, 6.8202, 5.9088, 5.8437, 5.9088, 5.5399, 5.6267, 5.2578, 6.039, 5.4965, 6.3862, 6.473, 5.7352, 6.1909, 6.7334, 5.4531, 5.9956, 5.822, 6.473, 5.9522, 5.8654, 5.9088, 5.8654, 5.6267, 5.4965, 5.9305, 5.8871, 5.3446, 5.6484, 5.4531, 5.5182, 4.954, 5.1059, 5.4748, 5.2144, 5.8871, 5.4097, 5.5616, 5.605, 5.5833, 5.6701, 5.5399, 5.605, 5.2795, 5.605, 5.6484, 5.5616, 5.2795, 5.3663, 5.2361, 5.6918, 5.3663, 5.4097, 5.1059, 4.954, 5.2361, 5.9305, 5.4314, 5.2578, 4.8672, 5.1276, 5.2361, 5.8437, 5.5399, 4.9974, 5.3446, 5.3229, 5.1493, 5.4748, 5.388, 5.388, 5.605, 5.2795, 5.6701, 5.7135, 5.9305, 5.9088, 5.8003, 5.9305, 5.9956, 5.8437, 5.9088, 6.0173, 6.2994, 6.3211, 6.3211, 6.039, 6.0607, 6.1041, 6.3428, 6.5164, 6.4296, 6.3211, 5.822, 6.0173, 5.8654, 5.4097, 5.6267, 5.7786, 5.9088, 6.1909, 6.5381, 6.8202, 7.124, 7.1674, 7.4061, 7.0155, 6.9287, 6.907, 7.0372, 6.9504, 7.1457, 7.0372, 6.7551, 6.4296, 6.69, 6.7334, 6.5598, 6.5815, 6.5815, 6.5598, 6.7334, 6.3428, 6.5815, 6.6032, 6.8636, 6.9287, 6.7768, 6.8636, 7.0806, 6.7768, 6.7768, 6.8636, 6.6683, 6.7768, 6.69, 6.6466, 6.5598, 6.5815, 6.6466, 6.6249, 6.69, 6.5598, 6.4513, 6.4513, 6.4079, 5.8654, 6.1258, 6.3211, 6.3645, 6.1041, 6.0607, 6.0607, 5.9739, 5.8871, 5.9088, 5.7786, 6.1258, 6.2126, 5.5399, 5.6918, 5.6918, 5.4965, 5.388, 5.2144, 5.5182, 5.9088, 5.7135, 5.6701, 5.4314, 5.2361, 5.2795, 5.605, 5.5399, 5.3229, 5.1493, 5.2144, 5.3012, 5.6918, 5.2795, 5.171, 5.1276, 5.171, 5.388, 5.1493, 5.0408, 5.0842, 4.9106, 4.5417, 4.3898, 4.3898, 4.6502, 4.4983, 4.1294, 4.3681, 3.9775, 4.303, 4.3464, 4.2162, 4.303, 4.4115, 4.52, 4.1945, 4.5851, 4.1511, 4.4115, 4.5634, 4.0426, 3.869, 3.8907, 4.1728, 4.0643, 4.0643, 3.9558, 3.8473, 3.8907, 4.0209, 4.2379, 4.0643, 3.9775, 3.9558, 3.9775, 3.8473, 4.0209, 3.6954, 3.435, 3.9124, 3.869, 3.8039, 3.5652, 3.9775, 4.1294, 3.8256, 4.1728, 4.0426, 4.2162, 3.9558, 4.0426, 3.9558, 3.6954, 3.8039, 3.8473, 3.4133, 3.6086, 3.6303, 3.3048, 3.3265, 3.1746, 3.4784, 3.7822, 3.8039, 3.435, 3.3916, 3.2831, 3.1963, 3.3916, 3.5869, 2.9142, 2.9793, 2.9576, 3.0444, 2.9142, 3.1529, 3.6954, 3.652, 3.5869, 3.3048, 3.6954, 3.652, 3.9992, 3.9775, 3.7171, 3.8473, 3.7605, 3.6303, 3.3699, 3.9341, 3.1312, 3.2614, 2.7623, 2.7189, 2.4585, 2.6104, 3.0661, 2.8708, 3.1095, 2.9359, 2.9142, 2.3934, 2.0462, 2.4151, 1.8943, 1.6773, 1.9811, 2.5236, 1.699, 2.0245, 2.2849, 2.567, 1.6773, 1.4386, 1.4603, 1.4169, 1.6122, 1.265, 1.5471, 1.3952, 1.3952, 1.3952, 1.2433, 2.1547, 1.4386, 1.3518, 1.3518, 1.6122, 1.4169, 1.7207, 1.7641, 1.9377, 2.35, 2.5019, 2.8274, 2.7189, 2.8057, 2.9142, 2.784, 2.7189, 2.784, 2.784, 2.784, 2.5019, 2.6104, 2.5453, 2.3717, 2.3066, 2.2849, 2.2198, 2.2415, 1.9377, 1.699, 1.3952, 1.3518, 1.4603, 1.1565, 1.0263, 0.9178, 0.8093, 0.8093, 0.9829, 1.1782, 1.1348, 1.048, 0.8527, 0.5706, 0.4838, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.4404, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.8961, 1.3301, 1.5688, 1.5471, 2.0028, 2.0245, 2.2198, 2.1764, 2.1764, 2.133, 1.7641, 1.3735, 1.6773, 2.0028, 2.8491, 2.5019, 2.6972, 2.35, 2.5019, 2.6972, 2.5019, 2.3934, 2.2198, 1.916, 1.8726, 1.916, 2.3717, 2.8708, 2.7623, 2.5019, 2.3283, 2.1547, 2.133, 2.1764, 2.2415, 2.4585, 2.8057, 2.0896, 2.4151, 1.9811, 2.133, 1.9377, 1.916, 1.6556, 1.1131, 0.7442, 0.6357, 1.1131, 1.3301, 1.2867, 1.7858, 1.5471, 2.0028, 1.8726, 1.8943, 1.7424, 2.1113, 2.2198, 2.1547, 1.8726, 1.7424, 1.5905, 1.5254, 1.5471, 1.5471, 1.482, 1.4603, 1.3301, 1.5905, 1.6339, 1.6122, 1.8075, 1.6556, 1.5254, 1.5037, 1.6122, 1.2433, 1.0914, 1.048, 1.5905, 1.6556, 1.482, 1.4169, 1.3735, 1.4169, 1.5471, 1.3952, 0.9395, 1.6556, 1.2216, 1.048, 0.9395, 1.048, 1.0263, 0.5923, 0.9612, 0.9612, 0.8093, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.3102, 0.3319, 1.0263, 1.3518, 0.5706, 0.3102, 0.3102, 0.3102, 0.3102, 0.3319, 1.1782, 0.5055, 0.3102, 0.3102, 0.3319, 0.6357, 0.9612, 0.614, 0.3102, 0.3319, 2.1764, 2.6321, 3.0444, 2.8491, 4.086, 3.8907, 2.8274, 3.652, 3.7388 };
	int comparisons = 0; // declare and initialize comparisons counter
	int swaps = 0; // declare and initialize swaps counter
	double minimum; // declare minimum variable for storing minimum in event of swap
	int position; // delcare position variable for storing position in event of swap
	clock_t startTime; // declare starTime variable for measuring execution time
	clock_t endTime; // declare endTime variable for measuring execution time
	double totalTime; // declare totalTime for measuring execution time
	int i; // declare counter for comparisons
	int j; // declare counter for passes

	startTime = clock(); // set start time

	// iterate through entire array SIZE - 1 passes to order by minimums of remaining unsorted portion of array

	for (j = 0; j < SIZE; j++) {
		minimum = array[j]; // set minimum equal to first element of remaining unsorted array
		position = j; // set position equal to first index of remaining unsorted array
		for (i = j + 1; i < SIZE; i++) {
			if (array[i] < minimum) { // compare minimum to other array elements
				minimum = array[i]; // set minimum to new value if new minimum is found
				position = i; // set position to new value if new minimum is found
				comparisons++; // increment comparisons by 1
			}
		}
		if (position != j) {
			array[position] = array[j]; // swap array elements
			array[j] = minimum; // set j element of array to minimum value
			swaps++; // increments swaps by 1
		}
	}

	endTime = clock(); // set end time

	totalTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC; // calculate total time to execute

	// print array results

	for (i = 0; i < SIZE; i++) {
		if (i == 0) {
			printf("{%1.4f, ", array[i]); // formatting for first array element
		}
		else if (i == SIZE - 1) {
			printf("%1.4f}\n", array[i]); // formatting for last array element
		}
		else {
			printf("%1.4f, ", array[i]); // formatting for all other array elements
		}
	}

	// print performance results

	printf("\nThe total number of swaps is: %d", swaps);
	printf("\nThe total number of comparisons is: %d", comparisons);
	printf("\nThe total time to execute is: %f seconds\n", totalTime);

	system("pause"); // pause to view results
	return 0;
}