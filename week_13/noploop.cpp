// Пример за това какво представлява noploop отвътре
int main(int argc, char **argv) {
    long long iterations = 1000000000; // Примерно 1 милиард
    for (long long i = 0; i < iterations; i++) {
        asm volatile("nop"); // Директна NOP инструкция към процесора
    }
    return 0;
}