import asyncio

# Replace with the ESP32 IP address
esp32_ip = "10.67.70.186"  
port = 80

async def receive_data():
    while True:
        try:
            # Open a connection to the ESP32
            reader, writer = await asyncio.open_connection(esp32_ip, port)

            # Receive data from ESP32
            data = await reader.read(1024)  # Read up to 1024 bytes
            print(data.decode())

            # Close the connection
            writer.close()
            await writer.wait_closed()

        except Exception as e:
            print("Failed to receive data:", e)

        # Optional: Wait for a short period before the next attempt
        await asyncio.sleep(1)  # Adjust the sleep duration as necessary

if __name__ == "__main__":
    asyncio.run(receive_data())
