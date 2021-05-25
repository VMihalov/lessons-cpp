let matrix = [
  [ Infinity, 6, 1, 5, Infinity, Infinity ],
  [ 6, Infinity, 5, Infinity, 3, Infinity ],
  [ 1, 5, Infinity, 5, 6, 4 ],
  [ 5, Infinity, 5, Infinity, Infinity, 2 ],
  [ Infinity, 3, 6, Infinity, Infinity, 6 ],
  [ Infinity,Infinity, 4, 2, 6, Infinity ]
];

function kruskal(){
  let edgeObj = generateEdgeObj(matrix);

  edgeObj = sortEdge_increse(edgeObj);

  let vset = [];

  for (let i = 0; i < matrix.length; i++) {
    vset.push(i);
  }

  let edges = [];
  let m, n;

  for (i = 0; i < edgeObj.length; i++) {
    m = locate(edgeObj[i].start, vset);
    n = locate(edgeObj[i].end, vset);

    if (m != n) {
      edges.push({
        start: edgeObj[i].start,
        end: edgeObj[i].end
      });

      vset [m] = n;
    }
  }

  return edges;
}

function generateEdgeObj(matrix) {
  let edgeObj = [];

  for (let i = 0; i < matrix.length; i++) {
    for (let j = 0; j < i; j++) {
      if (matrix[i][j] != Infinity) {
        edgeObj.push({
          start: i,
          end: j,
          weight: matrix[i][j]
        });
      }
    }
  }

  return edgeObj;
}

function sortEdge_increse(edgeObj) {
  for (let i = 0; i < edgeObj.length-1; i++) {
    for (let j = 0; j < edgeObj.length-1-i; j++) {
      if (edgeObj[j].weight > edgeObj[j+1].weight) {
        let temp = edgeObj[j];
        edgeObj[j] = edgeObj[j+1];
        edgeObj[j+1] = temp;
      }
    }
  }

  return edgeObj;
}

function locate(vexIndex, vset) {
  let temp = vexIndex;

  while (temp != vset[temp]) {
    temp = vset[temp];
  }

  return temp;
}

console.log(kruskal());