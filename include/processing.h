#ifndef PROCESSING_H
#define PROCESSING_H

#include "models.h"
#include "io.h"
#include <vector>
#include <map>
using namespace std;

namespace Processing
{
    vector<DailySummary> group_and_validate(const vector<IO::RawRow> &raw_data);
    void normalize_products(vector<DailySummary> &summaries);
}

#endif
