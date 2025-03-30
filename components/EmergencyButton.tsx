import React from "react";
import { View, Button } from "react-native";

export default function EmergencyButton() {
  return (
    <View>
      <Button title="Emergency" onPress={() => alert("Emergency Triggered!")} />
    </View>
  );
}
