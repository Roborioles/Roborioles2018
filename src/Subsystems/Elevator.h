// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Elevator: public frc::Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<WPI_TalonSRX> elevatorMotor;
	std::shared_ptr<frc::SpeedController> elevatorLEDs;
	std::shared_ptr<frc::Ultrasonic> ultraS;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	double targetPos = 0;
	bool bottomLimitHit = false;
	bool incrementButtonDown = false;
	bool isTargetMoving = false;
	bool isManualMoving = false;
	bool targetMode = false;
	bool isGoingToFloor = false;
public:
	Elevator();
	void InitDefaultCommand() override;
	void Periodic() override;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	void Init();
	void ElevatorGoToRevolutions(double newTargetPos);
	void ElevatorGoToExchange();
	void ElevatorGoToSwitch();
	void ElevatorGoToScale();
	void ElevatorGoToHighScale();
	void ElevatorGoToFloor();
	void ElevatorGoToInches(double inches);
	//void ElevatorGoToSwitch();
	//void ElevatorGoToScale();
	//void ElevatorGoToHighScale();
	//void ElevatorGoToFloor();
	void ElevatorExecute();
	void ElevatorExecuteTarget();
	void ElevatorMoveUp();
	void ElevatorMoveDown();
	void PartyLight(bool isMoving, double encoderValue);
	void SetPIDs();
};

#endif
