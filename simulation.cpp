/**
 * @file simulation.cpp
 * @author xl (xuli2020sj@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#define G4VIS_USE 1
#define G4UI_USE


#include "G4UImanager.hh"
#include "QBBC.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


#include "DetectorConstruction.h"
#include "ActionInitialization.h"
#include "PhysicisList.h"

#include "SteppingAction.h"
#include "time.h"
//#include "PhyscisList.hh"

int main(int argc, char **argv)
{


#ifdef G4MULTITHREADED
    G4int nThreads = 4; // default number of thread
    G4MTRunManager *runManager = new G4MTRunManager;

    // Number of threads can be defined via 3rd argument
    if (argc == 3)
    {
        nThreads = G4UIcommand::ConvertToInt(argv[2]);
    }
    runManager->SetNumberOfThreads(nThreads);
    G4cout << "##### Application started for " << runManager->GetNumberOfThreads()
           << " threads"
           << " #####" << G4endl;
#else
    G4RunManager *runManager = new G4RunManager;
#endif

    DetectorConstruction *detector = new DetectorConstruction;
    runManager->SetUserInitialization(detector);

    G4VModularPhysicsList *physicsList = new PhysicsList();
//    G4VModularPhysicsList *physicsList = new QBBC;
    physicsList->SetVerboseLevel(1);
    /*QGSP_BERT_HP;//FTFP_BERT;*/
    runManager->SetUserInitialization(physicsList);

    // G4VModularPhysicsList *physicsList = new QBBC;
    // physicsList->SetVerboseLevel(1);
    // runManager->SetUserInitialization(physicsList);

    ActionInitialization *actionInitialization = new ActionInitialization();
    runManager->SetUserInitialization(actionInitialization);




    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (argc != 1) // batch mode
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else // interactive mode : define UI session
    {
#ifdef G4VIS_USE
    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialize();
#endif

#ifdef G4UI_USE
        G4UIExecutive *ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
        UImanager->ApplyCommand("/control/execute vis.mac");
#endif
        ui->SessionStart();
        delete ui;
#endif
#ifdef G4VIS_USE
    delete visManager;
#endif
    }



    return 0;
}
