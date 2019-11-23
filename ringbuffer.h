struct buffer_type{
	unsigned char *head; // store address of head_value
	unsigned char *tail;
	unsigned char *beginning;
	unsigned char *end;
};

typedef enum error_type {
	OK,
	BUFFER_OVER_FLOW,
	EMPTY_BUFFER,
	POINTER_ERROR,
	BUFFER_FULL
}error_type;

#define SIZE 256

void init_buffer(struct buffer_type *b, unsigned char *buffer, int buffer_size);
void empty_buffer(struct buffer_type *b);
int get_buffer_state(struct buffer_type *b, enum error_type *err);
int  add_char_to_buffer(struct buffer_type *b,  unsigned char c, enum  error_type *err);
char get_char_from_buffer(struct buffer_type *b, enum error_type *err);
int print_buffer(struct buffer_type *b, enum error_type *err);