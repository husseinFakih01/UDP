#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
	//socket variable
	int sock;

	//socket address, and server address variables
	struct sockaddr_in server_addr, client_addr;

	//server message and client message variables
	int server_mess01;
	int client_mess01;
	int client_mess02;
	int client_mess03;
	int reply = 0;

	//length of address
	int client_struct_length = sizeof(client_addr);

	// Create UDP socket:
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	//error checking when creating socket
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

	// Bind to the set port and IP:
	if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		//error checking
		printf("Couldn't bind to the port\n");
		return -1;
	}
	printf("Binded Successfully \n");

	printf("Waiting for incoming messages...\n\n");

	// Receive client's message:
	if (recvfrom(sock, (char*)&client_mess01, sizeof(int), 0,
		(struct sockaddr*)&client_addr, &client_struct_length) < 0) {
		//error checking
		printf("Couldn't receive\n");
		return -1;
	}
	//change byte order
	int correct_int = ntohl(client_mess01);

	//print client's message
	printf(" First Msg from client: %d\n", correct_int);

	//second message from client
	if (recvfrom(sock, (char*)&client_mess02, sizeof(int), 0,
		(struct sockaddr*)&client_addr, &client_struct_length) < 0) {
		//error checking
		printf("Couldn't receive\n");
		return -1;
	}
	//change byte order
	int correct_int02 = ntohl(client_mess02);
	//print client's message
	printf(" Second Msg from client: %d\n", correct_int02);

	//Third message from client
	if (recvfrom(sock, (char*)&client_mess03, sizeof(int), 0,
		(struct sockaddr*)&client_addr, &client_struct_length) < 0) {
		//error checking
		printf("Couldn't receive\n");
		return -1;
	}

	int correct_int03 = ntohl(client_mess03);

	switch (correct_int03) {

	case 1:
		reply = correct_int + correct_int02;
		break;

	case 2:
		reply = correct_int - correct_int02;
		break;

	case 3:
		reply = correct_int * correct_int02;
		break;

	case 4:
		if (correct_int == 0 || correct_int02 == 0) {
			printf("Can't perform devision");
			break;
		}
		reply = correct_int / correct_int02;
		break;

	case 5:
		reply = (correct_int + correct_int02) / 2;
		break;

	}


	//change byte order
	int correct_byte = htonl(reply);

	//send to server
	if (sendto(sock, (char*)&correct_byte, sizeof(int), 0,
		(struct sockaddr*)&client_addr, client_struct_length) < 0) {
		//error checking
		printf("Can't send\n");
		return -1;
	}

	// Close the socket:
	close(sock);

	return 0;
}