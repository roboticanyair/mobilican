/*******************************************************************************
* Copyright (c) 2018 RoboTICan
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the disclaimer
* below) provided that the following conditions are met:
*
*     * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*     * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*
*     * Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
* THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

/* Author: Elhay Rauper*/

#ifndef MOBILICAN_HW_SERVO_LIFT_H
#define MOBILICAN_HW_SERVO_LIFT_H

#include <hardware_interface/joint_command_interface.h>
#include <lpf_ros/lpf_ros.h>
#include "mobilican_hw/utils.h"

class EffortPositionControl {

private:
    std::string joint_name_;
    double position_ = 0;
    double prev_position_ = 0;
    double velocity_ = 0;
    double effort_ = 0;
    double command_effort_ = 0;
    float pos_filter_alpha_ = 0;
    bool use_position_filter_ = false;
    bool first_read_ = true;

    lpf::Lpf pos_filter_;
    ros::NodeHandle * nh_ = nullptr;
    std::vector<hardware_interface::JointStateHandle> joint_state_handles_;
    std::vector<hardware_interface::JointHandle> pos_handles_;

public:
    EffortPositionControl(ros::NodeHandle & nh, std::string joint_name);
    void registerHandles(hardware_interface::JointStateInterface &joint_state_interface,
                            hardware_interface::EffortJointInterface &effort_interface);
    double output() { return command_effort_; };
    void update(double position, const ros::Duration elapsed);
    void usePositionFilter(float alpha);
    void initPositionFilter(double init_position);
};


#endif //MOBILICAN_HW_SERVO_LIFT_H
