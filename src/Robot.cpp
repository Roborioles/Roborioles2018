// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Robot.h"
#include "Commands/Drive.h"
#include <CameraServer.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveBase> Robot::driveBase;
std::shared_ptr<Elevator> Robot::elevator;
std::shared_ptr<IntakeSub> Robot::intakeSub;
std::shared_ptr<Elevate> Robot::elevate;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

bool Robot::teleop = false;
bool Robot::intrpt = false;
int Robot::teleopReset = 0;

void Robot::RobotInit() {
	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveBase.reset(new DriveBase());
    elevator.reset(new Elevator());
    intakeSub.reset(new IntakeSub());
    elevate.reset(new Elevate());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// Add commands to Autonomous Sendable Chooser
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS


	chooser.AddDefault("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	frc::SmartDashboard::PutData("Auto Modes", &chooser);
	//CameraServer::GetInstance()->StartAutomaticCapture();
	Robot::driveBase->ShiftingInfo();
	teleopReset = 0;
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	Robot::driveBase->EncoderReset();
	Robot::driveBase->ResetAngle();
	SmartDashboard::PutBoolean("DB/Button 0",false);
	SmartDashboard::PutBoolean("DB/Button 1",false);
	SmartDashboard::PutBoolean("DB/Button 2",false);
	SmartDashboard::PutBoolean("DB/Button 3",false);
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	SmartDashboard::PutString("DB/String 5", "Pressure: " + std::to_string(Robot::driveBase->SensorReading()));
	// Location
	if (SmartDashboard::GetBoolean("DB/Button 0", false)) {
		SmartDashboard::PutBoolean("DB/Button 1",false);
		SmartDashboard::PutString("DB/String 0","Left Position");
	} else if(SmartDashboard::GetBoolean("DB/Button 1", false)) {
		SmartDashboard::PutBoolean("DB/Button 0",false);
		SmartDashboard::PutString("DB/String 0","Right Position");
	} else {
		SmartDashboard::PutString("DB/String 0","Middle Position");
	}
	// Action taken
	if (SmartDashboard::GetBoolean("DB/Button 2", false)) {
		SmartDashboard::PutString("DB/String 9","Switch Override");
		SmartDashboard::PutBoolean("DB/Button 3",false);
	} else if (SmartDashboard::GetBoolean("DB/Button 3", false)){
		SmartDashboard::PutString("DB/String 9","Scale Override");
		SmartDashboard::PutBoolean("DB/Button 2",false);
	} else {
		SmartDashboard::PutString("DB/String 9","");
	}
}

void Robot::AutonomousInit() {
	teleopReset++;
	Robot::intakeSub->openIntake(false);
	Robot::driveBase->EncoderReset();
	Robot::driveBase->ResetAngle();
	Robot::elevate->Extend();
	Robot::elevate->ElevateInit();
	Robot::elevator->Init(false);

	//autonomousCommand = chooser.GetSelected();
	autonomousCommand = new AutonomousCommand();
	if (autonomousCommand != nullptr)
		autonomousCommand->Start();

}

void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
	Robot::driveBase->PrintValues();
	SmartDashboard::PutString("DB/String 5", "Pressure: " + std::to_string(Robot::driveBase->SensorReading()));
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand != nullptr)
		autonomousCommand->Cancel();
	cmd.reset(new Drive());
	cmd->Start();
	if(teleopReset == 0)
		Robot::elevator->Init(true);
	Robot::teleop = true;
	Robot::intrpt = true;
	Robot::driveBase->DisablePID();
	Robot::driveBase->EncoderReset();
	Robot::driveBase->ResetAngle();

	Robot::elevate->ElevateInit();
	Robot::intakeSub->openIntake(false);
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

START_ROBOT_CLASS(Robot);

