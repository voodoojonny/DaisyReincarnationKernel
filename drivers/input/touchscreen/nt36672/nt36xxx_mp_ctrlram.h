/*
 * Copyright (C) 2010 - 2017 Novatek, Inc.
 * Copyright (C) 2018 XiaoMi, Inc.
 *
 * $Revision: 15234 $
 * $Date: 2017-08-09 11:34:54 +0800 (週三, 09 八月 2017) $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */

#if NVT_TOUCH_MP

static uint32_t IC_X_CFG_SIZE = 18;
static uint32_t IC_Y_CFG_SIZE = 32;
static uint32_t IC_KEY_CFG_SIZE = 4;
static uint32_t X_Channel = 18;
static uint32_t Y_Channel = 32;
static uint32_t Key_Channel = TOUCH_KEY_NUM;
static uint8_t AIN_X[40] = {17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
static uint8_t AIN_Y[40] = {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
#if TOUCH_KEY_NUM > 0
static uint8_t AIN_KEY[8] = {0, 1, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
#endif /* #if TOUCH_KEY_NUM > 0 */

static int32_t PS_Config_Lmt_Short_Rawdata_P = 13500;
static int32_t PS_Config_Lmt_Short_Rawdata_N = 11500;
static int32_t PS_Config_Lmt_Key_Short_Rawdata_P = 20000;
static int32_t PS_Config_Lmt_Key_Short_Rawdata_N = 11550;
static int32_t PS_Config_Lmt_Short_Diff_P = 6300;
static int32_t PS_Config_Lmt_Short_Diff_N;
static int32_t PS_Config_Lmt_Key_Short_Diff_P = 6300;
static int32_t PS_Config_Lmt_Key_Short_Diff_N;
static int32_t PS_Config_Lmt_Short_Base_P = 2000;
static int32_t PS_Config_Lmt_Short_Base_N = -2000;
static int32_t PS_Config_Lmt_Key_Short_Base_P = 2000;
static int32_t PS_Config_Lmt_Key_Short_Base_N = -2000;

static int32_t PS_Config_Lmt_Open_Rawdata_P[40 * 40] = {
10288, 10571, 10538, 10516, 10489, 10469, 10460, 10489, 10509, 10474, 10495, 10470, 10454, 10454, 10458, 10461, 10475, 10402,
10203, 10356, 10326, 10308, 10287, 10276, 10272, 10295, 10305, 10273, 10287, 10268, 10256, 10250, 10251, 10249, 10260, 10258,
10262, 10393, 10367, 10350, 10333, 10337, 10322, 10344, 10348, 10307, 10320, 10298, 10289, 10277, 10279, 10275, 10283, 10281,
10178, 10320, 10290, 10273, 10261, 10258, 10253, 10275, 10276, 10252, 10264, 10245, 10234, 10230, 10219, 10215, 10226, 10208,
10199, 10348, 10307, 10291, 10285, 10278, 10277, 10299, 10299, 10279, 10290, 10270, 10260, 10248, 10245, 10242, 10263, 10234,
10137, 10276, 10233, 10217, 10215, 10216, 10210, 10233, 10231, 10199, 10208, 10189, 10178, 10165, 10164, 10160, 10182, 10153,
10151, 10284, 10241, 10226, 10228, 10225, 10224, 10247, 10246, 10235, 10245, 10225, 10215, 10214, 10202, 10196, 10218, 10190,
10067, 10186, 10153, 10139, 10143, 10140, 10140, 10164, 10162, 10140, 10149, 10127, 10118, 10109, 10106, 10100, 10114, 10093,
10095, 10205, 10188, 10167, 10171, 10167, 10168, 10191, 10189, 10152, 10162, 10139, 10130, 10120, 10119, 10126, 10124, 10106,
9997, 10101, 10083, 10065, 10068, 10065, 10068, 10092, 10090, 10072, 10080, 10057, 10048, 10049, 10038, 10045, 10043, 10026,
10000, 10100, 10082, 10068, 10068, 10068, 10072, 10097, 10094, 10069, 10076, 10053, 10044, 10037, 10035, 10041, 10041, 10021,
9917, 10011, 9988, 9983, 9993, 9983, 9987, 10012, 10009, 9977, 9984, 9959, 9951, 9942, 9943, 9948, 9949, 9930,
9910, 9999, 9969, 9983, 9977, 9974, 9980, 10005, 10001, 9986, 9994, 9969, 9960, 9965, 9961, 9949, 9962, 9938,
9811, 9892, 9867, 9884, 9870, 9871, 9878, 9903, 9899, 9881, 9888, 9862, 9853, 9850, 9861, 9844, 9861, 9832,
9823, 9900, 9880, 9898, 9896, 9884, 9893, 9917, 9911, 9876, 9881, 9856, 9847, 9843, 9857, 9839, 9862, 9826,
9708, 9779, 9763, 9780, 9769, 9769, 9777, 9800, 9794, 9784, 9790, 9764, 9755, 9765, 9768, 9752, 9777, 9735,
9690, 9758, 9747, 9750, 9750, 9752, 9760, 9784, 9780, 9758, 9763, 9739, 9732, 9734, 9732, 9728, 9759, 9711,
9597, 9661, 9652, 9658, 9666, 9668, 9662, 9685, 9681, 9652, 9657, 9632, 9640, 9629, 9631, 9631, 9665, 9610,
9572, 9636, 9628, 9634, 9632, 9632, 9640, 9661, 9656, 9641, 9646, 9623, 9620, 9631, 9623, 9624, 9659, 9598,
9458, 9521, 9513, 9518, 9514, 9519, 9537, 9547, 9542, 9529, 9533, 9522, 9510, 9511, 9512, 9518, 9554, 9485,
9449, 9511, 9504, 9509, 9517, 9512, 9529, 9538, 9533, 9494, 9498, 9485, 9477, 9474, 9478, 9489, 9523, 9448,
9316, 9380, 9371, 9376, 9376, 9381, 9399, 9406, 9401, 9394, 9398, 9389, 9380, 9387, 9380, 9396, 9430, 9347,
9282, 9348, 9339, 9343, 9341, 9350, 9359, 9374, 9368, 9349, 9353, 9335, 9336, 9338, 9338, 9357, 9391, 9301,
9179, 9245, 9237, 9242, 9252, 9249, 9255, 9285, 9265, 9236, 9250, 9218, 9225, 9226, 9229, 9248, 9283, 9186,
9131, 9198, 9190, 9196, 9198, 9205, 9210, 9239, 9219, 9208, 9224, 9192, 9199, 9201, 9207, 9228, 9261, 9158,
9015, 9084, 9077, 9082, 9082, 9093, 9098, 9126, 9105, 9094, 9110, 9078, 9086, 9088, 9099, 9120, 9152, 9042,
8984, 9054, 9046, 9052, 9063, 9062, 9067, 9088, 9072, 9046, 9060, 9032, 9041, 9043, 9057, 9078, 9111, 8989,
8806, 8877, 8871, 8877, 8878, 8882, 8889, 8903, 8902, 8903, 8892, 8872, 8881, 8883, 8903, 8923, 8955, 8828,
8763, 8836, 8830, 8836, 8835, 8838, 8845, 8859, 8861, 8858, 8837, 8818, 8826, 8832, 8853, 8874, 8906, 8769,
8673, 8746, 8741, 8746, 8751, 8743, 8749, 8764, 8765, 8751, 8726, 8705, 8711, 8724, 8747, 8767, 8797, 8650,
8633, 8707, 8701, 8706, 8696, 8697, 8706, 8719, 8716, 8725, 8697, 8677, 8694, 8703, 8726, 8747, 8779, 8621,
10520, 10245, 10233, 10231, 10209, 10213, 10224, 10243, 10220, 10229, 10211, 10185, 10199, 10226, 10252, 10278, 10309, 9059
#if TOUCH_KEY_NUM > 0
, 13000,13000,13000
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_Open_Rawdata_N[40 * 40] = {
8578, 8744, 8725, 8712, 8696, 8684, 8679, 8696, 8708, 8687, 8699, 8685, 8675, 8675, 8678, 8679, 8688, 8645,
8528, 8617, 8600, 8590, 8577, 8571, 8568, 8582, 8588, 8569, 8577, 8566, 8559, 8556, 8556, 8555, 8561, 8560,
8562, 8640, 8624, 8614, 8604, 8607, 8598, 8611, 8613, 8589, 8597, 8584, 8578, 8571, 8572, 8570, 8575, 8574,
8513, 8597, 8579, 8569, 8562, 8560, 8557, 8570, 8571, 8556, 8564, 8553, 8546, 8544, 8537, 8535, 8541, 8531,
8525, 8613, 8589, 8579, 8576, 8572, 8571, 8584, 8584, 8572, 8579, 8567, 8561, 8554, 8553, 8551, 8563, 8546,
8489, 8571, 8546, 8536, 8535, 8536, 8532, 8546, 8544, 8525, 8531, 8519, 8513, 8506, 8505, 8502, 8515, 8499,
8497, 8576, 8550, 8541, 8543, 8541, 8540, 8554, 8553, 8547, 8553, 8541, 8535, 8534, 8527, 8524, 8537, 8520,
8448, 8518, 8499, 8490, 8493, 8491, 8491, 8505, 8504, 8491, 8496, 8483, 8478, 8472, 8471, 8467, 8476, 8463,
8464, 8529, 8519, 8507, 8509, 8507, 8507, 8521, 8520, 8498, 8504, 8491, 8485, 8479, 8478, 8483, 8482, 8471,
8407, 8468, 8458, 8447, 8449, 8447, 8448, 8463, 8461, 8451, 8456, 8442, 8437, 8438, 8431, 8435, 8434, 8424,
8409, 8467, 8457, 8449, 8448, 8449, 8451, 8466, 8464, 8449, 8454, 8440, 8435, 8430, 8429, 8433, 8433, 8421,
8360, 8415, 8402, 8399, 8405, 8399, 8401, 8416, 8414, 8395, 8399, 8384, 8380, 8375, 8375, 8378, 8379, 8368,
8356, 8408, 8390, 8398, 8395, 8393, 8397, 8411, 8409, 8401, 8405, 8390, 8385, 8388, 8386, 8379, 8386, 8372,
8297, 8345, 8330, 8340, 8332, 8333, 8337, 8352, 8349, 8339, 8343, 8328, 8322, 8321, 8327, 8317, 8327, 8310,
8304, 8350, 8338, 8349, 8347, 8340, 8346, 8360, 8357, 8336, 8339, 8324, 8319, 8316, 8325, 8314, 8328, 8306,
8237, 8279, 8269, 8279, 8273, 8273, 8277, 8291, 8288, 8282, 8285, 8270, 8265, 8270, 8272, 8263, 8278, 8253,
8227, 8266, 8260, 8262, 8262, 8263, 8268, 8282, 8280, 8266, 8270, 8255, 8251, 8252, 8251, 8249, 8267, 8239,
8172, 8209, 8204, 8208, 8212, 8214, 8210, 8224, 8221, 8204, 8207, 8193, 8197, 8191, 8192, 8192, 8212, 8180,
8157, 8195, 8190, 8193, 8192, 8193, 8197, 8210, 8207, 8198, 8201, 8187, 8186, 8192, 8187, 8188, 8208, 8172,
8090, 8127, 8123, 8126, 8123, 8126, 8137, 8143, 8140, 8132, 8134, 8128, 8121, 8121, 8122, 8126, 8147, 8106,
8085, 8122, 8117, 8120, 8125, 8122, 8132, 8137, 8135, 8111, 8114, 8106, 8101, 8100, 8102, 8109, 8129, 8085,
8007, 8044, 8039, 8042, 8042, 8045, 8056, 8060, 8057, 8053, 8055, 8050, 8044, 8048, 8044, 8054, 8074, 8025,
7987, 8025, 8020, 8023, 8022, 8027, 8032, 8041, 8038, 8027, 8028, 8018, 8019, 8020, 8020, 8031, 8051, 7998,
7926, 7966, 7961, 7964, 7970, 7968, 7971, 7989, 7977, 7960, 7968, 7950, 7954, 7954, 7956, 7967, 7988, 7931,
7898, 7938, 7933, 7936, 7937, 7942, 7945, 7962, 7950, 7944, 7953, 7934, 7938, 7939, 7943, 7955, 7975, 7914,
7830, 7871, 7867, 7870, 7869, 7876, 7879, 7895, 7883, 7877, 7886, 7867, 7872, 7873, 7880, 7892, 7911, 7846,
7812, 7853, 7849, 7852, 7858, 7858, 7861, 7873, 7864, 7848, 7857, 7840, 7846, 7847, 7855, 7867, 7886, 7815,
7708, 7749, 7746, 7749, 7750, 7752, 7756, 7765, 7764, 7765, 7758, 7746, 7751, 7752, 7764, 7776, 7795, 7720,
7682, 7725, 7722, 7725, 7724, 7726, 7730, 7738, 7740, 7738, 7726, 7714, 7719, 7723, 7735, 7747, 7766, 7685,
7629, 7672, 7669, 7672, 7675, 7670, 7674, 7683, 7683, 7675, 7660, 7648, 7652, 7659, 7673, 7684, 7702, 7616,
7606, 7649, 7646, 7648, 7643, 7643, 7649, 7656, 7655, 7660, 7643, 7632, 7642, 7647, 7660, 7673, 7692, 7599,
8714, 8553, 8545, 8545, 8531, 8534, 8540, 8551, 8538, 8543, 8533, 8518, 8525, 8542, 8556, 8572, 8590, 7856
#if TOUCH_KEY_NUM > 0
, 6500,6500,6500
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_FW_Rawdata_P[40 * 40] = {
1126, 1131, 1127, 1122, 1126, 1127, 1128, 1123, 1125, 1130, 1119, 1128, 1127, 1117, 1119, 1130, 1120, 1127,
1125, 1129, 1126, 1118, 1133, 1125, 1125, 1123, 1127, 1122, 1126, 1127, 1124, 1126, 1122, 1119, 1123, 1124,
1123, 1123, 1125, 1125, 1124, 1123, 1123, 1122, 1126, 1128, 1120, 1123, 1120, 1125, 1120, 1123, 1122, 1121,
1123, 1121, 1128, 1123, 1122, 1128, 1123, 1124, 1123, 1121, 1125, 1122, 1120, 1124, 1121, 1124, 1127, 1124,
1130, 1126, 1129, 1127, 1124, 1122, 1124, 1128, 1121, 1126, 1120, 1129, 1118, 1119, 1120, 1137, 1121, 1122,
1126, 1124, 1131, 1117, 1129, 1122, 1127, 1120, 1119, 1125, 1120, 1123, 1122, 1121, 1118, 1126, 1125, 1127,
1125, 1122, 1131, 1125, 1123, 1126, 1124, 1118, 1118, 1126, 1122, 1124, 1124, 1129, 1121, 1124, 1123, 1120,
1128, 1128, 1122, 1129, 1121, 1128, 1129, 1119, 1120, 1118, 1118, 1123, 1125, 1122, 1126, 1121, 1129, 1126,
1125, 1126, 1123, 1118, 1123, 1117, 1119, 1118, 1125, 1122, 1125, 1127, 1122, 1126, 1120, 1123, 1123, 1123,
1126, 1129, 1124, 1128, 1119, 1127, 1119, 1126, 1118, 1125, 1123, 1121, 1121, 1122, 1121, 1127, 1122, 1130,
1126, 1123, 1125, 1127, 1121, 1121, 1124, 1128, 1120, 1119, 1124, 1118, 1126, 1121, 1123, 1123, 1126, 1119,
1130, 1129, 1124, 1132, 1123, 1123, 1121, 1127, 1118, 1125, 1126, 1122, 1131, 1120, 1127, 1127, 1121, 1128,
1125, 1128, 1130, 1128, 1124, 1129, 1122, 1123, 1125, 1124, 1128, 1122, 1123, 1120, 1124, 1123, 1123, 1122,
1124, 1129, 1125, 1129, 1129, 1127, 1123, 1123, 1129, 1124, 1123, 1121, 1125, 1121, 1126, 1123, 1124, 1125,
1127, 1128, 1126, 1122, 1129, 1123, 1128, 1130, 1130, 1123, 1132, 1125, 1130, 1128, 1130, 1119, 1128, 1123,
1127, 1127, 1128, 1127, 1126, 1126, 1126, 1128, 1129, 1125, 1129, 1128, 1129, 1126, 1130, 1122, 1125, 1120,
1125, 1126, 1126, 1129, 1129, 1127, 1126, 1126, 1127, 1131, 1127, 1132, 1126, 1125, 1121, 1131, 1122, 1121,
1127, 1129, 1131, 1121, 1124, 1130, 1123, 1131, 1135, 1122, 1126, 1133, 1135, 1133, 1129, 1130, 1125, 1124,
1118, 1122, 1131, 1120, 1126, 1125, 1133, 1134, 1136, 1133, 1130, 1128, 1127, 1128, 1128, 1132, 1127, 1126,
1127, 1126, 1128, 1132, 1125, 1129, 1126, 1128, 1124, 1127, 1128, 1131, 1126, 1129, 1122, 1128, 1128, 1126,
1120, 1125, 1123, 1126, 1125, 1124, 1128, 1128, 1133, 1129, 1127, 1127, 1124, 1129, 1118, 1128, 1128, 1121,
1124, 1126, 1125, 1127, 1124, 1128, 1130, 1125, 1130, 1127, 1125, 1127, 1126, 1123, 1128, 1123, 1128, 1130,
1130, 1125, 1124, 1122, 1122, 1126, 1127, 1129, 1123, 1127, 1126, 1132, 1123, 1126, 1122, 1128, 1122, 1120,
1120, 1124, 1125, 1125, 1126, 1127, 1117, 1127, 1126, 1126, 1123, 1127, 1124, 1125, 1127, 1123, 1119, 1119,
1125, 1132, 1127, 1135, 1124, 1128, 1125, 1116, 1131, 1126, 1128, 1122, 1129, 1121, 1127, 1127, 1121, 1125,
1131, 1128, 1125, 1127, 1123, 1128, 1124, 1118, 1126, 1126, 1124, 1128, 1128, 1129, 1120, 1124, 1123, 1126,
1127, 1122, 1126, 1123, 1129, 1123, 1127, 1129, 1123, 1122, 1125, 1119, 1124, 1128, 1116, 1128, 1121, 1121,
1132, 1127, 1123, 1126, 1125, 1129, 1119, 1120, 1119, 1125, 1120, 1128, 1126, 1125, 1125, 1129, 1124, 1126,
1129, 1125, 1129, 1132, 1125, 1126, 1123, 1122, 1123, 1127, 1122, 1126, 1125, 1130, 1120, 1130, 1118, 1128,
1126, 1133, 1126, 1130, 1125, 1128, 1123, 1123, 1125, 1128, 1129, 1122, 1130, 1128, 1123, 1125, 1121, 1123,
1122, 1124, 1125, 1126, 1128, 1126, 1126, 1126, 1126, 1124, 1121, 1124, 1124, 1124, 1124, 1121, 1124, 1120,
1126, 1119, 1125, 1128, 1123, 1128, 1124, 1128, 1125, 1128, 1117, 1125, 1129, 1127, 1121, 1126, 1125, 1126
#if TOUCH_KEY_NUM > 0
, 2000,2000,2000
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_FW_Rawdata_N[40 * 40] = {
676, 678, 676, 673, 676, 676, 677, 674, 675, 678, 671, 677, 676, 670, 671, 678, 672, 676,
675, 677, 676, 671, 680, 675, 675, 674, 676, 673, 675, 676, 674, 676, 673, 672, 674, 675,
674, 674, 675, 675, 675, 674, 674, 673, 675, 677, 672, 674, 672, 675, 672, 674, 673, 673,
674, 673, 677, 674, 673, 677, 674, 675, 674, 672, 675, 673, 672, 674, 673, 675, 676, 674,
678, 676, 677, 676, 675, 673, 674, 677, 673, 676, 672, 678, 671, 671, 672, 682, 673, 673,
676, 674, 679, 670, 678, 673, 676, 672, 671, 675, 672, 674, 673, 673, 671, 676, 675, 676,
675, 673, 679, 675, 674, 675, 674, 671, 671, 676, 673, 674, 674, 677, 672, 675, 674, 672,
677, 677, 673, 677, 673, 677, 677, 671, 672, 671, 671, 674, 675, 673, 676, 673, 677, 676,
675, 676, 674, 671, 674, 670, 671, 671, 675, 673, 675, 676, 673, 675, 672, 674, 674, 674,
676, 677, 675, 677, 672, 676, 672, 676, 671, 675, 674, 673, 672, 673, 673, 676, 673, 678,
675, 674, 675, 676, 673, 673, 674, 677, 672, 671, 675, 671, 675, 672, 674, 674, 675, 672,
678, 677, 674, 679, 674, 674, 673, 676, 671, 675, 676, 673, 678, 672, 676, 676, 672, 677,
675, 677, 678, 677, 674, 677, 673, 674, 675, 675, 677, 673, 674, 672, 675, 674, 674, 673,
675, 678, 675, 677, 677, 676, 674, 674, 677, 674, 674, 672, 675, 673, 676, 674, 675, 675,
676, 677, 675, 673, 678, 674, 677, 678, 678, 674, 679, 675, 678, 677, 678, 672, 677, 674,
676, 676, 677, 676, 676, 676, 675, 677, 678, 675, 677, 677, 677, 675, 678, 673, 675, 672,
675, 675, 675, 677, 677, 676, 675, 676, 676, 679, 676, 679, 676, 675, 673, 678, 673, 673,
676, 678, 679, 673, 674, 678, 674, 679, 681, 673, 676, 680, 681, 680, 678, 678, 675, 675,
671, 673, 679, 672, 675, 675, 680, 681, 682, 680, 678, 677, 676, 677, 677, 679, 676, 675,
676, 676, 677, 679, 675, 677, 675, 677, 674, 676, 677, 679, 676, 677, 673, 677, 677, 676,
672, 675, 674, 676, 675, 675, 677, 677, 680, 677, 676, 676, 674, 677, 671, 677, 677, 673,
674, 676, 675, 676, 674, 677, 678, 675, 678, 676, 675, 676, 676, 674, 677, 674, 677, 678,
678, 675, 675, 673, 673, 676, 676, 677, 674, 676, 676, 679, 674, 676, 673, 677, 673, 672,
672, 674, 675, 675, 675, 676, 670, 676, 675, 675, 674, 676, 674, 675, 676, 674, 671, 672,
675, 679, 676, 681, 674, 677, 675, 670, 679, 675, 677, 673, 677, 673, 676, 676, 672, 675,
678, 677, 675, 676, 674, 677, 674, 671, 676, 675, 674, 677, 677, 677, 672, 674, 674, 676,
676, 673, 676, 674, 678, 674, 676, 678, 674, 673, 675, 672, 674, 677, 669, 677, 673, 673,
679, 676, 674, 676, 675, 677, 672, 672, 671, 675, 672, 677, 676, 675, 675, 677, 674, 675,
677, 675, 678, 679, 675, 676, 674, 673, 674, 676, 673, 676, 675, 678, 672, 678, 671, 677,
675, 680, 676, 678, 675, 677, 674, 674, 675, 677, 678, 673, 678, 677, 674, 675, 672, 674,
673, 674, 675, 676, 677, 676, 675, 675, 676, 674, 673, 674, 675, 675, 674, 672, 674, 672,
675, 671, 675, 677, 674, 677, 674, 677, 675, 677, 670, 675, 678, 676, 673, 676, 675, 676
#if TOUCH_KEY_NUM > 0
, 400,400,400
#endif /* #if TOUCH_KEY_NUM > 0 */
};

static int32_t PS_Config_Lmt_FW_CC_P = 112;
static int32_t PS_Config_Lmt_FW_CC_N = 72;
static int32_t PS_Config_Lmt_Key_FW_CC_P = 38;
static int32_t PS_Config_Lmt_Key_FW_CC_N = 9;
static int32_t PS_Config_Lmt_FW_CC_I_P = 25;
static int32_t PS_Config_Lmt_FW_CC_I_N;
static int32_t PS_Config_Lmt_FW_CC_Q_P = 25;
static int32_t PS_Config_Lmt_FW_CC_Q_N;
static int32_t PS_Config_Lmt_Key_FW_CC_I_P = 25;
static int32_t PS_Config_Lmt_Key_FW_CC_I_N;
static int32_t PS_Config_Lmt_Key_FW_CC_Q_P = 25;
static int32_t PS_Config_Lmt_Key_FW_CC_Q_N;

static int32_t PS_Config_Lmt_FW_Diff_P = 35;
static int32_t PS_Config_Lmt_FW_Diff_N = -35;
static int32_t PS_Config_Lmt_Key_FW_Diff_P = 35;
static int32_t PS_Config_Lmt_Key_FW_Diff_N = -35;

static int32_t PS_Config_Diff_Test_Frame = 50;

#endif /* #if NVT_TOUCH_MP */
