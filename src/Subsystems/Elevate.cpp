// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "../Robot.h"
#include "Elevate.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevate::Elevate() : frc::Subsystem("Elevate") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    deployTop = RobotMap::elevateDeployTop;
    deployBottom = RobotMap::elevateDeployBottom;
    rightElevate = RobotMap::elevateRightElevate;
    leftElevate = RobotMap::elevateLeftElevate;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}

void Elevate::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Elevate::Periodic() {
    // Put code here to be run every loop

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevate::Raise(int position) {
	if (deployTop->Get()==false){
		// left
		if (position==1) {
			printf("Raising left\n");
			if (leftElevate->Get()==frc::DoubleSolenoid::Value::kForward) {
				leftElevate->Set(frc::DoubleSolenoid::Value::kOff);
			} else {
				leftElevate->Set(frc::DoubleSolenoid::Value::kForward);
			}
		} else { // right
			printf("Raising Right\n");
			if (rightElevate->Get()==frc::DoubleSolenoid::Value::kForward) {
				rightElevate->Set(frc::DoubleSolenoid::Value::kOff);
			} else {
				rightElevate->Set(frc::DoubleSolenoid::Value::kForward);
			}
		}
	}
}

void Elevate::Deploy() {
	deployTop->Set(false);
}

void Elevate::Extend() {
	deployTop->Set(true);
	deployBottom->Set(true);
}

void Elevate::ElevateInit() {
	leftElevate->Set(frc::DoubleSolenoid::Value::kOff);
	rightElevate->Set(frc::DoubleSolenoid::Value::kOff);
}
