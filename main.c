#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  initVM();
  Chunk chunk;
  initChunk(&chunk);

  writeConstant(&chunk, 100, 1);
  writeConstant(&chunk, 10, 1);

  writeChunk(&chunk, OP_ADD, 1);

  writeConstant(&chunk, 2.5, 1);

  writeChunk(&chunk, OP_DIVIDE, 1);
  writeChunk(&chunk, OP_NEGATE, 1);
  writeChunk(&chunk, OP_RETURN, 1);

  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);
  return 0;
}