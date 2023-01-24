#ifndef __NOTES_H__
#define __NOTES_H__

//formula for pitch notes -> NOTE = 750000/freq

#define NOTE_B0  24295
#define NOTE_C1  22936
#define NOTE_CS1 21645
#define NOTE_D1  20430
#define NOTE_DS1 19285
#define NOTE_E1  18204
#define NOTE_F1  17182
#define NOTE_FS1 16216
#define NOTE_G1  15306
#define NOTE_GS1 14448
#define NOTE_A1  13636
#define NOTE_AS1 12871
#define NOTE_B1  12148
#define NOTE_C2  11466
#define NOTE_CS2 10823
#define NOTE_D2  10215
#define NOTE_DS2 9642
#define NOTE_E2  9101
#define NOTE_F2  8590
#define NOTE_FS2 8108
#define NOTE_G2  7653
#define NOTE_GS2 7223
#define NOTE_A2  6818
#define NOTE_AS2 6436
#define NOTE_B2  6074
#define NOTE_C3  5733
#define NOTE_CS3 5412
#define NOTE_D3  4550
#define NOTE_DS3 4821
#define NOTE_E3  4551
#define NOTE_F3  4295
#define NOTE_FS3 4054
#define NOTE_G3  3827
#define NOTE_GS3 3612
#define NOTE_A3  3409
#define NOTE_AS3 3218
#define NOTE_B3  3037
#define NOTE_C4  2867
#define NOTE_CS4 2706
#define NOTE_D4  2554
#define NOTE_DS4 2410
#define NOTE_E4  2275
#define NOTE_F4  2148
#define NOTE_FS4 2027
#define NOTE_G4  1913
#define NOTE_GS4 1806
#define NOTE_A4  1705
#define NOTE_AS4 1609
#define NOTE_B4  1519
#define NOTE_C5  1433
#define NOTE_CS5 1353
#define NOTE_D5  1277
#define NOTE_DS5 1205
#define NOTE_E5  1138
#define NOTE_F5  1074
#define NOTE_FS5 1014
#define NOTE_G5  957
#define NOTE_GS5 903
#define NOTE_A5  852
#define NOTE_AS5 804
#define NOTE_B5  759
#define NOTE_C6  717
#define NOTE_CS6 676
#define NOTE_D6  638
#define NOTE_DS6 603
#define NOTE_E6  569
#define NOTE_F6  537
#define NOTE_FS6 507
#define NOTE_G6  478
#define NOTE_GS6 451
#define NOTE_A6  426
#define NOTE_AS6 402
#define NOTE_B6  380
#define NOTE_C7  358
#define NOTE_CS7 338
#define NOTE_D7  319
#define NOTE_DS7 301
#define NOTE_E7  284
#define NOTE_F7  268
#define NOTE_FS7 253
#define NOTE_G7  239
#define NOTE_GS7 226
#define NOTE_A7  213
#define NOTE_AS7 201
#define NOTE_B7  190
#define NOTE_C8  179
#define NOTE_CS8 169
#define NOTE_D8  160
#define NOTE_DS8 151
#define REST      0

#define WHOLE_NOTE          65536
#define HALF_NOTE           WHOLE_NOTE/2
#define HALF_DOTTED_NOTE    WHOLE_NOTE/2 + WHOLE_NOTE/4
#define QUARTER_NOTE        WHOLE_NOTE/4
#define QUARTER_DOTTED_NOTE WHOLE_NOTE/4 + WHOLE_NOTE/8
#define EIGHT_NOTE          WHOLE_NOTE/8
#define EIGHT_DOTTED_NOTE   WHOLE_NOTE/8 + WHOLE_NOTE/16

#endif
