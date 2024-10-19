#include "../inc/pathfinder.h"

void free_results(ResultArray result_array) {
    for (int i = 0; i < result_array.count; i++) {
        Result res = result_array.results[i];
        for (int j = 0; j < res.length; j++) {
            free(res.path[j]);  // Free each island name
        }
        free(res.path);         // Free the path array
        free(res.distances);    // Free the distances array
    }
    free(result_array.results); // Free the results array
}
