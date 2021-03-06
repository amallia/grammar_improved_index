//
// Created by alejandro on 15-05-19.
//

#include <iostream>
#include <fstream>
#include <gflags/gflags.h>
#include <benchmark/benchmark.h>


#include "repetitive_collections.h"
#include "utils.h"

#define MAX 1000

using namespace std::chrono;
using timer = std::chrono::high_resolution_clock;

std::vector<size_t> random_nodes(MAX);
std::vector<size_t> random_childs(MAX);
std::vector<size_t> random_leaves(MAX);
std::vector<size_t> random_ancestor(MAX);

bp_tree _tree;
uint code = 5;

size_t n_nodes = 0;
size_t n_leaves = 0;
std::vector<size_t> n_childs;
std::vector<size_t> pos;
std::vector<size_t> node_depth;


void generate_random_queries(std::vector<size_t> &R, const size_t &n) {
    std::srand(std::time(nullptr));

    for (int i = 0; i < MAX; ++i) {
        R[i] = rand() % n + 1;

    }

}

void generate_random_queries(std::vector<size_t> &R, std::vector<size_t> &N) {
    std::srand(std::time(nullptr));

    for (int i = 0; i < MAX; ++i) {
        size_t rn = random_nodes[i];
        size_t v = N[rn];
        if (v == 0)
            R[i] = 0;
        else
            R[i] = rand() % (v) + 1;

    }

}

static void load_tree(benchmark::State &state) {

    std::cout << "loading mtree from " << collections_code_inv[code] << "\n";
    fstream f(read_path + std::to_string(code) + "_tree_dfuds", std::ios::in | std::ios::binary);

    for (auto _ : state) {
        _tree.load(f);
        sleep(3);
    }

    size_t b_size = _tree.bit_vector.size();
    size_t b_r_1 = _tree.bps.rank(_tree.bit_vector.size() - 1);

    std::cout << "SIZE OF BITVECTOR: " << b_size << "\n";
    std::cout << "RANK 1 IN SIZE: " << b_r_1 << "\n";

    n_nodes = b_size - b_r_1 - 1;
    std::cout << "NUMBER OF NODES: " << n_nodes << "\n";
    n_leaves = _tree.rank_10(_tree.bit_vector.size());
    std::cout << "NUMBER OF LEAVES: " << n_leaves << "\n";

    n_childs.resize(n_nodes);
    random_childs.resize(MAX);
    pos.resize(n_nodes);
    node_depth.resize(n_nodes);
    size_t max_child =  0;
    size_t max_depth =  0;

    for (size_t ii = 0; ii < n_nodes; ++ii) {
        size_t p_node = _tree[ii + 1];
        pos[ii] = p_node;
        n_childs[ii] = _tree.children(p_node);
        max_child = (max_child < n_childs[ii])?n_childs[ii]:max_child;
        node_depth[ii] = _tree.depth(p_node);
        max_depth = (max_depth < node_depth[ii])?node_depth[ii]:max_depth;
    }
    std::cout<<"MAX CHILDS "<<max_child<<"\n";
    std::cout<<"MAX DEPTH "<<max_depth<<"\n";


    std::cout << "generate_random_nodes_queries" << std::endl;
    generate_random_queries(random_nodes, n_nodes);
    std::cout << "generate_random_child_queries" << std::endl;
    generate_random_queries(random_childs, n_childs);
    std::cout << "generate_random_leaves_queries" << std::endl;
    generate_random_queries(random_leaves, n_leaves);
    std::cout << "generate_random_depth_queries" << std::endl;
    generate_random_queries(random_ancestor, node_depth);

    std::cout << "end_load" << std::endl;
}


static void isleaf(benchmark::State &state) {

    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.isleaf(pos[random_nodes[i]]);
        }

    }

}
static void child(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            size_t node = random_nodes[i];
            _tree.child(pos[node],random_childs[i]);
        }

    }

}
static void pre_order(benchmark::State &state) {

    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.pre_order(pos[random_nodes[i]]);
        }
    }
}
static void operator_sel(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree[random_nodes[i]];
        }

    }
}
static void nsibling(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.nsibling(pos[random_nodes[i]]);
        }

    }
}
static void lchild(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.lchild(pos[random_nodes[i]]);
        }
    }
}
static void fchild(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.fchild(pos[random_nodes[i]]);
        }
    }
}
static void depth(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.depth(pos[random_nodes[i]]);
        }
    }
}
static void levelancestor(benchmark::State &state){
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {

            _tree.levelancestor(random_nodes[i],random_ancestor[i]);
        }
    }
}
static void children(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.children(pos[random_nodes[i]]);
        }
    }
}
static void parent(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.parent(pos[random_nodes[i]]);
        }
    }
}
static void subtree(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX-1; ++i) {
            _tree.subtree(pos[random_nodes[i]]);
        }
    }
}
static void leafrank(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.leafrank(pos[random_nodes[i]]);
        }
    }
}
static void leafnum(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.leafnum(pos[random_nodes[i]]);
        }
    }
}
static void leafselect(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.leafselect(random_leaves[i]);
        }
    }
}
static void level_anc(benchmark::State &state) {
    for (auto _ : state) {
        for (int i = 0; i < MAX; ++i) {
            _tree.bps.level_anc(random_nodes[i],random_ancestor[i]);
        }
    }
}




BENCHMARK(load_tree)     ->Unit(benchmark::kMicrosecond);
BENCHMARK(isleaf)        ->Unit(benchmark::kMicrosecond);
BENCHMARK(child)         ->Unit(benchmark::kMicrosecond);
BENCHMARK(pre_order)     ->Unit(benchmark::kMicrosecond);
BENCHMARK(operator_sel)  ->Unit(benchmark::kMicrosecond);
BENCHMARK(nsibling)      ->Unit(benchmark::kMicrosecond);
BENCHMARK(lchild)        ->Unit(benchmark::kMicrosecond);
BENCHMARK(fchild)        ->Unit(benchmark::kMicrosecond);
BENCHMARK(depth)         ->Unit(benchmark::kMicrosecond);
BENCHMARK(levelancestor) ->Unit(benchmark::kMicrosecond);
BENCHMARK(level_anc)     ->Unit(benchmark::kMicrosecond);
BENCHMARK(children)      ->Unit(benchmark::kMicrosecond);
BENCHMARK(parent)        ->Unit(benchmark::kMicrosecond);
BENCHMARK(subtree)       ->Unit(benchmark::kMicrosecond);
BENCHMARK(leafrank)      ->Unit(benchmark::kMicrosecond);
BENCHMARK(leafselect)    ->Unit(benchmark::kMicrosecond);
BENCHMARK(leafnum)       ->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
