#pragma once

#include <vector>

#include <IO/WriteBuffer.h>
#include <IO/ReadBuffer.h>
#include <Storages/MergeTree/MarkRange.h>
#include <Storages/MergeTree/MergeTreeData.h>


namespace DB
{

/// The only purpose of this struct is that serialize and deserialize methods
/// they look natural here because we can fully serialize and then deserialize original DataPart class.
struct RangesInDataPartDescription
{
    MergeTreePartInfo info;
    MarkRanges ranges;

    void serialize(WriteBuffer & out) const;
    void describe(WriteBuffer & out) const;
    void deserialize(ReadBuffer & in);
};

struct RangesInDataPartsDescription: public std::vector<RangesInDataPartDescription>
{
    using std::vector<RangesInDataPartDescription>::vector;

    void serialize(WriteBuffer & out) const;
    void describe(WriteBuffer & out) const;
    void deserialize(ReadBuffer & in);
};

struct RangesInDataPart
{
    MergeTreeData::DataPartPtr data_part;
    size_t part_index_in_query;
    MarkRanges ranges;

    RangesInDataPart() = default;

    RangesInDataPart(
        const MergeTreeData::DataPartPtr & data_part_,
        const size_t part_index_in_query_,
        const MarkRanges & ranges_ = MarkRanges{})
        : data_part{data_part_}
        , part_index_in_query{part_index_in_query_}
        , ranges{ranges_}
    {}

    RangesInDataPartDescription getDescription() const;

    size_t getMarksCount() const;
    size_t getRowsCount() const;
};

struct RangesInDataParts: public std::vector<RangesInDataPart>
{
    using std::vector<RangesInDataPart>::vector;

    size_t getMarksCountAllParts() const;
    size_t getRowsCountAllParts() const;
};

}
