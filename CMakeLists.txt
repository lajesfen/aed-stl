cmake_minimum_required(VERSION 3.28)
project(Algorithm)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Algorithm
        main.cpp
        src/forward_list.h
        src/doubly_linked_list.h
        src/circular_list.h
        src/stack.h
        src/queue.h
        src/hash_table.h
        src/binary_tree.h
        src/avl_tree.h
        src/max_heap.h
        src/min_heap.h
        src/graph_matrix.h
        src/trie.h
        src/disjoint_set.h
        src/mst.h
        src/b_tree.h
        src/graph_list.h
        src/simplified_graph.h
        src/simplified_graph.h)
