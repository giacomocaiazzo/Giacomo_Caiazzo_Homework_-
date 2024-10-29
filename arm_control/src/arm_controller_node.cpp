#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector> // Per std::vector
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp" // Inclusione della classe Float64MultiArray
#include "sensor_msgs/msg/joint_state.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class Controller : public rclcpp::Node
{
  public:
    Controller()
    : Node("controller")
    {
    
    	values_.resize(4);
    	
    	std::cout << "Enter " << "4" << " elements:\n";
      	std::cin >> values_[0] >> values_[1] >> values_[2] >> values_[3];
      	
      // Cambia il tipo del publisher
      publisher_ = this->create_publisher<std_msgs::msg::Float64MultiArray>("/position_controller/commands", 10);
      
      // Timer che chiama timer_callback ogni 500 ms
      timer_ = this->create_wall_timer(
      500ms, std::bind(&Controller::timer_callback, this));
      
      // Cambia il tipo della subscription a Float64MultiArray
      subscription_ = this->create_subscription<sensor_msgs::msg::JointState>(
      "/joint_states", 10, std::bind(&Controller::topic_callback, this, _1));
      
    }

  private:
    void timer_callback()
    {
      // Crea un oggetto Float64MultiArray
      auto message = std_msgs::msg::Float64MultiArray();
      // Popola l'array con dei valori (ad esempio, valori incrementali)
      for (size_t i = 0; i < 4; ++i) {
        message.data.push_back(static_cast<double>(values_[i])); // Aggiungi valori all'array
      }

      // Pubblica il messaggio
      publisher_->publish(message);
    }
    
    // Modifica del tipo di parametro nel callback
    void topic_callback(const sensor_msgs::msg::JointState & message) const
    {
      // Logga i valori ricevuti
      RCLCPP_INFO(this->get_logger(), "position: [%.2f, %.2f, %.2f, %.2f]", message.position[0], message.position[1], message.position[2], message.position[3]);
      
    }
   
   // Cambia il tipo della subscription
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr subscription_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr publisher_;
    std::vector<float> values_; 
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Controller>());
  rclcpp::shutdown();
  return 0;
}

