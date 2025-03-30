import React from "react";
import { View, Text, StyleSheet } from "react-native";
import StepCounter from "../components/StepCounter";
import EmergencyButton from "../components/EmergencyButton";

export default function HomeScreen() {
  return (
    <View style={styles.container}>
      <Text style={styles.title}>Velora - Child Safety App</Text>
      <StepCounter />
      <EmergencyButton />
    </View>
  );
}

const styles = StyleSheet.create({
  container: { flex: 1, justifyContent: "center", alignItems: "center" },
  title: { fontSize: 24, fontWeight: "bold", marginBottom: 20 },
});
