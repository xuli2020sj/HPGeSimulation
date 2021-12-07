#if !defined(ActionInitialization_h)
#define ActionInitialization_h

#include "G4VUserActionInitialization.hh"

#include "PrimaryGeneratorAction.h"
#include "EventAction.h"
#include "RunAction.h"
#include "SteppingAction.h"

class ActionInitialization : public G4VUserActionInitialization
{
private:
    /* data */
public:
    ActionInitialization(/* args */);
    ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};




#endif // ActionInitialization_h






