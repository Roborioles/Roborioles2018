// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "AutoElevatorExec.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoElevatorExec::AutoElevatorExec(double wait): frc::Command() {
    m_wait = wait;
    t = 0;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::elevator.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void AutoElevatorExec::Initialize() {
	SetTimeout(m_wait + 2);
	t = 0;
}

// Called repeatedly when this Command is scheduled to run
void AutoElevatorExec::Execute() {
	if (t == 0) {
		Wait(m_wait);
	}
	t++;
	Robot::elevator->ElevatorExecute();
}

// Make this return true when this Command no longer needs to run execute()
bool AutoElevatorExec::IsFinished() {
	if (IsTimedOut() || Robot::elevator->AutoFinished()) {
		return true;
	}
    return false;
}

// Called once after isFinished returns true
void AutoElevatorExec::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoElevatorExec::Interrupted() {

}