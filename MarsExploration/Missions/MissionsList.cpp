#include"MissionsList.h"

MissionsList::MissionsList()
{
    WaitingMissions = InExecutionMissions = AutoPromotedMissions = 0;
    Enum = Mnum = Pnum = 0;
}

void MissionsList::AddMission(Missions* newMission)
{
    if (newMission->getType() == 'E')
    {
        Pair<Missions*, int> P;
        P.first = newMission;
        //=============================  for the priority equation  =============================//
        // the most important factor is the mission significance so we will multiply it by (50)
        // the second important factor is the mission duration, target location came third, then finally formulation day
        // so the second factor will be (3000) for mission duration, (2000) for target location, (1000) for formulation day
        // note: we used large number to fix the integer division problem
        P.second = (50 * newMission->getSignificance()) + (3000 / newMission->getMD()) + (2000 / newMission->getTL()) + (1000 / newMission->getFD());
        E.enqueue(P);
        Enum++;
    }
    else if (newMission->getType() == 'M')
    {
        M.enqueue(newMission);
        Mnum++;
    }
    else if (newMission->getType() == 'P')
    {
        P.enqueue(newMission);
        Pnum++;
    }
    WaitingMissions++;
}

void MissionsList::AddMissionToExecution(Missions* newMission)
{
    Pair<Missions*, int> P;
    P.first = newMission;
    P.second = 1 + (1000 / newMission->getCD());
    inEx.enqueue(P);
    InExecutionMissions++;
    WaitingMissions--;
}

void MissionsList::Update(int CurrentDay, RoverLists& RL)
{
    //update the main lists
    PriorityLinkedQueue<Missions*> temp;
    LinkedQueue<Missions*> ltemp;
    while (!E.isEmpty())
    {
        Pair<Missions*, int> P;
        E.dequeue(P);
        P.first->Update();
        temp.enqueue(P);
    }
    while (!temp.isEmpty())
    {
        Pair<Missions*, int> P;
        temp.dequeue(P);
        E.enqueue(P);
    }
    while (!M.isEmpty())
    {
        Missions* P;
        M.dequeue(P);
        //for the auto promotion
        if (P->getWD() == P->getAutoP())
        {
            P->setType('E');
            AddMission(P);
            AutoPromotedMissions++;
            Mnum--;
            WaitingMissions--;
        }
        else ltemp.enqueue(P);
        P->Update();
    }
    while (!ltemp.isEmpty())
    {
        Missions* P;
        ltemp.dequeue(P);
        M.enqueue(P);
    }
    while (!P.isEmpty())
    {
        Missions* Pa;
        P.dequeue(Pa);
        Pa->Update();
        ltemp.enqueue(Pa);
    }
    while (!ltemp.isEmpty())
    {
        Missions* Pa;
        ltemp.dequeue(Pa);
        P.enqueue(Pa);
    }
    //update inexecution list
    while (!inEx.isEmpty())
    {
        Pair<Missions*, int> P;
        inEx.dequeue(P);
        if (P.first->getCD() == CurrentDay)
        {
            CompletedMissionsL.enqueue(P.first);
            InExecutionMissions--;

            Rover* R = P.first->getHelpingRover();
            RL.ReturnRover(R, CurrentDay);
        }
        else 
            temp.enqueue(P);
    }
    while (!temp.isEmpty())
    {
        Pair<Missions*, int> P;
        temp.dequeue(P);
        inEx.enqueue(P);
    }
}

Missions*& MissionsList::getAvailable_E()
{
    Missions* M = NULL;
    Pair<Missions*, int> P;
    P.first = NULL;
    if (!E.isEmpty())
        E.dequeue(P);
    M = P.first;
    return M;
}

Missions*& MissionsList::getAvailable_M()
{
    Missions* Mi = NULL;
    if (!M.isEmpty())
        M.dequeue(Mi);
    return Mi;
}

Missions*& MissionsList::getAvailable_P()
{
    Missions* Mi = NULL;
    if (!P.isEmpty())
        P.dequeue(Mi);
    return Mi;
}

bool MissionsList::isEmpty()
{
    return (E.isEmpty() && M.isEmpty() && P.isEmpty() && inEx.isEmpty());
}

int MissionsList::getNumOf_WaitingMissions()
{
    return WaitingMissions;
}

int MissionsList::getNumOf_InExecutionMissions()
{
    return InExecutionMissions;
}

int MissionsList::getNumOf_AutoPromotedMissions()
{
    return AutoPromotedMissions;
}

int MissionsList::getNumOf_EM()
{
    return Enum;
}

int MissionsList::getNumOf_MM()
{
    return Mnum;
}

int MissionsList::getNumOf_PM()
{
    return Pnum;
}

void MissionsList::decrease_MNum()
{
    Mnum--;
}

LinkedQueue<Missions*> MissionsList::getWaitingMountainuousList()
{
    return M;
}

LinkedQueue<Missions*> MissionsList::getWaitingPolarList()
{
    return P;
}

LinkedQueue<Missions*> MissionsList::getCompletedMissions()
{
    return CompletedMissionsL;
}

PriorityLinkedQueue<Missions*> MissionsList::getInExecutionList()
{
    return inEx;
}

PriorityLinkedQueue<Missions*> MissionsList::getWaitingEmergencyList()
{
    return E;
}

Missions*& MissionsList::GetWaitingMount(int id)
{
    LinkedQueue<Missions*> temp;
    Missions* P = NULL, * Mi = NULL;

    while (!M.isEmpty())
    {
        M.dequeue(P);
        if (P->getID() != id)
            temp.enqueue(P);
        else { 
            Mi = P;
            WaitingMissions--;
        }
    }
    while (!temp.isEmpty())
    {
        temp.dequeue(P);
        M.enqueue(P);
    }
    return Mi;
}

MissionsList::~MissionsList()
{

}