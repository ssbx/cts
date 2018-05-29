#include <stdio.h>
#include <tensorflow/c/c_api.h>

void rungraph(const char *graph_file)
{
}

int main(int argc, char **argv) 
{
    printf("Hello from TensorFlow C library version %s\n", TF_Version());

    rungraph("graphfile");

    return 0;
}
