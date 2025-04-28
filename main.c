#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
  // Chunk chunk;
  // initChunk(&chunk);

  // writeConstant(&chunk, 100, 1);
  // writeConstant(&chunk, 10, 1);

  // writeChunk(&chunk, OP_ADD, 1);

  // writeConstant(&chunk, 2.5, 1);

  // writeChunk(&chunk, OP_DIVIDE, 1);
  // writeChunk(&chunk, OP_NEGATE, 1);
  
  // writeChunk(&chunk, OP_RETURN, 1);

  // interpret(&chunk);
  // freeChunk(&chunk);
  initVM();

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  freeVM();
  
  return 0;
}

static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static void runFile(const char* path) {
  char* source = readFile(path);
  InterpretResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR) exit(65);
  if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

static char* readFile(const char* path) {
  FILE* file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char* buffer = (char*)malloc(fileSize + 1);
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }

  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (buffer == NULL) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }

  buffer[bytesRead] = '\0';
  fclose(file);
  return buffer;
}