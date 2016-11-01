##Python Server

Start: ```python ./server.py <PORT>```

Execution & Control: 
- Input Server Name at Prompt for Handle
- Server will listen for client connection
- Respond to messages by typing and hit ENTER to send
- Terminate Connection by typing \quit and ENTER
- When connection is closed, server resumes listening for connections
- Shutdown server with CTRL-C

**Tested on OSU flip servers**


##C Client

build: ```make all```
run: ```./client <IP of Host Server> <PORT of Host Server>```
clean: ```make clean```

Execution & Control: 
- Input Client Name at Prompt for Handle
- Client will try to connect to server and sends handle as initial message
- Send messages by typing message and ENTER to send
- Terminate Connection by typing \quit and ENTER
- When connection is closed with '\quit' from either side, client shuts down

**Tested on OSU flip servers**
