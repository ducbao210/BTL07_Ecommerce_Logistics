#include "../include/analytics.h"
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;

namespace Analytics
{
    Stats calculate_stats(const vector<double> &revenues)
    {
        if (revenues.empty())
            return {0, 0, 0, 0};

        double sum = accumulate(revenues.begin(), revenues.end(), 0.0);
        double mean = sum / revenues.size();

        double sq_sum = 0;
        double min_val = revenues[0];
        double max_val = revenues[0];

        for (double v : revenues)
        {
            sq_sum += (v - mean) * (v - mean);
            if (v < min_val)
                min_val = v;
            if (v > max_val)
                max_val = v;
        }

        double std_dev = sqrt(sq_sum / revenues.size());
        return {mean, std_dev, min_val, max_val};
    }

    vector<pair<string, double>> get_top_k_products(const vector<DailySummary> &summaries, int k)
    {
        map<string, double> prod_rev;
        for (const auto &s : summaries)
        {
            for (const auto &o : s.orders)
            {
                for (const auto &item : o.items)
                {
                    prod_rev[item.product] += item.revenue();
                }
            }
        }

        vector<pair<string, double>> sorted_prods(prod_rev.begin(), prod_rev.end());
        sort(sorted_prods.begin(), sorted_prods.end(), [](const auto &a, const auto &b)
             { return a.second > b.second; });

        if (sorted_prods.size() > (size_t)k)
        {
            sorted_prods.resize(k);
        }
        return sorted_prods;
    }

    vector<double> min_max_normalize(const vector<double> &data)
    {
        if (data.empty())
            return {};
        double min_val = *min_element(data.begin(), data.end());
        double max_val = *max_element(data.begin(), data.end());

        vector<double> res;
        double range = max_val - min_val;
        if (range == 0)
        {
            res.assign(data.size(), 0.0);
            return res;
        }

        for (double v : data)
        {
            res.push_back((v - min_val) / range);
        }
        return res;
    }
}
