#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>
#include <numeric>
using namespace std;

struct LineItem
{
    string product;
    int qty;
    double price;

    double revenue() const
    {
        return qty * price;
    }
};

struct Order
{
    string id;
    string date;
    string customer;
    vector<LineItem> items;

    double total() const
    {
        double sum = 0;
        for (const auto &item : items)
        {
            sum += item.revenue();
        }
        return sum;
    }
};

struct DailySummary
{
    string date;
    vector<Order> orders;

    double dayRevenue() const
    {
        double sum = 0;
        for (const auto &order : orders)
        {
            sum += order.total();
        }
        return sum;
    }
};

#endif
