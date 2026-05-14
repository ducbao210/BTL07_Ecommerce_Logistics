#include "../include/io.h"
#include "../include/utils.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

namespace IO
{
    vector<RawRow> read_orders_csv(const string &filename)
    {
        vector<RawRow> data;
        ifstream file(filename);
        if (!file.is_open())
            return data;

        string line;
        // Skip header
        getline(file, line);

        while (getline(file, line))
        {
            if (line.empty())
                continue;
            auto tokens = Utils::split(line, ',');
            if (tokens.size() >= 6)
            {
                try
                {
                    RawRow row;
                    row.order_id = Utils::trim(tokens[0]);
                    row.date = Utils::trim(tokens[1]);
                    row.customer = Utils::trim(tokens[2]);
                    row.product = Utils::trim(tokens[3]);
                    row.qty = stoi(Utils::trim(tokens[4]));
                    row.price = stod(Utils::trim(tokens[5]));
                    data.push_back(row);
                }
                catch (...)
                {
                    // Skip invalid numeric conversion
                    continue;
                }
            }
        }
        return data;
    }

    double read_target(const string &filename)
    {
        ifstream file(filename);
        double s = 0;
        if (file >> s)
            return s;
        return 0;
    }

    void write_revenue_report(const string &filename, const vector<DailySummary> &summaries)
    {
        ofstream file(filename);
        file << "Date,Revenue,OrderCount\n";
        for (const auto &s : summaries)
        {
            file << s.date << "," << fixed << setprecision(2) << s.dayRevenue() << "," << s.orders.size() << "\n";
        }
    }

    void write_best_period(const string &filename, int start_idx, int end_idx, double max_rev, const vector<DailySummary> &summaries)
    {
        ofstream file(filename);
        if (start_idx == -1)
        {
            file << "No best period found.\n";
            return;
        }
        file << "Best period (Kadane):\n";
        file << "From: " << summaries[start_idx].date << "\n";
        file << "To: " << summaries[end_idx].date << "\n";
        file << "Max Revenue: " << fixed << setprecision(2) << max_rev << "\n";
    }

    void write_window(const string &filename, int start_idx, int end_idx, double total_rev, const vector<DailySummary> &summaries)
    {
        ofstream file(filename);
        if (start_idx == -1)
        {
            file << "No window satisfies the target.\n";
            return;
        }
        file << "Shortest Window reaching target:\n";
        file << "From: " << summaries[start_idx].date << "\n";
        file << "To: " << summaries[end_idx].date << "\n";
        file << "Total Revenue: " << fixed << setprecision(2) << total_rev << "\n";
        file << "Length: " << (end_idx - start_idx + 1) << " days\n";
    }
}
