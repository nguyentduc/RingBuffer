#include <gtest/gtest.h>
#include "ringbuffer.h"


TEST(InitBuffer,MyTest1)
{
	struct buffer_type test; 
	int buffer_size = 10;
	unsigned char buffer[SIZE];
	
	init_buffer( &test, buffer, 10); // sua size 
	
    EXPECT_EQ(test.head, buffer);
	EXPECT_EQ(test.tail, buffer);
	EXPECT_EQ(test.beginning, buffer);
	EXPECT_EQ(test.end, buffer + buffer_size -1);
}
///////////////////////////////////////////////////////////////
TEST(EmptyBuffer,MyTest1)
{
	struct buffer_type test; 
	int buffer_size = 10;
	unsigned char buffer[SIZE];
	
	//init_buffer( &test, buffer, size);
	test.beginning=buffer;
	test.head = buffer;
	test.tail = buffer;
	test.end = buffer + buffer_size - 1;
	
	test.head = test.head + 2;
    empty_buffer(&test);
	
    
	EXPECT_EQ(test.tail, test.head);
	EXPECT_EQ(test.head, buffer + 2);
	EXPECT_EQ(test.tail, buffer + 2);
	EXPECT_EQ(test.beginning, buffer);
	EXPECT_EQ(test.end, buffer + (buffer_size -1) * sizeof(unsigned char));
}
/*
TEST(EmptyBuffer,MyTest2)
{
	struct buffer_type test; 
	int size = 10;
	unsigned char buffer[size];
	
	test.beginning=buffer;
	test.end=buffer+(size-1)*sizeof(unsigned char);
	test.head = buffer + 4*sizeof(unsigned char);
	test.tail = buffer + 2*sizeof(unsigned char);
	
	empty_buffer(&test);
	
    EXPECT_EQ(test.head, buffer + 4*sizeof(unsigned char));
	EXPECT_EQ(test.tail, buffer + 4*sizeof(unsigned char));
	EXPECT_EQ(test.beginning, buffer);
	EXPECT_EQ(test.end, buffer + (size -1) * sizeof(unsigned char));
	
}
*/
/////////////////////////////////////////////////////////////
TEST(GetBuffer,MyTest1)
{
	
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning=buffer;
	test.head = buffer;
	test.tail = buffer;
	test.end = buffer + buffer_size - 1;
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len,0);
	EXPECT_EQ(err,EMPTY_BUFFER);
	EXPECT_EQ(test.head, buffer);
	EXPECT_EQ(test.tail, buffer);	
}

TEST(GetBuffer,MyTest2)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning=buffer;
	test.end = buffer+(buffer_size-1)*sizeof(unsigned char);
	test.head = buffer + 5*sizeof(unsigned char);
	test.tail = buffer + 3*sizeof(unsigned char);
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len,2);
	EXPECT_EQ(err,OK);
	//EXPECT_EQ(test.head, buffer);
	//EXPECT_EQ(test.tail, buffer);	
}

TEST(GetBuffer,MyTest4)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning = buffer;
	test.end = buffer + (buffer_size-1)*sizeof(unsigned char);
	test.head = buffer + (buffer_size-1)*sizeof(unsigned char);
	test.tail = buffer;
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len,9);
	EXPECT_EQ(err,BUFFER_FULL);
	//EXPECT_EQ(test.head, buffer);
	//EXPECT_EQ(test.tail, buffer);	
}
TEST(GetBuffer,MyTest3)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	error_type err;
	
	test.beginning=buffer;
	test.end=buffer+(buffer_size-1)*sizeof(unsigned char);
	test.head = buffer + 3*sizeof(unsigned char);
	test.tail = buffer + 4*sizeof(unsigned char);
	int buff_len = get_buffer_state(&test, &err);
	
	
    EXPECT_EQ(buff_len,9);
	EXPECT_EQ(err,BUFFER_FULL);
	//EXPECT_EQ(test.head, buffer);
	//EXPECT_EQ(test.tail, buffer);	
}


///////////////////////////////////////////////////////////////
TEST(AddCharToBuffer,addToEmpty)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning=buffer;
	test.end = buffer+(buffer_size-1);
	test.head=buffer;
	test.tail=buffer;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len,1);
	EXPECT_EQ(err,OK);
}

TEST(AddCharToBuffer,addToFull)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning=buffer;
	test.end=buffer+(buffer_size-1);
	test.head=buffer+(buffer_size-1);
	test.tail=buffer;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len,9);
	EXPECT_EQ(err,BUFFER_FULL);
}

TEST(AddCharToBuffer,addToPointerError)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning=buffer;
	test.end=buffer+(buffer_size-1);
	test.head=buffer+(buffer_size);
	test.tail=buffer;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len,-1);
	EXPECT_EQ(err,POINTER_ERROR);
}

TEST(AddCharToBuffer,addToOK1)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning=buffer;
	test.end = buffer+(buffer_size-1);
	test.head = buffer+2;
	test.tail = buffer;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len,3);
	EXPECT_EQ(err,OK);
}

TEST(AddCharToBuffer,addToOKThenFull)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char add = 'c';
	error_type err;
	int len;
	
	test.beginning=buffer;
	test.end = buffer+(buffer_size-1);
	test.head = buffer+2;
	test.tail = buffer + 4;
	len = add_char_to_buffer(&test,add,&err);
	
    EXPECT_EQ(len,9);
	EXPECT_EQ(err,BUFFER_FULL);
}



//////////////////////////////////////////////////////////////

/*TEST(GetCharFromBuffer,getFromEmpty)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	int len;
	
	test.beginning=buffer;
	test.end = buffer+(buffer_size-1);
	test.head=buffer;
	test.tail=buffer;
	read = get_char_from_buffer(&test, &err);
	
    EXPECT_EQ(read,'-1');
	EXPECT_EQ(err,EMPTY_BUFFER);
	//EXPECT_EQ(test.head, buffer);
	//EXPECT_EQ(test.tail, buffer);	
}*/
TEST(GetCharFromBuffer,getFromOK)
{
	int buffer_size = 10;
	struct buffer_type test; 
	unsigned char buffer[SIZE];
	unsigned char read;
	error_type err;
	int i;
	
	test.beginning=buffer;
	test.end = buffer+(buffer_size-1);
	test.head=buffer;
	for ( i=0; i<4; i++){
		*(test.head) = 'a';
		test.head++;
	}
	test.tail=buffer+2;
	read = get_char_from_buffer(&test, &err);
	
    EXPECT_EQ(read,'a');
	EXPECT_EQ(err,OK);
	EXPECT_EQ(test.head, buffer+4);
	//EXPECT_EQ(test.tail, buffer);	
}
/*
TEST(GetCharFromBuffer,MyTest2)
{
	struct buffer_type test; 
	int size = 10;
	unsigned char buffer[size];
	unsigned char get;
	int buff_len,i;
	error_type err;
	
	test.beginning=buffer;
	test.end=buffer+(size-1)*sizeof(unsigned char);
	for(i=1; i<3; i++){
		buff_len = add_char_to_buffer(&test, '1', &err);
	}
	get_char_from_buffer(&test, &err);
	
    EXPECT_EQ(get,-1);
	EXPECT_EQ(err,2);
	EXPECT_EQ(test.head, buffer);
	EXPECT_EQ(test.tail, buffer);	
}
*/

