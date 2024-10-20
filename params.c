int main(int argc, char** v) {
    for (int i = 1; i < argc; i++)
        printf("Arg %d: %s\n", i, v[i]);
}