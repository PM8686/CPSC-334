import socket

# Set up the UDP server
udp_ip = "192.168.56.1"  # This should be the IP address of the computer running this script
udp_port = 1234  # Port number should match the one used on the ESP32

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((udp_ip, udp_port))

print(f"Listening for UDP messages on {udp_ip}:{udp_port}...")

while True:
    # Receive data from the ESP32
    data, addr = sock.recvfrom(1024)  # Buffer size is 1024 bytes
    print(f"Received message from {addr}: {data.decode('utf-8')}")
