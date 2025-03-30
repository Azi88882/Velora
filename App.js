import React, { useEffect, useState } from "react";
import { View, Text, TextInput, Button } from "react-native";
import axios from "axios";

const ESP32_IP = "http://192.168.1.100"; // REPLACE with ESP32C3's actual IP

export default function App() {
    const [data, setData] = useState("");
    const [input, setInput] = useState("");

    // Fetch data from ESP32C3
    const fetchData = async () => {
        try {
            const response = await axios.get(`${ESP32_IP}/get-data`);
            setData(response.data);
        } catch (error) {
            console.error("Error fetching data:", error);
        }
    };

    // Send data to ESP32C3
    const sendData = async () => {
        try {
            await axios.post(`${ESP32_IP}/post-data`, input, {
                headers: { "Content-Type": "text/plain" },
            });
            alert("Data sent successfully!");
        } catch (error) {
            console.error("Error sending data:", error);
        }
    };

    return (
        <View style={{ padding: 20 }}>
            <Text>Data from ESP32: {data}</Text>
            <Button title="Get Data from ESP32" onPress={fetchData} />
            
            <TextInput
                placeholder="Enter data"
                value={input}
                onChangeText={setInput}
                style={{ borderBottomWidth: 1, marginVertical: 10 }}
            />
            <Button title="Send Data to ESP32" onPress={sendData} />
        </View>
    );
}
