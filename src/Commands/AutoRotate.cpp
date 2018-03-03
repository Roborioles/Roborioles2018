// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoRotate.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoRotate::AutoRotate(double angle, double speed): frc::Command() {
    m_angle = angle;
    m_speed = speed;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveBase.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoRotate::Initialize() {
	SetTimeout(5);
	Robot::driveBase->DisablePID();
}

// Called repeatedly when this Command is scheduled to run
void AutoRotate::Execute() {
	Robot::driveBase->RotateToAngle(m_angle,m_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool AutoRotate::IsFinished() {
	if(IsTimedOut() || Robot::driveBase->CheckAngle(m_angle)) {
		return true;
	}
    return false;
}

// Called once after isFinished returns true
void AutoRotate::End() {
	Robot::driveBase->ResetAngle();
	Robot::driveBase->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoRotate::Interrupted() {

}
