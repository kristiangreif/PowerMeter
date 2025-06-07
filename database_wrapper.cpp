#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <WiFi.h>
#include "sensor_wrapper.h"
#include "server_wrapper.h"

#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "YXrVFOp_jGtkrG_m5eTauEm0wxzNA_khi5P6f0S5Qi_HsrIOoK5t4q1DQmZR1nJ1D5HzibDP1ODKGBdGMrxewg=="
#define INFLUXDB_ORG "d813fc04dea42d8a"
#define INFLUXDB_BUCKET "Readings"
  
// Time zone info
#define TZ_INFO "UTC2"

// Declare InfluxDB client instance with preconfigured InfluxCloud certificate
InfluxDBClient influxClient(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);


Point primaryReadings("primary_readings");
Point accumulatedCapacity("capacity");

void initDB() {

  // Add tags to the data point
  primaryReadings.addTag("device", "ESP32");
  accumulatedCapacity.addTag("device", "ESP32");

  // Accurate time is necessary for certificate validation and writing in batches
  // We use the NTP servers in your area as provided by: https://www.pool.ntp.org/zone/
  // Syncing progress and the time will be printed to Serial.
  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  // Check server connection
  if (influxClient.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(influxClient.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(influxClient.getLastErrorMessage());
  }

  // Enable messages batching and retry buffer
  influxClient.setWriteOptions(WriteOptions().writePrecision(WritePrecision::MS).batchSize(20).bufferSize(60));
}

int writeReadingsToDb(READINGS *readings) {
  // Clear fields for reusing the point. Tags will remain the same as set above.
  primaryReadings.clearFields();
  accumulatedCapacity.clearFields();

  primaryReadings.addField("voltage", readings->voltage);
  primaryReadings.addField("current", readings->current);
  primaryReadings.addField("power", readings->power);

  accumulatedCapacity.addField("capacity_ah", readings->capacityAh);
  accumulatedCapacity.addField("capacity_wh", readings->capacityWh);

  if (WiFi.status() != WL_CONNECTED)
    return 1;

  // Serial.print("Writing: ");
  // Serial.println(primaryReadings.toLineProtocol());


  if (!influxClient.writePoint(primaryReadings)) {
      Serial.print("InfluxDB primary readings write failed: ");
      Serial.println(influxClient.getLastErrorMessage());
      return 2;
  }

  if (!influxClient.writePoint(accumulatedCapacity)) {
      Serial.print("InfluxDB capacity write failed: ");
      Serial.println(influxClient.getLastErrorMessage());
      return 2;
  }

  return 0;

}

// char lineBuffer[40];

void getDbReadings(const char* timeFrom, const char* timeTo) {

  Serial.print(timeFrom);
  Serial.print(", ");
  Serial.println(timeTo);

  String query = "from(bucket: \"Readings\") |> range(start: " + String(timeFrom) + ", stop: " + String(timeTo) + ") \
  |> filter(fn: (r) => r._measurement == \"primary_readings\" or r._measurement == \"capacity\") \
  |> filter(fn: (r) => r._field == \"voltage\" or r._field == \"current\" or r._field == \"power\" or r._field == \"capacity_ah\" or r._field == \"capacity_wh\") \
  |> filter(fn: (r) => r.device == \"ESP32\") \
  |> timeShift(duration: 2h)";


  sendMessage("QUERY_STARTED");
  // Send query to the server and get result
  FluxQueryResult result = influxClient.query(query);

  // Iterate over rows. Even there is just one row, next() must be called at least once.
  

  const unsigned int MAX_LINE_LENGTH = 40; // Adjust based on your expected line length
  const unsigned int MAX_BUFFER_SIZE = 20; // Number of lines to store before sending
  char lineBuffer[MAX_BUFFER_SIZE][MAX_LINE_LENGTH];
  unsigned int bufferIndex = 0;

  while (result.next()) {
      String line = result.getValueByName("_field").getString() + ',' + result.getValueByName("_time").getDateTime().format("%FT%T") + ',' + result.getValueByName("_value").getRawValue();

      const unsigned int LINE_LENGTH = line.length() + 1;

      if (line.length() < MAX_LINE_LENGTH) {
          line.toCharArray(lineBuffer[bufferIndex], MAX_LINE_LENGTH);
          bufferIndex++;

          if (bufferIndex >= MAX_BUFFER_SIZE) {
              String batchMessage;
              for (unsigned int i = 0; i < bufferIndex; i++) {
                  batchMessage += String(lineBuffer[i]) + "\n"; // Combine messages with newline separator
              }
              sendMessage(batchMessage.c_str());
              bufferIndex = 0; // Reset the buffer index after sending
          }
      } else {
          Serial.println("Line length exceeds buffer size");
      }

      handleConnections();
      
      // Check and log free memory
      // Serial.print("Free heap: ");
      // Serial.println(ESP.getFreeHeap());
  }

  // Send any remaining lines in the buffer
  if (bufferIndex > 0) {
      String batchMessage;
      for (unsigned int i = 0; i < bufferIndex; i++) {
          batchMessage += String(lineBuffer[i]) + "\n"; // Combine messages with newline separator
      }
      sendMessage(batchMessage.c_str());
      bufferIndex = 0; // Reset the buffer index after sending
  }

  sendMessage("QUERY_FINISHED");

  // Check if there was an error
  if(result.getError() != "") {
    sendMessage("QUERY_ERROR");
    Serial.print("Query result error: ");
    Serial.println(result.getError());
  }

  result.close(); 
}
