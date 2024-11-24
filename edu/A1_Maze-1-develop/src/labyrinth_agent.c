#include "labyrinth.h"

static int choose_action(double *q_values, int num_actions) {
  int best_action = 0;
  double max_value = q_values[0];
  for (int i = 1; i < num_actions; ++i) {
    if (q_values[i] > max_value) {
      max_value = q_values[i];
      best_action = i;
    }
  }
  return best_action;
}

static int epsilon_greedy_action(double *q_values, int num_actions,
                                 double epsilon) {
  if ((double)rand() / RAND_MAX < epsilon) {
    return rand() % num_actions;  // Случайное действие
  } else {
    return choose_action(q_values, num_actions);  // Жадное действие
  }
}

Agent *init_agent(int rows, int cols, int end_x, int end_y) {
  Agent *agent = malloc(sizeof(Agent));
  agent->rows = rows;
  agent->cols = cols;
  agent->end_x = end_x;
  agent->end_y = end_y;
  agent->q_table = malloc(rows * cols * sizeof(double *));
  for (int i = 0; i < rows * cols; ++i) {
    agent->q_table[i] = malloc(ACTIONS * sizeof(double));
    for (int j = 0; j < ACTIONS; ++j) {
      agent->q_table[i][j] = 0.0;
    }
  }
  return agent;
}

void train_agent(Agent *agent, const Labyrinth *labyrinth, int episodes,
                 int max_steps) {
  for (int e = 0; e < episodes; ++e) {
    int x = rand() % agent->cols;
    int y = rand() % agent->rows;
    for (int step = 0; step < max_steps; ++step) {
      int state = y * agent->cols + x;
      int action =
          epsilon_greedy_action(agent->q_table[state], ACTIONS, EPSILON);
      int new_x = x, new_y = y;

      switch (action) {
        case 0:
          if (x < agent->cols - 1 && labyrinth->v_walls[y][x] == 0) new_x++;
          break;
        case 1:
          if (y < agent->rows - 1 && labyrinth->h_walls[y][x] == 0) new_y++;
          break;
        case 2:
          if (x > 0 && labyrinth->v_walls[y][x - 1] == 0) new_x--;
          break;
        case 3:
          if (y > 0 && labyrinth->h_walls[y - 1][x] == 0) new_y--;
          break;
      }

      int new_state = new_y * agent->cols + new_x;
      double reward =
          (new_x == agent->end_x && new_y == agent->end_y) ? 100.0 : -1.0;
      double best_next_q = agent->q_table[new_state][choose_action(
          agent->q_table[new_state], ACTIONS)];

      agent->q_table[state][action] = agent->q_table[state][action] +
                                      ALPHA * (reward + GAMMA * best_next_q -
                                               agent->q_table[state][action]);

      x = new_x;
      y = new_y;

      if (x == agent->end_x && y == agent->end_y) break;
    }
  }
}

bool get_optimal_path(const Agent *agent, const Labyrinth *labyrinth,
                      int start_x, int start_y, Point **path,
                      int *path_length) {
  int x = start_x, y = start_y;
  int max_steps = agent->rows * agent->cols;
  *path_length = 0;
  *path = malloc(max_steps * sizeof(Point));

  while (x != agent->end_x || y != agent->end_y) {
    if (*path_length >= max_steps) {
      free(*path);
      return false;
    }
    (*path)[(*path_length)++] = (Point){x, y};
    int state = y * agent->cols + x;
    int action = choose_action(agent->q_table[state], ACTIONS);

    switch (action) {
      case 0:
        if (x < agent->cols - 1 && labyrinth->v_walls[y][x] == 0) x++;
        break;
      case 1:
        if (y < agent->rows - 1 && labyrinth->h_walls[y][x] == 0) y++;
        break;
      case 2:
        if (x > 0 && labyrinth->v_walls[y][x - 1] == 0) x--;
        break;
      case 3:
        if (y > 0 && labyrinth->h_walls[y - 1][x] == 0) y--;
        break;
    }
  }

  (*path)[(*path_length)++] = (Point){agent->end_x, agent->end_y};
  return true;
}

void free_agent(Agent *agent) {
  for (int i = 0; i < agent->rows * agent->cols; ++i) {
    free(agent->q_table[i]);
  }
  free(agent->q_table);
  free(agent);
}