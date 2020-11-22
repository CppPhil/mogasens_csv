#include <exception>
#include <stdexcept>

#include "gtest/gtest.h"

#include <pl/os.hpp>

#include "segment.hpp"

#if PL_OS == PL_OS_LINUX
TEST(segment, shouldGetExpectedSegmentationPointsFromPython)
{
  cm::Configuration::Builder builder{};
  builder.skipWindow(false)
    .deleteTooClose(false)
    .deleteTooLowVariance(false)
    .imu(cm::Imu::Accelerometer)
    .segmentationKind("max")
    .windowSize(501)
    .filterKind("butterworth");
  const cm::Configuration config{builder.build()};

  const std::unordered_map<cl::fs::Path, std::vector<std::uint64_t>> map{
    cm::segment(config)};

  const auto fetch = [&map](const char* path) {
    auto it{map.find(cl::fs::Path{std::string{path}})};

    if (it == map.end()) {
      throw std::runtime_error{"iterator was not valid!"};
    }

    return it->second;
  };

#define EXPECT_SEGMENTATION_POINTS(path, ...) \
  EXPECT_EQ((std::vector<std::uint64_t>{__VA_ARGS__}), fetch(path))

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.07.33_Belly.csv",
    8145,
    9465,
    10693,
    12029,
    13325,
    14649,
    15945,
    17177,
    18525,
    19805,
    21109,
    22449,
    23921,
    25261,
    26581,
    27953,
    29401,
    30849,
    32245,
    33689,
    35101,
    36601,
    38037,
    39585,
    41225,
    42937);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_13.00.09_LeftArm.csv",
    26999,
    28183,
    30023,
    31891,
    33619,
    35503,
    37587,
    39527,
    41531,
    43463,
    45939,
    48083,
    50539,
    53011,
    55543,
    58067,
    60871,
    62311);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/Andre_Squats_13_10_2020_RightArm.csv",
    61566,
    63476,
    66831,
    72081,
    74321,
    77416,
    79426,
    82576,
    87386,
    89871,
    92541,
    94451,
    97746,
    102686,
    104966,
    107621,
    109481,
    112526,
    117291,
    119746,
    121956,
    126521,
    128901,
    131241,
    133671,
    136011,
    138406,
    140871,
    143376,
    145741,
    148151,
    150451,
    152891,
    155361,
    157756);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/Andre_Squats2_13_10_2020_Chest.csv",
    47500,
    49730,
    52040,
    54275,
    56555,
    58950,
    61320,
    63680,
    65950,
    69470,
    73330,
    76825,
    80270,
    83740,
    87330,
    92095,
    94465,
    96995,
    99160,
    101550,
    104170,
    106175,
    113240,
    120255,
    126010,
    130685,
    135375,
    139895,
    141935,
    144710,
    146880,
    149715,
    154135,
    158915,
    160910,
    163650,
    168670,
    171005,
    173875,
    175975,
    178655,
    180810,
    183485,
    185820,
    188685,
    190775,
    193520,
    198370,
    203080,
    205080,
    207785,
    212570);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen3_13_10_2020_Belly.csv",
    30998,
    32793,
    34438,
    36038,
    37668,
    39253,
    40863,
    42463,
    44163,
    45853,
    47613,
    49433,
    51678,
    53758,
    55978,
    58333,
    61248,
    63933);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_11.17.39_RightArm.csv",
    59267,
    61191,
    62851,
    64587,
    66199,
    67879,
    69555,
    71383,
    73155,
    74919,
    76631,
    78511,
    80415,
    82267,
    84123,
    86187,
    88119,
    90379,
    92387,
    94691,
    97227,
    99695,
    102015,
    104647,
    108139);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen2_13_10_2020_Chest.csv",
    41636,
    43316,
    44911,
    46526,
    48241,
    49911,
    51576,
    53266,
    55001,
    56781,
    58621,
    60426,
    62256,
    64251,
    66231,
    68381,
    70596,
    73106,
    75871,
    79206);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen1_13_10_2020_RightArm.csv",
    18796,
    20551,
    22326,
    23981,
    25681,
    27316,
    29046,
    30631,
    32186,
    33791,
    35416,
    37071,
    38686,
    40276,
    41891,
    43561,
    45226,
    46941,
    48686,
    50431,
    52191,
    54076,
    56116,
    58226,
    60576,
    63561,
    66281);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.20.28_Belly.csv",
    62703,
    64303,
    65431,
    66535,
    68783,
    69891,
    71007,
    72175,
    73363,
    74551,
    75727,
    76995,
    78411,
    79843,
    81379,
    83131);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_13.00.09_RightArm.csv",
    28163,
    30035,
    31903,
    33203,
    35655,
    37411,
    39251,
    41539,
    43483,
    45299,
    47887,
    49943,
    52315,
    55423,
    58059,
    60875);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen1_13_10_2020_Chest.csv",
    40110,
    41765,
    43580,
    45255,
    47005,
    48715,
    50485,
    52305,
    54195,
    56100,
    57910,
    59735,
    61655,
    63465,
    65250,
    67190,
    69100,
    71015,
    72810,
    74545,
    76300,
    77970,
    79765,
    81625,
    83525);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.14.32_Belly.csv",
    32951,
    34487,
    35643,
    36911,
    38207,
    39475,
    40771,
    42079,
    43431,
    44823,
    46219,
    47579,
    48923,
    50287,
    51703,
    53103,
    54551,
    55987,
    57575,
    59207,
    61027,
    63063);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_12.50.00_RightArm.csv",
    16043,
    19047,
    20935,
    22783,
    24959,
    26935,
    28999,
    30919,
    32875,
    34975,
    37175,
    39379,
    41723,
    43763,
    45971,
    48399,
    50907,
    53211,
    56087,
    58403,
    61063);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Jan_liegestuetzen3_13_10_2020_LeftArm.csv",
    36655,
    38125,
    39655,
    41045,
    42450,
    43925,
    45280,
    46700,
    48110,
    49690,
    51465,
    53205,
    55245);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen1_13_10_2020_RightArm.csv",
    40105,
    41760,
    43560,
    45240,
    46985,
    48715,
    50475,
    52310,
    54205,
    56110,
    57920,
    59750,
    61665,
    63470,
    65270,
    67220,
    69120,
    71030,
    72820,
    74560,
    76315,
    77980,
    79780,
    81660,
    83530);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.20.28_Chest.csv",
    62695,
    64323,
    65447,
    66547,
    68783,
    69903,
    71023,
    72179,
    73379,
    74571,
    75739,
    77019,
    78427,
    79859,
    81419,
    83163);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_12.50.00_LeftArm.csv",
    19051,
    20907,
    22783,
    24963,
    26935,
    29027,
    30919,
    32875,
    34971,
    37203,
    39367,
    41727,
    43783,
    45983,
    48383,
    50887,
    53935,
    56167,
    58471,
    61099);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen1_13_10_2020_Chest.csv",
    18791,
    20556,
    22321,
    23981,
    25691,
    27316,
    29051,
    30641,
    32196,
    33806,
    35411,
    37071,
    38701,
    40286,
    41901,
    43566,
    45236,
    46946,
    48656,
    50416,
    52186,
    54076,
    56101,
    58221,
    60536,
    63546,
    66256);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_15.13.22_RightArm.csv",
    25991,
    27659,
    29523,
    31607,
    33659,
    35807,
    38115,
    40303,
    42711,
    45339,
    47575,
    50567,
    53499,
    56803,
    60443,
    62499,
    64227);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen1_13_10_2020_Belly.csv",
    18811,
    20566,
    22331,
    23976,
    25691,
    27321,
    29041,
    30636,
    32181,
    33791,
    35406,
    37061,
    38696,
    40281,
    41891,
    43546,
    45226,
    46931,
    48641,
    50401,
    52176,
    54061,
    56091,
    58226,
    60561,
    63536,
    66266);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Jan_liegestuetzen3_13_10_2020_Chest.csv",
    34040,
    36735,
    38165,
    39670,
    41060,
    42460,
    43940,
    45340,
    46720,
    48135,
    49715,
    51475,
    53245,
    55255);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.07.33_RightArm.csv",
    7957,
    10685,
    12017,
    13301,
    14649,
    15909,
    17225,
    19729,
    21049,
    22457,
    23925,
    25213,
    26577,
    27937,
    29397,
    30853,
    32253,
    33673,
    35109,
    36585,
    38045,
    39621,
    41233,
    42937);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated-Revised/"
    "Jan_liegestuetzen1_13_10_2020_edited_RightArm.csv",
    86150,
    88785,
    92390,
    96325,
    100355,
    104150,
    108040,
    111865,
    115805,
    119825,
    123805,
    127760,
    131485,
    135265,
    139005,
    142755,
    146555,
    150410,
    154415,
    158390,
    162735,
    166660,
    170160,
    173645,
    177305,
    181940);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen2_13_10_2020_Chest.csv",
    37590,
    39195,
    40720,
    42265,
    43785,
    45565,
    47250,
    49000,
    50675,
    52325,
    53970,
    55550,
    57105,
    58755,
    60430,
    62295,
    64850,
    67980,
    72220);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_15.31.36_Belly.csv",
    73767,
    76559,
    78323,
    80239,
    83739,
    87263,
    89203,
    91419,
    93627,
    95835,
    98095,
    100439,
    102771,
    105295,
    107907,
    110579,
    113279);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen3_13_10_2020_Belly.csv",
    12861,
    14691,
    17356,
    21286,
    22726,
    24156,
    25711,
    27491);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.14.32_RightArm.csv",
    32923,
    34491,
    35619,
    36887,
    38175,
    39435,
    40691,
    42031,
    43391,
    44791,
    46195,
    47567,
    48919,
    50303,
    51691,
    53099,
    54495,
    55971,
    57535,
    59227,
    61051,
    63075);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated-Revised/"
    "Jan_liegestuetzen1_13_10_2020_edited_LeftArm.csv",
    85600,
    88695,
    92450,
    96265,
    100235,
    104150,
    108005,
    111840,
    115750,
    119740,
    123790,
    127740,
    131415,
    135145,
    138820,
    142645,
    146490,
    150275,
    154350,
    158285,
    160390,
    162650,
    166615,
    170010,
    173460,
    177405,
    179855,
    181920);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.59.59_Chest.csv",
    73999,
    75971,
    77795,
    80323,
    82683,
    85039,
    87471,
    89907,
    92455,
    95139,
    97955,
    99847);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen2_13_10_2020_Belly.csv",
    37610,
    39180,
    40720,
    42270,
    43780,
    45560,
    47235,
    48990,
    50670,
    52305,
    53945,
    55540,
    57095,
    58750,
    60425,
    62295,
    64845,
    67965,
    72125);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen3_13_10_2020_Chest.csv",
    12866,
    14666,
    16141,
    18601,
    21296,
    22731,
    24156,
    25716,
    27491);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/Andre_Squats2_13_10_2020_Belly.csv",
    47500,
    49725,
    52020,
    54275,
    56555,
    58940,
    61315,
    63675,
    65960,
    69505,
    73365,
    76820,
    80325,
    83735,
    87310,
    92215,
    94435,
    96970,
    99170,
    101525,
    104120,
    106105,
    113300,
    120265,
    125985,
    130675,
    135400,
    139870,
    141880,
    144720,
    146885,
    149670,
    154130,
    158910,
    160935,
    163605,
    168670,
    171020,
    173870,
    175945,
    178645,
    180780,
    183470,
    185790,
    188700,
    190750,
    193520,
    198365,
    203120,
    205060,
    207790,
    212610);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_12.50.00_Belly.csv",
    16779,
    18995,
    20863,
    22755,
    24911,
    26879,
    29007,
    30903,
    32847,
    34927,
    37207,
    39347,
    41687,
    43759,
    45911,
    48351,
    50847,
    53127,
    55979,
    58331,
    60987);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen2_13_10_2020_LeftArm.csv",
    37565,
    39195,
    40705,
    42265,
    43770,
    45550,
    47235,
    49000,
    50670,
    52340,
    53975,
    55525,
    57095,
    58750,
    60420,
    62275,
    64850,
    67975,
    72125);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Jan_liegestuetzen3_13_10_2020_Belly.csv",
    36745,
    38175,
    39665,
    41075,
    42470,
    43935,
    45355,
    46715,
    48140,
    49715,
    51460,
    53240,
    55245);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen2_13_10_2020_Belly.csv",
    41631,
    43316,
    44906,
    46516,
    48231,
    49901,
    51561,
    53256,
    54991,
    56776,
    58611,
    60416,
    62246,
    64246,
    66226,
    68381,
    70586,
    73111,
    75871,
    79181);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_15.13.22_LeftArm.csv",
    26003,
    27647,
    29643,
    31635,
    33627,
    35879,
    37983,
    40055,
    42707,
    45343,
    47935,
    50567,
    53431,
    56363,
    60499,
    63587);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.59.59_LeftArm.csv",
    73999,
    75771,
    78151,
    80263,
    82687,
    85051,
    87431,
    89903,
    92443,
    95095,
    97959,
    99995);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated-Revised/"
    "Jan_liegestuetzen1_13_10_2020_edited_Chest.csv",
    86065,
    88680,
    92395,
    96300,
    100250,
    104140,
    107965,
    111825,
    115780,
    119765,
    123775,
    127710,
    131400,
    135145,
    138890,
    142655,
    146445,
    150260,
    154310,
    158240,
    160465,
    162600,
    166575,
    170000,
    173480,
    177320,
    181880);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen3_13_10_2020_LeftArm.csv",
    11251,
    12906,
    14631,
    17351,
    21241,
    22701,
    24156,
    25691,
    27466);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_15.31.36_LeftArm.csv",
    72559,
    74707,
    76547,
    77967,
    81055,
    82395,
    83651,
    87243,
    89235,
    91467,
    93635,
    95831,
    98159,
    100423,
    102911,
    105487,
    107875,
    110571,
    113395);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_13.00.09_Belly.csv",
    28143,
    29859,
    31771,
    33391,
    35583,
    37515,
    39427,
    41411,
    43443,
    45319,
    47911,
    49991,
    53115,
    55427,
    57971,
    61067);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.59.59_RightArm.csv",
    73999,
    75943,
    78091,
    80331,
    82687,
    85051,
    87451,
    89939,
    92495,
    95119,
    97967,
    99995);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_15.31.36_Chest.csv",
    72499,
    74739,
    76639,
    77975,
    80247,
    83667,
    87255,
    89263,
    91511,
    93623,
    95875,
    98111,
    100503,
    102859,
    105379,
    107903,
    110623,
    113355);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_11.17.39_LeftArm.csv",
    58739,
    60523,
    62771,
    64507,
    66255,
    67963,
    69655,
    71375,
    73163,
    74811,
    76603,
    78603,
    80527,
    82267,
    84131,
    86023,
    87723,
    90491,
    92507,
    94731,
    97223,
    99735,
    102075,
    104563,
    108139);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Jan_liegestuetzen2_13_10_2020_LeftArm.csv",
    19801,
    21156,
    22541,
    23911,
    26566,
    27906,
    29301,
    30696,
    32066,
    33496,
    34891,
    36436,
    37976,
    39641,
    41311,
    43141,
    45051,
    47416);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen1_13_10_2020_LeftArm.csv",
    18791,
    20516,
    22311,
    23976,
    25661,
    27301,
    29026,
    30621,
    32171,
    33791,
    35396,
    37056,
    38676,
    40271,
    41891,
    43546,
    45221,
    46936,
    48651,
    50406,
    52176,
    54081,
    56096,
    58221,
    60551,
    63556,
    66266);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen3_13_10_2020_RightArm.csv",
    31003,
    32783,
    34433,
    36043,
    37683,
    39268,
    40888,
    42488,
    44188,
    45878,
    47628,
    49463,
    51678,
    53763,
    55988,
    58363,
    61213,
    63943);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_13.00.09_Chest.csv",
    28195,
    29887,
    31759,
    33463,
    35455,
    37467,
    39451,
    41575,
    43447,
    45299,
    47979,
    49999,
    53003,
    55335,
    57995,
    60883);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen2_13_10_2020_LeftArm.csv",
    41636,
    43306,
    44896,
    46511,
    48236,
    49901,
    51566,
    53266,
    54996,
    56776,
    58621,
    60421,
    62261,
    64246,
    66236,
    68376,
    70596,
    73136,
    75881,
    79201);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.59.59_Belly.csv",
    73999,
    76023,
    77795,
    80263,
    82671,
    85023,
    87403,
    89883,
    92415,
    95015,
    97935,
    99995);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Jan_liegestuetzen2_13_10_2020_Belly.csv",
    19806,
    21221,
    22586,
    25246,
    26596,
    27956,
    29321,
    30721,
    32111,
    33486,
    34901,
    36451,
    38006,
    39651,
    41311,
    43146,
    45041,
    47391,
    50361);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Jan_liegestuetzen3_13_10_2020_RightArm.csv",
    36725,
    38125,
    39645,
    41025,
    42450,
    43920,
    45295,
    46680,
    48110,
    49665,
    51410,
    53225,
    55235);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_15.13.22_Chest.csv",
    24163,
    26011,
    27691,
    29559,
    31651,
    33659,
    35827,
    37931,
    40251,
    42711,
    44911,
    47563,
    50559,
    53383,
    56411,
    60471,
    64291);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen2_13_10_2020_RightArm.csv",
    37560,
    39200,
    40715,
    42255,
    43790,
    45550,
    47260,
    49000,
    50685,
    52325,
    53965,
    55535,
    57100,
    58775,
    60430,
    62295,
    64865,
    67985,
    72225);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/Andre_Squats_13_10_2020_LeftArm.csv",
    61591,
    63491,
    67041,
    72111,
    74456,
    77421,
    79481,
    82501,
    84781,
    87546,
    89876,
    92546,
    94436,
    97766,
    102691,
    104861,
    107656,
    109516,
    112601,
    114826,
    117291,
    119701,
    121916,
    124246,
    126521,
    128906,
    131221,
    133676,
    136016,
    138406,
    140871,
    143371,
    145741,
    148161,
    150446,
    152881,
    155366,
    157756);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.14.32_Chest.csv",
    32939,
    34491,
    35655,
    36923,
    38223,
    39495,
    40783,
    42099,
    43475,
    44859,
    46259,
    47595,
    48963,
    50355,
    51747,
    53151,
    54615,
    56035,
    57683,
    59279,
    61083,
    63135);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Jan_liegestuetzen2_13_10_2020_Chest.csv",
    19821,
    21211,
    22571,
    23941,
    25246,
    26586,
    27936,
    29326,
    30716,
    32101,
    33506,
    34916,
    36461,
    38011,
    39661,
    41321,
    43161,
    45056,
    47416,
    50296);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_11.17.39_Chest.csv",
    59311,
    61191,
    62799,
    64539,
    66195,
    67899,
    69583,
    71363,
    73175,
    74891,
    76671,
    78503,
    80375,
    82275,
    84123,
    86043,
    87971,
    90431,
    92387,
    94671,
    97223,
    99487,
    102639,
    104579,
    106775,
    108139);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Jan_liegestuetzen2_13_10_2020_RightArm.csv",
    19816,
    21191,
    22541,
    23881,
    25231,
    26551,
    27906,
    29306,
    30656,
    32076,
    33476,
    34896,
    36446,
    37991,
    39636,
    41276,
    43146,
    45036,
    47411);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.07.33_Chest.csv",
    8085,
    9473,
    10717,
    12025,
    13337,
    14669,
    15945,
    17161,
    18553,
    19797,
    21117,
    22489,
    23949,
    25285,
    26613,
    27993,
    29413,
    30885,
    32285,
    33717,
    35149,
    36629,
    38085,
    39621,
    41289,
    42969);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.07.33_LeftArm.csv",
    9437,
    10725,
    12033,
    14605,
    15909,
    17129,
    19765,
    21053,
    22421,
    23921,
    25209,
    26537,
    27925,
    29385,
    30825,
    32217,
    33585,
    35061,
    36573,
    38001,
    39569,
    41201,
    42877);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen3_13_10_2020_RightArm.csv",
    10996,
    12881,
    14681,
    17336,
    21296,
    22721,
    24136,
    25721,
    27486);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_15.13.22_Belly.csv",
    24323,
    26019,
    27683,
    29559,
    31603,
    33619,
    35731,
    38027,
    40067,
    42635,
    44887,
    47539,
    50527,
    53351,
    56371,
    59815,
    63691);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen1_13_10_2020_LeftArm.csv",
    38195,
    40110,
    41765,
    43545,
    45215,
    46985,
    48695,
    50445,
    52290,
    54180,
    56100,
    57880,
    59725,
    61655,
    63445,
    65235,
    67195,
    69100,
    71010,
    72810,
    74545,
    76290,
    77975,
    79765,
    81630,
    83415);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/Andre_Squats2_13_10_2020_LeftArm.csv",
    49735,
    52050,
    54275,
    56555,
    58955,
    61315,
    63675,
    65965,
    69610,
    73345,
    76935,
    80275,
    83890,
    87285,
    91240,
    94385,
    98230,
    101615,
    103870,
    106120,
    113140,
    120175,
    126060,
    130690,
    135310,
    139835,
    141830,
    144690,
    146870,
    149635,
    151970,
    154125,
    158855,
    163630,
    166265,
    168695,
    170880,
    173755,
    178570,
    181225,
    183470,
    188535,
    190655,
    193480,
    196040,
    198300,
    203180,
    207760,
    210300,
    212640);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated-Revised/"
    "Jan_liegestuetzen1_13_10_2020_edited_Belly.csv",
    86080,
    88770,
    92415,
    96340,
    100290,
    104145,
    108000,
    111910,
    115870,
    119865,
    123855,
    127760,
    131455,
    135255,
    139025,
    142760,
    146510,
    150285,
    154365,
    158380,
    162770,
    166630,
    170050,
    173510,
    177350,
    181885);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen3_13_10_2020_Chest.csv",
    32793,
    34433,
    36043,
    37678,
    39263,
    40878,
    42473,
    44178,
    45858,
    47623,
    49438,
    51678,
    53758,
    55978,
    58348,
    61223,
    63933);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.20.28_RightArm.csv",
    62791,
    64307,
    66487,
    68715,
    70847,
    72063,
    73295,
    74471,
    76955,
    78391,
    79835,
    81359,
    83135);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_12.50.00_Chest.csv",
    16759,
    18995,
    20867,
    22727,
    24923,
    26883,
    28967,
    30907,
    32831,
    34939,
    37195,
    39343,
    41691,
    43747,
    45939,
    48351,
    50855,
    53147,
    56011,
    58331,
    61003);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_15.31.36_RightArm.csv",
    72615,
    74903,
    77947,
    80879,
    83571,
    87243,
    89263,
    91495,
    93559,
    95827,
    98103,
    100583,
    102927,
    105459,
    108007,
    111327,
    113339);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen3_13_10_2020_LeftArm.csv",
    32788,
    34428,
    36038,
    37663,
    39258,
    40873,
    42473,
    44173,
    45853,
    47613,
    49438,
    51678,
    53763,
    55993,
    58363,
    61238,
    63923);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/Andre_Squats_13_10_2020_Belly.csv",
    61561,
    63491,
    67031,
    72036,
    74416,
    77466,
    82516,
    87411,
    89636,
    92581,
    97766,
    102721,
    107621,
    109686,
    112561,
    117286,
    119376,
    121981,
    124051,
    126531,
    128911,
    131251,
    133681,
    136021,
    138426,
    140886,
    143401,
    145761,
    148201,
    150486,
    152901,
    155391,
    157786);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/Andre_Squats_13_10_2020_Chest.csv",
    61561,
    63491,
    67036,
    72051,
    74401,
    77511,
    82571,
    87476,
    89661,
    92581,
    97806,
    102751,
    107656,
    109696,
    112586,
    117306,
    119391,
    121991,
    124011,
    126536,
    128906,
    131256,
    133686,
    136026,
    138426,
    140891,
    143396,
    145751,
    148176,
    150476,
    152906,
    155376,
    157771);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.14.32_LeftArm.csv",
    32963,
    34459,
    35587,
    36867,
    38143,
    39415,
    40699,
    42043,
    43367,
    44791,
    46183,
    47503,
    48899,
    50271,
    51671,
    53075,
    54423,
    55907,
    57639,
    59199,
    60995,
    63067);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Lukas_liegestuetzen1_13_10_2020_Belly.csv",
    40095,
    41760,
    43595,
    45270,
    46990,
    48730,
    50480,
    52315,
    54225,
    56095,
    57905,
    59735,
    61640,
    63450,
    65240,
    67175,
    69085,
    71005,
    72805,
    74545,
    76305,
    77960,
    79765,
    81630,
    83590);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/Andre_Squats2_13_10_2020_RightArm.csv",
    47500,
    49710,
    52050,
    54260,
    56545,
    58930,
    61305,
    63665,
    65960,
    69625,
    73395,
    77040,
    80260,
    83910,
    87345,
    91180,
    94400,
    97975,
    101575,
    105970,
    107595,
    113155,
    115000,
    120175,
    126075,
    130610,
    135330,
    139845,
    142010,
    144640,
    146945,
    149455,
    151965,
    154130,
    158935,
    163520,
    168670,
    170520,
    173800,
    178555,
    183480,
    185660,
    188565,
    191160,
    193535,
    198350,
    200850,
    202955,
    207805,
    212535);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_11.17.39_Belly.csv",
    59211,
    61183,
    62779,
    64555,
    66195,
    67899,
    69539,
    71299,
    73167,
    74907,
    76619,
    78491,
    80311,
    82239,
    84111,
    85991,
    88087,
    90419,
    92275,
    94679,
    97163,
    99459,
    102391,
    104447,
    106727,
    108139);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/"
    "Andre_liegestuetzen2_13_10_2020_RightArm.csv",
    41651,
    43311,
    44911,
    46521,
    48246,
    49911,
    51576,
    53261,
    54991,
    56786,
    58621,
    60431,
    62256,
    64276,
    66246,
    68381,
    70616,
    73121,
    75881,
    79191);

  EXPECT_SEGMENTATION_POINTS(
    "resources/preprocessed/Interpolated/2020-07-02_14.20.28_LeftArm.csv",
    64307,
    65407,
    68651,
    69787,
    70891,
    72043,
    73243,
    74415,
    75583,
    76939,
    78347,
    79799,
    81331,
    83095);
}
#elif PL_OS == PL_OS_WINDOWS
TEST(segmentWindowsDummyTest, shouldSucceedOnWindowsBecauseItDoesNothing)
{
  const volatile bool b{true};
  EXPECT_TRUE(b);
}
#endif
