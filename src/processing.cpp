#include "../include/processing.h"
#include "../include/utils.h"
#include <map>
#include <algorithm>
using namespace std;

namespace Processing
{
    vector<DailySummary> group_and_validate(const vector<IO::RawRow> &raw_data)
    {
        // Step 1: Group into Orders
        map<string, Order> order_map;
        for (const auto &row : raw_data)
        {
            // Removed strict > 0 validation to support "doanh thu âm (hoàn trả)" test case
            if (order_map.find(row.order_id) == order_map.end())
            {
                order_map[row.order_id] = {row.order_id, row.date, row.customer, {}};
            }
            order_map[row.order_id].items.push_back({row.product, row.qty, row.price});
        }

        // Step 2: Group Orders into DailySummary
        map<string, DailySummary> day_map;
        for (auto const &pair : order_map)
        {
            const auto &id = pair.first;
            const auto &order = pair.second;

            if (day_map.find(order.date) == day_map.end())
            {
                day_map[order.date] = {order.date, {}};
            }

            day_map[order.date].orders.push_back(order);
        }

        // Convert map to sorted vector (by date string)
        vector<DailySummary> result;
        for (auto const &pair : day_map)
        {
            const auto &date = pair.first;
            const auto &summary = pair.second;

            result.push_back(summary);
        }
        sort(result.begin(), result.end(), [](const DailySummary &a, const DailySummary &b)
             { return a.date < b.date; });

        return result;
    }

    void normalize_products(vector<DailySummary> &summaries)
    {
        for (auto &s : summaries)
        {
            for (auto &o : s.orders)
            {
                for (auto &item : o.items)
                {
                    item.product = Utils::to_lowercase(Utils::trim(item.product));
                }
            }
        }
    }
}
