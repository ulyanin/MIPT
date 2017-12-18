import math


def degree(graph, v, colors):
    if colors[v] != -1:
        return -1
    deg = 0
    for u in graph[v]:
        deg += colors[u] == -1
    return deg


def find_max_deg(graph, vertices, colors):
    return max(
        [
            (degree(graph, v, colors), v)
            for v in vertices
        ]
    )


def bipartition_coloring(graph, v, colors, valid_vertices, color=0):
    if colors[v] != -1:
        return
    colors[v] = color
    for u in graph[v]:
        if u in valid_vertices:
            bipartition_coloring(graph, u, colors, valid_vertices, color ^ 1)
            if colors[v] == colors[u]:
                raise ValueError("neighbours have the same colors")


def mex(s, start=0):
    while start in s:
        start += 1
    return start


def greedy_coloring(graph, v, colors, valid_vertices):
    if colors[v] != -1:
        return
    colors[v] = -2
    used_colors = set()
    for u in graph[v]:
        greedy_coloring(graph, u, colors, valid_vertices)
        used_colors.add(colors[u])
    colors[v] = mex(used_colors)


def neighbours(graph, v, colors):
    return [u for u in graph[v] if colors[u] == -1]


def wigderson_algorithm(graph):
    """
    implements Wigderson Algorithm of finding O(sqrt(n))-coloring of
    3-colored input graph with polynomial complexity
    :param graph: adjacency matrix
    :return: list of colors of vertices
    """

    def apply_coloring(vertices_to_color, color_alg):
        vertices_to_color = set(vertices_to_color)
        for v in vertices_to_color:
            color_alg(graph, v, colors, vertices_to_color)
        for v in vertices_to_color:
            colors[v] += min_color

    colors = [-1] * len(graph)
    min_color = 0
    sqrt_n = max(2, int(math.sqrt(len(graph))))
    while True:
        vertices = [v for v in range(len(graph)) if colors[v] == -1]
        if not vertices:
            break
        d, v = find_max_deg(graph, vertices, colors)
        if d < sqrt_n:
            break
        colors[v] = min_color
        min_color += 1
        curr_neighbours = neighbours(graph, v, colors)
        apply_coloring(curr_neighbours, bipartition_coloring)
        min_color = max(colors) + 1
    rest_vertices = [v for v in range(len(graph)) if colors[v] == -1]
    apply_coloring(rest_vertices, greedy_coloring)
    return colors


get_coloring = wigderson_algorithm
