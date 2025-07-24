#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "multi_map_nav/action/multi_map_navigate.hpp"
#include "multi_map_nav/wormhole_db.hpp"

class MultiMapNavServer : public rclcpp::Node {
public:
    using Navigate = multi_map_nav::action::MultiMapNavigate;
    using GoalHandle = rclcpp_action::ServerGoalHandle<Navigate>;

    MultiMapNavServer() : Node("multi_map_nav_server") {
        wormhole_db_ = std::make_shared<WormholeDB>("/path/to/wormholes.db");
        wormhole_db_->connect();

        action_server_ = rclcpp_action::create_server<Navigate>(
            this,
            "multi_map_navigate",
            std::bind(&MultiMapNavServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&MultiMapNavServer::handle_cancel, this, std::placeholders::_1),
            std::bind(&MultiMapNavServer::handle_accepted, this, std::placeholders::_1)
        );
    }

private:
    rclcpp_action::Server<Navigate>::SharedPtr action_server_;
    std::shared_ptr<WormholeDB> wormhole_db_;

    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID&, std::shared_ptr<const Navigate::Goal> goal) {
        RCLCPP_INFO(get_logger(), "Received goal for map: %s", goal->target_map.c_str());
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandle>) {
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handle_accepted(const std::shared_ptr<GoalHandle> goal_handle) {
        std::thread([this, goal_handle]() {
            const auto goal = goal_handle->get_goal();
            // Handle map switching + move_base goal publishing here
            // Use wormhole_db_->getWormholesTo(goal->target_map)
        }).detach();
    }
};
