#define MAX_ALLOC_SIZE (size_t) pow(2.0, 27.0)
#define FALSE 0
#define TRUE 1

#define FUNCTIONIZE(a,b) a(b)
#define STRINGIZE(a) #a
#define INT2STRING(i) FUNCTIONIZE(STRINGIZE,i)
#define FILE_POS __FILE__ ":" INT2STRING(__LINE__)
#define malloc(s) *slug_malloc((s), FILE_POS)
#define free(s) slug_free((s), FILE_POS)
#define memstats() slug_memstats()
