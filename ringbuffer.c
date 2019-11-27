#include <stdio.h>
#include "ringbuffer.h"


// Initilazes the buffer 
void init_buffer(struct buffer_type *b, unsigned char *buffer,  int buffer_size){
	
	if(buffer_size > SIZE)
		printf("Buffer size needs to be smaller than 256");
	else{
		b->beginning = buffer;
		b->end= buffer + buffer_size - 1;
		b->head = buffer;
		b->tail = buffer;
	}
}

void empty_buffer(struct buffer_type *b){
	b->tail = b->head;
}

int get_buffer_state(struct buffer_type *b, error_type *err){
	int len;
	
	//Pointer ERROR
	if ( b->head > b->end || b->head < b->beginning || b->tail > b->end || b->tail < b->beginning){
		len = -1;
		*err = POINTER_ERROR;
	}
	else if( b->head > b->tail){
		len = b->head - b->tail;
		if(b->head == b->end && b->tail == b->beginning)
			*err = BUFFER_FULL;
		else
			*err = OK;
	}
	else if (b->head < b->tail){
		len = (b->end - b->beginning + 1) - (b->tail - b->head);
		if (b->head == b->tail -1 )
			*err = BUFFER_FULL;
		else
			*err = OK;
		}
	else{
		len = 0;
		*err = EMPTY_BUFFER;
	}
	return len;
}


int add_char_to_buffer(struct buffer_type *b,  unsigned char c, error_type *err){
	int len;
	len = get_buffer_state(b, err);

	switch (*err){
		case BUFFER_FULL :
		case POINTER_ERROR :
			break;
		case EMPTY_BUFFER :
			*(b->head) = c;
			b->head++;
			break;
		case OK :
			*(b->head) = c;
			( b->head == b->end) ? (b->head = b->beginning) : (b->head++);
			break;
	}
	
	len = get_buffer_state(b, err);
	return len;
}

char get_char_from_buffer(struct buffer_type *b, error_type *err){
	int len;
	len = get_buffer_state(b, err);
	unsigned char *read;

	if (*err == POINTER_ERROR || *err == EMPTY_BUFFER){
		return -1;
	}

	read = b->tail;
	(b->tail == b->end) ? b->tail = b->beginning : b->tail++;
	
	len = get_buffer_state(b, err);
	return *read;
}

int print_buffer(struct buffer_type *b, error_type *err){
	int len;
	len = get_buffer_state(b, err);
	int i;

	switch (*err){
		case POINTER_ERROR :
		case EMPTY_BUFFER :
			len = -1;
			break;
		case OK :
		case BUFFER_FULL :
			for(i=0; i<len; i++){
				printf("%c ",*(b->tail+i));
			}
			printf("\n");
			break;
	}
	return len;
}

  
  