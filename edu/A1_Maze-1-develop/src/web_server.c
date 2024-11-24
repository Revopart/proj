#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cave.h"
#include "labyrinth.h"

#define PORT 8088

struct post_status {
  char rows_str[10];
  char cols_str[10];
  char x1_str[10];
  char y1_str[10];
  char x2_str[10];
  char y2_str[10];
  char chance_str[10];
  char birth_limit_str[10];
  char death_limit_str[10];
  int completed;
  struct MHD_PostProcessor *pp;
};

static enum MHD_Result post_iterator(void *con_cls, enum MHD_ValueKind kind,
                                     const char *key, const char *filename,
                                     const char *content_type,
                                     const char *transfer_encoding,
                                     const char *data, uint64_t off,
                                     size_t size) {
  struct post_status *status = (struct post_status *)con_cls;

  // Unused parameters
  (void)kind;
  (void)filename;
  (void)content_type;
  (void)transfer_encoding;
  (void)off;

  if (0 == strcmp(key, "rows"))
    snprintf(status->rows_str, sizeof(status->rows_str), "%.*s", (int)size,
             data);
  else if (0 == strcmp(key, "cols"))
    snprintf(status->cols_str, sizeof(status->cols_str), "%.*s", (int)size,
             data);
  else if (0 == strcmp(key, "x1"))
    snprintf(status->x1_str, sizeof(status->x1_str), "%.*s", (int)size, data);
  else if (0 == strcmp(key, "y1"))
    snprintf(status->y1_str, sizeof(status->y1_str), "%.*s", (int)size, data);
  else if (0 == strcmp(key, "x2"))
    snprintf(status->x2_str, sizeof(status->x2_str), "%.*s", (int)size, data);
  else if (0 == strcmp(key, "y2"))
    snprintf(status->y2_str, sizeof(status->y2_str), "%.*s", (int)size, data);
  else if (0 == strcmp(key, "chance"))
    snprintf(status->chance_str, sizeof(status->chance_str), "%.*s", (int)size,
             data);
  else if (0 == strcmp(key, "birth_limit"))
    snprintf(status->birth_limit_str, sizeof(status->birth_limit_str), "%.*s",
             (int)size, data);
  else if (0 == strcmp(key, "death_limit"))
    snprintf(status->death_limit_str, sizeof(status->death_limit_str), "%.*s",
             (int)size, data);

  return MHD_YES;
}

static enum MHD_Result request_handler(
    void *cls, struct MHD_Connection *connection, const char *url,
    const char *method, const char *version, const char *upload_data,
    size_t *upload_data_size, void **con_cls) {
  // Unused parameters
  (void)cls;
  (void)version;

  if (NULL == *con_cls) {
    struct post_status *status = malloc(sizeof(struct post_status));
    if (!status) return MHD_NO;
    status->completed = 0;
    status->pp =
        MHD_create_post_processor(connection, 1024, post_iterator, status);
    *con_cls = (void *)status;
    return MHD_YES;
  }

  struct post_status *status = (struct post_status *)*con_cls;

  if (strcmp(url, "/") == 0) {
    const char *page =
        "<html><body>"
        "<h1>Labyrinth and Cave Generator</h1>"
        "<form method='post' action='/generate_labyrinth'>"
        "<h2>Generate Labyrinth</h2>"
        "<label>Rows: <input type='number' name='rows'></label><br>"
        "<label>Cols: <input type='number' name='cols'></label><br>"
        "<label>X1: <input type='number' name='x1'></label><br>"
        "<label>Y1: <input type='number' name='y1'></label><br>"
        "<label>X2: <input type='number' name='x2'></label><br>"
        "<label>Y2: <input type='number' name='y2'></label><br>"
        "<input type='submit' value='Generate'>"
        "</form>"
        "<form method='post' action='/generate_cave'>"
        "<h2>Generate Cave</h2>"
        "<label>Rows: <input type='number' name='rows'></label><br>"
        "<label>Cols: <input type='number' name='cols'></label><br>"
        "<label>Chance: <input type='number' step='0.01' "
        "name='chance'></label><br>"
        "<label>Birth Limit: <input type='number' "
        "name='birth_limit'></label><br>"
        "<label>Death Limit: <input type='number' "
        "name='death_limit'></label><br>"
        "<input type='submit' value='Generate'>"
        "</form>"
        "</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(
        strlen(page), (void *)page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
  } else if (strcmp(url, "/generate_labyrinth") == 0 &&
             strcmp(method, "POST") == 0) {
    if (*upload_data_size != 0) {
      MHD_post_process(status->pp, upload_data, *upload_data_size);
      *upload_data_size = 0;
      return MHD_YES;
    }

    if (status->completed) return MHD_YES;

    status->completed = 1;

    struct MHD_Response *response;
    int rows, cols, x1, y1, x2, y2;
    Labyrinth labyrinth;
    Point *path_points = NULL;
    int path_length = 0;

    rows = atoi(status->rows_str);
    cols = atoi(status->cols_str);
    x1 = atoi(status->x1_str);
    y1 = atoi(status->y1_str);
    x2 = atoi(status->x2_str);
    y2 = atoi(status->y2_str);

    generate_labyrinth(rows, cols, &labyrinth);
    char *html_response = malloc(1024 * 1024);  // 1MB buffer
    sprintf(html_response, "<html><body><h2>Generated Labyrinth</h2><pre>");
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        sprintf(html_response + strlen(html_response), "%c",
                labyrinth.v_walls[r][c] ? '|' : ' ');
      }
      sprintf(html_response + strlen(html_response), "\n");
    }
    sprintf(html_response + strlen(html_response), "</pre>");

    if (find_path(&labyrinth, x1, y1, x2, y2, &path_points, &path_length)) {
      sprintf(html_response + strlen(html_response),
              "<h2>Path Found</h2><pre>");
      for (int i = 0; i < path_length; ++i) {
        sprintf(html_response + strlen(html_response), "(%d, %d) ",
                path_points[i].x, path_points[i].y);
      }
      sprintf(html_response + strlen(html_response), "</pre>");
      free(path_points);
    } else {
      sprintf(html_response + strlen(html_response), "<h2>No Path Found</h2>");
    }

    sprintf(html_response + strlen(html_response), "</body></html>");

    response = MHD_create_response_from_buffer(
        strlen(html_response), (void *)html_response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    free_labyrinth(&labyrinth);
    return ret;
  } else if (strcmp(url, "/generate_cave") == 0 &&
             strcmp(method, "POST") == 0) {
    if (*upload_data_size != 0) {
      MHD_post_process(status->pp, upload_data, *upload_data_size);
      *upload_data_size = 0;
      return MHD_YES;
    }

    if (status->completed) return MHD_YES;

    status->completed = 1;

    struct MHD_Response *response;
    int rows, cols, birth_limit, death_limit;
    double chance;
    Cave *cave;

    rows = atoi(status->rows_str);
    cols = atoi(status->cols_str);
    chance = atof(status->chance_str);
    birth_limit = atoi(status->birth_limit_str);
    death_limit = atoi(status->death_limit_str);

    cave = create_cave(rows, cols, chance);
    generate_cave(cave, birth_limit, death_limit);

    char *html_response = malloc(1024 * 1024);  // 1MB buffer
    sprintf(html_response, "<html><body><h2>Generated Cave</h2><pre>");
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < cols; c++) {
        sprintf(html_response + strlen(html_response), "%c",
                cave->cells[r][c] ? '#' : '.');
      }
      sprintf(html_response + strlen(html_response), "\n");
    }
    sprintf(html_response + strlen(html_response), "</pre></body></html>");

    response = MHD_create_response_from_buffer(
        strlen(html_response), (void *)html_response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    free_cave(cave);
    return ret;
  } else {
    const char *error_page = "Page not found";
    struct MHD_Response *response = MHD_create_response_from_buffer(
        strlen(error_page), (void *)error_page, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
    return ret;
  }
}

static void free_request_handler(void *cls, struct MHD_Connection *connection,
                                 void **con_cls,
                                 enum MHD_RequestTerminationCode toe) {
  // Unused parameters
  (void)cls;
  (void)connection;
  (void)toe;

  struct post_status *status = *con_cls;
  if (status != NULL) {
    MHD_destroy_post_processor(status->pp);
    free(status);
  }
}

int init_server() {
  struct MHD_Daemon *daemon;

  daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                            &request_handler, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                            free_request_handler, NULL, MHD_OPTION_END);
  if (NULL == daemon) {
    perror("MHD_start_daemon");
    fprintf(stderr,
            "Failed to start the server on port %d. Possible reasons:\n", PORT);
    fprintf(stderr, "- The port might be already in use.\n");
    fprintf(
        stderr,
        "- You might not have the necessary permissions to open the port.\n");
    return 1;
  }

  printf("Server is running on port %d. Press Enter to stop.\n", PORT);
  (void)getchar();

  MHD_stop_daemon(daemon);
  return 0;
}
