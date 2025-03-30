#include <WiFi.h>
#include <FirebaseESP32.h>
#include <TinyGPS++.h>
#include <SD.h>
#include <SPI.h>

// WiFi Credentials
#define WIFI_SSID "..."
#define WIFI_PASSWORD "whekewhy"

// Firebase Credentials
#define FIREBASE_HOST "https://velora-3f66b-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQCOnLYA817R1j3q\niqlH6x+0VkYgLq74HZD8Ou3b6e91wpMYM3X/WCiMqKzxHG+bGzsKMhTcupxw06Fq\nUCDtNUDkdYBqwZQm90iABwGtXqHWn3Qud6Ows6KouMP+vB9FJxnx+/NCX/ze4ig7\nNDS870g0+mjGIf1FApnEmjEbKsF4Z1wRp7C87tMIvdRRy8+FWlGTjDCV0htpTdU6\nQW4ZYPwg5dqiGPI/UyHH9y94DFjJ7gBwE1PoR6OChBQzs71wFyvto1jJoQo/InpT\n1mP7xwqaKouCH1TYdfeGaB2Ab8YfCBwstRLpAKFbw7XapaydAqgRHwJME8crdTXM\n21VNALKDAgMBAAECggEADWR9GRDBzk3iyaRU6lqTwyE4+6u2pblNFMrJ7JWG9dWc\nb7Dhe2XBhRgQCaKEfpnrjPUQDXx+1X+iUHQO64fNPMcmFKByM8iUJ+XAjBHve9LE\nm9qDZkQwWczkJwdunlViM93XxdtyyVGOuqSX8Ug9TTBY54ZonPL2EsbyJp14xsA2\nO3kHeRF0tIMGcYdvTYiXO77w2S8PbtY1OOhNBzcFwLnqN9rewTsip2pJ8CyJxf5b\nqXISMhNpmHA+DL09XHfLK+bYtxmj9Jlx4oTvDSWoyb/KAaY1EyCvjIhUpBU5Xiux\nO6VvO+eZIrDhWwbJMyshmC7ezyLai62pcvMF290M6QKBgQC/7WxvxiLn7eLYRUtt\nxLCGJQpOVTERyYq+m0EyBDtpXG2XhC42v3AVSxRTwgRBTQtYwIk1fogV7wfhjRgr\nrNNo7wnuz0H/UiSPteAFeUkLQ4lPHjBF+bOj8b+aLp0tIKKprfIlyqUSIUmvRJ4D\nFG0n4qmFxhVfgjW8KLWwi66HqQKBgQC+OK+EAxdMizyxxxViW2c7ChagLDWctdfs\n4AjeU1R+lVBvzNKaOAj9Hb0YdoQhyAsJsWwksBpJYuiDY3su3FHQsTBr/2O4SUFH\n+tUBr5KxpEPH4jrbUb0+li523YbqoSLwnqMxnMYK4UuKbVfz/dQCB6GEAqYhrNuu\nm8mZvK/USwKBgGwBH9SGm34I0G8ED75lwTC8B2CtcD+iOwGoPLf4ybYw3Ts2lwsY\nD+rrpTS9KcfVo1z+fDguTEaLjNPQoplxWEbkvaI1393eS9TTdI2gAwrjppFvW5sF\nOaI4mKobMTgD9YWm7W127A2Xze9jncf95q9bTiqJnd1xWOvZvOTstfqBAoGBALn7\n2HfdQdGALaawPRM+xQ7vjTGsJ/sBvI2IeoNNvEZLnSrCe4N3mCpLAlDBx+zzlv8y\nLscsO3dXMnkMMiueFIxUQkDFom1TinVjJRKR5H61WeQ8KEm5gKuJ0QI9FCWhyPS0\nVmEypFuM7fv5bs5LdhdJ+LyGjoJMbToqbZFX8B5DAoGAMfGwsbAmFUHdFEDiH9v+\nHN5wqGaT/itEWOv0TgA99HKKPlMAQVpYX9Qj4IgtlqsdMjKZW9/USzQ1Q7FfsJ+M\nvw55BnPZKqJZN1twbkTP4mWBljpMREscqxtVWNUMbx3GrDm9e7i4iuOvX7HeVBiF\np2nFnl41Tl6cXOxIQanXGA4=\n-----END PRIVATE KEY-----\n"

// GPS and SD Card Setup
#define RXD2 20
#define TXD2 21
#define SD_CS 3

TinyGPSPlus gps;
HardwareSerial neogps(1);
FirebaseData firebaseData;

void setup()
{
    Serial.begin(115200);
    neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);

    // Connect to WiFi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi!");

    // Initialize Firebase
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);

    // Initialize SD Card
    if (!SD.begin(SD_CS))
    {
        Serial.println("SD Card Mount Failed");
        return;
    }
    Serial.println("SD Card Initialized");
}

void loop()
{
    while (neogps.available() > 0)
    {
        if (gps.encode(neogps.read()))
        {
            if (gps.location.isValid())
            {
                float latitude = gps.location.lat();
                float longitude = gps.location.lng();

                Serial.print("Latitude: ");
                Serial.println(latitude);
                Serial.print("Longitude: ");
                Serial.println(longitude);

                // Save to SD Card
                File file = SD.open("/gps_data.txt", FILE_APPEND);
                if (file)
                {
                    file.printf("Lat: %f, Lng: %f\n", latitude, longitude);
                    file.close();
                }
                else
                {
                    Serial.println("Failed to write to SD Card");
                }

                // Upload to Firebase
                FirebaseJson json;
                json.set("latitude", latitude);
                json.set("longitude", longitude);

                if (Firebase.pushJSON(firebaseData, "/gps/location", json))
                {
                    Serial.println("Firebase Upload Successful!");
                }
                else
                {
                    Serial.println("Firebase Upload Failed: " + firebaseData.errorReason());
                }
            }
        }
    }
}
