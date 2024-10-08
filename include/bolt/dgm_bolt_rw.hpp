/**
 * @file dgm_bolt.hpp
 * @author Manuel Wuthrich
 * @author Maximilien Naveau
 * @author Julian Viereck
 * @author Johannes Pfleging
 * @license License BSD-3-Clause
 * @copyright Copyright (c) 2019, New York University and Max Planck
 * Gesellshaft.
 */

#ifndef DGM_SOLO_HH
#define DGM_SOLO_HH

#include "bolt/bolt_rw.hpp"
#include "dynamic_graph_manager/dynamic_graph_manager.hpp"
#include "mim_msgs/srv/joint_calibration.hpp"
#include "yaml_utils/yaml_cpp_fwd.hpp"

namespace bolt
{
class DGMBoltRW : public dynamic_graph_manager::DynamicGraphManager
{
public:
    /**
     * @brief DemoSingleMotor is the constructor.
     */
    DGMBoltRW();

    /**
     * @brief ~DemoSingleMotor is the destructor.
     */
    ~DGMBoltRW();

    /**
     * @brief is_in_safety_mode check if the dynamic graph is still alive and
     * sending commands at a descent frequency. Inheriting this method is not
     * mandatory but recommanded.
     * This function make also sure that the joint velocity do not exceed
     * a certain value
     * @return true if there is a problem.
     */
     bool is_in_safety_mode();

    /**
     * @brief initialize_hardware_communication_process is the function that
     * initialize the hardware.
     */
    void initialize_hardware_communication_process();

    /**
     * @brief get_sensors_to_map acquieres the sensors data and feed it to the
     * input/output map
     * @param[in][out] map is the sensors data filled by this function.
     */
    void get_sensors_to_map(dynamic_graph_manager::VectorDGMap& map);

    /**
     * @brief set_motor_controls_from_map reads the input map that contains the
     * controls and send these controls to the hardware.
     * @param map
     */
    void set_motor_controls_from_map(
        const dynamic_graph_manager::VectorDGMap& map);

    /**
     * @brief Ros callback for the callibration procedure. Warning the robot
     * will move to the next the joint index and back to "0" upon this call.
     * Be sure that no controller are running in parallel.
     *
     * @param req nothing
     * @param res True if everything went well.
     * @return true if everything went well.
     * @return false if something went wrong.
     */
    void calibrate_joint_position_callback(
        mim_msgs::srv::JointCalibration::Request::SharedPtr req,
        mim_msgs::srv::JointCalibration::Response::SharedPtr res);

private:
    /**
     * @brief Calibrate the robot joint position
     *
     * @param zero_to_index_angle is the angle between the theoretical zero and
     * the next positive angle.
     */
    void calibrate_joint_position();

    /**
     * Entries for the real hardware.
     */

    /**
     * @brief test_bench_ the real test bench hardware drivers.
     */
    BoltRW bolt_;

    /**
     * @brief ctrl_joint_torques_ the joint torques to be sent. Used in this
     * class to perform a local copy of the control. This is need in order
     * to send this copy to the Bolt class
     */
    Eigen::Vector7d ctrl_joint_torques_;

    /**
     * @brief Check if we entered once in the safety mode and stay there if so
     */
    bool was_in_safety_mode_;

    /**
     * @brief These are the calibration value extracted from the paramters.
     * They represent the distance between the theorical zero joint angle and
     * the next jont index.
     */
    Eigen::Vector7d zero_to_index_angle_from_file_;
};

}  // namespace bolt

#endif  // DGM_TEST_BENCH_8_MOTORS_HH
