#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef enum {
  OP_CONSTANT,
  OP_CONSTANT_LONG,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NEGATE,
  OP_RETURN,
} OpCode;

typedef struct {
  int offset;
  int line;
} LineStart;

typedef struct {
  int count;
  int capacity;
  uint8_t *code;
  ValueArray constants;
  int lineCount;
  int lineCapacity;
  LineStart* lines;
} Chunk;

void initChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte, int line);
int addConstant(Chunk *chunk, Value value);
void freeChunk(Chunk *chunk);
int getLine(Chunk *chunk, int instruction);
void writeConstant(Chunk *chunk, Value val, int line);

#endif