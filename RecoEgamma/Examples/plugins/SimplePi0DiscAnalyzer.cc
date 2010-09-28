// -*- C++ -*-
//
// Package:    RecoEgamma/Examples
// Class:      SimplePi0DiscAnalyzer
//
/**\class SimplePi0DiscAnalyzer RecoEgamma/Examples/src/SimplePi0DiscAnalyzer.cc

<<<<<<< SimplePi0DiscAnalyzer.cc
 Description: Pi0Disc analyzer using reco data
=======
 Description: Pi0DiscAnalyzer analyzer using reco data
>>>>>>> 1.8

 Implementation:
     <Notes on implementation>
*/
//
<<<<<<< SimplePi0DiscAnalyzer.cc
// Original Author:  Ursula Berthon
//         Created:  Mon Mar 27 13:22:06 CEST 2006
// $Id: SimplePi0DiscAnalyzer.cc,v 1.7 2009/05/26 10:45:45 akyriaki Exp $
// $Id: Bug fixed version by Lindsay Gray and Jan Verveka 27/9/2010
=======
// Original Author:  Aristotelis Kyriakis
//         Created:  May 26 13:22:06 CEST 2009
// $Id: SimplePi0DiscAnalyzer.cc,v 1.8 2010/02/05 14:42:08 akyriaki Exp $
>>>>>>> 1.8
//
//

// user include files
#include "RecoEgamma/Examples/plugins/SimplePi0DiscAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectronFwd.h"
#include "DataFormats/EgammaReco/interface/BasicClusterFwd.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"
#include "DataFormats/EgammaReco/interface/ElectronSeedFwd.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"

#include "CLHEP/Units/PhysicalConstants.h"
#include <iostream>
#include "TMath.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TProfile.h"
#include "TTree.h"
#include <iostream>

using namespace reco;

SimplePi0DiscAnalyzer::SimplePi0DiscAnalyzer(const edm::ParameterSet& conf)
{

  outputFile_ = conf.getParameter<std::string>("outputFile");
  rootFile_ = new TFile(outputFile_.c_str(),"RECREATE");


  photonCollectionProducer_ = conf.getParameter<string>("phoProducer");
  photonCollection_ = conf.getParameter<string>("photonCollection");


 
}

SimplePi0DiscAnalyzer::~SimplePi0DiscAnalyzer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
   rootFile_->Write();
   rootFile_->Close();
}

void SimplePi0DiscAnalyzer::beginJob(){

  rootFile_->cd();
  cout << "beginJob() ->  Book the Histograms" << endl;
  
  hConv_ntracks_ = new TH1F("nConvTracks","Number of tracks of converted Photons ",10,0.,10);
  hAll_nnout_Assoc_ = new TH1F("All_nnout_Assoc","NNout for All Photons(AssociationMap)",100,0.,1.);
  hAll_nnout_NoConv_Assoc_ = new TH1F("All_nnout_NoConv_Assoc","NNout for Unconverted Photons(AssociationMap)",100,0.,1.);
  hAll_nnout_NoConv_Assoc_R9_ = new TH1F("All_nnout_NoConv_Assoc_R9","NNout for Unconverted Photons with R9>0.93 (AssociationMap)",100,0.,1.);
  hBarrel_nnout_Assoc_ = new TH1F("barrel_nnout_Assoc","NNout for Barrel Photons(AssociationMap)",100,0.,1.);
  hBarrel_nnout_NoConv_Assoc_ = new TH1F("barrel_nnout_NoConv_Assoc","NNout for Barrel Unconverted Photons(AssociationMap)",100,0.,1.);
  hBarrel_nnout_NoConv_Assoc_R9_ = new TH1F("barrel_nnout_NoConv_Assoc_R9","NNout for Barrel Unconverted Photons with R9>0.93 (AssociationMap)",100,0.,1.);
  hEndcNoPresh_nnout_Assoc_ = new TH1F("endcNoPresh_nnout_Assoc","NNout for Endcap NoPresh Photons(AssociationMap)",100,0.,1.);
  hEndcNoPresh_nnout_NoConv_Assoc_ = new TH1F("endcNoPresh_nnout_NoConv_Assoc","NNout for Endcap Unconverted NoPresh Photons(AssociationMap)",100,0.,1.);
  hEndcNoPresh_nnout_NoConv_Assoc_R9_ = new TH1F("endcNoPresh_nnout_NoConv_Assoc_R9","NNout for Endcap Unconverted NoPresh Photons with R9>0.93 (AssociationMap)",100,0.,1.);
  hEndcWithPresh_nnout_Assoc_ = new TH1F("endcWithPresh_nnout_Assoc","NNout for Endcap WithPresh Photons(AssociationMap)",100,0.,1.);
  hEndcWithPresh_nnout_NoConv_Assoc_ = new TH1F("endcWithPresh_nnout_NoConv_Assoc","NNout for Endcap Unconverted WithPresh Photons(AssociationMap)",100,0.,1.);
  hEndcWithPresh_nnout_NoConv_Assoc_R9_ = new TH1F("endcWithPresh_nnout_NoConv_Assoc_R9","NNout for Endcap Unconverted WithPresh Photons with R9>0.93 (AssociationMap)",100,0.,1.);

}

void
SimplePi0DiscAnalyzer::endJob(){

  rootFile_->cd();
  cout << "endJob() ->  Write the Histograms" << endl;
  hConv_ntracks_->Write();

  hAll_nnout_Assoc_->Write();
  hAll_nnout_NoConv_Assoc_->Write();
  hAll_nnout_NoConv_Assoc_R9_->Write();
  hBarrel_nnout_Assoc_->Write();
  hBarrel_nnout_NoConv_Assoc_->Write();
  hBarrel_nnout_NoConv_Assoc_R9_->Write();
  hEndcNoPresh_nnout_Assoc_->Write();
  hEndcNoPresh_nnout_NoConv_Assoc_->Write();
  hEndcNoPresh_nnout_NoConv_Assoc_R9_->Write();
  hEndcWithPresh_nnout_Assoc_->Write();
  hEndcWithPresh_nnout_NoConv_Assoc_->Write();
  hEndcWithPresh_nnout_NoConv_Assoc_R9_->Write();

}

void
SimplePi0DiscAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  cout << endl;
  cout << " -------------- NEW EVENT : Run, Event =  " << iEvent.id() << endl;

 Handle<reco::PhotonCollection> PhotonHandle;
  iEvent.getByLabel(photonCollectionProducer_, photonCollection_ , PhotonHandle);
  const reco::PhotonCollection photons = *(PhotonHandle.product());

  cout <<"----> Photons size: "<< photons.size()<<endl;

  edm::Handle<reco::PhotonPi0DiscriminatorAssociationMap>  map;
  iEvent.getByLabel("piZeroDiscriminators","PhotonPi0DiscriminatorAssociationMap",  map);
  reco::PhotonPi0DiscriminatorAssociationMap::const_iterator mapIter;

//  int PhoInd = 0;

  for( reco::PhotonCollection::const_iterator  iPho = photons.begin(); iPho != photons.end(); iPho++) { // Loop over Photons

    reco::Photon localPho(*iPho);

    float Photon_et = localPho.et(); float Photon_eta = localPho.eta(); 
    float Photon_phi = localPho.phi(); float Photon_r9 = localPho.r9();
    bool isPhotConv  = localPho.hasConversionTracks();
//    cout << "Photon Id = " << PhoInd 
    cout << "Photon Id = " <<  iPho - photons.begin()
         << " with Et = " << Photon_et 
         << " Eta = " << Photon_eta 
	 << " Phi = " << Photon_phi 
	 << " R9 = " << Photon_r9 
	 << " and conv_id = " << isPhotConv << endl;


    SuperClusterRef it_super = localPho.superCluster(); // get the SC related to the Photon candidate

//    hConv_ntracks_->Fill(Ntrk_conv);

    float nn = -10;
//    mapIter = map->find(edm::Ref<reco::PhotonCollection>(PhotonHandle,PhoInd));
    mapIter = map->find(edm::Ref<reco::PhotonCollection>(PhotonHandle,iPho - photons.begin()));
    if(mapIter!=map->end()) {
      nn = mapIter->val;
    }
    if(fabs(it_super->eta()) <= 1.442) {
       hBarrel_nnout_Assoc_->Fill(nn);
       hAll_nnout_Assoc_->Fill(nn);
       cout << "AssociationMap Barrel NN = " << nn << endl;
       if(!isPhotConv) {
	  hBarrel_nnout_NoConv_Assoc_->Fill(nn);
	  hAll_nnout_NoConv_Assoc_->Fill(nn);
       }
       if(Photon_r9>0.93) {
	  hBarrel_nnout_NoConv_Assoc_R9_->Fill(nn);
	  hAll_nnout_NoConv_Assoc_R9_->Fill(nn);
       }
    } else if( (fabs(it_super->eta()) >= 1.556 && fabs(it_super->eta()) < 1.65) || fabs(it_super->eta()) > 2.5) {
       hEndcNoPresh_nnout_Assoc_->Fill(nn);
       hAll_nnout_Assoc_->Fill(nn);
       cout << "AssociationMap EndcNoPresh NN = " << nn << endl;
       if(!isPhotConv) {
	  hEndcNoPresh_nnout_NoConv_Assoc_->Fill(nn);
	  hAll_nnout_NoConv_Assoc_->Fill(nn);
       }
       if(Photon_r9>0.93) {
	  hEndcNoPresh_nnout_NoConv_Assoc_R9_->Fill(nn);
	  hAll_nnout_NoConv_Assoc_R9_->Fill(nn);
       }       
    } else if(fabs(it_super->eta()) >= 1.65 && fabs(it_super->eta()) <= 2.5 ) {
       hEndcWithPresh_nnout_Assoc_->Fill(nn);
       hAll_nnout_Assoc_->Fill(nn);
       cout << "AssociationMap EndcWithPresh NN = " << nn << endl;
       if(!isPhotConv) {
	  hEndcWithPresh_nnout_NoConv_Assoc_->Fill(nn);
	  hAll_nnout_NoConv_Assoc_->Fill(nn);
       }
       if(Photon_r9>0.93) {
	  hEndcWithPresh_nnout_NoConv_Assoc_R9_->Fill(nn);
	  hAll_nnout_NoConv_Assoc_R9_->Fill(nn);
       }       
    }


//    PhoInd++;
  } // End Loop over Photons

}
//define this as a plug-in
DEFINE_FWK_MODULE(SimplePi0DiscAnalyzer);

