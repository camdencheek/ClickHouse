#pragma once

#include <Core/NamesAndTypes.h>
#include <Storages/MergeTree/RangesInDataPart.h>
#include <Storages/MergeTree/MergeTreeBlockReadUtils.h>
#include <Storages/MergeTree/MergeTreeData.h>
#include <Storages/SelectQueryInfo.h>
#include "Storages/MergeTree/MergeTreeBaseSelectProcessor.h"
#include "Storages/MergeTree/MergeTreeReadPool.h"
#include <mutex>


namespace DB
{


class MergeTreeReadPoolParallelReplicas :  private boost::noncopyable
{

public:


    MergeTreeReadPoolParallelReplicas(
        size_t threads,
        ParallelReadingExtension externsion_,
    )
    {}

    /// Sends all the data about selected parts to the initiator
    void initialize();


private:


    RangesInDataParts parts_ranges;

    mutable std::mutex mutex;

    Poco::Logger * log = &Poco::Logger::get("MergeTreeReadPool");

}




}
