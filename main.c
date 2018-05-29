#include <stdio.h>
#include <stdlib.h>
#include <tensorflow/c/c_api.h>

static char *graph_file_name = "graph.pb";

TF_Buffer
load_graph_file(const char *filename)
{
    FILE *fp;
    TF_Buffer buff;
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

    buff.data = data;
    buff.length = s;
    return buff;
}

void
tf_free_tensor(void *data, size_t len, void* arg) {
    free(data);
}

/*
https://medium.com/jim-fleming/loading-a-tensorflow-graph-with-the-c-api-4caaff88463f
https://medium.com/jim-fleming/loading-tensorflow-graphs-via-host-languages-be10fd81876f

Implementation example of the C API for swift:
https://github.com/PerfectlySoft/Perfect-TensorFlow

Load graph in C++
https://github.com/tensorflow/tensorflow/blob/master/tensorflow/examples/label_image/main.cc
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

    TF_Buffer graph_def = load_graph_file(graph_file_name);

    TF_ImportGraphDefOptions *graph_opts = TF_NewImportGraphDefOptions();
    TF_GraphImportGraphDef(graph, &graph_def, graph_opts, status);
    if (TF_GetCode(status) != TF_OK) {
        fprintf(stderr, "Error: %s\n", TF_Message(status));
        exit(EXIT_FAILURE);
    }

    int64_t *aDims = malloc(sizeof(int64_t) * 200);
    int      aData[3];
    /*
    TF_Tensor *t1 = TF_NewTensor(TF_FLOAT,
            aDims, 200, 
            aData, 3, tf_free_tensor, NULL);
            */

    /*
    TF_Tensor *t2 = TF_NewTensor(TF_FLOAT,
            aDims, 0, 
            aData, 3, free, 0);
            */

    //TF_SessionRun();


    TF_DeleteImportGraphDefOptions(graph_opts);
    TF_DeleteSession(session, status);
    TF_DeleteStatus(status);
    TF_DeleteSessionOptions(opts);
    TF_DeleteGraph(graph);

    exit(EXIT_SUCCESS);
}
