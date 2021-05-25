// Алгоритм Прима

function prim(matrix: any) {
  let edges = 1;
  let selected: any = [];

  selected[0] = true;

  while (edges < matrix.length) {
    let min = Infinity;
    let x = 0;
    let y = 0;

    for (let i = 0; i < matrix.length; i++) {
      if (selected[i]) {
        for (let j = 0; j < matrix[i].length; j++) {
          if (!selected[j] && matrix[i][j]) {
            if (min > matrix[i][j]) {
              min = matrix[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }

    console.log(x + ' -> ' + y + ' = ' + matrix[x][y]);

    selected[y] = true;

    edges++;
  }
}

function main(): number {
  const matrix = [
    [0, 9, 75, 0, 0],
    [9, 0, 95, 19, 42],
    [75, 95, 0, 51, 66],
    [0, 19, 51, 0, 31],
    [0, 42, 66, 31, 0],
  ];

  prim(matrix);

  return 0;
}

main();
