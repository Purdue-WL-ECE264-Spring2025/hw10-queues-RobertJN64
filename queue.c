#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
  insert_at_tail(&(q->data), serialize(state));
}

struct game_state dequeue(struct queue *q) {
  return deserialize(remove_from_head(&(q->data)));
}

int number_of_moves(struct game_state start) {
  struct queue q = {NULL};
  enqueue(&q, start);

  // while still have states to check
  while (q.data.head != NULL) {
    struct game_state state = dequeue(&q);
    uint16_t prev_steps = state.num_steps;

    // check if done
    int counter = 1;
    bool done = true;
    for (int row = 0; row < 4; row++) {
      for (int col = 0; col < 4; col++) {
        if (state.tiles[row][col] != counter) {
          done = false;
        }
        counter++;
        counter %= 16;
      }
    }

    if (done) {
      free_list(q.data);
      return state.num_steps;
    }

    // generate each of the next states, queue them, and then revert
    move_up(&state);
    if (state.num_steps > prev_steps) {
      enqueue(&q, state);
      move_down(&state);
      state.num_steps -= 2;
    }

    move_down(&state);
    if (state.num_steps > prev_steps) {
      enqueue(&q, state);
      move_up(&state);
      state.num_steps -= 2;
    }

    move_left(&state);
    if (state.num_steps > prev_steps) {
      enqueue(&q, state);
      move_right(&state);
      state.num_steps -= 2;
    }

    move_right(&state);
    if (state.num_steps > prev_steps) {
      enqueue(&q, state);
      move_left(&state);
      state.num_steps -= 2;
    }
  }

  free_list(q.data);
  return -1;
}
