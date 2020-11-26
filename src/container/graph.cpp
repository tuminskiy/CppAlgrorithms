#include "graph.hpp"

#include <iterator>
#include <unordered_map>

namespace Container {

GraphNode::GraphNode(const std::string& _label)
  : label(_label)
{ }

GraphAdjacency::GraphAdjacency(std::weak_ptr<GraphNode> _node, size_t _coast)
  : node(_node)
  , coast(_coast)
{ }


std::optional<size_t> Graph::first(const std::string& label) const
{
  const auto it = get_node(label);

  if (it == data_.end() || it->get()->adjacent.empty())
    return std::nullopt;

  const auto target = find(data_.begin(), data_.end(),
                           it->get()->adjacent.front().node.lock());

  if (target == data_.end())
    return std::nullopt;

  return target - data_.begin();
}

std::optional<size_t> Graph::next(const std::string& label, size_t index) const
{
  const auto it = get_node(label);

  if (it == data_.end() || it->get()->adjacent.empty())
    return std::nullopt;

  const auto& adj = it->get()->adjacent;

  const auto adj_it = find_if(adj.begin(), adj.end(),
    [&node = data_[index]](const auto& item) {
      return node == item.node.lock();
    }
  );

  const auto next_adj_it = std::next(adj_it);

  if (next_adj_it == adj.end())
    return std::nullopt;

  const auto target = find(data_.begin(), data_.end(),
                           next_adj_it->node.lock());

  if (target == data_.end())
    return std::nullopt;

  return target - data_.begin();
}


void Graph::add_node(const std::string& label)
{
  data_.push_back(std::make_shared<GraphNode>(label));
}

void Graph::add_adj(const std::string& from, const std::string& to, size_t coast)
{
  auto it_from = get_node(from);
  auto it_to = get_node(to);

  it_from->get()->adjacent.emplace_back(*it_to, coast);
}


GraphNodePtr Graph::vertex(const std::string& label, size_t index) const
{
  if (data_.size() < index)
    return nullptr;

  const auto it = get_node(label);

  if (it == data_.end() || it->get()->adjacent.empty())
    return nullptr;

  const auto& adj = it->get()->adjacent;

  const auto adj_it = find_if(adj.begin(), adj.end(),
    [&node = data_[index]](const auto& item) {
      return node == item.node.lock();
    }
  );

  if (adj_it == adj.end())
    return nullptr;

  return data_[index];
}


void Graph::del_node(const std::string& label)
{
  const auto it = get_node(label);
  data_.erase(it);
}

void Graph::del_adj(const std::string& from, const std::string& to)
{
  const auto it_from = get_node(from);

  if (it_from == data_.end() || it_from->get()->adjacent.empty())
    return;

  const auto it_to = get_node(from);

  if (it_to == data_.end())
    return;

  auto& adj = it_from->get()->adjacent;

  const auto it_adj = find_if(adj.begin(), adj.end(),
    [&node = *it_to](const auto& item) {
      return node == item.node.lock();
    }
  );

  adj.erase(it_adj);
}


void Graph::edit_node(const std::string& label, const std::string& new_label)
{
  auto it = get_node(label);

  if (it != data_.end())
    it->get()->label = new_label;
}

void Graph::edit_adj(const std::string& from, const std::string& to, size_t new_coast)
{
  const auto it_from = get_node(from);

  if (it_from == data_.end() || it_from->get()->adjacent.empty())
    return;

  const auto it_to = get_node(to);

  if (it_to == data_.end())
    return;

  auto& adj = it_from->get()->adjacent;

  const auto it_adj = find_if(adj.begin(), adj.end(),
    [&node = *it_to](const auto& item) {
      return node == item.node.lock();
    }
  );

  adj.erase(it_adj);
}


size_t Graph::radius() const
{
  std::vector<size_t> distances;
  distances.reserve(data_.size());

  std::transform(data_.begin(), data_.end(), std::back_inserter(distances),
    [from = center(), this](auto to) {
      return shortest_path(from, to);
    }
  );

  return *std::max_element(distances.begin(), distances.end());
}


size_t Graph::shortest_path(const GraphNodePtr from, const GraphNodePtr to) const
{
  if (from == to)
    return 0;

  // Has the node been visited
  std::unordered_map<std::string, bool> visited;
  // Minimal distance from node "from" to other nodes
  std::unordered_map<std::string, size_t> distances;

  for (const auto& node : data_) {
    visited[node->label] = false;
    distances[node->label] = std::numeric_limits<size_t>::max();
  }

  std::queue<GraphNodePtr> q;
  q.push(from);
  distances[from->label] = 0;

  auto from_adj_to_queue = [&q](const auto& adj) {
    for (const auto& item : adj) {
      q.push(item.node.lock());
    }
  };

  while (!q.empty()) {
    const auto current = q.front();
    q.pop();

    if (visited[current->label])
      continue;

    // iteration over all neighboring nodes
    for (const auto& adj : current->adjacent) {
      const auto node = adj.node.lock();

      // distance to current adj node
      auto& current_dist = distances[node->label];
      const auto new_dist = distances[current->label] + adj.coast;

      current_dist = std::min(current_dist, new_dist);
    }

    visited[current->label] = true;
    // push all neighboring nodes to queue
    from_adj_to_queue(current->adjacent);
  }

  return distances[to->label];
}

GraphNodePtr Graph::center() const
{
  std::unordered_map<
      GraphNodePtr, std::unordered_map<GraphNodePtr, size_t>
  > distance_matrix;

  for (const auto from : data_) {
    for (const auto to : data_) {
      distance_matrix[from][to] = shortest_path(from, to);
    }
  }

  auto by_coast = [](const auto& lhs, const auto& rhs) {
    return lhs.second < rhs.second;
  };

  std::unordered_map<GraphNodePtr, size_t> max_distances;

  for (const auto& [from, to] : distance_matrix) {
    const auto it = std::max_element(to.begin(), to.end(), by_coast);
    max_distances[from] = it->second;
  }

  return std::min_element(max_distances.begin(), max_distances.end(), by_coast)->first;
}


auto Graph::get_node(const std::string& label) const
  -> std::vector<GraphNodePtr>::const_iterator
{
  return find_if(data_.begin(), data_.end(),
    [&label](const auto& node) {
      return node->label == label;
    }
  );
}

auto Graph::get_node(const std::string& label)
  -> std::vector<GraphNodePtr>::iterator
{
  return find_if(data_.begin(), data_.end(),
    [&label](const auto& node) {
      return node->label == label;
    }
  );
}


} // namespace Container
