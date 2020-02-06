#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char*argv[]) {
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char buffer[100000];
	char identification[5] = "test";

	//set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); //Clear out the address struct
	printf("arg 1 is : %s\n", argv[1]);
	portNumber = atoi(argv[1]); //Get the port number, convert to an integer from a string
	printf("1\n");
	serverAddress.sin_family = AF_INET; //Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); //Convert port number to network type
	serverHostInfo = gethostbyname("localhost");	//convert the machine name into a special form of address

	if (serverHostInfo == NULL) {
		fprintf(stderr, "CLIENT: ERROR, no such host\n");
	};

	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length);

	//Set up the socket
	socketFD = socket(AF_INET, SOCK_STREAM, 0); //Create a TCP socket
	if (socketFD < 0) fprintf(stderr, "CLIENT: ERROR CONNECTING\n");

	//Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
		fprintf(stderr, "CLIENT: ERROR CONNECTING\n");
	};

	//Send identification to server
	charsWritten = send(socketFD, identification, strlen(identification), 0);
	if (charsWritten < 0) {
		fprintf(stderr, "CLIENT: ERROR writing to socket\n");
	};
	if (charsWritten < strlen(identification)) {
		fprintf(stderr, "CLIENT: WARNING: Not all data written to socket!\n");
	};

	
	return 0;
}
