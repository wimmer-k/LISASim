#include "Reaction.hh"
#include "G4RunManager.hh"


Reaction::Reaction(Outgoing_Beam* BO,  DataManager* data, DetectorConstruction* det, const G4String& aName)
  : G4VProcess(aName), BeamOut(BO), fdata(data), Det(det)
{
 
  G4cout <<GetProcessName() << "  is created "<< G4endl;
 
  BeamOut=BO;
  theProcessType=(G4ProcessType)6;       // Decay
  theProcessSubType=(G4ProcessType)231;  //DecayExt

  decayed_at_rest = false;
  target_reaction = false;
  ground_state    = false;
}

Reaction::~Reaction() 
{                                     
}                                     

// In-flight reaction
// G4VParticleChange* Reaction::PostStepDoIt(
// 			     const G4Track& aTrack,
// 			     const G4Step& aStep
// 			    )
G4VParticleChange* Reaction::PostStepDoIt(
			     const G4Track& aTrack,
			     const G4Step&           // (unused parameter)
			    )
{

  //  G4cout << "I'm in PostStepDoIt." << G4endl;
  //  G4cout << "  " 
  //  	 << aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName()
  //  	 << G4endl;
  //  G4cout << "  reaction_here: " 
  //  	 << reaction_here
  //  	 << G4endl;
  //  G4cout << "  ground_state: " 
  //  	 << ground_state
  //  	 << G4endl;

  aParticleChange.Initialize(aTrack);
//G4cout<<"Legia2"<<endl;
 if(reaction_here)
 
    {
      reaction_here=false;
    if(false){}
      // Kill the track if we've already reacted and wandered back
      //if(BeamOut->GetReactionFlag() == 1){
           //reaction_here=false;
         

	//aParticleChange.ProposeTrackStatus(fStopAndKill);

	// G4cout << "************************* PostStepDoIt: terminating track in "
	//        << aStep.GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()
	//        << " at reaction depth"
	//        << G4endl;
       
      //} 
      // React!
      else {

		//G4cout << "*** PostStepDoIt: I'm reacting." << G4endl;
	
	BeamOut->ScanInitialConditions(aTrack);

	aParticleChange.ProposeTrackStatus(fStopAndKill);
  //G4cout<<"stopandkilltest"<<endl;
  
	if(BeamOut->AboveThreshold()){
	  aParticleChange.SetNumberOfSecondaries(1);
   
	  G4DynamicParticle* rp = BeamOut->ReactionProduct();
     //G4cout<<"reaction test"<<endl;
	  G4ThreeVector rm = BeamOut->ReactionPosition();
	  //G4cout << rp->GetMomentum().mag()/rp->GetTotalEnergy() << "\t" << rm.z() << G4endl;
	  aParticleChange.AddSecondary(rp,rm,true);
	}

	BeamOut->SetReactionFlag(1);

      }

    }

  // Stop and kill the reaction product in its ground state.
  if(ground_state){
    ground_state = false;
    //aParticleChange.ProposeTrackStatus(fStopAndKill);

    // G4cout << "************************* PostStepDoIt: terminating track in "
    // 	   << aStep.GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()
    // 	   << G4endl;

  }
   
  return &aParticleChange;
}

// Trigger the in-flight reaction at the depth in the target determined
// by the PrimaryGeneratorAction.
G4double Reaction::PostStepGetPhysicalInteractionLength(
                             const G4Track& aTrack,
                             G4double,
                             G4ForceCondition* condition
                            )
{

  //  G4cout << "I'm in PostStepGPIL." << G4endl;
  //  G4cout << "  " 
  //  	 << aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName()
  // 	 << G4endl;
  //  G4cout << "  momentum: " 
  //  	 << aTrack.GetDynamicParticle()->GetMomentum()
  //  	 << G4endl;
  //  G4cout << "  target_reaction: " 
  //  	 << target_reaction
  //  	 << G4endl;

  reaction_here=false;
  *condition=NotForced;


  G4String name=aTrack.GetVolume()->GetLogicalVolume()->GetName();

  //int NStep = 10;
  //G4double Target_thickness = 0.5;
  //G4double depth = Target_thickness/2. ;
  //G4double depth = 2.75 ;

  G4UserLimits* target_limits= new G4UserLimits();
 
  //target_limits->SetMaxAllowedStep(Target_thickness/NStep);
 // target_limits->SetMaxAllowedStep(1000);
  //target_limits->SetUserMinRange(depth);
  //target_limits->SetUserMinRange(5);
  aTrack.GetVolume()->GetLogicalVolume()->SetUserLimits(target_limits);



////////////////TEMPORARY RANDOM GENERATION/////////////////////

feventAction = (EventAction*)G4RunManager::GetRunManager()->GetUserEventAction();
EventInfo* eventInfo = (EventInfo*)feventAction->GetEvent()->GetUserInformation();
G4double r = feventAction->getRGRL();
G4double r2 = feventAction->getRGRL2();
G4double r3 = feventAction->getRGRL3();

 CLHEP::HepRandom::setTheSeed((unsigned)clock());
  //double rand = G4UniformRand();
  //G4double r= G4UniformRand();
 
  G4int EventNo = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
 
//Det is detector construction instance
std::vector<double> Mids = Det->GetLayerMids();
 G4double NLayers = Mids.size();
 G4int RLayer = -1;
//cout<<eventInfo->GetSimEvent()->GetReactionLayer()<<endl;
if(eventInfo->GetSimEvent()->GetReactionLayer() <0){ eventInfo->GetSimEvent()->SetReactionLayer(RLayer); } 
//cout<<eventInfo->GetSimEvent()->GetReactionLayer()<<endl;
//cout<<r<<"    "<<NLayers<<"  "<<1./NLayers*(i-1.)<<"   "<<1./NLayers*i<<endl;
//G4cout<<BeamOut->GetProb_Bef()<<G4endl;


//cout<<RLayer<<"       RLAYER"<<endl;


  
  G4UserLimits* pUserLimits
    = aTrack.GetVolume()->GetLogicalVolume()->GetUserLimits();
    //cout<<name<<endl;
  //if(G4StrUtil::contains(name, "Diamond")){
    if(r3<BeamOut->GetProb_In()){
      for(int i=1;i<=NLayers;i++){
        if(r>(1/NLayers*(i-1))&&r<=(1/NLayers*i)){RLayer = i-1 ;}  // determination of the reaction layer based on the random generated number (one number for one event) 
        }
      
    }


     //G4cout<<aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName()<<" particle name"<<endl;
   // G4cout<<BeamOut->GetAin()<<endl;
    std::string s = std::to_string(BeamOut->GetAin());
    if(aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName().contains(s)){

      //cout<<"contain !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;


    }
   //G4cout<< aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName()<<endl;
   
      
    //Target excitations:
    //Stop and kill the decay product once it reaches its ground state.
   
    if( target_reaction &&
	 !aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName().contains('[') ){
       ground_state = true;
      target_reaction = false;  //Reset for next decay
      return 0;
     }
  
    //G4double ZReaction=pUserLimits->GetUserMinRange(aTrack)*(-1);

    // REACTION CAN HAPPPEN IN THE WHOLE VOLUME OF THE DIAMOND, NOT ONLY IN THE MITTEL

    G4double thic = Det->GetLayerThickness(RLayer) ; 
    //cout<<r<<"    "<<thic<<"   "<<RLayer<<endl;
    G4double ZReaction = -100.0  ; 

    if(r3<BeamOut->GetProb_In()){

      ZReaction= (Mids[RLayer]+ (r2*thic - 0.5*thic));}

    if(r3>=BeamOut->GetProb_In() && r3 < (BeamOut->GetProb_In()+BeamOut->GetProb_Bef())) {
      ZReaction= Det->GetKW_Zdim() ;
      }
      if(r3>=(BeamOut->GetProb_In()+BeamOut->GetProb_Bef()) && r3 <= (BeamOut->GetProb_In()+BeamOut->GetProb_Bef()+BeamOut->GetProb_Aft())){ eventInfo->GetSimEvent()->SetReactionLayer(999); } 

    //cout<<r2*thic - 0.5*thic<<endl;
    //cout<<ZReaction<<"   ZReaction"<<endl;
    //G4double ZReaction= -7.75;
    //cout<<Mids[RLayer]<<endl;
    //G4cout<<"Reaction should be in Layer  "<<RLayer<<endl;

    //ZReaction = -100.0  ;   ////////////////////////////////////////////////////     comment if you want to have reaction !!!!!!!!!!!!!!!!1111111

    G4double ZCurrent=aTrack.GetPosition().getZ();
    G4double Z=(ZReaction-ZCurrent);
      if(Z>0){
      //if(Z<0 ){
      //  G4cout<<" Past the reaction point"<<G4endl;
      //  G4cout<<" Volume "<<name<<G4endl;
      //  G4cout<<" Z[mm]: reaction "<<ZReaction/mm<<" current "<<ZCurrent/mm<<" DZ "<<Z/mm<<G4endl;

      return DBL_MAX;
      //return dir.mag();
    } else if(abs(Z)>eps ) {
      G4ThreeVector dir=aTrack.GetDynamicParticle()->GetMomentumDirection();
      
      dir*=(ZReaction-ZCurrent);
      //  G4cout<<" Before the reaction point"<<G4endl;
      //  G4cout<<" Volume "<<name<<G4endl;
      //  G4cout<<" Z[mm]: reaction "<<ZReaction/mm<<" current "<<ZCurrent/mm<<" DZ "<<Z/mm<<G4endl;
       reaction_here=false;
      return dir.mag();
    } else if( (abs(Z)<eps && BeamOut->GetAin()==0) ||(abs(Z)<eps && aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName().contains(s))) {
      
       // G4cout<<" At the reaction point"<<G4endl;
      //  G4cout<<" Volume "<<name<<G4endl;
      //  G4cout<<" Z[mm]: reaction "<<ZReaction/mm<<" current "<<ZCurrent/mm<<" DZ "<<Z/mm<<G4endl;
      //cout<<RLayer<<endl;
       eventInfo->GetSimEvent()->SetReactionLayer(RLayer);  
       if(G4StrUtil::contains(name, "plate")){eventInfo->GetSimEvent()->SetReactionLayer(RLayer+10);}  
       //cout<<ZReaction<<endl;
      reaction_here = true;
      if( BeamOut->TargetExcitation() ) 
	target_reaction = true;
      return 0.;
    }
      




  //}
    


  //G4cout<<RLayer<<endl;

 
  
  return DBL_MAX;
}

// If the reaction product comes to rest after emitting its gamma(s), kill it.
// G4VParticleChange* Reaction::AtRestDoIt(
// 			     const G4Track& aTrack,
// 			     const G4Step& aStep
// 			    )
G4VParticleChange* Reaction::AtRestDoIt(
			     const G4Track& aTrack,
			     const G4Step&          // unused parameter
			    )
{

   G4cout << "I'm in AtRestDoIt." << G4endl;
  // G4cout << "  " 
  // 	 << aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName()
  // 	 << G4endl;

  aParticleChange.Initialize(aTrack);
    
  if( !aTrack.GetDynamicParticle()->GetParticleDefinition()->GetParticleName().contains('[') ) { 

     //G4cout << "************************* AtRestDoIt: terminating track in "
     	   //<< aStep.GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()
    	   //<< G4endl;

    //aParticleChange.ProposeTrackStatus(fStopAndKill);

  }

  return &aParticleChange;

}