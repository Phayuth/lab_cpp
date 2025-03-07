#ifndef PHAYUTH_GEOMETRIC_PLANNERS_RRT_RRTSTAR_CONNECT_
#define PHAYUTH_GEOMETRIC_PLANNERS_RRT_RRTSTAR_CONNECT_

#include "ompl/datastructures/NearestNeighbors.h"
#include "ompl/geometric/planners/PlannerIncludes.h"

namespace ompl {
namespace geometric {
class RRTStarConnect : public base::Planner {
    public:
        RRTStarConnect(const base::SpaceInformationPtr &si, bool addIntermediateStates = false);

        ~RRTStarConnect() override;

        void getPlannerData(base::PlannerData &data) const override;

        base::PlannerStatus solve(const base::PlannerTerminationCondition &ptc) override;

        void clear() override;

        void setup() override;

        bool getIntermediateStates() const {
            return addIntermediateStates_;
        }

        void setIntermediateStates(bool addIntermediateStates) {
            addIntermediateStates_ = addIntermediateStates;
        }

        void setRange(double distance) {
            maxDistance_ = distance;
        }

        double getRange() const {
            return maxDistance_;
        }

        template <template <typename T> class NN>
        void setNearestNeighbors() {
            if ((tStart_ && tStart_->size() != 0) || (tGoal_ && tGoal_->size() != 0))
                OMPL_WARN("Calling setNearestNeighbors will clear all states.");
            clear();
            tStart_ = std::make_shared<NN<Motion *>>();
            tGoal_ = std::make_shared<NN<Motion *>>();
            setup();
        }


    protected:
        class Motion {
            public:
                Motion() = default;

                Motion(const base::SpaceInformationPtr &si) : state(si->allocState()) {
                }

                ~Motion() = default;

                const base::State *root{nullptr};
                base::State *state{nullptr};
                Motion *parent{nullptr};
        };

        using TreeData = std::shared_ptr<NearestNeighbors<Motion *>>;

        struct TreeGrowingInfo {
                base::State *xstate;
                Motion *xmotion;
                bool start;
        };

        enum GrowState {
            TRAPPED,
            ADVANCED,
            REACHED
        };

        void freeMemory();

        double distanceFunction(const Motion *a, const Motion *b) const {
            return si_->distance(a->state, b->state);
        }

        GrowState growTree(TreeData &tree, TreeGrowingInfo &tgi, Motion *rmotion);

        base::StateSamplerPtr sampler_;

        TreeData tStart_;

        TreeData tGoal_;

        bool startTree_{true};

        double maxDistance_{0.};

        bool addIntermediateStates_;

        RNG rng_;

        std::pair<base::State *, base::State *> connectionPoint_;

        double distanceBetweenTrees_;
};
} // namespace geometric
} // namespace ompl

#endif