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
#include "DriveBaseConstants.h"


#include "DriveBase.h"
#include "../RobotMap.h"
#include "../Robot.h"

#include <math.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

DriveBase::DriveBase() : frc::Subsystem("DriveBase") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    leftMotor1 = RobotMap::driveBaseLeftMotor1;
    leftMotor2 = RobotMap::driveBaseLeftMotor2;
    rightMotor1 = RobotMap::driveBaseRightMotor1;
    rightMotor2 = RobotMap::driveBaseRightMotor2;
    compressor = RobotMap::driveBaseCompressor;
    shiftSolenoid = RobotMap::driveBaseShiftSolenoid;
    pressureSensor = RobotMap::driveBasePressureSensor;
    pigeonIMU = RobotMap::driveBasePigeonIMU;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    leftMotor2->Set(ControlMode::Follower,2);
    rightMotor2->Set(ControlMode::Follower,4);
    leftMotor1->SetInverted(false);
    leftMotor2->SetInverted(false);
    rightMotor1->SetInverted(true);
    rightMotor2->SetInverted(true);

	/* choose the sensor and sensor direction */
			leftMotor1->ConfigSelectedFeedbackSensor(
					FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx,
					kTimeoutMs);
			leftMotor1->SetSensorPhase(false);

			/* choose the sensor and sensor direction */
			rightMotor1->ConfigSelectedFeedbackSensor(
					FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx,
					kTimeoutMs);
			rightMotor1->SetSensorPhase(false);

			/* set the peak and nominal outputs, 12V means full */
			leftMotor1->ConfigNominalOutputForward(0, kTimeoutMs);
			leftMotor1->ConfigNominalOutputReverse(0, kTimeoutMs);
			leftMotor1->ConfigPeakOutputForward(0.25, kTimeoutMs);
			leftMotor1->ConfigPeakOutputReverse(-0.25, kTimeoutMs);

			/* Set ramp rate */
			//leftMotor1->ConfigClosedloopRamp(0.75,kTimeoutMs);

			/* set closed loop gains in slot0 */
			leftMotor1->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
			leftMotor1->Config_kP(kPIDLoopIdx, 0.14, kTimeoutMs);
			leftMotor1->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
			leftMotor1->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

			/* set the peak and nominal outputs, 12V means full */
			rightMotor1->ConfigNominalOutputForward(0, kTimeoutMs);
			rightMotor1->ConfigNominalOutputReverse(0, kTimeoutMs);
			rightMotor1->ConfigPeakOutputForward(0.25, kTimeoutMs);
			rightMotor1->ConfigPeakOutputReverse(-0.25, kTimeoutMs);

			/* set closed loop gains in slot0 */
			rightMotor1->Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
			rightMotor1->Config_kP(kPIDLoopIdx, 0.14, kTimeoutMs);
			rightMotor1->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
			rightMotor1->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

			/* Set ramp rate */
			//rightMotor1->ConfigClosedloopRamp(0.75,kTimeoutMs);


}

void DriveBase::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void DriveBase::Periodic() {
    // Put code here to be run every loop

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void DriveBase::DriveWithJoysticks() {
	//leftMotor1->Set(-1*Robot::oi->getDriveStick()->GetY());
	//rightMotor1->Set(-1*Robot::oi->getDriveStick()->GetY());
	Robot::driveBase->ArcadeDrive(-1*Robot::oi->getDriveStick()->GetY(),-1*Robot::oi->getDriveStick()->GetX());
}

double DriveBase::SensorReading() {
	double a1 = ((pressureSensor->GetVoltage())*50)-25;
	double a2 = (ceil(a1*100))/100;
	return a2;
}

void DriveBase::AutoShift(double upshift, double downshift){
	double motorVelocity = leftMotor1->GetSensorCollection().GetQuadratureVelocity();
		bool isHigh = shiftSolenoid->Get();
		int rpm = ((motorVelocity*10)/4096)*60;
		rpm = abs(rpm);
		SmartDashboard::PutNumber("RPM: ", rpm);

		if(isHigh == false && rpm > upshift){
			shiftSolenoid->Set(true);
		}

		if(isHigh == true && rpm < downshift){
			shiftSolenoid->Set(false);
		}
}

void DriveBase::ShiftingInfo(){
	SmartDashboard::PutNumber("Upshift", 900);
	SmartDashboard::PutNumber("Downshift", 700);
}

void DriveBase::ArcadeDrive(float moveValue, float rotateValue){
	float leftMotorOutput;
	float rightMotorOutput;
	moveValue = Limit(moveValue);
	if (moveValue > 0.0)
	{
			if (rotateValue > 0.0)
			{
				leftMotorOutput = moveValue - rotateValue;
				rightMotorOutput = max(moveValue, rotateValue);

			}
			else
			{
				leftMotorOutput = max(moveValue, -rotateValue);
				rightMotorOutput = moveValue + rotateValue;
			}
		}
		else
		{
			if (rotateValue > 0.0)
			{

				leftMotorOutput = - max(-moveValue, rotateValue);
				rightMotorOutput = moveValue + rotateValue;
			}
			else
			{

				leftMotorOutput = moveValue - rotateValue;
				rightMotorOutput = - max(-moveValue, -rotateValue);
			}
		}
		leftMotor1->Set(leftMotorOutput);
		rightMotor1->Set(rightMotorOutput);
		// leftMotor2->Set(leftMotorOutput);
		// rightMotor2->Set(rightMotorOutput);
}

float DriveBase::Limit(float num)
{
	if (num > 1.0)
	{
		return 1.0;
	}
	if (num < -1.0)
	{
		return -1.0;
	}
	return num;

}
void DriveBase::EncoderReset(){
	//int absolutePosition = leftMotor1->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	//leftMotor1->SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx, kTimeoutMs);

	/* lets grab the 360 degree position of the MagEncoder's absolute position */
	//int RabsolutePosition = rightMotor1->GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
	/* use the low level API to set the quad encoder signal */
	//rightMotor1->SetSelectedSensorPosition(RabsolutePosition, kPIDLoopIdx, kTimeoutMs);

	// Absolute value reset
	leftMotor1->SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
	rightMotor1->SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
}

void DriveBase::AutoDrive(double distance){
		distance = distance*12*.01577287;
		double targetPositionRotations = distance * 10.0 * 4096; /* 50 (NOT) Rotations in either direction */

		leftMotor1->Set(ControlMode::Position, targetPositionRotations); /* 50 rotations in either direction */
		rightMotor1->Set(ControlMode::Position, targetPositionRotations); /* 50 rotations in either direction */
}

bool DriveBase::isOnTarget(double distance) {
	distance = distance*12*.01577287;
	if ((distance - 3720) < leftMotor1->GetSelectedSensorPosition(kPIDLoopIdx)&&leftMotor1->GetSelectedSensorPosition(kPIDLoopIdx)<(distance+3720))
		return true;
	else
		return false;

}

void DriveBase::RotateToAngle(double angle, double speed) {
	if(angle<0) {
		leftMotor1->Set(ControlMode::PercentOutput,  speed);
		//leftMotor2->Set(ControlMode::PercentOutput,  speed);
		rightMotor1->Set(ControlMode::PercentOutput, -speed);
		//rightMotor2->Set(ControlMode::PercentOutput, -speed);
	} else {
		leftMotor1->Set(ControlMode::PercentOutput,  -speed);
		//leftMotor2->Set(ControlMode::PercentOutput,  -speed);
		rightMotor1->Set(ControlMode::PercentOutput, speed);
		//rightMotor2->Set(ControlMode::PercentOutput, speed);
	}
}

void DriveBase::StopMotors() {
	leftMotor1->Set(0);
	//leftMotor2->Set(0);
	rightMotor1->Set(0);
	//rightMotor2->Set(0);

}

bool DriveBase::CheckAngle(double target) {
	if(target - pigeonIMU->GetFusedHeading() >= -2 && target - pigeonIMU->GetFusedHeading() <= 2) {
		return true;
	} else {
		return false;
	}

}

void DriveBase::ResetAngle() {
	pigeonIMU->SetFusedHeading(0,0);
}

void DriveBase::PrintValues(){
	int lefterror = 0;
	int righterror = 0;

	if (leftMotor1->GetControlMode() == ControlMode::Position) {
		lefterror = leftMotor1->GetClosedLoopError(kPIDLoopIdx);
		righterror = rightMotor1->GetClosedLoopError(kPIDLoopIdx);
	}

	printf("LeftPosition %i [%i], RightPosition %i [%i], angle %f\n",
			leftMotor1->GetSelectedSensorPosition(kPIDLoopIdx),lefterror,
			rightMotor1->GetSelectedSensorPosition(kPIDLoopIdx),righterror,
			pigeonIMU->GetFusedHeading());

	SmartDashboard::PutNumber("LeftPosition", leftMotor1->GetSelectedSensorPosition(kPIDLoopIdx));
	SmartDashboard::PutNumber("LeftError", leftMotor1->GetClosedLoopError(kPIDLoopIdx));
	SmartDashboard::PutNumber("RightPosition", rightMotor1->GetSelectedSensorPosition(kPIDLoopIdx));
	SmartDashboard::PutNumber("RightError", rightMotor1->GetClosedLoopError(kPIDLoopIdx));
	SmartDashboard::PutNumber("Gyro", pigeonIMU->GetFusedHeading());


}

void DriveBase::EnablePID() {
	leftMotor1->ConfigPeakOutputForward(0.42, kTimeoutMs);
	leftMotor1->ConfigPeakOutputReverse(-0.42, kTimeoutMs);
	rightMotor1->ConfigPeakOutputForward(0.35, kTimeoutMs);
	rightMotor1->ConfigPeakOutputReverse(-0.35, kTimeoutMs);
	rightMotor1->ConfigClosedloopRamp(0.5,kTimeoutMs);
	leftMotor1->ConfigClosedloopRamp(0.5,kTimeoutMs);
}

void DriveBase::DisablePID() {
	//leftMotor1->Set(ControlMode::Position,0);
	leftMotor1->Set(ControlMode::PercentOutput,0);
	//rightMotor1->Set(ControlMode::Position,0);
	rightMotor1->Set(ControlMode::PercentOutput,0);

	leftMotor1->ConfigPeakOutputForward(1, kTimeoutMs);
	leftMotor1->ConfigPeakOutputReverse(-1, kTimeoutMs);
	leftMotor1->ConfigClosedloopRamp(0,kTimeoutMs);
	rightMotor1->ConfigPeakOutputForward(1, kTimeoutMs);
	rightMotor1->ConfigPeakOutputReverse(-1, kTimeoutMs);
	rightMotor1->ConfigClosedloopRamp(0,kTimeoutMs);
}
