import React, { useEffect } from "react";
import { View, Text, StyleSheet } from "react-native";
import { messaging } from "../firebaseConfig";
import { onMessage } from "firebase/messaging";

export default function EmergencyScreen() {
  useEffect(() => {
    const unsubscribe = onMessage(messaging, (payload) => {
      alert("Emergency Alert: Child pressed the button!");
      console.log(payload);
    });

    return () => unsubscribe();
  }, []);

  return (
    <View style={styles.container}>
      <Text style={styles.title}>Emergency Alerts</Text>
      <Text>You'll receive an alert if the child presses the button.</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, justifyContent: "center", alignItems: "center" },
  title: { fontSize: 24, fontWeight: "bold", marginBottom: 20 },
});
