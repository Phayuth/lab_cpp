import networkx as nx
import matplotlib.pyplot as plt
import numpy as np


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


graph = nx.read_graphml("./exompl/build/zzzzz_planner_data.graphml")
path = np.loadtxt("./exompl/build/zzzzz_path.csv", delimiter=",")
state = np.loadtxt("./exompl/build/zzzzz_start_goal.csv", delimiter=",")
colp = np.load("./exompl/build/collisionpoint_exts.npy")



# def get_graphml_node_as_array(graph):
#     coord = []
#     for i in range(len(graph.nodes)):
#         qstr: str = graph.nodes[f"n{i}"]["coords"]
#         coord.append(qstr.rsplit(","))
#     coordar = np.array(coord, dtype=np.float32)
#     return coordar

# coordar = get_graphml_node_as_array(graph)
# plt.plot(coordar[:, 0], coordar[:, 1], linewidth=0, color="darkgray", marker="o", markerfacecolor="darkgray")
# plt.plot(path[:, 0], path[:, 1], linewidth=3, color="red", marker="o", markerfacecolor="black")
# plt.show()

# plotting
plt.figure(figsize=(8,8))
plt.tight_layout()

# tree
for u, v in graph.edges:
    u = graph.nodes[u]["coords"].rsplit(",")
    v = graph.nodes[v]["coords"].rsplit(",")
    plt.plot(
        [float(u[0]), float(v[0])],
        [float(u[1]), float(v[1])],
        color=PlotterConfig.treeColor,
        linewidth=PlotterConfig.globalLinewidth,
        marker=PlotterConfig.treeMarker,
        markerfacecolor=PlotterConfig.treeFaceColor,
        markersize=PlotterConfig.treeMarkersize,
    )

# path
plt.plot(
    path[:, 0],
    path[:, 1],
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

plt.xlim((-2*np.pi, 2*np.pi))
plt.ylim((-2*np.pi, 2*np.pi))
plt.axhline(y=np.pi,color="gray", alpha=0.4)
plt.axhline(y=-np.pi,color="gray", alpha=0.4)
plt.axvline(x=np.pi,color="gray", alpha=0.4)
plt.axvline(x=-np.pi,color="gray", alpha=0.4)
plt.show()
