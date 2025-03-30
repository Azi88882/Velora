import { Tabs } from "expo-router";
import React, { useEffect } from "react";
import { Platform, Alert } from "react-native";
import { Ionicons } from "@expo/vector-icons";
import messaging from "@react-native-firebase/messaging";

const requestUserPermission = async () => {
  const authStatus = await messaging().requestPermission();
  const enabled =
    authStatus === messaging.AuthorizationStatus.AUTHORIZED ||
    authStatus === messaging.AuthorizationStatus.PROVISIONAL;

  if (enabled) {
    console.log("FCM Permission granted");
  }
};

export default function Layout() {
  useEffect(() => {
    requestUserPermission();

    // Foreground message listener
    const unsubscribe = messaging().onMessage(async (remoteMessage) => {
      Alert.alert(
        "Emergency Alert!",
        remoteMessage.notification?.title || "Emergency alert received!"
      );
    });

    return unsubscribe;
  }, []);

  return (
    <Tabs
      screenOptions={{
        headerShown: false,
        tabBarStyle: Platform.select({
          ios: { position: "absolute" },
          default: {},
        }),
      }}
    >
      <Tabs.Screen
        name="index"
        options={{
          title: "Home",
          tabBarIcon: ({ color }) => (
            <Ionicons name="home" size={24} color={color} />
          ),
        }}
      />
      <Tabs.Screen
        name="map"
        options={{
          title: "Map",
          tabBarIcon: ({ color }) => (
            <Ionicons name="map" size={24} color={color} />
          ),
        }}
      />
      <Tabs.Screen
        name="emergency"
        options={{
          title: "Emergency",
          tabBarIcon: ({ color }) => (
            <Ionicons name="alert-circle" size={24} color={color} />
          ),
        }}
      />
    </Tabs>
  );
}
