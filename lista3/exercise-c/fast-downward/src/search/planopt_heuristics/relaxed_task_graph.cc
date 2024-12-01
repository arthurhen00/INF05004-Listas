#include "relaxed_task_graph.h"

#include <iostream>
#include <vector>
#include <deque>

using namespace std;

namespace planopt_heuristics {
RelaxedTaskGraph::RelaxedTaskGraph(const TaskProxy &task_proxy)
    : relaxed_task(task_proxy),
      variable_node_ids(relaxed_task.propositions.size()) {
    /*
      TODO: add your code for exercise 2 (b) here. Afterwards
        - variable_node_ids[i] should contain the node id of the variable node for variable i
        - initial_node_id should contain the node id of the initial node
        - goal_node_id should contain the node id of the goal node
        - the graph should contain precondition and effect nodes for all operators
        - the graph should contain all necessary edges.
    */
    for (size_t i = 0; i < variable_node_ids.size(); i++)
    {
        variable_node_ids[i] = graph.add_node(NodeType::OR);
    }

    initial_node_id = graph.add_node(NodeType::AND);
    for(int id : relaxed_task.initial_state){
        graph.add_edge(variable_node_ids[id],initial_node_id);
    }

    for(RelaxedOperator &op : relaxed_task.operators){
        NodeID op_id = graph.add_node(NodeType::AND);
        for(int precondition_id : op.preconditions){
            graph.add_edge(op_id,variable_node_ids[precondition_id]);
        }

        NodeID effect_node = graph.add_node(NodeType::AND, op.cost);
        for(int effect_id : op.effects){
            graph.add_edge(variable_node_ids[effect_id], effect_node);
        }

        graph.add_edge(effect_node, op_id);
    }
    
    goal_node_id = graph.add_node(NodeType::AND);
    for(int id : relaxed_task.goal){
        graph.add_edge(goal_node_id, variable_node_ids[id]);
    }
}

void RelaxedTaskGraph::change_initial_state(const GlobalState &global_state) {
    // Remove all initial edges that where introduced for relaxed_task.initial_state.
    for (PropositionID id : relaxed_task.initial_state) {
        graph.remove_edge(variable_node_ids[id], initial_node_id);
    }

    // Switch initial state of relaxed_task
    relaxed_task.initial_state = relaxed_task.translate_state(global_state);

    // Add all initial edges for relaxed_task.initial_state.
    for (PropositionID id : relaxed_task.initial_state) {
        graph.add_edge(variable_node_ids[id], initial_node_id);
    }
}

bool RelaxedTaskGraph::is_goal_relaxed_reachable() {
    // Compute the most conservative valuation of the graph and use it to
    // return true iff the goal is reachable in the relaxed task.

    graph.most_conservative_valuation();
    return graph.get_node(goal_node_id).forced_true;
}

int RelaxedTaskGraph::additive_cost_of_goal() {
    // Compute the weighted most conservative valuation of the graph and use it
    // to return the h^add value of the goal node.

    // TODO: add your code for exercise 2 (c) here.
    graph.weighted_most_conservative_valuation();
    const AndOrGraphNode &goal_node = graph.get_node(goal_node_id);
    return goal_node.additive_cost;
}

int RelaxedTaskGraph::ff_cost_of_goal() {
    // TODO: add your code for exercise 2 (e) here.
    graph.weighted_most_conservative_valuation();

    deque<NodeID> queue;
    queue.push_back(goal_node_id);

    std::unordered_set<NodeID> visited;

    int total_cost = 0;

    while(!queue.empty()) {
        int node_id = queue.front();
        queue.pop_front();

        if(visited.find(node_id) != visited.end()) { continue; }

        visited.insert(node_id);

        const AndOrGraphNode &node = graph.get_node(node_id);
        total_cost += node.direct_cost;

        if(node.type == NodeType::OR) {
            queue.push_back(node.achiever);
        } else if (node.type == NodeType::AND) {
            for (int successor_id : node.successor_ids) {
                queue.push_back(successor_id);
            }
        }

    }

    return total_cost;
}

}
