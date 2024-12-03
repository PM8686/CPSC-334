# ESPNOW

- edited code so that we deny people with the wrong mac address in `register_new_peer`

1. How are peers/primary being created/discovered (function name and/or line number): explain
- `register_new_peer`
Discovery and Registration: Peers are discovered through broadcasting and registering callbacks to listen for incoming data packets. The function register_new_peer (line 303) is called when a new peer is discovered. This function:
Checks if the incoming priority conflicts with the device’s own.
Registers the peer with ESP_NOW_Network_Peer to manage communication.
Adds the new peer to the peers vector.
Primary Determination: After all peers are registered, check_highest_priority (line 258) determines the primary device by comparing the priority of each peer. This logic ensures the device with the highest priority is designated as the primary.

2. How are MAC addresses being communicated? (function name and/or line number)
MAC addresses are sent and managed via ESP-NOW messages, utilizing the register_new_peer callback (line 303), which receives the MAC address of incoming peers (info->src_addr). MAC addresses are included in each esp_now_data_t struct sent in messages, allowing devices to recognize each peer and primary through their MAC addresses.

3. How many total peers are possible? (EASY)
    20 peers

4. What affect does “channel” have?
    Can't find each other if we are not on the same channel.

5. How does each peer send messages to: (function name and/or line number) 
    1. other peers
    2. the primary esp32

6. How would you edit this code to send some data interactively (via button press, for example)?
    On button press, I would send a message to the primary so that the primary could send it out or if I am the primary I would just send out the message.

7. What here is unnecessary for our purposes?
    we could get away with maybe not having a priority and creating one sender and one reciever, if that makes sense for our purposes. 
