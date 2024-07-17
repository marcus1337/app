
fetch('example.wasm')
  .then(response => response.arrayBuffer())
  .then(buffer => WebAssembly.instantiate(buffer))
  .then(({ instance }) => {
    console.log(instance.exports.main());
  })
  .catch(err => {
    console.error('Failed to fetch WebAssembly module:', err);
  });
