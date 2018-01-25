/**
 * @file mm1MqttSn.h
 * @description Basic setup and protocol to interact 
 * with the Deutsche Telekom Cloud of things MQTT-SN connector.
 * @author Andreas Krause
 * @copyright (C) 2018 mm1 Technology GmbH - all rights reserved. 
 * @licence MIT licence
 * 
 * Find out more about mm1 Technology:
 * Company: http://mm1-technology.de/
 * GitHub:  https://github.com/mm1technology/
 */

#ifndef MM1_MQTTSN_HEADER_FILE
#define MM1_MQTTSN_HEADER_FILE

#include "DTCOTSetup.h"

#if CONN_TYPE == NB_IOT

#include <Arduino.h>
#include <Client.h>

#include "mm1MqttSnClientSettings.h"
#include "mqttsn-messages.h"

/**
 * MM1's impementation of the MQTT-SN protocol
 */
class MM1MqttSn: public MQTTSN {
public:

   /**
    * Constructor
    * @param clientId MQTT-SN user ID
    * @param brokerPort port of the NBIoT server
    * @param ioStream standard Arduino communications Client to use (ie WiFi)
    * @param password password for the connection
    */
  MM1MqttSn( const char* clientId
	, unsigned short brokerPort
	, const char* password
	, Client& ioStream );

public:
	/**
	 * Start MM1's MQTT-SN interface
	 */
  bool init();

/**
 * Publish value on MQTT broker.
 * Publishes a value to the remote broker. You should see the value change immediately.
 * @param topicId the key/topic to publish to.
 * @param value the value to publish to the given key/topic. For example: 123, "hello" 
 */
  bool publish(
    int topicId
    , const void* value
    );
  
  /**
   * connect to the MQTT-SN broker
   * @param flags for the MQTT-SN CONNECT message. See official MQTT-SN documentation for details.
   * @param duration duration for the MQTT-SN CONNECT message. See official MQTT-SN documentation for details.
   */
  int connect(const uint8_t flags, const uint16_t duration);
  
  /**
   * Get printable error string
   * @param error number for MQTT-SN error
   * @return string explaining this error
   */
  String connectErrorString(int error);
  
  /**
   * Disconnect from broker.
   */
  void disconnect();
  
  /**
   * Register to an MQTT-SN topic
   * @param topic topic name
   * @param valueType value type. See official MQTT-SN documentation for details.
   */
  int RegisterTopicDTCoT(String topic, char valueType);

public:
	
	/**
	 * Called when gateway info available.
 	 */
	void gwinfo_handler( const msg_gwinfo* msg);
	void advertise_handler(const msg_advertise* msg);
	void disconnect_handler(const msg_disconnect* msg);
	void willtopicreq_handler(const message_header* msg);
	void willmsgreq_handler(const message_header* msg);


private:
  String _clientId;
  uint16_t _brokerPort;
  const char* _imsi;
  const char* _password;
  
};

#endif

#endif /* MM1_MQTTSN_HEADER_FILE */
