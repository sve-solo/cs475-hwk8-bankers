#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "banker.h"

// TODO - Safety Algorithm goes here
// m = number of resource types (3)
// n = number of threads (5)

// pseudocode (from homework assignment description):
//
// isSafe(Available, Alloc, Need) {
//
// 	Work[m] = Available.clone();
// 	Finish[n] = [0, 0, ..., 0] for all 0 <= i < n
//
// 	while (exists unfinished thread i && Need[i] <= Work) {
// 		// pretend that thread i finishes execution
// 		// then OS can reclaim thread i's allocated resources
// 		Work += Alloc[i]
// 		Finish[i] = 1
// 	}
// 	// there's an execution order in which all threads
// 	if (Finish == [1, 1, ..., 1])
// 		return true	// safe!
// 	return false		// unsafe!
// }

// TODO: function to clone (deep copy) vectors/matrices

// TODO: function to compare two vectors

// TODO: function to add, subtract two vectors/matrices

// TODO: function to print the contents of vectors/matrices
