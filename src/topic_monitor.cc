//#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "rclcpp_components/register_node_macro.hpp"
using std::placeholders::_1;

class TopicMonitor : public rclcpp::Node
{
  public:
    TopicMonitor()
    : Node("TopicMonitor")
    {
        rclcpp::SubscriptionOptions sub_opts;
        // Update the subscription options, so an event handler that will report the number of lost
        // messages is created together with the subscription.
        sub_opts.event_callbacks.message_lost_callback =
        [logger = this->get_logger()](rclcpp::QOSMessageLostInfo & info)
        {
            RCLCPP_INFO_STREAM(
            logger,
            "Some messages were lost:\n>\tNumber of new lost messages: " <<
                info.total_count_change << " \n>\tTotal number of messages lost: " <<
                info.total_count);
        };
        // Create the subscription. This will also create an event handler based on the above
        // subscription options.
        subscription_ = this->create_subscription<std_msgs::msg::String>(
      "test_topic", 1, std::bind(&TopicMonitor::topic_callback, this, _1), sub_opts);
    }

  private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<TopicMonitor>());
  rclcpp::shutdown();
  return 0;
}