#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
using namespace std;

namespace Algorithms
{
    // Kadane: Returns {start_idx, end_idx, max_sum}
    struct KadaneResult
    {
        int start;
        int end;
        double max_sum;
    };
    KadaneResult kadane(const vector<double> &arr);

    // LIS variant: Longest increasing streak (contiguous)
    struct StreakResult
    {
        int start;
        int length;
    };
    StreakResult longest_increasing_streak(const vector<double> &arr);

    // Sliding Window: Shortest subarray with sum >= S
    struct WindowResult
    {
        int start;
        int end;
        double current_sum;
        bool found;
    };
    WindowResult shortest_window_with_sum(const vector<double> &arr, double S);

    // Prefix Sum
    vector<double> build_prefix_sum(const vector<double> &arr);
    double query_range_sum(const vector<double> &prefix_sum, int l, int r);
}

#endif
