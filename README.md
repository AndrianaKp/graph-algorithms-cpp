# Graph Algorithms in C++ (LEDA & Boost)

Implementations and experimental comparison of classic graph algorithms in C++, written for the *Algorithm Implementation Technologies* course (University of Patras, CEID). Each project includes correctness tests and timing experiments on graphs with up to **100,000 nodes / 500,000 edges**.

![C++](https://img.shields.io/badge/C++-00599C?logo=cplusplus&logoColor=white)
![Boost](https://img.shields.io/badge/Boost_Graph_Library-grey)
![LEDA](https://img.shields.io/badge/LEDA-grey)

| Project | Algorithms | Libraries |
|---|---|---|
| [`mst-prim-sollin/`](mst-prim-sollin) | Minimum Spanning Tree: Prim (priority queue) and Sollin/Borůvka, compared with LEDA's `MIN_SPANNING_TREE` | LEDA |
| [`shortest-paths-astar/`](shortest-paths-astar) | Dijkstra vs A* with **Euclidean** and **landmark (ALT)** heuristics, compared with LEDA's `DIJKSTRA_T` | Boost Graph Library (Fibonacci heap), LEDA |

---

## 1. Minimum Spanning Trees: Prim vs Sollin

- **Prim** with LEDA `node_pq` and `decrease_p` → O(m log n)
- **Sollin (Borůvka)**: every component picks its cheapest outgoing edge each round
- Tested on 5 graph families (random sparse, random dense, planar, complete, grid), K = 5 runs each, random weights in [1, 1000]
- Correctness check on a textbook graph (expected MST cost = 80) for all three implementations

| Graph | n | m | Prim | LEDA |
|---|---|---|---|---|
| Random sparse | 100,000 | 500,000 | **0.276 s** | 0.312 s |
| Random dense | 2,000 | 1,000,000 | 0.208 s | **0.048 s** |

**Finding:** my Sollin implementation relabels component IDs with a full node scan after each merge, which makes it O(n²) in practice; it is only run up to n = 1,000. Using a **Union-Find** structure would bring it back to O(m log n), which is the improvement I identified in the report.

## 2. Shortest Paths: Dijkstra vs A*

- Graph stored as a Boost `adjacency_list` (bidirectional, so the reverse graph is available for free)
- **Fibonacci heap** with handles for O(1) decrease-key
- A* takes the heuristic as a `std::function`, so heuristics are interchangeable:
  - **Euclidean distance** (grid graphs, weights in [1, 2])
  - **Landmarks / ALT**: precomputed distances from L1 and to L2 (reverse Dijkstra), `h(u) = max(d(L1,t) − d(L1,u), d(u,L2) − d(t,L2))`, with overflow-safe handling of unreachable nodes
- Distances from Dijkstra and A* match in every experiment

Selected results (grid 60 × 1000, weights in [1, 100], landmark heuristic):

| Algorithm | Nodes explored | Time |
|---|---|---|
| Dijkstra | 59,910 | 23 ms |
| A* (landmarks) | **33,239** (−45%) | **10 ms** |

On a random graph with 20,000 nodes / 40,000 edges, A* with landmarks explored **622** nodes versus **6,185** for Dijkstra.

---

## Build

Both projects need a LEDA installation (`/usr/local/LEDA` by default, edit the Makefile otherwise); the shortest-path project also needs Boost.

```bash
cd mst-prim-sollin/bin && make compile && make run
cd shortest-paths-astar/bin && make compile && make run
```
