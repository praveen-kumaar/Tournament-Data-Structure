/**
 * @file tournament.h
 * @author praveen kumar
 * @date 26 sept 2017
 * @brief Tournament Data Structure.
 *
 * The data structure Tournament, as the name signifies, is a knock out tournament
 * of objects/elements of same data type where it is characterized by rounds. every
 * round, except the last one where we are left with the winner only, consist of set of
 * objects. only the winners from the previous round proceed in the next round.<br>
 * <br>
 * The library is flexible to be used for any data type and have several of functions for
 * manipulating the tournament.for the matter of usecase, the first call to a
 * function&nbsp;(during&nbsp;using&nbsp;this&nbsp;structure) must be a #newTournament and must end
 * with a call to #finishTournament, failing to do so may result in inconsistency or
 * memory leak.
 */

#ifndef _tournament_h
#define _tournament_h

/**
 * @brief Abstract data type for a Tournament data structure.
 *
 * typedef-ed for a pointer to a internally maintained structure for the tournament.
 */
typedef struct tournament *Tournament;

struct tournament {
    struct tournam *tourn;
    void *temp;
};

/**
 * @brief Constructor for dynamically allocating a space for the Tournament.
 *
 * @param sizeofPlayer Size of the player(in bytes) or the object taking part in a
 *                     tournament. @c sizeof operator can be useful here for determining
 *                     the size of the object in bytes.
 * @param noOfPlayers Total no of players or objects taking part in the Tournament in the
                      initial phase.
 * @return Tournament Immutable Pointer to a allocated space for the tournament to take place
 *                    or @c NULL if the request for allocation fails.
 *
 * @note Its an error&nbsp;(Dereferencing&nbsp;the&nbsp;incomplete&nbsp;type) if the pointer
 *       returned by this function is dereferenced, there are getters provided by this library
 *       in order to fetch any attribute if needed.
 */
extern Tournament newTournament(size_t sizeofPlayer, uint32_t noOfPlayers);

/**
 * @brief Starts the Tournament.
 *
 * The tournament starts with the players or objects residing in the memory pointed by @p base
 * where a policy for win or loose between players is decided by the @p comp. Call to this function
 * guarantee the completion of all the rounds to be held(depending on the no of players participating).
 * @param tour Pointer to a space allocated for tournament to be held, this pointer must be the one
 *             returned by #newTournament.
 * @param base Pointer to a memory holding the players/elements taking part in the tournament.
 * @param comp pointer to a comparator function for evaluating a loss or win among players.
 * @return Tournament a pointer to a memory holding the tournament structure after completion of rounds
 *                    or @c NULL if either of the parameter passed is @c NULL.
 */
extern Tournament setupTour(Tournament tour, void *base,
                            int (*comp)(const void *, const void *));

/**
 * @brief Useful for viewing the winner of the Tournament @p tour.
 *
 * The function returns a flexible pointer, so its the responsibility of the user of this library to
 * correctly cast the result. For the consistent result the type of the cast must be the type of the
 * players pointed by @p base, which is passed as a parameter in #setupTour.
 * @param tour Tournament for which the winner is to be evaluated.
 * @return void* pointer to a winner and @c NULL if @p tour is @c NULL.
 * @note Their is not any effect of changing the value(through dereferencing) in the memory pointed by
 *       the pointer returned here on the actual data structure, however changing the value is not
 *       accompanied.
 */
extern void *getWinner(Tournament tour);

/**
 * @brief Useful for viewing the Next winner of the Tournament @p tour.
 *
 * Please note the next winner can be different from a runner up. next winner means that this
 * element will loose to the winner only and win against all the other tournament players. since this
 * element might have loose to the winner in the initial rounds their is a good possibility for be it
 * the runner up.<br>
 * The function returns a flexible pointer, so its the responsibility of the user of this library to
 * correctly cast the result. For the consistent result the type of the cast must be the type of the
 * players pointed by @p base, which is passed as a parameter in #setupTour.
 * @param tour Tournament for which the winner is to be evaluated.
 * @return void* pointer to a next winner and @c NULL if @p tour is @c NULL.
 * @note Their is not any effect of changing the value(through dereferencing) in the memory pointed by
 *       the pointer returned here on the actual data structure, however changing the value is not
 *       accompanied.
 */
extern void *getNextWinner(Tournament tour);

/**
 * @brief Useful for viewing the element at arbitrary position in a Tournament.
 * The function returns a flexible pointer, so its the responsibility of the user of this library to
 * correctly cast the result. For the consistent result the type of the cast must be the type of the
 * players pointed by @p base, which is passed as a parameter in #setupTour.
 * @param tour Tournament for which the element is to be evaluated.
 * @param i index of the element in the tournament, which conventionally starts from @c 0 and must end
 *          at a value <tt>2 * getNoOfPlayers(tour) - 2</tt>.
 * @return void* pointer to a element at index @c i or @c NULL if @p tour is @c NULL
 * @note Their is not any effect of changing the value(through dereferencing) in the memory pointed by
 *       the pointer returned here on the actual data structure, however changing the value is not
 *       accompanied.
 */
extern void *getElemAt(Tournament tour, uint16_t i);

/**
 * Useful for evaluating total no of objects or players who had participated in the initial phase of
 * tournament(i.e.. round one).
 * @param tour where the players or objects have participated.
 * @return int the total no of players participating in the tournament @c tour or @c -1 if the @c tour
 *             is @c NULL.
 */
extern int getNoOfPlayers(Tournament tour);

/**
 * @brief Prints the complete tournament in the sequence from winner to the initial phase i.e.. round one.
 *
 * The total no of elements printed are one less than the twice of the initial no of players or elements in
 * the tournament in the initial phase. if we see the view of this printing round wise then it depends upon
 * either the initial no of players are either odd or even. we will start from end. lets see the example:
 * @verbatim CASE: Even
 * Lets suppose we have an array of integers as {8, 7, 15, 1, 6, 9, 4, 3} then the play
 * begins from end i.e.. 3 and 4 will be paired to play, 9 and 6 will be paired to play
 * and so on, our comparator is the max of 2 values. the winners will proceed in round
 * two according to the comparator and are put in front of the round 1 elements,
 * as shown below:
 * {8, 15, 9, 4, 8, 7, 15, 1, 6, 9, 4, 3}, here {8, 15, 9, 4} are round 2 elements
 * the same process will continue among round two elements to get to round Three and so on.
 * finally we will be left with the single element which is the winner and the complete
 * structure looks as:
 * {15, 15, 9, 8, 15, 9, 4, 8, 7, 15, 1, 6, 9, 4, 3} 15 is the winner.
CASE: odd
 * This time take the example: {8, 7, 15, 1, 6, 9, 4}
 * we will proceed in the same way as we do earlier, only the difference is we are left
 * with 1 element in round 1 having not any pair, so this element will be moved to round
 * two without any comparison and the view looks as:
 * {15, 6, 9, 8, 7, 15, 1, 6, 9, 4}
 * please note 8 is not put twice and is shared among round one and two for the view purpose
 * and so we will move further as we did. finally complete structure looks as:
 * {15, 15, 9, 15, 6, 9, 8, 7, 15, 1, 6, 9, 4} 15 is the winner.@endverbatim
 * @param tour tournament to be printed.
 * @param toString pointer to a function providing the string(of characters) view of the player.
 * @param buffer pointer to a memory that will hold the string representation of player returned by @p toString
 * @return void
 *
 */
extern void printTour(Tournament tour, char *(*toString)(const void *elem,
                      char *buffer), char *buffer);

/**
 * @brief Clears all the memory owned by this library.
 *
 * This must be a last function called during utilising this library.
 * @param tour tournament to be freed. their is no effect if @c NULL is passed as parameters.
 * @return void
 * @note @p tour must be a pointer returned by the call to #newTournament.
 *          if this function is called twice on the same Tournament then their is a chance of
 *          inconsistency for the underlying program and it may crash.
 */

extern void finishTournament(Tournament tour);

#endif
