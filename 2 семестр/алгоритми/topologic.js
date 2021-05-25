// Поиск в глубину

function dfs(graph, start, visited = {}) {
  if (!graph[start]) return;

	visited[start] = true;

  console.log(start);

  for (const vertex of graph[start]) {
    if (!visited[vertex]) {
      dfs(graph, vertex, visited);
    }
  }
}

function main() {
  const graph = {};

  graph.a = ['b', 'c'];
  graph.b = ['f'];
  graph.c = ['d', 'e'];
  graph.d = ['f'];
  graph.e = ['f'];
  graph.f = ['g'];

  dfs(graph, 'a');

  return 0;
}

main();
