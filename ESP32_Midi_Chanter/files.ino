#include <LittleFS.h>

void initStorage() {
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS Mount Failed!");
    return;
  }

  // Calculate and print partition usage
  size_t total = LittleFS.totalBytes();
  size_t used = LittleFS.usedBytes();

  Serial.println("--- Storage Status ---");
  Serial.printf("Total space: %d KB\n", total / 1024);
  Serial.printf("Used space:  %d KB\n", used / 1024);
  Serial.printf("Free space:  %d KB\n", (total - used) / 1024);

  // List the files to confirm they are there
  Serial.println("--- Files Found ---");
  File root = LittleFS.open("/");
  File file = root.openNextFile();
  while(file){
      Serial.printf("File: %s  |  Size: %d bytes\n", file.name(), file.size());
      file = root.openNextFile();
  }
  Serial.println("-----------------------");
}