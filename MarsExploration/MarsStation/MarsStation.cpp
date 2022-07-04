#include"MarsStation.h"
#include"iomanip" //used to align (justify) the numbers in the output file

MarsStation::MarsStation()
{
	CurrentDay = 1;
}


int MarsStation::getCurrentDay()
{
	return CurrentDay;
}

void MarsStation::Simulate()
{
	OpenFile();
	int mode = Ui.getMode();
	if (mode == 3) //silent mode, we dont need to call it in the loop
	{
		DailyDisplay();
	}

	do
	{
		// check if the event list is already empty
		//excute the events which on the same day
		Event* E;
		while (true)
		{
			EventList.peek(E);
			if (E->getED() == CurrentDay)
			{
				E->Execute(ML);
				EventList.dequeue(E);
				delete E;
			}
			else break;
		}
		
		//assign waiting missions and move them to inEx list
		//first we assign the emergency missions
		Assign('E');
		//second we assign the polar missions
		Assign('P');
		//third we assign the mountainous missions
		Assign('M');

	
		//update missions list and rovers list
		// for the Missions (move the completed ones to the completed list)
		// for the Rovers (check if the rover needs to go to the checkup list)
		//                (return the rovers which finished the checkup duaration to the available rovers lists)
		ML.Update(CurrentDay, RL);
		RL.Update(CurrentDay);

		//assign the waiting mission to any possible rover came from the checkup list or just finished another mission
		Assign('E');
		Assign('P');
		Assign('M');

		//get the daily output (console)
		if (mode == 1 || mode == 2)
			DailyDisplay();
		
		CurrentDay++;

	} while (Continue());

	// after finishing the simulation, we need to create the output file
	OutPutFile();
}

void MarsStation::OutPutFile()
{

	//output should be sorted by CD
	//then we should have a queue containing the completed missions..
	ofstream output;
	output.open("Input and output files/Output.txt");
	int missionsNo = 0; //to calculate the total missiong number (used in calculation on avg wait and avg exc)
	LinkedQueue<Missions*> CompMissionsListTemp(ML.getCompletedMissions());
	Missions* tempVar; //to dequeue from the list
	int WDsum = 0; //to calculate the average WD
	int EDsum = 0; //to calculate the average ED
	float AvgWait;
	float AvgExec;
	float AutoPromoted;
	if (output.is_open())
	{
		//setw(4) is used to align (justify) the numbers in the output file
		output << "CD" << setw(4) << "ID" << setw(4) << "FD" << setw(4) << "WD" << setw(4) << "ED" << endl;
		while (CompMissionsListTemp.dequeue(tempVar))
		{
			WDsum += tempVar->getWD(); //calculate the average WD
			EDsum += tempVar->getED(); //to calculate the average ED
			output << tempVar->getCD() << setw(4) << tempVar->getID() << setw(4) << tempVar->getFD() << setw(4)
				   << tempVar->getWD() << setw(4) << tempVar->getED() << endl;
			missionsNo++;
		}
		AvgWait = (float)WDsum / (missionsNo);
		AvgExec = (float)EDsum / (missionsNo);
		output << endl;
		output << "Mission: " << ML.getNumOf_EM() + ML.getNumOf_MM() + ML.getNumOf_PM() << " [" << "M: " << ML.getNumOf_MM() << ", "
			<< "P: " << ML.getNumOf_PM() << ", " << "E: " << ML.getNumOf_EM() << "]\n";
		output << "Rovers: " << RL.getNumOf_ER() + RL.getNumOf_MR() + RL.getNumOf_PR() << " [" << "M: " << RL.getNumOf_MR() << ", "
			<< "P: " << RL.getNumOf_PR() << ", " << "E: " << RL.getNumOf_ER() << "]\n";
		output << "Avg Wait = " << AvgWait << ", " << "Avg Exec = " << AvgExec << endl;
		AutoPromoted = (float(ML.getNumOf_AutoPromotedMissions()) / (ML.getNumOf_MM() + ML.getNumOf_AutoPromotedMissions())) * 100;
		//promoted missions / total number of mountanuous missions
		output << "Auto-promoted: " << AutoPromoted << "%";
	}
	output.close();
}

MarsStation::~MarsStation()
{
	//clear all the lists missions and rovers

}

void MarsStation::OpenFile()
{
	Ui.readInput(RL, EventList);
}

void MarsStation::DailyDisplay()
{
	Ui.consoleOutput(ML, RL, CurrentDay);
}

void MarsStation::Assign(char t)
{
	while (true)
	{
		// check if there is any ready rover of the required type
		if (RL.isAvailable(t))
		{
			// if there is an available rover, then we should get the available mission of the required type
			Missions* Mis = NULL;
			switch (t)
			{
			case 'E':
				Mis = ML.getAvailable_E();
				break;
			case 'P':
				Mis = ML.getAvailable_P();
				break;
			case 'M':
				Mis = ML.getAvailable_M();
				break;
			}
			// if there is a mission, then assign that rover to this mission
			if (Mis)
			{
				Rover* R = RL.getAvailableRover(t);
				Mis->AssignRover(R);
				ML.AddMissionToExecution(Mis);
			}
			else break;
		}
		else break;
	}
}

bool MarsStation::Continue()
{
	// if the waiting missions lists are empty and no missions in execution list
	// AND rovers checkup list is empty
	// AND the event list is empty
	// then the program should stop simulating
	return (!(ML.isEmpty() && RL.isCheckUpEmpty()) || !EventList.isEmpty());
}