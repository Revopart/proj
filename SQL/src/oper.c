#include "oper.h"

void *read_record_from_file(FILE *pfile, int index, size_t size) {
    int offset = index * size;
    fseek(pfile, offset, SEEK_SET);
    void *record = (void *)malloc(size);
    fread(record, size, 1, pfile);
    rewind(pfile);
    return record;
}

void write_record_in_file(FILE *pfile, size_t size, int index, void *data) {
    int offset = index * size;
    fseek(pfile, offset, SEEK_SET);
    fwrite(data, size, 1, pfile);
    fflush(pfile);
    rewind(pfile);
}

void swap_records_in_file(FILE *pfile, int record_index1, int record_index2, size_t size) {
    void *record1 = read_record_from_file(pfile, record_index1, size);
    void *record2 = read_record_from_file(pfile, record_index1, size);
    write_record_in_file(pfile, size, record_index2, record1);
    write_record_in_file(pfile, size, record_index1, record2);
}

int get_file_size_in_bytes(FILE *pfile) {
    int size = 0;
    fseek(pfile, 0, SEEK_END);
    size = ftell(pfile);
    rewind(pfile);
    return size;
}

int get_records_count_in_file(FILE *pfile, size_t size) { return get_file_size_in_bytes(pfile) / size; }
