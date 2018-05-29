#include <stdio.h>
#include <stdlib.h>
#include <tensorflow/c/c_api.h>

static char *graph_file_name = "graph.pb";

const char*
load_graph_file(const char *filename, size_t *length)
{
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL) {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    fseek(fp, 0, SEEK_END);
    long s = ftell(fp);
    char *data = malloc(s);

    rewind(fp);
    fread(data, 1, s, fp);
    fclose(fp);

    *length = s;
    return data;
}


/*
https://medium.com/jim-fleming/loading-a-tensorflow-graph-with-the-c-api-4caaff88463f
https://medium.com/jim-fleming/loading-tensorflow-graphs-via-host-languages-be10fd81876f

Implementation example of the C API for swift:
https://github.com/PerfectlySoft/Perfect-TensorFlow
 */
int main(int argc, char **argv) 
{
    printf("Hello from TensorFlow C library version %s\n", TF_Version());

    TF_Graph *graph         = TF_NewGraph();
    TF_SessionOptions *opts = TF_NewSessionOptions();
    TF_Status *status       = TF_NewStatus();
    TF_Session *session     = TF_NewSession(graph, opts, status);

    if (TF_GetCode(status) != TF_OK) {
        fprintf(stderr, "Error: %s\n", TF_Message(status));
        exit(EXIT_FAILURE);
    }

    TF_Buffer graph_def;
    graph_def.data = load_graph_file(graph_file_name, &graph_def.length);

    TF_ImportGraphDefOptions *graph_opts = TF_NewImportGraphDefOptions();
    TF_GraphImportGraphDef(graph, &graph_def, graph_opts, status);
    if (TF_GetCode(status) != TF_OK) {
        fprintf(stderr, "Error: %s\n", TF_Message(status));
        exit(EXIT_FAILURE);
    }

    /* TODO */

    TF_DeleteImportGraphDefOptions(graph_opts);
    TF_DeleteSession(session, status);
    TF_DeleteStatus(status);
    TF_DeleteSessionOptions(opts);
    TF_DeleteGraph(graph);

    exit(EXIT_SUCCESS);
}
