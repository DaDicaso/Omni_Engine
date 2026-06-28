#include<iostream>
#include "lab/experiment_manager.h"

#include "lab/experiment.h"
#include "lab/experiments/Gravity/gravity_experiment.h"

#include "engine/renderer/renderer.h" 

namespace omni
{

  ExperimentManager::ExperimentManager(){
    setExperiment(std::make_unique<GravityExperiment>());
  }
  
  ExperimentManager::~ExperimentManager(){
    shutdown();
  }

  void ExperimentManager::setExperiment(std::unique_ptr<Experiment> experiment){
    if(mCurrentExperiment){
      mCurrentExperiment->shutdown();
    }

    mCurrentExperiment = std::move(experiment);
    if(mCurrentExperiment){
      mCurrentExperiment->initialize();
    }
  }

  void ExperimentManager::initialize(){
    if(mCurrentExperiment){
      mCurrentExperiment->initialize();
    }
  }

  void ExperimentManager::update(float dt){
    if(mCurrentExperiment)
      mCurrentExperiment->update(dt);

   // std::cout << dt << '\n';
  }

  void ExperimentManager::render(Renderer& renderer){
    if(mCurrentExperiment)
      mCurrentExperiment->render(renderer);
  }

  void ExperimentManager::shutdown(){
    if(mCurrentExperiment)
      mCurrentExperiment->shutdown();
  }

  Experiment* ExperimentManager::getcurrentExperiment() const{
    return mCurrentExperiment.get();
  }

}
