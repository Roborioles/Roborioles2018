// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "AutoCmdGrp.h"
#include "AutoDrive.h"
#include "AutoRotate.h"
#include "ElevatorFloor.h"
#include "ElevatorHighScale.h"
#include "ElevatorScale.h"
#include "ElevatorSwitch.h"
#include "IntakeOpenCmd.h"
#include "IntakeDrive.h"
#include "WaitCmd.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

AutoCmdGrp::AutoCmdGrp(int position, int override): CommandGroup() {
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
     // Add Commands here:
    // e.g. AddSequential(new Command1());
    //      AddSequential(new Command2());
    // these will run in order.
	std::string gameData;
	gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();

	// Position
	// 1 - left
	// 0 - middle or undefined
	// 2 - right

	// override
	// 0 - no override
	// 1 - score on switch, no matter what
	// 2 - score on scale, no matter what

	if (position==0 && override==0) {
		// No Input
		printf("Driving forward 10 feet\n");
		AddSequential(new AutoDrive(9));
	}

	if (position==1) {
		// Left Position
		if (gameData[0] == 'L') {
			// Switch also on left
			if (override < 2 || override == 3) {
				// Go for switch - left position - no override/switch override
				printf("Driving forward 13 feet, to score on left switch\n");
				AddSequential(new ElevatorSwitch());
				AddSequential(new AutoDrive(13));
				AddSequential(new AutoRotate(-60, .7));
				AddSequential(new IntakeOpenCmd(true));
				AddSequential(new AutoDrive(3));
				AddSequential(new WaitCmd(1));
				AddSequential(new AutoDrive(-1));
				AddSequential(new ElevatorFloor());
				AddSequential(new AutoDrive(-1));
			} else if (override == 2) {
				// go for scale - overriden, switch is also on left
				if (gameData[1] == 'L') {
					printf("Driving forward 26 feet, to score on left scale\n");
					AddSequential(new ElevatorSwitch());
					AddSequential(new AutoDrive(22));
					AddSequential(new ElevatorScale());
					AddSequential(new AutoRotate(-40, .6));
					AddSequential(new IntakeOpenCmd(true));
					AddSequential(new AutoDrive(3));
					AddSequential(new WaitCmd(1));
					AddSequential(new AutoDrive(-2));
					AddSequential(new ElevatorFloor());
					AddSequential(new AutoDrive(-1));
				} else {
					// Scale is on the right, so good luck - left position,
					printf("Drive down the alley and hope for the best trying right scale\n");
					//down to alleyway
					AddSequential(new AutoDrive(18.5));
					AddSequential(new AutoRotate(-85, .5));
					//down the alleyway
					AddSequential(new ElevatorScale());
					AddSequential(new AutoDrive(20));
					AddSequential(new AutoRotate(80, .5));
					//up on scale, closing in and releasing
					AddSequential(new AutoDrive(3));
					AddSequential(new AutoRotate(30, .5));
					AddSequential(new AutoDrive(2));
					AddSequential(new IntakeOpenCmd(true));
					AddSequential(new WaitCmd(2));
					AddSequential(new AutoDrive(-2));
					AddSequential(new ElevatorFloor());
					AddSequential(new AutoDrive(-1));
				}
			}
		} else {
			// Switch is on the right
			if (override == 1) {
				printf("Drive down the alley and hope for the best trying right switch\n");
				//down to alleyway
				AddSequential(new AutoDrive(18.5));
				AddSequential(new AutoRotate(-80, .5));
				//down the alleyway
				AddSequential(new AutoDrive(20));
				AddSequential(new AutoRotate(-120, .5));
				//back down other side
				AddSequential(new ElevatorSwitch());
				AddSequential(new AutoDrive(4));
				//up on switch, closing in and releasing
				AddSequential(new IntakeOpenCmd(true));
				AddSequential(new WaitCmd(2));
				AddSequential(new AutoDrive(-2));
				AddSequential(new ElevatorFloor());
				AddSequential(new AutoDrive(-1));
			} else {
				if (gameData[1] == 'L') {
					// Scale is on the left, switch is on the right, scale is better
					printf("Driving forward 26 feet, to score on left scale\n");
					AddSequential(new ElevatorScale());
					AddSequential(new AutoDrive(23.5));
					AddSequential(new AutoRotate(-40, .5));
					AddSequential(new AutoDrive(2));
					AddSequential(new IntakeOpenCmd(true));
					AddSequential(new WaitCmd(2));
					AddSequential(new AutoDrive(-2));
					AddSequential(new ElevatorFloor());
					AddSequential(new AutoDrive(-1));
				} else {
					// Scale and switch are both on the right
					if (override == 0) {
						printf("Drive down the alley and hope for the best trying right switch\n");
						//down to alleyway
						AddSequential(new AutoDrive(18.5));
						AddSequential(new AutoRotate(-80, .5));
						//down the alleyway
						AddSequential(new AutoDrive(20));
						AddSequential(new AutoRotate(-120, .5));
						//back down other side
						AddSequential(new ElevatorSwitch());
						AddSequential(new AutoDrive(4));
						//up on switch, closing in and releasing
						AddSequential(new IntakeOpenCmd(true));
						AddSequential(new WaitCmd(2));
						AddSequential(new AutoDrive(-2));
						AddSequential(new ElevatorFloor());
						AddSequential(new AutoDrive(-1));
					} else {
						// Scale is on the right, so good luckS
						printf("Drive down the alley and hope for the best trying right scale\n");
						//down to alleyway
						AddSequential(new AutoDrive(18.5));
						AddSequential(new AutoRotate(-85, .5));
						//down the alleyway
						AddSequential(new ElevatorScale());
						AddSequential(new AutoDrive(20));
						AddSequential(new AutoRotate(80, .5));
						//up on scale, closing in and releasing
						AddSequential(new AutoDrive(3));
						AddSequential(new AutoRotate(30, .5));
						AddSequential(new AutoDrive(2));
						AddSequential(new IntakeOpenCmd(true));
						AddSequential(new WaitCmd(2));
						AddSequential(new AutoDrive(-2));
						AddSequential(new ElevatorFloor());
						AddSequential(new AutoDrive(-1));
					}
				}
			}
		}
	} else if (position==2) {
		// Right Position
		if (gameData[0] == 'R') {
			if (override < 2 || override == 3) {
				// Go for switch
				printf("Driving forward 13 feet, to score on right switch\n");
				AddSequential(new ElevatorSwitch());
				AddSequential(new AutoDrive(13));
				AddSequential(new AutoRotate(75, .7));
				AddSequential(new AutoDrive(2));
				AddSequential(new IntakeOpenCmd(true));
				AddSequential(new WaitCmd(2));
				AddSequential(new AutoDrive(-1));
				AddSequential(new ElevatorFloor());
				AddSequential(new AutoDrive(-1));
			} else if (override == 2) {
				// go for scale
				if (gameData[1] == 'R') {
					printf("Driving forward 26 feet, to score on right scale\n");
					AddSequential(new ElevatorScale());
					AddSequential(new AutoDrive(23.5));
					AddSequential(new AutoRotate(50, .5));
					AddSequential(new AutoDrive(2));
					AddSequential(new IntakeOpenCmd(true));
					AddSequential(new WaitCmd(2));
					AddSequential(new AutoDrive(-2));
					AddSequential(new ElevatorFloor());
					AddSequential(new AutoDrive(-1));

				} else {
					// Scale is on the left, so good luck
					printf("Drive down the alley and hope for the best trying left scale\n");
					//down to alleyway
					AddSequential(new AutoDrive(18.5));
					AddSequential(new AutoRotate(85, .5));
					//down the alleyway
					AddSequential(new ElevatorScale());
					AddSequential(new AutoDrive(20));
					AddSequential(new AutoRotate(-80, .5));
					//up on scale, closing in and releasing
					AddSequential(new AutoDrive(3));
					AddSequential(new AutoRotate(-30, .5));
					AddSequential(new AutoDrive(2));
					AddSequential(new IntakeOpenCmd(true));
					AddSequential(new WaitCmd(2));
					AddSequential(new AutoDrive(-2));
					AddSequential(new ElevatorFloor());
					AddSequential(new AutoDrive(-1));
				}
			}
		} else {
			// Switch is on the left
			if (override == 1) {
				printf("Drive down the alley and hope for the best trying left switch\n");
				//down to alleyway
				AddSequential(new AutoDrive(18.5));
				AddSequential(new AutoRotate(80, .5));
				//down the alleyway
				AddSequential(new AutoDrive(20));
				AddSequential(new AutoRotate(120, .5));
				//back down other side
				AddSequential(new ElevatorSwitch());
				AddSequential(new AutoDrive(4));
				//up on switch, closing in and releasing
				AddSequential(new IntakeOpenCmd(true));
				AddSequential(new WaitCmd(2));
				AddSequential(new AutoDrive(-2));
				AddSequential(new ElevatorFloor());
				AddSequential(new AutoDrive(-1));
			} else {
				if (gameData[1] == 'R') {
					// Scale is on the right, switch is on the left, scale is better
					printf("Driving forward 26 feet, to score on right scale\n");
					AddSequential(new ElevatorScale());
					AddSequential(new AutoDrive(22));
					AddSequential(new AutoRotate(50, .5));
					AddSequential(new AutoDrive(2.5));
					AddSequential(new IntakeOpenCmd(true));
					AddSequential(new WaitCmd(2));
					AddSequential(new AutoDrive(-2));
					AddSequential(new ElevatorFloor());
					AddSequential(new AutoDrive(-1));
				} else {
					// Scale and switch are both on the left
					if (override == 0) {
						printf("Drive down the alley trying for the left switch\n");
						//down to alleyway
						AddSequential(new AutoDrive(18.5));
						AddSequential(new AutoRotate(80, .5));
						//down the alleyway
						AddSequential(new AutoDrive(20));
						AddSequential(new AutoRotate(120, .5));
						//back down other side
						AddSequential(new ElevatorSwitch());
						AddSequential(new AutoDrive(4));
						//up on switch, closing in and releasing
						AddSequential(new IntakeOpenCmd(true));
						AddSequential(new WaitCmd(2));
						AddSequential(new AutoDrive(-2));
						AddSequential(new ElevatorFloor());
						AddSequential(new AutoDrive(-1));
					} else {
						printf("Drive down the allow trying for the left scale\n");
						//down to alleyway
						AddSequential(new AutoDrive(18.5));
						AddSequential(new AutoRotate(85, .5));
						//down the alleyway
						AddSequential(new ElevatorScale());
						AddSequential(new AutoDrive(20));
						AddSequential(new AutoRotate(-80, .5));
						//up on scale, closing in and releasing
						AddSequential(new AutoDrive(3));
						AddSequential(new AutoRotate(30, .5));
						AddSequential(new AutoDrive(2));
						AddSequential(new IntakeOpenCmd(true));
						AddSequential(new WaitCmd(2));
						AddSequential(new AutoDrive(-2));
						AddSequential(new ElevatorFloor());
						AddSequential(new AutoDrive(-1));
					}
				}
			}
		}
	} else if (position == 0 && override == 1) {
		//Middle Position
		if (gameData[0] == 'L') {
			printf("Middle, going for left switch\n");
			AddSequential(new AutoDrive(4));
			AddSequential(new AutoRotate(80, .5));
			AddSequential(new AutoDrive(5));
			AddSequential(new AutoRotate(-80, .5));
			AddSequential(new ElevatorSwitch());
			AddSequential(new AutoDrive(4.5));
			AddSequential(new IntakeOpenCmd(true));
			AddSequential(new WaitCmd(2));
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorFloor());
			AddSequential(new AutoDrive(-1));
		} else if (gameData[0] == 'R') {
			printf("Middle, going for left switch\n");
			AddSequential(new ElevatorSwitch());
			AddSequential(new AutoDrive(8.5));
			AddSequential(new IntakeOpenCmd(true));
			AddSequential(new WaitCmd(2));
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorFloor());
			AddSequential(new AutoDrive(-1));
		}
	}

    /* need to figure out how to select modes of two cube autonomous vs one cube
     * right now, probably only on one side, else it defaults to getting one of the things on the other side
     * ALSO need to speed everything up somehow, can't get anything done if we take fingg forever
     * can speed up turns, finagle the PIDs to get faster BUT BE CAREFUL OF TIPPING -- perhaps raise later??? somehow
     * also hey we need to figure out how to get that good good cube, or else our new autonomous isn't going to work very well
     * and also how the heck do we figure out where we are again
     * HAVE to figure out what the heck is happening with the gyro and being weird
     *
	 * two cube autonomous, one in switch and one in scale
	 * double scale
	 * do we want double switch???????? kinda seems like a waste,,,,
     *
     *  else if (position == 1 && gameData[0] == 'L' && gameData[1] == 'L' && true) {
     *  	//everything including bot is on the left
     *  	//true being if they want to have double auto or nah
     * 		//go to scale, drop off cube on that good good scale
     * 		//then go back and go and grab cube
     * 		//and put in switch
     * 		AddSequential(new ElevatorScale());
			AddSequential(new AutoDrive(23.5));
			AddSequential(new AutoRotate(-40, .5));
			AddSequential(new AutoDrive(2));
			AddSequential(new IntakeOpenCmd(true));
			AddSequential(new WaitCmd(2));
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorFloor());
			AddSequential(new AutoRotate(40, .5));
			AddSequential(new AutoDrive(-10)); //NEEDS TO BE LEVEL WITH CUBES
			AddSequential(new AutoRotate(-80, .5));
			ADD COMMAND(S) HERE THAT SEARCHES FOR CUBE AND THEN STOPS SEARCHING WHEN ULTRASONIC SEES IT
     	 	THEN PUT IT IN THE SWITCH
     	 	and then spin a lot}
     	else if (position == 3 && gameData [0] == 'R' && gameData[1] == 'R') {
     		AddSequential(new ElevatorScale());
     		AddSequential(new AutoDrive(23.5));
     		AddSequential(new AutoRotate(40, .5));
     		AddSequential(new AutoDrive(2));
     		AddSequential(new IntakeOpenCmd(true));
     		AddSequential(new WaitCmd(2));
     		AddSequential(new AutoDrive(-2));
     		AddSequential(new ElevatorFloor());
     		AddSequential(new AutoRotate(-40, .5));
     		AddSequential(new AutoDrive(-10)); //level with cubes
     		AddSequential(new AutoRotate(80, .5));
			add command(s) that search and stop searching
			put on switch
			random dance partyyyyy
			}
		else if (position == 1 && gameData[1] == 'L' && true) { //true being something that drivers choose to do double scale
			AddSequential(new ElevatorScale());
			AddSequential(new AutoDrive(23.5));
			AddSequential(new AutoRotate(-40, .5));
			AddSequential(new AutoDrive(2));
			AddSequential(new IntakeOpenCmd(true));
			AddSequential(new WaitCmd(2));
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorFloor());
			AddSequential(new AutoRotate(40, .5));
			AddSequential(new AutoDrive(-10)); //level with cubes
			AddSequential(new AutoRotate(-80, .5));
			add commands that search and stop searching
			put on scale
			}
		else if (position == 3 && gameData[1] == 'R' && true) {
			AddSequential(new ElevatorScale());
			AddSequential(new AutoDrive(23.5));
			AddSequential(new AutoRotate(40, .5));
			AddSequential(new AutoDrive(2));
			AddSequential(new IntakeOpenCmd(true));
			AddSequential(new WaitCmd(2));
			AddSequential(new AutoDrive(-2));
			AddSequential(new ElevatorFloor());
			AddSequential(new AutoRotate(40, .5));
			AddSequential(new AutoDrive(-10)); //level with cubes
			add commands that find block and get it
			put on scale
		}

     */
              // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
                      // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=COMMAND_DECLARATIONS
 }
