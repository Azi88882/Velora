import { initializeApp } from "firebase/app";
import { getFirestore } from "firebase/firestore";
import { getMessaging } from "firebase/messaging";

const firebaseConfig = {
  apiKey: "AIzaSyAZKqv8hw74pl2Bc4oA3Pyx-m6lprcCHjs",
  authDomain: "velora-3f66b.firebaseapp.com",
  projectId: "velora-3f66b",
  storageBucket: "velora-3f66b.appspot.com",
  messagingSenderId: "829317727597",
  appId: "1:829317727597:android:92954f800b8e4eed30c664",
};

const app = initializeApp(firebaseConfig);
const db = getFirestore(app);
const messaging = getMessaging(app);

// Listen for messages in foreground
onMessage(messaging, (payload) => {
  console.log("Message received:", payload);
});

export { db, messaging };