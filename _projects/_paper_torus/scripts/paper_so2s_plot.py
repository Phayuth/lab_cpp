import numpy as np
from itertools import product
import networkx as nx
import matplotlib.pyplot as plt


class Utils:

    def wrap_to_pi(q):
        return (q + np.pi) % (2 * np.pi) - np.pi

    def find_alt_config(q, configLimit, configConstrict=None, filterOriginalq=False):  # a better function than find_shifted_value
        """
        Find the alternative value of configuration in different quadrand.
        configConstrict : Constrict specific joint from finding alternative. Ex: the last joint of robot doesn't make any different when moving so we ignore them.
        filterOriginalq : Filter out the original q value. Keep only the alternative value in array. by default False
        """
        # possible config value
        qw = Utils.wrap_to_pi(q)  # transform to base quadrand first
        qShifted = qw + np.array(list(product([-2.0 * np.pi, 0.0, 2.0 * np.pi], repeat=qw.shape[0]))).T

        # eliminate with joint limit
        isInLimitMask = np.all((qShifted >= configLimit[:, 0, np.newaxis]) & (qShifted <= configLimit[:, 1, np.newaxis]), axis=0)
        qInLimit = qShifted[:, isInLimitMask]

        # joint constrict
        if configConstrict is not None:
            assert isinstance(configConstrict, list), "configConstrict must be in list format"
            assert len(configConstrict) == qw.shape[0], "configConstrict length must be equal to state number"
            for i in range(len(configConstrict)):
                if configConstrict[i] is True:
                    qInLimit[i] = qw[i]

        if filterOriginalq:
            exists = np.all(qInLimit == q, axis=0)
            filterout = qInLimit[:, ~exists]
            return filterout

        return qInLimit

    def nearest_qb_to_qa(qa, qb, configLimit, ignoreOrginal=True):
        """
        if ignore_original there alway be torus path arround even the two point is close
        if not, then the original will be consider and if it has minimum distance there only 1 way to move.
        """
        Qb = Utils.find_alt_config(qb, configLimit, filterOriginalq=ignoreOrginal)
        di = Qb - qa
        n = np.linalg.norm(di, axis=0)
        minid = np.argmin(n)
        return Qb[:, minid, np.newaxis]


class PlotterConfig:
    globalLinewidth = 1

    obstColor = "darkcyan"
    obstFaceColor = "darkcyan"
    obstMarker = "o"
    obstMarkersize = 1.5

    treeColor = "darkgray"
    treeFaceColor = None
    treeMarker = None
    treeMarkersize = None

    stateStartColor = "blue"
    stateStartFaceColor = "yellow"
    stateAppColor = "blue"
    stateAppFaceColor = "green"
    stateGoalColor = "blue"
    stateGoalFaceColor = "red"
    stateMarkersize = 7
    stateMarker = "o"

    pathColor = "blue"
    pathFaceColor = "plum"
    pathMarker = "o"
    pathMarkersize = 7


graph = nx.read_graphml("./exompl/build/paper_so2s_planner_data.graphml")
path = np.loadtxt("./exompl/build/paper_so2s_path.csv", delimiter=",")
state = np.loadtxt("./exompl/build/paper_so2s_start_goal.csv", delimiter=",")
colp = np.load("./exompl/build/collisionpoint_so2s.npy")

# plotting
plt.figure(figsize=(8,8))
plt.tight_layout()

limt2 = np.array([[-2 * np.pi, 2 * np.pi], [-2 * np.pi, 2 * np.pi]])
# tree
for u, v in graph.edges:
    u = graph.nodes[u]["coords"].rsplit(",")
    u = np.array(u).astype(np.float32).reshape(2, 1)
    v = graph.nodes[v]["coords"].rsplit(",")
    v = np.array(v).astype(np.float32).reshape(2, 1)
    quvw = Utils.nearest_qb_to_qa(u, v, limt2, ignoreOrginal=False)
    qvuw = Utils.nearest_qb_to_qa(v, u, limt2, ignoreOrginal=False)
    plt.plot(
        [u[0], quvw[0]],
        [u[1], quvw[1]],
        color=PlotterConfig.treeColor,
        linewidth=PlotterConfig.globalLinewidth,
        marker=PlotterConfig.treeMarker,
        markerfacecolor=PlotterConfig.treeFaceColor,
        markersize=PlotterConfig.treeMarkersize,
    )
    plt.plot(
        [v[0], qvuw[0]],
        [v[1], qvuw[1]],
        color=PlotterConfig.treeColor,
        linewidth=PlotterConfig.globalLinewidth,
        marker=PlotterConfig.treeMarker,
        markerfacecolor=PlotterConfig.treeFaceColor,
        markersize=PlotterConfig.treeMarkersize,
    )


# path
for i in range(path.shape[0] - 1):
    u = path[i].reshape(2, 1)
    v = path[i + 1].reshape(2, 1)
    quvw = Utils.nearest_qb_to_qa(u, v, limt2, ignoreOrginal=False)
    qvuw = Utils.nearest_qb_to_qa(v, u, limt2, ignoreOrginal=False)
    plt.plot(
        [u[0], quvw[0]],
        [u[1], quvw[1]],
        color=PlotterConfig.pathColor,
        linewidth=PlotterConfig.globalLinewidth,
        marker=PlotterConfig.pathMarker,
        markerfacecolor=PlotterConfig.pathFaceColor,
        markersize=PlotterConfig.pathMarkersize,
    )
    plt.plot(
        [v[0], qvuw[0]],
        [v[1], qvuw[1]],
        color=PlotterConfig.pathColor,
        linewidth=PlotterConfig.globalLinewidth,
        marker=PlotterConfig.pathMarker,
        markerfacecolor=PlotterConfig.pathFaceColor,
        markersize=PlotterConfig.pathMarkersize,
    )


# state start
plt.plot(
    state[0, 0],
    state[0, 1],
    color=PlotterConfig.stateStartColor,
    linewidth=0,
    marker=PlotterConfig.stateMarker,
    markerfacecolor=PlotterConfig.stateStartFaceColor,
    markersize=PlotterConfig.stateMarkersize,
)

# state goals
plt.plot(
    state[1:, 0],
    state[1:, 1],
    color=PlotterConfig.stateGoalColor,
    linewidth=0,
    marker=PlotterConfig.stateMarker,
    markerfacecolor=PlotterConfig.stateGoalFaceColor,
    markersize=PlotterConfig.stateMarkersize,
)

plt.plot(
    colp[:, 0],
    colp[:, 1],
    color="darkcyan",
    linewidth=0,
    marker="o",
    markerfacecolor="darkcyan",
    markersize=1.5,
)

plt.xlim((-np.pi, np.pi))
plt.ylim((-np.pi, np.pi))
plt.show()
