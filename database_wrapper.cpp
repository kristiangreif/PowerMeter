#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>
#include <WiFi.h>
#include "sensor_wrapper.h"

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

int writeReadings(READINGS *readings) {
  // Clear fields for reusing the point. Tags will remain the same as set above.
  primaryReadings.clearFields();
  accumulatedCapacity.clearFields();

  primaryReadings.addField("voltage", readings->voltage);
  primaryReadings.addField("current", readings->current);
  primaryReadings.addField("power", readings->power);

  accumulatedCapacity.addField("cpacity_ah", readings->capacityAh);
  accumulatedCapacity.addField("cpacity_wh", readings->capacityWh);

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
