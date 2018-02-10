// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/Drive.h"
#include "Commands/IntakeDrive.h"
#include "Commands/IntakeOpenCmd.h"
#include "Commands/ElevatorExchange.h"
#include "Commands/ElevatorFloor.h"
#include "Commands/ElevatorHighScale.h"
#include "Commands/ElevatorScale.h"
#include "Commands/ElevatorSwitch.h"
#include "Commands/ElevatorTarget.h"


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    gamePad.reset(new frc::Joystick(1));
    
    intakeClose.reset(new frc::JoystickButton(gamePad.get(), 8));
    intakeClose->WhenPressed(new IntakeOpenCmd(false));
    intakeOpen.reset(new frc::JoystickButton(gamePad.get(), 7));
    intakeOpen->WhenPressed(new IntakeOpenCmd(true));

    gamePadLB.reset(new frc::JoystickButton(gamePad.get(), 5));
    gamePadLB->WhenPressed(new ElevatorFloor());
    gamePadX.reset(new frc::JoystickButton(gamePad.get(), 1));
    gamePadX->WhenPressed(new ElevatorScale());
    gamePadY.reset(new frc::JoystickButton(gamePad.get(), 4));
    gamePadY->WhenPressed(new ElevatorHighScale());
    gamePadB.reset(new frc::JoystickButton(gamePad.get(), 3));
    gamePadB->WhenPressed(new ElevatorSwitch());
    gamePadA.reset(new frc::JoystickButton(gamePad.get(), 2));
    gamePadA->WhenPressed(new ElevatorExchange());

    driveStick.reset(new frc::Joystick(0));
    

    // SmartDashboard Buttons
    frc::SmartDashboard::PutData("ElevatorHighScale", new ElevatorHighScale());
    frc::SmartDashboard::PutData("ElevatorSwitch", new ElevatorSwitch());
    frc::SmartDashboard::PutData("ElevatorScale", new ElevatorScale());
    frc::SmartDashboard::PutData("ElevatorExchange", new ElevatorExchange());
    frc::SmartDashboard::PutData("ElevatorFloor", new ElevatorFloor());
    frc::SmartDashboard::PutData("ElevatorTarget", new ElevatorTarget());
    frc::SmartDashboard::PutData("Drive", new Drive());
    frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDriveStick() {
   return driveStick;
}

std::shared_ptr<frc::Joystick> OI::getGamePad() {
   return gamePad;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
