// The simplest version:
// Data structures for depth first search is created internally,
// and depth first search runs internally.
template <class Graph, class DomTreePredMap>
void
lengauer_tarjan_dominator_tree
  (const Graph& g,const typename graph_traits<Graph>::vertex_descriptor& entry,DomTreePredMap domTreePredMap)

// The version providing data structures for depth first search:
// After calling this function,
// user can reuse the depth first search related information
// filled in property maps.
template <class Graph, class IndexMap, class TimeMap, class PredMap,
             class VertexVector, class DomTreePredMap>
void
lengauer_tarjan_dominator_tree
  (const Graph& g,
   const typename graph_traits<Graph>::vertex_descriptor& entry,
   const IndexMap& indexMap,
   TimeMap dfnumMap, PredMap parentMap, VertexVector& verticesByDFNum,
   DomTreePredMap domTreePredMap)

// The version without depth first search:
// The caller should provide depth first search related information
// evaluated before.
template <class Graph, class IndexMap, class TimeMap, class PredMap,
             class VertexVector, class DomTreePredMap>
void
lengauer_tarjan_dominator_tree_without_dfs(
  (const Graph& g,
   const typename graph_traits<Graph>::vertex_descriptor& entry,
   const IndexMap& indexMap,
   TimeMap dfnumMap, PredMap parentMap, VertexVector& verticesByDFNum,
   DomTreePredMap domTreePredMap)
