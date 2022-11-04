#include <Storages/MergeTree/RangesInDataPart.h>


namespace DB
{

void RangesInDataPartDescription::serialize(WriteBuffer & out) const
{
    info.serialize(out);
    ranges.serialize(out);
}

void RangesInDataPartDescription::describe(WriteBuffer & out) const
{
    String result;
    result += fmt::format("partition_id: {} \n", info.partition_id);
    // TODO: More fields
    (void)out;
}

void RangesInDataPartDescription::deserialize(ReadBuffer & in)
{
    info.deserialize(in);
    ranges.deserialize(in);
}


void RangesInDataPartsDescription::serialize(WriteBuffer & out) const
{
    for (const auto & desc : *this)
        desc.serialize(out);
}

void RangesInDataPartsDescription::describe(WriteBuffer & out) const
{
    String result;
    for (const auto & desc : *this)
        desc.describe(out);
}

void RangesInDataPartsDescription::deserialize(ReadBuffer & in)
{
    for (auto & desc : *this)
        desc.deserialize(in);
}

RangesInDataPartDescription RangesInDataPart::getDescription() const
{
    return RangesInDataPartDescription{
        .info = data_part->info,
        .ranges = ranges,
    };
}

size_t RangesInDataPart::getMarksCount() const
{
    size_t total = 0;
    for (const auto & range : ranges)
        total += range.end - range.begin;

    return total;
}

size_t RangesInDataPart::getRowsCount() const
{
    return data_part->index_granularity.getRowsCountInRanges(ranges);
}

size_t RangesInDataParts::getMarksCountAllParts() const
{
    size_t result = 0;
    for (const auto & part : *this)
        result += part.getMarksCount();
    return result;
}

size_t RangesInDataParts::getRowsCountAllParts() const
{
    size_t result = 0;
    for (const auto & part: *this)
        result += part.getRowsCount();
    return result;
}

}
