#include <gtest/gtest.h>
#include "ringbuffer.h"

/**************************************************************
 * Test cases for init_buffer()
 * ***********************************************************/		
TEST(initBuffer,init)
{
	struct buffer_type test; 
	int buffer_size = 10;
	unsigned char buffer[SIZE];
	
	init_buffer( &test, buffer, 10); 
	
    EXPECT_EQ(test.head, buffer);
	EXPECT_EQ(test.tail, buffer);
	EXPECT_EQ(test.beginning, buffer);
	EXPECT_EQ(test.end, buffer + buffer_size -1);
}

/**************************************************************
 * Test cases for empty_buffer()
 * ***********************************************************/														
TEST(emptyBuffer,empty)
{
	struct buffer_type test; 
	int buffer_size = 10;
	unsigned char buffer[SIZE];
	
	//Manually init buffer
	test.beginning = buffer;
	test.head = buffer;
	test.tail = buffer;
	test.end = buffer + buffer_size - 1;
	
	test.head = test.head + 2;
    empty_buffer(&test);
	

	EXPECT_EQ(test.tail, test.head);
	EXPECT_EQ(test.head, buffer + 2);
	EXPECT_EQ(test.tail, buffer + 2);
	EXPECT_EQ(test.beginning, buffer);
	EXPECT_EQ(test.end, buffer + buffer_size -1);
}

/**************************************************************
 * Test cases for get_buffer_state()
 * ***********************************************************/		
TEST(getBufferState,emptyBuffer1)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning = buffer;
	test.head = buffer;
	test.tail = buffer;
	test.end = buffer + buffer_size - 1;
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len, 0);
	EXPECT_EQ(err, EMPTY_BUFFER);
	EXPECT_EQ(test.head, buffer);
	EXPECT_EQ(test.tail, buffer);	
}

TEST(getBufferState,emptyBuffer2)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning = buffer;
	test.head = buffer + 5;
	test.tail = buffer + 5;
	test.end = buffer + buffer_size - 1;
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len, 0);
	EXPECT_EQ(err, EMPTY_BUFFER);
	EXPECT_EQ(test.head, buffer + 5);
	EXPECT_EQ(test.tail, buffer + 5);	
}

TEST(getBufferState,oKbuffer)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + 5;
	test.tail = buffer + 3;
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len,2);
	EXPECT_EQ(err,OK);
	EXPECT_EQ(test.head, buffer + 5);
	EXPECT_EQ(test.tail, buffer + 3);	
}

TEST(getBufferState,bufferFull)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + buffer_size - 1;
	test.tail = buffer;
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len,9);
	EXPECT_EQ(err,BUFFER_FULL);
	EXPECT_EQ(test.head, buffer + 9);
	EXPECT_EQ(test.tail, buffer);	
}
TEST(getBufferState,bufferFull2)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + 3;
	test.tail = buffer + 4;
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len,9);
	EXPECT_EQ(err,BUFFER_FULL);
	EXPECT_EQ(test.head, buffer + 3);
	EXPECT_EQ(test.tail, buffer + 4);	
}

TEST(getBufferState,Error1)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer - 1;
	test.tail = buffer + 4;

	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len, -1);
	EXPECT_EQ(err, POINTER_ERROR);
}

TEST(getBufferState,Error2)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer;
	test.tail = buffer + 10;

	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len, -1);
	EXPECT_EQ(err, POINTER_ERROR);
}

/**************************************************************
 * Test cases for add_char_to_buffer()
 * ***********************************************************/		
TEST(addCharToBuffer,addToEmpty)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer;
	test.tail = buffer;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len, 1);
	EXPECT_EQ(err, OK);
	EXPECT_EQ(test.head, buffer + 1);
}

TEST(addCharToBuffer,addToFull)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + buffer_size - 1;
	test.tail = buffer;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len,9);
	EXPECT_EQ(err,BUFFER_FULL);
	EXPECT_EQ(test.head, buffer + 9);
	EXPECT_EQ(test.tail, buffer);
}

TEST(addCharToBuffer,addToPointerError)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + buffer_size;
	test.tail = buffer;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len, -1);
	EXPECT_EQ(err, POINTER_ERROR);
}

TEST(addCharToBuffer,addToOK1)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + 2;
	test.tail = buffer;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len,3);
	EXPECT_EQ(err,OK);
	EXPECT_EQ(test.head, buffer + 3);
	EXPECT_EQ(test.tail, buffer);
}

TEST(addCharToBuffer,addToOKThenFull)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + 2;
	test.tail = buffer + 4;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len,9);
	EXPECT_EQ(err,BUFFER_FULL);
	EXPECT_EQ(test.head, buffer + 3);
	EXPECT_EQ(test.tail, buffer + 4);
}

/**************************************************************
 * Test cases for get_char_from_buffer()
 * ***********************************************************/		
TEST(getCharFromBuffer,getFromEmpty)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer;
	test.tail = buffer;
	read = get_char_from_buffer(&test, &err);
	
    EXPECT_EQ(read,(unsigned char)-1);
	EXPECT_EQ(err,EMPTY_BUFFER);
	EXPECT_EQ(test.head, buffer);
	EXPECT_EQ(test.tail, buffer);	
}

TEST(getCharFromBuffer,getFromOK)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	int i;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head=buffer;
	for ( i=0; i<4; i++){
		*(test.head) = 'a';
		test.head++;
	}
	test.tail = buffer + 2;
	read = get_char_from_buffer(&test, &err);
	
    EXPECT_EQ(read,'a');
	EXPECT_EQ(err, OK);
	EXPECT_EQ(test.head, buffer + 4);
	EXPECT_EQ(test.tail, buffer + 3);	
}

TEST(getCharFromBuffer,getFromFull)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	int i;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer;
	for ( i=0; i<buffer_size -1; i++){
		*(test.head) = 'a';
		test.head++;
	}

	test.tail = buffer;
	read = get_char_from_buffer(&test, &err);
	
    EXPECT_EQ(read,'a');
	EXPECT_EQ(err, OK);
	EXPECT_EQ(test.head, buffer + 9);
	EXPECT_EQ(test.tail, buffer + 1);	
}

TEST(getCharFromBuffer,getFromError)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + buffer_size;
	test.tail = buffer;

	read = get_char_from_buffer(&test, &err);
	
    EXPECT_EQ(read,(unsigned char)-1);
	EXPECT_EQ(err, POINTER_ERROR);
} 

/**************************************************************
 * Test cases for print_buffer()
 * ***********************************************************/		
TEST(printBuffer,printFromEmpty)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	int len;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer;
	test.tail = buffer;
	len = print_buffer(&test, &err);
	
    EXPECT_EQ(len, -1);
	EXPECT_EQ(err,EMPTY_BUFFER);
	EXPECT_EQ(test.head, buffer);
	EXPECT_EQ(test.tail, buffer);	
}

TEST(printBuffer,printFromOK)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	int i;
	int len;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head=buffer;
	for ( i=0; i<4; i++){
		*(test.head) = 'a';
		test.head++;
	}
	test.tail = buffer;
	len = print_buffer(&test, &err);

    EXPECT_EQ(len, 4);
	EXPECT_EQ(err, OK);
	EXPECT_EQ(test.head, buffer + 4);
	EXPECT_EQ(test.tail, buffer);	
}

TEST(printBuffer,printFromFull)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	int i;
	int len;
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer;
	for ( i=0; i<buffer_size -1; i++){
		*(test.head) = 'a';
		test.head++;
	}

	test.tail = buffer;
	len = print_buffer(&test, &err);
	
    EXPECT_EQ(len, 9);
	EXPECT_EQ(err, BUFFER_FULL);
	EXPECT_EQ(test.head, buffer + 9);
	EXPECT_EQ(test.tail, buffer);	
}

TEST(printBuffer,printFromError)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	int len;
	
	
	test.beginning = buffer;
	test.end = buffer + buffer_size - 1;
	test.head = buffer + buffer_size;
	test.tail = buffer;

	len = print_buffer(&test, &err);
	
    EXPECT_EQ(len, -1);
	EXPECT_EQ(err, POINTER_ERROR);
} 