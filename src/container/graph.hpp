#pragma once

#pragma once

#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <string>
#include <optional>
#include <algorithm>
#include <memory>

namespace Container {

struct GraphAdjacency;

struct GraphNode
{
  explicit GraphNode(const std::string& _label);

  std::string label;
  std::list<GraphAdjacency> adjacent;
};

struct GraphAdjacency
{
  explicit GraphAdjacency(std::weak_ptr<GraphNode> _node, size_t _coast);

  std::weak_ptr<GraphNode> node;
  size_t coast;
};

using GraphNodePtr = std::shared_ptr<GraphNode>;


class Graph
{
public:
  std::optional<size_t> first(const std::string& label) const;
  std::optional<size_t> next(const std::string& label, size_t index) const;

  void add_node(const std::string& label);
  void add_adj(const std::string& from, const std::string& to, size_t coast);

  GraphNodePtr vertex(const std::string& label, size_t index) const;

  void del_node(const std::string& label);
  void del_adj(const std::string& from, const std::string& to);

  void edit_node(const std::string& label, const std::string& new_label);
  void edit_adj(const std::string& from, const std::string& to, size_t new_coast);

  template <class Predicate>
  bool bfs_iterate(size_t start_index, Predicate p) const;

  size_t radius() const;

private:
  std::vector<GraphNodePtr> data_;

  size_t shortest_path(const GraphNodePtr from, const GraphNodePtr to) const;

  GraphNodePtr center() const;

  std::vector<GraphNodePtr>::const_iterator get_node(const std::string& label) const;
  std::vector<GraphNodePtr>::iterator get_node(const std::string& label);
};


template <class Predicate>
bool Graph::bfs_iterate(size_t start_index, Predicate p) const
{
  if (data_.size() < start_index)
    return false;

  std::unordered_map<std::string, bool> visited;
  for (const auto& node : data_) {
    visited[node->label] = false;
  }


  std::queue<GraphNodePtr> q;
  q.push(data_[start_index]);

  visited[data_[start_index]->label] = true;

  while (!q.empty()) {
    const auto node = q.front();
    q.pop();

    if (p(node))
      return true;

    for (const auto& item : node->adjacent) {
      const auto adj_node = item.node.lock();

      if (!visited[adj_node->label]) {
        q.push(adj_node);
        visited[adj_node->label] = true;
      }
    }
  }

  return false;
}

} // namespace Container
