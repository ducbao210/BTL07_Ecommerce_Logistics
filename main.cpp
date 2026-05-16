#include "./include/models.h"
#include "./include/io.h"
#include "./include/processing.h"
#include "./include/analytics.h"
#include "./include/algorithms.h"
#include "./include/utils.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Lấy tên file không kèm đường dẫn và phần mở rộng
// Ví dụ: data/test_cases/orders.csv -> orders
string get_stem(const string &path)
{
    size_t slash = path.find_last_of("/\\");
    string filename =
        (slash == string::npos) ? path : path.substr(slash + 1);

    size_t dot = filename.find_last_of('.');
    if (dot != string::npos)
        filename = filename.substr(0, dot);

    return filename;
}

int main(int argc, char *argv[])
{
    string input_file = "data/test_cases/orders.csv";
    string target_file = "data/target.txt";

    if (argc > 1)
        input_file = argv[1];
    if (argc > 2)
        target_file = argv[2];

    // Tạo thư mục output riêng cho từng test case
    string test_name = get_stem(input_file);
    string output_dir = "output/" + test_name;

    // Tạo thư mục (Windows)
    string cmd = "mkdir \"" + output_dir + "\" 2>nul";
    system(cmd.c_str());

    cout << "--- Logistics Data Analysis System ---" << endl;
    cout << "Loading: " << input_file << endl;
    cout << "Output directory: " << output_dir << endl;

    // 1. Data Pipeline
    auto raw_data = IO::read_orders_csv(input_file);
    if (raw_data.empty())
    {
        cerr << "Error: No data loaded from " << input_file << endl;
        return 1;
    }

    auto summaries = Processing::group_and_validate(raw_data);
    Processing::normalize_products(summaries);

    // Prepare revenue array
    vector<double> revenues;
    for (const auto &s : summaries)
    {
        revenues.push_back(s.dayRevenue());
    }

    double S = IO::read_target(target_file);
    cout << "Target Revenue (S): " << S << endl;

    // 2. Execution
    IO::write_revenue_report(output_dir + "/revenue_report.csv", summaries);

    // Kadane
    auto k_res = Algorithms::kadane(revenues);
    IO::write_best_period(
        output_dir + "/best_period.txt",
        k_res.start,
        k_res.end,
        k_res.max_sum,
        summaries);

    // Sliding Window
    auto w_res = Algorithms::shortest_window_with_sum(revenues, S);
    IO::write_window(
        output_dir + "/window.txt",
        w_res.start,
        w_res.end,
        w_res.current_sum,
        summaries);

    // LIS
    auto streak = Algorithms::longest_increasing_streak(revenues);

    // Statistics
    auto stats = Analytics::calculate_stats(revenues);
    auto top_products = Analytics::get_top_k_products(summaries, 5);

    // 3. Console Output Summary
    cout << "\n--- Statistics ---" << endl;
    cout << "Avg Daily Revenue: " << stats.mean << endl;
    cout << "STD Daily Revenue: " << stats.std_dev << endl;
    cout << "Max Daily Revenue: " << stats.max << endl;
    cout << "Min Daily Revenue: " << stats.min << endl;
    cout << "Longest Growth Streak: " << streak.length << " days" << endl;

    cout << "\n--- Top 5 Products ---" << endl;
    for (const auto &p : top_products)
    {
        cout << "- " << p.first << ": " << p.second << endl;
    }

    cout << "\nAnalysis complete. Results written to "
         << output_dir << "/" << endl;
    cout << "\n-----------------------------\n"
         << endl;
    return 0;
}