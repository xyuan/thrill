/*******************************************************************************
 * benchmarks/chaining/chain_count.cpp
 *
 * Runner program for WordCount example. See thrill/examples/word_count.hpp for
 * the source to the example.
 *
 * Part of Project Thrill - http://project-thrill.org
 *
 * Copyright (C) 2015 Timo Bingmann <tb@panthema.net>
 *
 * All rights reserved. Published under the BSD-2 license in the LICENSE file.
 ******************************************************************************/

#include <thrill/api/dia.hpp>
#include <thrill/api/generate.hpp>
#include <thrill/api/size.hpp>
#include <thrill/common/logger.hpp>
#include <thrill/common/stats_timer.hpp>
#include <tlx/cmdline_parser.hpp>

#include <benchmarks/chaining/helper.hpp>

#include <string>

using namespace thrill; // NOLINT

int main(int argc, char* argv[]) {

    tlx::CmdlineParser clp;

    std::string input;
    clp.add_param_string("input", input,
                         "number of elements");

    if (!clp.process(argc, argv)) {
        return -1;
    }

    clp.print_result();

    size_t count = std::stoi(input);

    common::StatsTimerStopped timer;

    auto start_func =
        [&count, &timer](api::Context& ctx) {
            auto key_value = Generate(
                ctx, count,
                [](const size_t& index) {
                    return KeyValue { index, index + 10 };
                });

            timer.Start();
            // auto result = key_value.map10;
            auto result = key_value.map.map.map.map.map.map.map.map.map.map;
            result.Size();
            timer.Stop();
        };

    api::Run(start_func);
    LOG1 << "took" << timer.Microseconds();

    return 0;
}

/******************************************************************************/
