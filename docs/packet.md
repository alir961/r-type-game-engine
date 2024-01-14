# UDP Packet Representation Documentation
## Enumerations

**'MessageType'**

An enumeration representing different types of messages within the UDP packet.

- UNKNOWN: Default or placeholder value (0) for an unidentified message type.
- CONNECT: Message indicating a connection.
- CONNECT_CALLBACK: Callback related to a connection.
- DISCONNECT: Message indicating a disconnection.
- CONFIRMATION: Confirmation message.
- PLAYER_NAME: Message containing player name information. 
- PLAYER_COLOR: Message containing player color information.
- MOVE_LEFT, MOVE_RIGHT, MOVE_DOWN, MOVE_UP: Messages for player movement in different directions.
- SHOOT: Message indicating a shooting action.
- DEATH: Message indicating player death.
- MOVE_PLAYER_BULLET: Message related to moving a player's bullet.

## Structures
**'Message'**

A structure encapsulating a UDP packet message.

- type: An instance of MessageType representing the type of the message. Initialized with MessageType::UNKNOWN by default.
- data: An array of characters (std::array<char, DATA_SIZE>) to hold the message data.

Note: Ensure to replace DATA_SIZE with the actual size of the data array in your implementation.
