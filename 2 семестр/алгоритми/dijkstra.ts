// Алгоритм Дейкстри

function getShortPath(graph: any, start: any): void {
  const costs: any = {};
  const checked: any = [];
  let result: any = {};

  Object.keys(graph).forEach(node => {
    if (node !== start) {
      let value = graph[start][node];
      costs[node] = value || Infinity;
    }
  });

  let node = findLowestCost(costs, checked);

  while (node) {
    const cost = costs[node];
    result = graph[node];

    Object.keys(result).forEach(neighbor => {
      let newCost = cost + result[neighbor];

      if (newCost < costs[neighbor]) {
        costs[neighbor] = newCost;
      }
    });

    checked.push(node);
    node = findLowestCost(costs, checked);
  }

  return costs;
}

function findLowestCost(costs: any, checked: any) {
  let lowestCost: Number = Infinity;
  let lowestNode;

  Object.keys(costs).forEach(node => {
    let cost = costs[node];

    if (cost < lowestCost && !checked.includes(node)) {
      lowestCost = cost;
      lowestNode = node;
    }
  });
  console.log(lowestNode);
  return lowestNode;
}

function main(): Number {
  const graph: any = {};

  graph.a = { b: 14, c: 9, d: 7 };
  graph.b = { f: 9, c: 2 };
  graph.c = { b: 2, e: 11 };
  graph.d = { c: 10, e: 15 };
  graph.e = { f: 6 };
  graph.f = {};

  const shortPath = getShortPath(graph, 'a');

  console.log(shortPath);

  return 0;
}


main();
