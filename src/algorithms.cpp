#include "../include/algorithms.h"
#include <algorithm>
using namespace std;

namespace Algorithms
{
    KadaneResult kadane(const vector<double> &arr)
    {
        if (arr.empty())
            return {-1, -1, 0};

        double max_so_far = arr[0];
        double current_max = arr[0];
        int start = 0, end = 0, temp_start = 0;

        for (int i = 1; i < (int)arr.size(); i++)
        {
            if (arr[i] > current_max + arr[i])
            {
                current_max = arr[i];
                temp_start = i;
            }
            else
            {
                current_max += arr[i];
            }

            if (current_max > max_so_far)
            {
                max_so_far = current_max;
                start = temp_start;
                end = i;
            }
        }
        return {start, end, max_so_far};
    }

    StreakResult longest_increasing_streak(const vector<double> &arr)
    {
        if (arr.empty())
            return {-1, 0};

        int max_len = 1;
        int current_len = 1;
        int best_start = 0;
        int current_start = 0;

        for (int i = 1; i < (int)arr.size(); i++)
        {
            if (arr[i] > arr[i - 1])
            {
                current_len++;
            }
            else
            {
                if (current_len > max_len)
                {
                    max_len = current_len;
                    best_start = current_start;
                }
                current_len = 1;
                current_start = i;
            }
        }
        if (current_len > max_len)
        {
            max_len = current_len;
            best_start = current_start;
        }
        return {best_start, max_len};
    }

    WindowResult shortest_window_with_sum(const vector<double> &arr, double S)
    {
        int n = arr.size();
        int min_len = n + 1;
        int best_start = -1, best_end = -1;
        double current_sum = 0;
        int start = 0;

        for (int end = 0; end < n; end++)
        {
            current_sum += arr[end];
            while (current_sum >= S && start <= end)
            {
                if (end - start + 1 < min_len)
                {
                    min_len = end - start + 1;
                    best_start = start;
                    best_end = end;
                }
                current_sum -= arr[start];
                start++;
            }
        }

        if (best_start == -1)
            return {-1, -1, 0, false};

        // Calculate final sum of the best window discovered
        double final_sum = 0;
        for (int i = best_start; i <= best_end; i++)
            final_sum += arr[i];

        return {best_start, best_end, final_sum, true};
    }

    vector<double> build_prefix_sum(const vector<double> &arr)
    {
        vector<double> prefix(arr.size() + 1, 0.0);
        for (int i = 0; i < (int)arr.size(); i++)
        {
            prefix[i + 1] = prefix[i] + arr[i];
        }
        return prefix;
    }

    double query_range_sum(const vector<double> &prefix_sum, int l, int r)
    {
        if (l < 0 || r >= (int)prefix_sum.size() - 1 || l > r)
            return 0;
        return prefix_sum[r + 1] - prefix_sum[l];
    }
}
