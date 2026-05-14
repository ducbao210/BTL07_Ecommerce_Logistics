#ifndef IO_H
#define IO_H

#include "models.h"
#include <vector>
#include <string>
using namespace std;

namespace IO
{
    struct RawRow
    {
        string order_id;
        string date;
        string customer;
        string product;
        int qty;
        double price;
    };

    vector<RawRow> read_orders_csv(const string &filename);
    double read_target(const string &filename);

    void write_revenue_report(const string &filename, const vector<DailySummary> &summaries);
    void write_best_period(const string &filename, int start_idx, int end_idx, double max_rev, const vector<DailySummary> &summaries);
    void write_window(const string &filename, int start_idx, int end_idx, double total_rev, const vector<DailySummary> &summaries);
}

#endif
