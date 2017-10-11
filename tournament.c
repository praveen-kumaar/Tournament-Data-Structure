#include <stdio.h>
#include <stdlib.h>
#include "headers/tournament.h"

struct tournam {
    uint32_t size;
    size_t sizeofPlayer;
    void *tourTree;
};

static int (*compa)(const void *, const void *);

static Tournament play(Tournament tour,
                       int (*comp)(const void *, const void *));

static void setElemAt(Tournament tour, uint16_t i);

Tournament newTournament(size_t sizeofPlayer, uint32_t noOfPlayers) {
    if (sizeofPlayer == 0 || noOfPlayers == 0) {
        return NULL;
    }
    Tournament tour = (struct tournament *) malloc(sizeof(struct tournament));
    tour->temp = malloc(sizeofPlayer);
    tour->tourn = (struct tournam *) malloc(sizeof(struct tournam));
    tour->tourn->tourTree = malloc((2 * noOfPlayers - 1) * sizeofPlayer);
    if (tour == NULL || tour->tourn == NULL || tour->temp == NULL
            || tour->tourn->tourTree == NULL) {
        return NULL;
    }
    tour->tourn->size = noOfPlayers;
    tour->tourn->sizeofPlayer = sizeofPlayer;
    return tour;
}

Tournament setupTour(Tournament tour, void *base,
                     int (*comp)(const void *, const void *)) {
    if (tour == NULL || base == NULL
            || comp == NULL) return NULL;
    compa = comp;
    uint32_t i;
    char *_base = (char *) base;
    char * _tourTree = (char *) (tour->tourn->tourTree);
    _tourTree = _tourTree + ((tour->tourn->size - 1) * tour->tourn->sizeofPlayer);
    for (i = 0; i < tour->tourn->size * tour->tourn->sizeofPlayer; i++) {
        *_tourTree++ = *_base++;
    }
    tour = play(tour, comp);
    return tour;
}

static Tournament play(Tournament tour,
                       int (*comp)(const void *, const void *)) {
    for (uint32_t  i = 2 * tour->tourn->size - 2; i > 0; i = i - 2) {
        char *j, *k;
        char *p;
        j = ((char *)(tour->tourn->tourTree) + (i * tour->tourn->sizeofPlayer));
        k = ((char *)(tour->tourn->tourTree) + ((i - 1) * tour->tourn->sizeofPlayer));
        p =  ((char *)(tour->tourn->tourTree) + (((i * tour->tourn->sizeofPlayer) / 2) -
                tour->tourn->sizeofPlayer));
        if ((*comp)(j, k) > 0) {
            for (uint32_t  h = 0; h < tour->tourn->sizeofPlayer; h++) {
                *(p + h) = *(j + h);
            }
        } else {
            for (uint32_t  h = 0; h < tour->tourn->sizeofPlayer; h++) {
                *(p + h) = *(k + h);
            }
        }
    }
    return tour;
}

static void setElemAt(Tournament tour, uint16_t i) {
    char *p = ((char *) tour->tourn->tourTree) + i * tour->tourn->sizeofPlayer;
    for (uint16_t j = 0; j < tour->tourn->sizeofPlayer; j++) {
        *(((char *) tour->temp) + j) = *(p + j);
    }
    return;
}

static void setNextWinner(Tournament tour) {
    char *next, *i, *j;
    i = ((char *) tour->tourn->tourTree) + tour->tourn->sizeofPlayer;
    j = i + tour->tourn->sizeofPlayer;
    if ((*compa)((void *)i, (void *)j) > 0) {
        next = j;
    } else {
        next = i;
        i = j;
    }
    char *k = ((char *)tour->tourn->tourTree) + ((2 * tour->tourn->size - 2) *
              tour->tourn->sizeofPlayer);
    while (1) {
        if ((i = i + 2 * tour->tourn->sizeofPlayer) > k) break;
        if ((*compa)(tour->tourn->tourTree, (void *)i) > 0) {
            if ((*compa)((void *)i, (void *)next) > 0) {
                next = (void *) i;
            }
        } else {
            i = i + tour->tourn->sizeofPlayer;
            if (i > k) break;
            if ((*compa)((void *)i, next) > 0) {
                next = (void *) i;
            }
        }
    }
    for (uint16_t m = 0; m < tour->tourn->sizeofPlayer; m++) {
        *(((char *) tour->temp) + m) = *(next + m);
    }
    return;
}

int getNoOfPlayers(Tournament tour) {
    if (tour == NULL) return -1;
    else
        return tour->tourn->size;
}

void *getWinner(Tournament tour) {
    if (tour == NULL) {
        return NULL;
    }
    setElemAt(tour, 0);
    return tour->temp;
}

void *getNextWinner(Tournament tour) {
    if (tour == NULL || tour->tourn->size <= 1 || compa == NULL) {
        return NULL;
    }
    setNextWinner(tour);
    return tour->temp;
}

void *getElemAt(Tournament tour, uint16_t i) {
    if (tour == NULL || i >= 2 * tour->tourn->size - 1) {
        return NULL;
    }
    setElemAt(tour, i);
    return tour->temp;
}

void printTour(Tournament tour, char *(*toString)(const void *elem,
               char *buffer), char *buffer) {
    if (tour == NULL || toString == NULL || buffer == NULL) {
        printf("EMPTY TOURNAMENT\n");
        return;
    }
    uint32_t i;
    for (i = 0; i < 2 * tour->tourn->size - 1; i++) {
        printf("%s ", (*toString)((char *)(tour->tourn->tourTree) +
                                  (i * tour->tourn->sizeofPlayer),
                                  buffer));
    }
    printf("\n");
    return;
}

void finishTournament(Tournament tour) {
    if (tour == NULL) return;
    free(tour->tourn->tourTree);
    free(tour->tourn);
    free(tour->temp);
    free(tour);
    return;
}
