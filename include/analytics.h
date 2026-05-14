#ifndef ANALYTICS_H
#define ANALYTICS_H

#include "models.h"
#include <vector>
#include <map>
using namespace std;

namespace Analytics
{
    struct Stats
    {
        double mean;
        double std_dev;
        double min;
        double max;
    };

    Stats calculate_stats(const vector<double> &revenues);
    vector<pair<string, double>> get_top_k_products(const vector<DailySummary> &summaries, int k);
    vector<double> min_max_normalize(const vector<double> &data);
}

#endif
