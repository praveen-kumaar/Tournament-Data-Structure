#include <stdio.h>
#include "headers/tournament.h"
#include <CUnit/Basic.h>
#include <string.h>

#define SIZE1 sizeof(int)
#define NPLAYERS1 0
#define WINNER1 NULL
#define NEXT_WINNER_NULL NULL

#define NPLAYERS2   2
#define WINNER2     8
#define NEXTWINNER2 7

#define NPLAYERS3   1
#define WINNER3     8

#define NPLAYERS4   8
#define WINNER4     15
#define NEXTWINNER4 9

#define NPLAYERS5   9
#define WINNER5     -4
#define NEXTWINNER5 -10

#define NPLAYERS6   9
#define WINNER6     -4
#define NEXTWINNER6 5

#define SIZE2 sizeof(char *)
#define NPLAYERS7   6
#define WINNER7     "WORLD"
#define NEXTWINNER7 "UNITTESTING"

#define SIZE3 sizeof(struct userType)
#define NPLAYERS8   6

static Tournament tour1 = NULL;
static void *base1 = NULL ;

static Tournament tour2 = NULL;
static int base2[] = {8, 7} ;
static int tournament2[] = {8, 8, 7};

static Tournament tour3 = NULL;
static int base3[] = {8};
static int tournament3[] = {8};

static Tournament tour4 = NULL;
static int base4[] = {8, 7, 15, 1, 6, 9, 4, 3} ;
static int tournament4[] = {15, 15, 9, 8, 15, 9, 4, 8, 7, 15, 1, 6, 9, 4, 3};

static Tournament tour5 = NULL;
static int base5[] = {-4, -12, -11, -16, -17, -10, -20, -108, -201};
static int tournament5[] = {-4, -4, -10, -4, -11, -16, -10, -108, -4, -12, -11, -16, -17, -10, -20, -108, -201};

static Tournament tour6 = NULL;
static int base6[] = {-4, 5, 7, 8, 9, 10, 18, 101, 786};
static int tournament6[] = {-4, -4, 8, -4, 5, 8, 10, 101, -4, 5, 7, 8, 9, 10, 18, 101, 786};

static Tournament tour7 = NULL;
static char *base7[] = {"HELLO", "WORLD", "ONE", "TWO", "TOURNAMENT", "UNITTESTING"};
static char *tournament7[] = {"WORLD", "UNITTESTING", "WORLD", "TWO", "UNITTESTING", "HELLO", "WORLD", "ONE", "TWO", "TOURNAMENT", "UNITTESTING"};

typedef struct userType {
    char name[10];
    int id;
} UserType;

const struct userType WINNER8     = {.name = "C#", .id = 1244};
const struct userType NEXTWINNER8 = {.name = "java", .id = 1239};

static Tournament tour8 = NULL;
static UserType base8[] = {
    {.name = "C language", .id = 1234},
    {.name = "C++", .id = 1235},
    {.name = "java", .id = 1239},
    {.name = "python", .id = 1237},
    {.name = "Lua", .id = 1236},
    {.name = "C#", .id = 1244}
};
static UserType tournament8[] = {
    {.name = "C#", .id = 1244},
    {.name = "C#", .id = 1244},
    {.name = "C++", .id = 1235},
    {.name = "java", .id = 1239},
    {.name = "C#", .id = 1244},
    {.name = "C language", .id = 1234},
    {.name = "C++", .id = 1235},
    {.name = "java", .id = 1239},
    {.name = "python", .id = 1237},
    {.name = "Lua", .id = 1236},
    {.name = "C#", .id = 1244}
};

int init_suite1(void) {
    if ((tour1 = newTournament(SIZE1, NPLAYERS1)) != NULL
            || (tour2 = newTournament(SIZE1, NPLAYERS2)) == NULL
            || (tour3 = newTournament(SIZE1, NPLAYERS3)) == NULL
            || (tour4 = newTournament(SIZE1, NPLAYERS4)) == NULL
            || (tour5 = newTournament(SIZE1, NPLAYERS5)) == NULL) {
        return -1;
    } else {
        return 0;
    }
}

int init_suite2(void) {
    if ((tour6 = newTournament(SIZE1, NPLAYERS6)) == NULL) {
        return -1;
    } else {
        return 0;
    }
}

int init_suite3(void) {
    if ((tour7 = newTournament(SIZE2, NPLAYERS7))) {
        return -1;
    } else {
        return 0;
    }
}

int init_suite4(void) {
    if ((tour8 = newTournament(SIZE3, NPLAYERS8)) == NULL) {
        return -1;
    } else {
        return 0;
    }
}


int clean_suite1(void) {
    finishTournament(tour1);
    finishTournament(tour2);
    finishTournament(tour3);
    finishTournament(tour4);
    finishTournament(tour5);
    return 0;
}

int clean_suite2(void) {
    finishTournament(tour6);
    return 0;
}

int clean_suite3(void) {
    finishTournament(tour7);
    return 0;
}

int clean_suite4(void) {
    finishTournament(tour8);
    return 0;
}

int comp_max(const void *a, const void *b) {
    return *((int *)a) > *((int *)b) ? 1 : 0;
}

int comp_min(const void *a, const void *b) {
    return *((int *)a) < *((int *)b) ? 1 : 0;
}

int comp_str(const void *a, const void *b) {
    return strcmp(*((char **)a), *((char **)b));
}

int comp_usert(const void *a, const void *b) {
    return ((struct userType *)a)->id > ((struct userType *)b)->id;
}

static int usert_equals(const struct userType a, const struct userType b) {
    return (strcmp(a.name, b.name) == 0 && a.id == b.id);
}

void testSetupTour(void) {
    tour1 = setupTour(tour1, base1, comp_max);
    CU_ASSERT_PTR_EQUAL(NULL, tour1);
    tour1 = setupTour(tour1, base1, NULL);
    CU_ASSERT_PTR_EQUAL(NULL, tour1);
    tour2 = setupTour(tour2, base2, comp_max);
    if (tour2 != NULL) {
        for (uint16_t i = 0; i < 2 * NPLAYERS2 - 1; i++) {
            CU_ASSERT(tournament2[i] == *((int *) getElemAt(tour2, i)));
        }
    }
    tour3 = setupTour(tour3, base3, comp_max);
    if (tour3 != NULL) {
        for (uint16_t i = 0; i < 2 * NPLAYERS3 - 1; i++) {
            CU_ASSERT(tournament3[i] == *((int *) getElemAt(tour3, i)));
        }
    }
    tour4 = setupTour(tour4, base4, comp_max);
    if (tour4 != NULL) {
        for (uint16_t i = 0; i < 2 * NPLAYERS4 - 1; i++) {
            CU_ASSERT(tournament4[i] == *((int *) getElemAt(tour4, i)));
        }
    }
    tour5 = setupTour(tour5, base5, comp_max);
    if (tour5 != NULL) {
        for (uint16_t i = 0; i < 2 * NPLAYERS5 - 1; i++) {
            CU_ASSERT(tournament5[i] == *((int *) getElemAt(tour5, i)));
        }
    }
}

void testSetupTour2(void) {
    tour6 = setupTour(tour6, base6, comp_min);
    if (tour6 != NULL) {
        for (uint16_t i = 0; i < 2 * NPLAYERS6 - 1; i++) {
            CU_ASSERT(tournament6[i] == *((int *) getElemAt(tour6, i)));
        }
    }
}

void testSetupTour3(void) {
    tour7 = setupTour(tour7, base7, comp_str);
    if (tour7 != NULL) {
        for (uint16_t i = 0; i < 2 * NPLAYERS7 - 1; i++) {
            CU_ASSERT_STRING_EQUAL(tournament7[i], *((char **) getElemAt(tour7, i)));
        }
    }
}

void testSetupTour4(void) {
    tour8 = setupTour(tour8, base8, comp_usert);
    if (tour8 != NULL) {
        for (uint16_t i = 0; i < 2 * NPLAYERS8 - 1; i++) {
            CU_ASSERT(usert_equals(tournament8[i], *((struct userType *) getElemAt(tour8,
                                   i))));
        }
    }
}

void testgetWinner(void) {
    CU_ASSERT_PTR_EQUAL(WINNER1, (int *) getWinner(tour1));
    CU_ASSERT(WINNER2 == *((int *)getWinner(tour2)));
    CU_ASSERT(WINNER3 == *((int *)getWinner(tour3)));
    CU_ASSERT(WINNER4 == *((int *)getWinner(tour4)));
    CU_ASSERT(WINNER5 == *((int *)getWinner(tour5)));
}

void testgetWinner2(void) {
    CU_ASSERT(WINNER6 == *((int *)getWinner(tour6)));
}

void testgetWinner3(void) {
    CU_ASSERT_STRING_EQUAL(WINNER7, *((char **)getWinner(tour7)));
}

void testgetWinner4(void) {
    CU_ASSERT(usert_equals(WINNER8, *((struct userType *)getWinner(tour8))));
}

void testgetNextWinner(void) {
    CU_ASSERT_PTR_EQUAL(NEXT_WINNER_NULL, ((int *) getNextWinner(tour1)));
    CU_ASSERT(NEXTWINNER2 == *((int *)getNextWinner(tour2)));
    CU_ASSERT_PTR_EQUAL(NEXT_WINNER_NULL, ((int *) getNextWinner(tour3)));
    CU_ASSERT(NEXTWINNER4 == *((int *)getNextWinner(tour4)));
    CU_ASSERT(NEXTWINNER5 == *((int *)getNextWinner(tour5)));
}

void testgetNextWinner2(void) {
    CU_ASSERT(NEXTWINNER6 == *((int *)getNextWinner(tour6)));
}

void testgetNextWinner3(void) {
    CU_ASSERT_STRING_EQUAL(NEXTWINNER7, *((char **)getNextWinner(tour7)));
}

void testgetNextWinner4(void) {
    CU_ASSERT(usert_equals(NEXTWINNER8, *((struct userType*)getNextWinner(tour8))));
}

int main() {
    CU_pSuite pSuite1 = NULL;
    CU_pSuite pSuite2 = NULL;
    CU_pSuite pSuite3 = NULL;
    CU_pSuite pSuite4 = NULL;
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    pSuite1 = CU_add_suite("Suite1", init_suite1, clean_suite1);
    pSuite2 = CU_add_suite("Suite2", init_suite2, clean_suite2);
    pSuite3 = CU_add_suite("Suite3", init_suite3, clean_suite3);
    pSuite4 = CU_add_suite("Suite4", init_suite4, clean_suite4);
    if (pSuite1 == NULL || pSuite2 == NULL || pSuite3 == NULL || pSuite4 == NULL ) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if (NULL == CU_add_test(pSuite1, "test of setupTour()", testSetupTour)
            || NULL == CU_add_test(pSuite1, "test of getWinner()", testgetWinner)
            || NULL == CU_add_test(pSuite1, "test of getNextWinner()", testgetNextWinner)
            || NULL == CU_add_test(pSuite2, "test of setupTour()", testSetupTour2)
            || NULL == CU_add_test(pSuite2, "test of getWinner()", testgetWinner2)
            || NULL == CU_add_test(pSuite2, "test of getNextWinner()", testgetNextWinner2)
            || NULL == CU_add_test(pSuite3, "test of setupTour()", testSetupTour3)
            || NULL == CU_add_test(pSuite3, "test of getWinner()", testgetWinner3)
            || NULL == CU_add_test(pSuite3, "test of getNextWinner()", testgetNextWinner3)
            || NULL == CU_add_test(pSuite4, "test of setupTour()", testSetupTour4)
            || NULL == CU_add_test(pSuite4, "test of getWinner()", testgetWinner4)
            || NULL == CU_add_test(pSuite4, "test of getNextWinner()",
                                   testgetNextWinner4)) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
