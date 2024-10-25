import socket

# Replace with the ESP32 IP address
esp32_ip = "10.67.70.186"  
port = 80

def receive_data():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((esp32_ip, port))
        data = b''  # Initialize an empty bytes object
        while True:
            part = s.recv(1024)  # Receive data in chunks
            data += part  # Append received data
            if len(part) < 1024:  # Break when no more data is coming in
                break
        return data.decode()

if __name__ == "__main__":
    while True:
        try:
            data = receive_data()
            print(data)
        except Exception as e:
            print("Failed to receive data:", e)
