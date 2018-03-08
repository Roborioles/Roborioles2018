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
std::shared_ptr<WPI_TalonSRX> RobotMap::driveBaseLeftMotor1;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveBaseLeftMotor2;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveBaseRightMotor1;
std::shared_ptr<WPI_TalonSRX> RobotMap::driveBaseRightMotor2;
std::shared_ptr<frc::Compressor> RobotMap::driveBaseCompressor;
std::shared_ptr<frc::Solenoid> RobotMap::driveBaseShiftSolenoid;
std::shared_ptr<frc::AnalogInput> RobotMap::driveBasePressureSensor;
std::shared_ptr<PigeonIMU> RobotMap::driveBasePigeonIMU;
std::shared_ptr<WPI_TalonSRX> RobotMap::elevatorElevatorMotor;
std::shared_ptr<frc::SpeedController> RobotMap::elevatorElevatorLEDs;
std::shared_ptr<frc::Ultrasonic> RobotMap::elevatorUltraS;
std::shared_ptr<frc::SpeedController> RobotMap::intakeSubIntakeMotor1;
std::shared_ptr<frc::SpeedController> RobotMap::intakeSubIntakeMotor2;
std::shared_ptr<frc::Solenoid> RobotMap::intakeSubClamper;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::elevateRightElevate;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::elevateLeftElevate;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::elevateDeployTop;
std::shared_ptr<frc::DoubleSolenoid> RobotMap::elevateDeployBottom;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    frc::LiveWindow *lw = frc::LiveWindow::GetInstance();

    driveBaseLeftMotor1.reset(new WPI_TalonSRX(2));
    
    
    driveBaseLeftMotor2.reset(new WPI_TalonSRX(1));
    
    
    driveBaseRightMotor1.reset(new WPI_TalonSRX(4));
    
    
    driveBaseRightMotor2.reset(new WPI_TalonSRX(3));
    
    
    driveBaseCompressor.reset(new frc::Compressor(0));
    lw->AddActuator("DriveBase", "Compressor", driveBaseCompressor);
    
    driveBaseShiftSolenoid.reset(new frc::Solenoid(0, 1));
    lw->AddActuator("DriveBase", "ShiftSolenoid", driveBaseShiftSolenoid);
    
    driveBasePressureSensor.reset(new frc::AnalogInput(0));
    lw->AddSensor("DriveBase", "PressureSensor", driveBasePressureSensor);
    
    driveBasePigeonIMU.reset(new PigeonIMU(20));
    
    
    elevatorElevatorMotor.reset(new WPI_TalonSRX(5));
    
    
    elevatorElevatorLEDs.reset(new frc::Talon(4));
    lw->AddActuator("Elevator", "ElevatorLEDs", std::static_pointer_cast<frc::Talon>(elevatorElevatorLEDs));
    
    elevatorUltraS.reset(new frc::Ultrasonic(1, 2));
    lw->AddSensor("Elevator", "UltraS", elevatorUltraS);
    
    intakeSubIntakeMotor1.reset(new frc::Spark(1));
    lw->AddActuator("IntakeSub", "IntakeMotor1", std::static_pointer_cast<frc::Spark>(intakeSubIntakeMotor1));
    
    intakeSubIntakeMotor2.reset(new frc::Spark(2));
    lw->AddActuator("IntakeSub", "IntakeMotor2", std::static_pointer_cast<frc::Spark>(intakeSubIntakeMotor2));
    
    intakeSubClamper.reset(new frc::Solenoid(0, 0));
    lw->AddActuator("IntakeSub", "Clamper", intakeSubClamper);
    
    elevateRightElevate.reset(new frc::DoubleSolenoid(0, 5, 7));
    lw->AddActuator("Elevate", "RightElevate", elevateRightElevate);
    
    elevateLeftElevate.reset(new frc::DoubleSolenoid(0, 6, 2));
    lw->AddActuator("Elevate", "LeftElevate", elevateLeftElevate);
    
    elevateDeployTop.reset(new frc::DoubleSolenoid(19, 4, 5));
    lw->AddActuator("Elevate", "DeployTop", elevateDeployTop);
    
    elevateDeployBottom.reset(new frc::DoubleSolenoid(19, 6, 7));
    lw->AddActuator("Elevate", "DeployBottom", elevateDeployBottom);
    


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
