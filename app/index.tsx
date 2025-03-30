import React, { useState, useEffect } from "react";
import { View, Text, StyleSheet } from "react-native";
import MapView, { Marker } from "react-native-maps";
import { firestore } from "./configuration";
import { doc, getDoc } from "firebase/firestore"; // Firestore imports

export default function MapScreen() {
  const [location, setLocation] = useState<{ latitude: number; longitude: number } | null>(null);

  useEffect(() => {
    console.log("Initializing Firebase Firestore...");

    const locationRef = doc(firestore, "location", "location"); // Firestore reference

    console.log("Firestore instance:", firestore);
    console.log("Location Reference:", locationRef);

    const fetchData = async () => {
      try {
        const docSnap = await getDoc(locationRef); // Get the document from Firestore
        if (docSnap.exists()) {
          const data = docSnap.data();
          console.log("Fetched Data:", data); // Debugging line to check if data is retrieved
          if (data) {
            setLocation({
              latitude: data.latitude,
              longitude: data.longitude,
            });
          }
        } else {
          console.log("No such document!");
        }
      } catch (error) {
        console.log("Error fetching data:", error);
      }
    };

    fetchData(); // Fetch data when component mounts

  }, []);

  return (
    <View style={styles.container}>
      <Text style={styles.title}>Child's Location</Text>
      {location ? (
        <MapView
          style={styles.map}
          initialRegion={{
            latitude: location.latitude,
            longitude: location.longitude,
            latitudeDelta: 0.01,
            longitudeDelta: 0.01,
          }}
        >
          <Marker coordinate={location} title="Child's Location" />
        </MapView>
      ) : (
        <Text>Fetching location...</Text>
      )}
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1 },
  title: { fontSize: 18, textAlign: "center", margin: 10 },
  map: { flex: 1 },
});