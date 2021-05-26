// Топологічне сортування

let vertexes = [];

function dfs(graph, start, visited = {}) {
	visited[start] = true;

  for (const vertex of graph[start]) {
    if (!visited[vertex]) {
      dfs(graph, vertex, visited);
    }
  }

  vertexes.push(start);
}

function main() {
  const graph = {};

  graph.a = ['d', 'e'];
  graph.b = ['d'],
  graph.c = ['e', 'h'];
  graph.d = ['f', 'g', 'h'];
  graph.e = ['g'];
  graph.f = [];
  graph.g = [];
  graph.h = [];

  dfs(graph, 'a');

  for (let v of vertexes)
    console.log(v);

  return 0;
}

main();
