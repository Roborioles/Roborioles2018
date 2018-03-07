// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "ctre/Phoenix.h"
#include "ElevatorConstants.h"

#include "Elevator.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/ElevatorTarget.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

Elevator::Elevator() : frc::Subsystem("Elevator") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    elevatorMotor = RobotMap::elevatorElevatorMotor;
    elevatorLEDs = RobotMap::elevatorElevatorLEDs;
    ultraS = RobotMap::elevatorUltraS;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    elevatorMotor->SetInverted(true);
}

void Elevator::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new ElevatorTarget());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

}

void Elevator::Periodic() {
	// Put code here to be run every loop
	//ElevatorExecute();


}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void Elevator::Init(){
	// * * * * * CHANGE MOTOR AND SOLENOID IDS * * * * * * * * * *
	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	//int absolutePosition = elevatorMotor->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	//elevatorMotor->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);


	ultraS->SetAutomaticMode(true);
	elevatorMotor->SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
	targetPos = 0;
	/* choose the sensor and sensor direction */
	elevatorMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx, kTimeoutMs);
	elevatorMotor->SetSensorPhase(true);
	//******************************CHANGE BACK TO TRUE**************************************

	/* set the peak and nominal outputs, 12V means full */
	elevatorMotor->ConfigNominalOutputForward(0, kTimeoutMs);
	elevatorMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
	elevatorMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	elevatorMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);

	//elevatorMotor->Set(ControlMode::Position,0);
	//targetPos = 0;


	/* set closed loop gains in slot0 */
	elevatorMotor->Config_kF(kPIDLoopIdx, 0, kTimeoutMs);
	elevatorMotor->Config_kP(kPIDLoopIdx, 0.12, kTimeoutMs);
	elevatorMotor->Config_kI(kPIDLoopIdx, 0, kTimeoutMs);
	elevatorMotor->Config_kD(kPIDLoopIdx, 0, kTimeoutMs);

}

void Elevator::ElevatorGoToRevolutions(double newTargetPos){
	targetPos = newTargetPos;
	isGoingToFloor = false;
	targetMode = true;
	frc::SmartDashboard::PutString("DB/String 1",std::to_string(targetPos));
}

void Elevator::ElevatorExecute(){
	double ultraValue = ultraS->GetRangeInches();
	frc::SmartDashboard::PutString("DB/String 9",std::to_string(ultraValue));
	double encoderValue = elevatorMotor->GetSelectedSensorPosition(0)/4096.0;
	frc::SmartDashboard::PutString("DB/String 0",std::to_string(encoderValue));
	//check for bottom limit switch
	bool bottomSwitch= elevatorMotor->GetSensorCollection().IsRevLimitSwitchClosed();
	if (isGoingToFloor){
		if (!bottomSwitch){
			double encoderValue = elevatorMotor->GetSelectedSensorPosition(0)/4096.0;
			double speed = encoderValue <= 3 ? -0.2 : -0.4;
			elevatorMotor->Set(ControlMode::PercentOutput,speed);
		}
		else{
			elevatorMotor->Set(ControlMode::PercentOutput,0);
			isGoingToFloor = false;
		}
	}
	/*if(!bottomSwitch && bottomLimitHit){
		elevatorMotor->SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
	}
	bottomLimitHit = bottomSwitch;*/

	//look for d-pad values
	int povValue = Robot::oi->getGamePad()->GetPOV(0);
	if (povValue == 270 && !incrementButtonDown){
		ElevatorMoveDown();
		incrementButtonDown = true;
		isGoingToFloor = false;
	}
	else if (povValue == 90 && !incrementButtonDown){
		ElevatorMoveUp();
		incrementButtonDown = true;
		isGoingToFloor = false;
	}
	else if (povValue == 0){
		targetMode = false;
		elevatorMotor->Set(ControlMode::PercentOutput,0.8);
		isManualMoving = true;
		isGoingToFloor = false;
	}
	else if (povValue == 180){
		targetMode = false;
		if (encoderValue >= 0){
			elevatorMotor->Set(ControlMode::PercentOutput,-0.60);
		}
		else {
			elevatorMotor->Set(ControlMode::PercentOutput,0);
		}
		isManualMoving = true;
		isGoingToFloor = false;
	}
	else if (povValue == -1){
		incrementButtonDown = false;
		if (!targetMode && isManualMoving){
			isManualMoving = false;
			double encoderValue = elevatorMotor->GetSelectedSensorPosition(0)/4096.0;
			ElevatorGoToRevolutions(encoderValue);
		}
	}
	if(targetMode){
		ElevatorExecuteTarget();
		encoderValue = elevatorMotor->GetSelectedSensorPosition(0)/4096.0;
		if(targetPos == 0 && encoderValue <= 0.1){
			elevatorMotor->Set(ControlMode::PercentOutput,0);
			isTargetMoving = false;
		}
	}
	else{
		isTargetMoving = false;
	}
	encoderValue = elevatorMotor->GetSelectedSensorPosition(0)/4096.0;
	PartyLight(isManualMoving || isTargetMoving, encoderValue);
}

void Elevator::ElevatorExecuteTarget(){
	SetPIDs();
	//process move

	double encoderValue = elevatorMotor->GetSelectedSensorPosition(0)/4096.0;
	double difference = targetPos - encoderValue;
	frc::SmartDashboard::PutString("DB/String 2",std::to_string(difference));
	if (difference > 1.5 || difference < -1.5){
		isTargetMoving = true;
	}
	else{
		isTargetMoving = false;
	}
	elevatorMotor->Set(ControlMode::Position,targetPos*4096.0);

}

void Elevator::ElevatorMoveUp(){
	isGoingToFloor = false;
	if(!targetMode){
		targetPos = (elevatorMotor->GetSelectedSensorPosition(0))/4096.0;
		targetMode = true;
	}
	bool topLimit = elevatorMotor->GetSensorCollection().IsFwdLimitSwitchClosed();
	if(!topLimit){
		targetPos += 4.0;
	}
	frc::SmartDashboard::PutString("DB/String 1",std::to_string(targetPos));
}

void Elevator::ElevatorMoveDown(){
	isGoingToFloor = false;
	if(!targetMode){
		targetPos = (elevatorMotor->GetSelectedSensorPosition(0))/4096.0;
		targetMode = true;
	}
	targetPos -= 4.0;
	frc::SmartDashboard::PutString("DB/String 1",std::to_string(targetPos));
}

//Move to setpoints
void Elevator::ElevatorGoToInches(double inches){
	ElevatorGoToRevolutions(inches*0.5098);
}
void Elevator::ElevatorGoToFloor(){
	/*isGoingToFloor = true;
	targetMode = false;
	targetPos = 0;
	bool bottomSwitch= elevatorMotor->GetSensorCollection().IsRevLimitSwitchClosed();
	if (!bottomSwitch){
		double encoderValue = elevatorMotor->GetSelectedSensorPosition(0)/4096.0;
		double speed = encoderValue <= 3 ? -0.2 : -0.4;
		elevatorMotor->Set(ControlMode::PercentOutput,speed);
	}
	else{
		elevatorMotor->Set(ControlMode::PercentOutput,0);
	}*/
	ElevatorGoToRevolutions(0);
}
void Elevator::ElevatorGoToExchange(){
	//ElevatorGoToRevolutions(1.254);
	ElevatorGoToRevolutions(3.254);
	//Height in inches for exchange (tied to button A)
}
void Elevator::ElevatorGoToSwitch(){
	//ElevatorGoToRevolutions(11.780);
	ElevatorGoToRevolutions(13.780);
	//Height in revolutions for switch (tied to button B)
}
void Elevator::ElevatorGoToScale(){
	//ElevatorGoToRevolutions(35.657);
	ElevatorGoToRevolutions(37.657);
	//Height in revolutions for scale (tied to button X)
}
void Elevator::ElevatorGoToHighScale(){
	ElevatorGoToRevolutions(39.045);
	//Height in revolutions for high scale (tied to button Y)
}

void Elevator::PartyLight(bool isMoving,double encoderValue){
	double Floor=1;
	double switchSpot=12.5;
	double lowScaleSpot=36;
	double midScaleSpot=37;
	double highScaleSpot=38;
	double IML=-.87;
	double FL=.57;
	double EL=.64;
	double SSL=.68;
	double LSL=.77;
	double MSL=.86;
	double HSL=.90;

/*
	if(isMoving){
		elevatorLEDs->Set(IML);
	}
	else if(encoderValue)
	else if(switchSpot >= encoderValue && encoderValue <= 14.5){
		elevatorLEDs->Set(SSL);
	}
	else if (lowScaleSpot >= encoderValue && encoderValue <= 36.25){
		elevatorLEDs->Set(LSL);
	}
	else if (midScaleSpot >= encoderValue && encoderValue <= 37.4){
		elevatorLEDs->Set(MSL);
	}
	else if (highScaleSpot >= encoderValue && encoderValue <= 42){
		elevatorLEDs->Set(HSL);
	}
	else{
		elevatorLEDs->Set(DDL);
	}
}
*/
	/*if(encoderValue < switchSpot){
		if(isMoving){
			elevatorLEDs->Set(IML);
		}
		else{
			elevatorLEDs->Set(.67);
		}


	} else if(encoderValue < lowScaleSpot){
		if(isMoving){
			elevatorLEDs->Set(-.06);
		}
		else{
			elevatorLEDs->Set(.61);
		}


	} else if(encoderValue < midScaleSpot){
		if(isMoving){
			elevatorLEDs->Set(-.06);
		}
		else{
			elevatorLEDs->Set(-.09);
		}
	} else if(encoderValue < highScaleSpot){
		if(isMoving){
			elevatorLEDs->Set(-.06);
		}
		else{
			elevatorLEDs->Set(.71);
		}
	} else {
		if(isMoving){
			elevatorLEDs->Set(-.06);
		}
		else{
			elevatorLEDs->Set(.71);

		}
	}
	*/
	double ultraValue = ultraS->GetRangeInches();
	if(ultraValue < 2 && encoderValue <= Floor){
		elevatorLEDs->Set(-.23);
	}
	else{
		if(isMoving){
			elevatorLEDs->Set(IML);
		}
		else if(encoderValue <= Floor){
			elevatorLEDs->Set(FL);
		}
		else if(encoderValue <= switchSpot){
			elevatorLEDs->Set(EL);
		}
		else if(encoderValue <= lowScaleSpot){
			elevatorLEDs->Set(SSL);
		}
		else if(encoderValue <= midScaleSpot){
			elevatorLEDs->Set(LSL);
		}
		else if(encoderValue <= highScaleSpot){
			elevatorLEDs->Set(MSL);
		}
		else{
			elevatorLEDs->Set(HSL);
		}
	}
}


void Elevator::SetPIDs(){
	std::string pstring = frc::SmartDashboard::GetString("DB/String 5", "0.12");
	double pdouble = 0.12;
	/*When the p-value is too large it moves very jumpy. A larger p-value increases the strength of the motor.
	 *When it is too low it won't even reach the target location.
	 */
	if (pstring.length() > 0) {
		pdouble = std::stod(pstring);
		}
	std::string istring = frc::SmartDashboard::GetString("DB/String 6", "0.0");
	double idouble = 0;
	/*The i-value must be pretty small. A large i-value causes the i-value to oscillate greatly.
	 * If the i-value is too small it takes a very long time to reach the target location.
	 */
	if (istring.length() > 0) {
		idouble = std::stod(istring);
		}
	std::string dstring = frc::SmartDashboard::GetString("DB/String 7", "0.0");
	double ddouble = 0;
	/*Putting the d-value to 100 freaked out the motor. D-value appears to make the motor less jumpy.
	 * Further testing is needed to see how high the d-value can be
	 */
	if (dstring.length() > 0) {
		ddouble = std::stod(dstring);
		}
	/* set closed loop gains in slot0 */
	elevatorMotor->Config_kF(kPIDLoopIdx, 0, kTimeoutMs);
	elevatorMotor->Config_kP(kPIDLoopIdx, pdouble, kTimeoutMs);
	elevatorMotor->Config_kI(kPIDLoopIdx, idouble, kTimeoutMs);
	elevatorMotor->Config_kD(kPIDLoopIdx, ddouble, kTimeoutMs);
}
