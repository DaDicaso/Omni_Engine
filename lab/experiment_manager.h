#pragma once

#include <memory>

namespace omni{
  class Experiment;
  class Renderer;

  class ExperimentManager{
    public:
      ExperimentManager();
      ~ExperimentManager();

      void setExperiment(std::unique_ptr<Experiment> experiment);

      void initialize();

      void update(float dt);

      void render(Renderer& renderer);

      void shutdown();

      Experiment* getcurrentExperiment() const;

    private:
      std::unique_ptr<Experiment> mCurrentExperiment;
  };

}