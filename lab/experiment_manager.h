#pragma once

#include <memory>
#include <vector>

namespace omni{
  class Experiment;

  class ExperimentManager{
    public:
      ExperimentManager() = default;

      ~ExperimentManager();

      void addExperiment(std::unique_ptr<Experiment> experiment);

      void initialize();

      void update(float dt);

      void render();

      void shutdown();

      Experiment* currentExperiment();

    private:
      std::vector<std::unique_ptr<Experiment>> mExperiments;

      Experiment* mCurrentExperiment = nullptr;
  };

}