#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(void) {

	//socket variable
	int sock;

	//socket addrress and server address variables
	struct sockaddr_in server_addr;

	//server messages and clients messages variables
	int input = 0;
	int input02 = 0;
	int input03 = 0;
	int check = 1;
	int client_mess01, client_mess02, client_mess03;
	int server_mess01 = 0;


	//length of address
	int server_struct_length = sizeof(server_addr);


	// Create socket:
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//check if socket created
	if (sock < 0) {
		printf("Error while creating socket\n");
		return -1;
	}

	printf("Socket created successfully\n");


	server_addr.sin_family = AF_INET;
	//set up port
	server_addr.sin_port = htons(2753);
	//set up IP
	server_addr.sin_addr.s_addr = INADDR_ANY;


	printf("Choose One of the following numbers:\n 1.Addition\n 2.Subtraction\n 3.Multiplication\n 4.Division \n 5. Average\n ");
	scanf("%d", &input03);

	// Get input from the user:
	printf("enter First number:");
	scanf("%d", &input);

	//change byte order
	client_mess01 = htonl(input);

	// Send the message to server:
	if (sendto(sock, (char*)&client_mess01, sizeof(int), 0,
		(struct sockaddr*)&server_addr, server_struct_length) < 0) {
		//error checking
		printf("Unable to send message\n");
		return -1;
	}

	// Get input from the user:
	printf("enter Second number:");
	scanf("%d", &input02);

	//change byte order
	client_mess02 = htonl(input02);

	// Send the message to server:
	if (sendto(sock, (char*)&client_mess02, sizeof(int), 0,
		(struct sockaddr*)&server_addr, server_struct_length) < 0) {
		//error checking
		printf("Unable to send message\n");
		return -1;
	}

	//change byte order
	client_mess03 = htonl(input03);

	//send to server
	if (sendto(sock, (char*)&client_mess03, sizeof(int), 0,
		(struct sockaddr*)&server_addr, server_struct_length) < 0) {
		//error checking
		printf("Unable to send message\n");
		return -1;
	}

	// Receive the server's response:
	if (recvfrom(sock, (char*)&server_mess01, sizeof(int), 0,
		(struct sockaddr*)&server_addr, &server_struct_length) < 0) {
		//error checking
		printf("Error while receiving server's msg\n");
		return -1;
	}
	//change byte order
	int correct_reply = ntohl(server_mess01);

	//server message
	printf("Server's response: %d\n", correct_reply);

	// Close the socket:
	close(sock);

	return 0;
}
