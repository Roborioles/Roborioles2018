// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include "ctre/Phoenix.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<WPI_TalonSRX> RobotMap::driveBaseLeftMotor2;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveBaseRightMotor2;
std::shared_ptr<frc::Compressor> RobotMap::driveBaseCompressor;
std::shared_ptr<frc::Solenoid> RobotMap::driveBaseShiftSolenoid;
std::shared_ptr<frc::AnalogInput> RobotMap::driveBasePressureSensor;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveBaseLeftMotor1;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveBaseRightMotor1;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

    driveBaseLeftMotor2.reset(new WPI_TalonSRX(1));
    
    
    driveBaseRightMotor2.reset(new WPI_TalonSRX(3));
    
    
    driveBaseCompressor.reset(new frc::Compressor(0));
    lw->AddActuator("DriveBase", "Compressor", driveBaseCompressor);
    
    driveBaseShiftSolenoid.reset(new frc::Solenoid(0, 1));
    lw->AddActuator("DriveBase", "ShiftSolenoid", driveBaseShiftSolenoid);
    
    driveBasePressureSensor.reset(new frc::AnalogInput(0));
    lw->AddSensor("DriveBase", "PressureSensor", driveBasePressureSensor);
    
    driveBaseLeftMotor1.reset(new WPI_TalonSRX(2));
    
    
    driveBaseRightMotor1.reset(new WPI_TalonSRX(4));
    
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
