// Поиск в глубину

function dfs(graph: any, start: string, visited: any = {}) {
  if (!graph[start]) return;

	visited[start] = true;

  console.log(start);

  for (const vertex of graph[start]) {
    if (!visited[vertex]) {
      dfs(graph, vertex, visited);
    }
  }
}

function main(): Number {
  const graph: any = {};

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
