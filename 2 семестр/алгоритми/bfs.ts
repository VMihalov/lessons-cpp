// Поиск в ширину

function search(graph: any, start: string, goal: string) {
  let queue: any = [];

  queue.push(start);

  while (true) {
    let node = queue.shift();

    if (node === goal) return true;

    if (!graph[node]) break;

    for (const vertex of graph[node]) {
      queue.push(vertex);
    }
  }

  return false;
}

function main() {
  const graph: any = {};

  graph.a = ['b', 'c'];
  graph.b = ['f'];
  graph.c = ['d', 'e'];
  graph.d = ['f'];
  graph.e = ['f'];
  graph.f = ['g'];

  let vertex = search(graph, 'a', 'g');

  console.log(vertex);
}

main();
