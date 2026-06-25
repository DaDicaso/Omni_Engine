#include "experiment_manager.h"
#include "experiment.h"

namespace omni
{
  ExperimentManager::~ExperimentManager(){
    shutdown();
  }

  void ExperimentManager::addExperiment(std::unique_ptr<Experiment> experiment){
    if(!mCurrentExperiment)
      mCurrentExperiment = experiment.get();

    mExperiments.emplace_back(std::move(experiment));
  }

  void ExperimentManager::initialize(){
    if(mCurrentExperiment){
      mCurrentExperiment->init();
    }
  }

  void ExperimentManager::update(float dt){
    if(mCurrentExperiment)
      mCurrentExperiment->update(dt);
  }

  void ExperimentManager::render(){
    if(mCurrentExperiment)
      mCurrentExperiment->render();
  }

  void ExperimentManager::shutdown(){
    if(mCurrentExperiment)
      mCurrentExperiment->shutdown();
  }

  Experiment* ExperimentManager::currentExperiment(){
    return mCurrentExperiment;
  }

}
