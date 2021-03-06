#ifndef __BLUENRG1_API_H__
#define __BLUENRG1_API_H__


/**
  ******************************************************************************
  * @file    bluenrg1_api.h
  * @author  AMS - VMA RF Application team
  * @version V1.0.0
  * @date    21-Sept-2015
  * @brief   Header file for BlueNRG-1 Bluetooth Low Energy stack APIs
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#include <stdint.h>
/** Documentation for Whitelist_Entry_t */
typedef struct Whitelist_Entry_t_s {
  uint8_t Peer_Address_Type /** 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use */;
  uint8_t Peer_Address[6] /** Public Device Address or Random Device Address of the device
to be added to the white list. */;
} Whitelist_Entry_t;
/** Documentation for Bonded_Device_Entry_t */
typedef struct Bonded_Device_Entry_t_s {
  uint8_t Address_Type /** 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use */;
  uint8_t Address[6] /** Public Device Address or Random Device Address of the device
to be added to the white list. */;
} Bonded_Device_Entry_t;
/** Documentation for Service_UUID_t */
typedef union Service_UUID_t_s {
  uint16_t Service_UUID_16 /** 16-bit UUID */;
  uint8_t Service_UUID_128[16] /** 128-bit UUID */;
} Service_UUID_t;
/** Documentation for Include_UUID_t */
typedef union Include_UUID_t_s {
  uint16_t Include_UUID_16 /** 16-bit UUID */;
  uint8_t Include_UUID_128[16] /** 128-bit UUID */;
} Include_UUID_t;
/** Documentation for Char_UUID_t */
typedef union Char_UUID_t_s {
  uint16_t Char_UUID_16 /** 16-bit UUID */;
  uint8_t Char_UUID_128[16] /** 128-bit UUID */;
} Char_UUID_t;
/** Documentation for Char_Desc_Uuid_t */
typedef union Char_Desc_Uuid_t_s {
  uint16_t Char_UUID_16 /** 16-bit UUID */;
  uint8_t Char_UUID_128[16] /** 128-bit UUID */;
} Char_Desc_Uuid_t;
/** Documentation for UUID_t */
typedef union UUID_t_s {
  uint16_t UUID_16 /** 16-bit UUID */;
  uint8_t UUID_128[16] /** 128-bit UUID */;
} UUID_t;
/** Documentation for Handle_Entry_t */
typedef struct Handle_Entry_t_s {
  uint16_t Handle /** The handles for which the attribute value has to be read */;
} Handle_Entry_t;
typedef uint8_t tBleStatus;
/**
 *@defgroup HCI_API HCI API
 *@brief HCI API layer.
 *@{
 */
/**
  * @brief The Disconnection command is used to terminate an existing connection. The
Connection_Handle command parameter indicates which connection is to be
disconnected. The Reason command parameter indicates the reason for ending
the connection. The remote Controller will receive the Reason command
parameter in the Disconnection Complete event. All synchronous connections
on a physical link should be disconnected before the ACL connection on the
same physical connection is disconnected.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.1.6)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Reason Authentication Failure error code (0x05), Other End Terminated Connection error codes (0x13-0x15),
Unsupported Remote Feature error code(0x1A) and Pairing with Unit Key Not Supported error code (0x29)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_disconnect(uint16_t Connection_Handle,
                          uint8_t Reason);
/**
  * @brief This command will obtain the values for the version information for the remote
device identified by the Connection_Handle parameter. The Connection_Handle
must be a Connection_Handle for an ACL or LE connection.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.1.23)
  * @param Connection_Handle Specifies which Connection_Handle's version information to get.
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_remote_version_information(uint16_t Connection_Handle);
/**
  * @brief The Set_Event_Mask command is used to control which events are generated
by the HCI for the Host.

If the bit in the Event_Mask is set to a one, then the
event associated with that bit will be enabled. For an LE Controller, the LE
Meta Event bit in the Event_Mask shall enable or disable all LE events in the
LE Meta Event (see Section 7.7.65). The Host has to deal with each event that
occurs. The event mask allows the Host to control how much it is interrupted.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.1)
  * @param Event_Mask 0x0000000000000000 No events specified
0x0000000000000001 Inquiry Complete Event
0x0000000000000002 Inquiry Result Event
0x0000000000000004 Connection Complete Event
0x0000000000000008 Connection Request Event
0x0000000000000010 Disconnection Complete Event
0x0000000000000020 Authentication Complete Event
0x0000000000000040 Remote Name Request Complete Event
0x0000000000000080 Encryption Change Event
0x0000000000000100 Change Connection Link Key Complete Event
0x0000000000000200 Master Link Key Complete Event
0x0000000000000400 Read Remote Supported Features Complete Event
0x0000000000000800 Read Remote Version Information Complete Event
0x0000000000001000 QoS Setup Complete Event
0x0000000000002000 Reserved
0x0000000000004000 Reserved
0x0000000000008000 Hardware Error Event
0x0000000000010000 Flush Occurred Event
0x0000000000020000 Role Change Event
0x0000000000040000 Reserved
0x0000000000080000 Mode Change Event
0x0000000000100000 Return Link Keys Event
0x0000000000200000 PIN Code Request Event
0x0000000000400000 Link Key Request Event
0x0000000000800000 Link Key Notification Event
0x0000000001000000 Loopback Command Event
0x0000000002000000 Data Buffer Overflow Event
0x0000000004000000 Max Slots Change Event
0x0000000008000000 Read Clock Offset Complete Event
0x0000000010000000 Connection Packet Type Changed Event
0x0000000020000000 QoS Violation Event
0x0000000040000000 Page Scan Mode Change Event [deprecated]
0x0000000080000000 Page Scan Repetition Mode Change Event
0x0000000100000000 Flow Specification Complete Event
0x0000000200000000 Inquiry Result with RSSI Event
0x0000000400000000 Read Remote Extended Features Complete Event
0x0000000800000000 Reserved
0x0000001000000000 Reserved
0x0000002000000000 Reserved
0x0000004000000000 Reserved
0x0000008000000000 Reserved
0x0000010000000000 Reserved
0x0000020000000000 Reserved
0x0000040000000000 Reserved
0x0000080000000000 Synchronous Connection Complete Event
0x0000100000000000 Synchronous Connection Changed Event
0x0000200000000000 Sniff Subrating Event
0x0000400000000000 Extended Inquiry Result Event
0x0000800000000000 Encryption Key Refresh Complete Event
0x0001000000000000 IO Capability Request Event
0x0002000000000000 IO Capability Request Reply Event
0x0004000000000000 User Confirmation Request Event
0x0008000000000000 User Passkey Request Event
0x0010000000000000 Remote OOB Data Request Event
0x0020000000000000 Simple Pairing Complete Event
0x0040000000000000 Reserved
0x0080000000000000 Link Supervision Timeout Changed Event
0x0100000000000000 Enhanced Flush Complete Event
0x0200000000000000 Reserved
0x0400000000000000 User Passkey Notification Event
0x0800000000000000 Keypress Notification Event
0x1000000000000000 Remote Host Supported Features Notification Event
0x2000000000000000 LE Meta-Event
0xC000000000000000 Reserved for future use
0x00001FFFFFFFFFFF Default
  * @retval Value indicating success or error code.
*/
tBleStatus hci_set_event_mask(uint8_t Event_Mask[8]);
/**
  * @brief The Reset command will reset the Link Layer on an LE
Controller.

The Reset command shall not affect the used HCI transport layer since the HCI transport
layers may have reset mechanisms of their own. After the reset is completed,
the current operational state will be lost, the Controller will enter standby mode
and the Controller will automatically revert to the default values for the parameters
for which default values are defined in the specification.
Note: The Reset command will not necessarily perform a hardware reset. This
is implementation defined. 
The Host shall not send additional HCI commands before the Command Complete
event related to the Reset command has been received.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.2)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_reset(void);
/**
  * @brief This command reads the values for the Transmit_Power_Level parameter for
the specified Connection_Handle. The Connection_Handle shall be a Connection_
Handle for an ACL connection.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.35)
  * @param Connection_Handle Specifies which Connection_Handle's Transmit Power Level setting to
read.
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Type 0x00 Read Current Transmit Power Level.
0x01 Read Maximum Transmit Power Level.
0x02-0xFF Reserved
  * @param[out] Transmit_Power_Level Size: 1 Octet (signed integer)
Range: -30 <= N <= 20
Units: dBm
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_transmit_power_level(uint16_t Connection_Handle,
                                         uint8_t Type,
                                         uint8_t *Transmit_Power_Level);
/**
  * @brief This command reads the values for the version information for the local Controller.
The HCI Version information defines the version information of the HCI layer.
The LMP/PAL Version information defines the version of the LMP or PAL. The
Manufacturer_Name information indicates the manufacturer of the local device.
The HCI Revision and LMP/PAL Subversion are implementation dependent.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.1)
  * @param[out] HCI_Version See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] HCI_Revision Revision of the Current HCI in the BR/EDR Controller.
  * @param[out] LMP_PAL_Version Version of the Current LMP or PAL in the Controller.
See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] Manufacturer_Name Manufacturer Name of the BR/EDR Controller.
See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] LMP_PAL_Subversion Subversion of the Current LMP or PAL in the Controller. This value is
implementation dependent.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_version_information(uint8_t *HCI_Version,
                                              uint16_t *HCI_Revision,
                                              uint8_t *LMP_PAL_Version,
                                              uint16_t *Manufacturer_Name,
                                              uint16_t *LMP_PAL_Subversion);
/**
  * @brief This command reads the list of HCI commands supported for the local Controller.
This command shall return the Supported_Commands configuration parameter.
It is implied that if a command is listed as supported, the feature underlying
that command is also supported.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.2)
  * @param[out] Supported_Commands Bit mask for each HCI Command. If a bit is 1, the Controller supports the
corresponding command and the features required for the command.
Unsupported or undefined commands shall be set to 0.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_supported_commands(uint8_t Supported_Commands[64]);
/**
  * @brief This command requests a list of the supported features for the local BR/EDR
Controller. This command will return a list of the LMP features. For details see
Part C, Link Manager Protocol Specification on page 227.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.3)
  * @param[out] LMP_Features Bit Mask List of LMP features.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_supported_features(uint8_t LMP_Features[8]);
/**
  * @brief On a BR/EDR Controller, this command reads the Bluetooth Controller address
(BD_ADDR). See the Part B, Baseband Specification on page 59 for details of
how BD_ADDR is used (see [Vol 3] Part C, Section 3.2.1).
On an LE Controller, this command shall read the Public Device Address as
defined in [Vol 6] Part B, Section 1.3, Device Address. If this Controller does
not have a Public Device Address, the value 0x000000000000 shall be
returned.
On a BR/EDR/LE Controller, the public address shall be the same as the
BD_ADDR.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.2)
  * @param[out] BD_ADDR BD_ADDR ( Bluetooth Device Address) of the Device.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_bd_addr(uint8_t BD_ADDR[6]);
/**
  * @brief This command reads the Received Signal Strength Indication (RSSI) value from
a Controller.
For a BR/EDR Controller, a Connection_Handle is used as the Handle command
parameter and return parameter. The RSSI parameter returns the difference
between the measured Received Signal Strength Indication (RSSI) and
the limits of the Golden Receive Power Range for a Connection Handle to
another BR/EDR Controller. The Connection_Handle must be a Connection_
Handle for an ACL connection. Any positive RSSI value returned by the
Controller indicates how many dB the RSSI is above the upper limit, any negative
value indicates how many dB the RSSI is below the lower limit. The value
zero indicates that the RSSI is inside the Golden Receive Power Range.
Note: How accurate the dB values will be depends on the Bluetooth hardware.
The only requirements for the hardware are that the BR/EDR Controller is able
to tell whether the RSSI is inside, above or below the Golden Device Power
Range.
The RSSI measurement compares the received signal power with two threshold
levels, which define the Golden Receive Power Range. The lower threshold
level corresponds to a received power between -56 dBm and 6 dB above the
actual sensitivity of the receiver. The upper threshold level is 20 dB above the
lower threshold level to an accuracy of +/- 6 dB.
For an AMP Controller, a Physical_Link_Handle is used for the Handle command
parameter and return parameter. The meaning of the RSSI metric is
AMP type specific and defined in the AMP PALs (see Volume 5, Core System
Package [AMP Controller volume]).
For an LE transport, a Connection_Handle is used as the Handle command
parameter and return parameter. The meaning of the RSSI metric is an absolute
receiver signal strength value in dBm to +/- 6 dB accuracy. If the RSSI cannot
be read, the RSSI metric shall be set to 127.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.5.4)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param[out] RSSI BR/EDR
Range: -128 =< N <= 127 (signed integer)
Units: dB
AMP:
Range: AMP type specific (signed integer)
Units: dBm
LE:
Range: -127 to 20, 127 (signed integer)
Units: dBm
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_rssi(uint16_t Connection_Handle,
                         uint8_t *RSSI);
/**
  * @brief The LE_Set_Event_Mask command is used to control which LE events are
generated by the HCI for the Host. If the bit in the LE_Event_Mask is set to a
one, then the event associated with that bit will be enabled. The Host has to
deal with each event that is generated by an LE Controller. The event mask
allows the Host to control which events will interrupt it.
For LE events to be generated, the LE Meta-Event bit in the Event_Mask shall
also be set. If that bit is not set, then LE events shall not be generated, regardless
of how the LE_Event_Mask is set.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.1)
  * @param LE_Event_Mask 0x0000000000000000 No LE events specified
0x0000000000000001 LE Connection Complete Event
0x0000000000000002 LE Advertising Report Event
0x0000000000000004 LE Connection Update Complete Event
0x0000000000000008 LE Read Remote Used Features Complete Event
0x0000000000000010 LE Long Term Key Request Event
0x000000000000001F Default
0xFFFFFFFFFFFFFE0 Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_event_mask(uint8_t LE_Event_Mask[8]);
/**
  * @brief The LE_Read_Buffer_Size command is used to read the maximum size of the
data portion of HCI LE ACL Data Packets sent from the Host to the Controller.
The Host will segment the data transmitted to the Controller according to these
values, so that the HCI Data Packets will contain data with up to this size. The
LE_Read_Buffer_Size command also returns the total number of HCI LE ACL
Data Packets that can be stored in the data buffers of the Controller. The
LE_Read_Buffer_Size command must be issued by the Host before it sends
any data to an LE Controller (see Section 4.1.1).
If the Controller returns a length value of zero, the Host shall use the
Read_Buffer_Size command to determine the size of the data buffers (shared
between BR/EDR and LE transports).
Note: Both the Read_Buffer_Size and LE_Read_Buffer_Size commands may
return buffer length and number of packets parameter values that are nonzero.
This allows a Controller to offer different buffers and number of buffers for
BR/EDR data packets and LE data packets.
The HC_LE_ACL_Data_Packet_Length return parameter shall be used to
determine the size of the L2CAP PDU segments contained in ACL Data
Packets, which are transferred from the Host to the Controller to be broken up
into packets by the Link Layer. Both the Host and the Controller shall support
command and event packets, where the data portion (excluding header)
contained in the packets is 255 octets in size. The
HC_Total_Num_LE_ACL_Data_Packets return parameter contains the total
number of HCI ACL Data Packets that can be stored in the data buffers of the
Controller. The Host determines how the buffers are to be divided between
different Connection Handles.
Note: The HC_LE_ACL_Data_Packet_Length return parameter does not
include the length of the HCI Data Packet header.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.2)
  * @param[out] HC_LE_ACL_Data_Packet_Length 0x0000 No dedicated LE Buffer - use Read_Buffer_Size command.
0x0001 - 0xFFFF Maximum length (in octets) of the data portion of each HCI ACL Data
Packet that the Controller is able to accept.
  * @param[out] HC_Total_Num_LE_ACL_Data_Packets 0x00 No dedicated LE Buffer - use Read_Buffer_Size command.
0x01 - 0xFF Total number of HCI ACL Data Packets that can be stored in the data
buffers of the Controller.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_buffer_size(uint16_t *HC_LE_ACL_Data_Packet_Length,
                                   uint8_t *HC_Total_Num_LE_ACL_Data_Packets);
/**
  * @brief This command requests the list of the supported LE features for the Controller.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.3)
  * @param[out] LE_Features Bit Mask List of LE features.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_local_supported_features(uint8_t LE_Features[8]);
/**
  * @brief The LE_Set_Random_Address command is used by the Host to set the LE
Random Device Address in the Controller (see [Vol 6] Part B, Section 1.3).
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.4)
  * @param Random_Address Random Device Address
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_random_address(uint8_t Random_Address[6]);
/**
  * @brief The LE_Set_Advertising_Parameters command is used by the Host to set the
advertising parameters.
The Advertising_Interval_Min shall be less than or equal to the Advertising_Interval_
Max. The Advertising_Interval_Min and Advertising_Interval_Max
should not be the same value to enable the Controller to determine the best
advertising interval given other activities.
For high duty cycle directed advertising, i.e. when Advertising_Type is 0x01
(ADV_DIRECT_IND, high duty cycle), the Advertising_Interval_Min and Advertising_
Interval_Max parameters are not used and shall be ignored.
The Advertising_Type is used to determine the packet type that is used for
advertising when advertising is enabled.
The Advertising_Interval_Min and Advertising_Interval_Max shall not be set to
less than 0x00A0 (100 ms) if the Advertising_Type is set to 0x02 (ADV_SCAN_
IND) or 0x03 (ADV_NONCONN_IND). The Own_Address_Type determines
if the advertising packets are identified with the Public Device Address of
the device, or a Random Device Address as written by the LE_Set_Random_
Address command.
If directed advertising is performed, i.e. when Advertising_Type is set to 0x01
(ADV_DIRECT_IND, high duty cycle) or 0x04 (ADV_DIRECT_IND, low duty
cycle mode), then the Direct_Address_Type and Direct_Address shall be valid,
otherwise they shall be ignored by the Controller and not used.
The Advertising_Channel_Map is a bit field that indicates the advertising channels
that shall be used when transmitting advertising packets. At least one
channel bit shall be set in the Advertising_Channel_Map parameter.
The Advertising_Filter_Policy parameter shall be ignored when directed advertising
is enabled.
The Host shall not issue this command when advertising is enabled in the Controller;
if it is the Command Disallowed error code shall be used.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.5)
  * @param Advertising_Interval_Min Minimum advertising interval for non-directed advertising.
Range: 0x0020 to 0x4000
Default: N = 0x0800 (1.28 second)
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval for non-directed advertising.
Range: 0x0020 to 0x4000
Default: N = 0x0800 (1.28 seconds)
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Type 0x00 Connectable undirected advertising (ADV_IND) (default)
0x01 Connectable directed advertising (ADV_DIRECT_IND)
0x02 Scannable undirected advertising (ADV_SCAN_IND)
0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
0x04 - 0xFF Reserved for future use
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Direct_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Direct_Address Public Device Address or Random Device Address of the device
to be connected
  * @param Advertising_Channel_Map 00000000b Reserved for future use
xxxxxxx1b Enable channel 37 use
xxxxxx1xb Enable channel 38 use
xxxxx1xxb Enable channel 39 use
00000111b Default (all channels enabled)
  * @param Advertising_Filter_Policy 0x00 Allow Scan Request from Any, Allow Connect Request from Any (default).
0x01 Allow Scan Request from White List Only, Allow Connect Request from Any.
0x02 Allow Scan Request from Any, Allow Connect Request from White List Only.
0x03 Allow Scan Request from White List Only, Allow Connect Request from
    White List Only.
0x04 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertising_parameters(uint16_t Advertising_Interval_Min,
                                             uint16_t Advertising_Interval_Max,
                                             uint8_t Advertising_Type,
                                             uint8_t Own_Address_Type,
                                             uint8_t Direct_Address_Type,
                                             uint8_t Direct_Address[6],
                                             uint8_t Advertising_Channel_Map,
                                             uint8_t Advertising_Filter_Policy);
/**
  * @brief The LE_Read_Advertising_Channel_Tx_Power command is used by the Host
to read the transmit power level used for LE advertising channel packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.6)
  * @param[out] Transmit_Power_Level Size: 1 Octet (signed integer)
Range: -20 <= N <= 10
Units: dBm
Accuracy: +/- 4 dBm
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_advertising_channel_tx_power(uint8_t *Transmit_Power_Level);
/**
  * @brief The LE_Set_Advertising_Data command is used to set the data used in advertising
packets that have a data field.
Only the significant part of the Advertising_Data is transmitted in the advertising
packets, as defined in [Vol 3] Part C, Section 11.,
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.7)
  * @param Advertising_Data_Length The number of significant octets in the following data field
  * @param Advertising_Data 31 octets of data formatted as defined in [Vol 3] Part
C, Section 11.
All octets zero (default).
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertising_data(uint8_t Advertising_Data_Length,
                                       uint8_t Advertising_Data[31]);
/**
  * @brief This command is used to provide data used in Scanning Packets that have a
data field.
Only the significant part of the Scan_Response_Data is transmitted in the
Scanning Packets, as defined in [Vol 3] Part C, Section 11.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.8)
  * @param Scan_Response_Data_Length The number of significant octets in the following data field
  * @param Scan_Response_Data 31 octets of data formatted as defined in [Vol 3] Part
C, Section 11.
All octets zero (default).
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_response_data(uint8_t Scan_Response_Data_Length,
                                         uint8_t Scan_Response_Data[31]);
/**
  * @brief The LE_Set_Advertise_Enable command is used to request the Controller to
start or stop advertising. The Controller manages the timing of advertisements
as per the advertising parameters given in the LE_Set_Advertising_Parameters
command.
The Controller shall continue advertising until the Host issues an LE_Set_Advertise_
Enable command with Advertising_Enable set to 0x00 (Advertising is
disabled) or until a connection is created or until the Advertising is timed out
due to high duty cycle Directed Advertising. In these cases, advertising is then
disabled.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.9)
  * @param Advertising_Enable 0x00 Advertising is disabled (default)
0x01 Advertising is enabled.
0x02 - 0xFF Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertise_enable(uint8_t Advertising_Enable);
/**
  * @brief The LE_Set_Scan_Parameters command is used to set the scan parameters.
The LE_Scan_Type parameter controls the type of scan to perform.
The LE_Scan_Interval and LE_Scan_Window parameters are recommendations
from the Host on how long (LE_Scan_Window) and how frequently
(LE_Scan_Interval) the Controller should scan (See [Vol 6] Part B, Section
4.5.3). The LE_Scan_Window parameter shall always be set to a value smaller
or equal to the value set for the LE_Scan_Interval parameter. If they are set to
the same value scanning should be run continuously.
The Own_Address_Type parameter determines the address used (Public or
Random Device Address) when performing active scan.
The Host shall not issue this command when scanning is enabled in the Controller;
if it is the Command Disallowed error code shall be used.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.10)
  * @param LE_Scan_Type 0x00 Passive Scanning. No SCAN_REQ packets shall be sent.(default)
0x01 Active scanning. SCAN_REQ packets may be sent.
0x02 - 0xFF Reserved for future use
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Scanning_Filter_Policy 0x00 Accept all advertisement packets (default).
Directed advertising packets which are not addressed for this device
shall be ignored.
0x01 Ignore advertisement packets from devices not in the White List Only.
Directed advertising packets which are not addressed for this device
shall be ignored.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_parameters(uint8_t LE_Scan_Type,
                                      uint16_t LE_Scan_Interval,
                                      uint16_t LE_Scan_Window,
                                      uint8_t Own_Address_Type,
                                      uint8_t Scanning_Filter_Policy);
/**
  * @brief The LE_Set_Scan_Enable command is used to start scanning. Scanning is
used to discover advertising devices nearby.
The Filter_Duplicates parameter controls whether the Link Layer shall filter
duplicate advertising reports to the Host, or if the Link Layer should generate
advertising reports for each packet received.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.11)
  * @param LE_Scan_Enable 00x00 Scanning disabled.
0x01 Scanning enabled.
0x02 - 0xFF Reserved for future use.
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_enable(uint8_t LE_Scan_Enable,
                                  uint8_t Filter_Duplicates);
/**
  * @brief TBD
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Initiator_Filter_Policy 0x00 White list is not used to determine which advertiser to connect to.
Peer_Address_Type and Peer_Address shall be used.
0x01 White list is used to determine which advertiser to connect to.
Peer_Address_Type and Peer_Address shall be ignored.
0x02 - 0xFF Reserved for future use.
  * @param Peer_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Peer_Address Public Device Address or Random Device Address of the device
to be connected
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F4
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_create_connection(uint16_t LE_Scan_Interval,
                                    uint16_t LE_Scan_Window,
                                    uint8_t Initiator_Filter_Policy,
                                    uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6],
                                    uint8_t Own_Address_Type,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length);
/**
  * @brief The LE_Create_Connection_Cancel command is used to cancel the LE_Create_
Connection command. This command shall only be issued after the
LE_Create_Connection command has been issued, a Command Status event
has been received for the LE Create Connection command and before the LE
Connection Complete event.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.13)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_create_connection_cancel(void);
/**
  * @brief The LE_Read_White_List_Size command is used to read the total number of
white list entries that can be stored in the Controller.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.14)
  * @param[out] White_List_Size 0x01 - 0xFF Total number of white list entries that can be stored in the Controller.
0x00 Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_white_list_size(uint8_t *White_List_Size);
/**
  * @brief The LE_Clear_White_List command is used to clear the white list stored in the
Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and an LE_Create_Connection
command is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.15)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_clear_white_list(void);
/**
  * @brief The LE_Add_Device_To_White_List command is used to add a single device
to the white list stored in the Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and a create connection command
is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.16)
  * @param Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Address Public Device Address or Random Device Address of the device
to be added to the white list.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_add_device_to_white_list(uint8_t Address_Type,
                                           uint8_t Address[6]);
/**
  * @brief The LE_Remove_Device_From_White_List command is used to remove a single
device from the white list stored in the Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and a create connection command
is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.17)
  * @param Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Address Public Device Address or Random Device Address of the device
to be removed from the white list.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_remove_device_from_white_list(uint8_t Address_Type,
                                                uint8_t Address[6]);
/**
  * @brief The LE_Connection_Update command is used to change the Link Layer connection
parameters of a connection. This command may be issued on both the
master and slave.
The Conn_Interval_Min and Conn_Interval_Max parameters are used to define
the minimum and maximum allowed connection interval. The Conn_Interval_
Min parameter shall not be greater than the Conn_Interval_Max parameter.
The Conn_Latency parameter shall define the maximum allowed connection
latency.
The Supervision_Timeout parameter shall define the link supervision timeout
for the LE link. The Supervision_Timeout in milliseconds shall be larger than (1
+ Conn_Latency) * Conn_Interval_Max * 2, where Conn_Interval_Max is given
in milliseconds.
The Minimum_CE_Length and Maximum_CE_Length are information parameters
providing the Controller with a hint about the expected minimum and maximum
length of the connection events. The Minimum_CE_Length shall be less
than or equal to the Maximum_CE_Length.
The actual parameter values selected by the Link Layer may be different from
the parameter values provided by the Host through this command.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.18)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_connection_update(uint16_t Connection_Handle,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length);
/**
  * @brief The LE_Set_Host_Channel_Classification command allows the Host to specify
a channel classification for data channels based on its "local information". This
classification persists until overwritten with a subsequent LE_Set_Host_Channel_
Classification command or until the Controller is reset using the Reset
command (see [Vol 6] Part B, Section 4.5.8.1).
If this command is used, the Host should send it within 10 seconds of knowing
that the channel classification has changed. The interval between two successive
commands sent shall be at least one second.
This command shall only be used when the local device supports the Master
role.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.19)
  * @param LE_Channel_Map This parameter contains 37 1-bit fields.
The nth such field (in the range 0 to 36) contains the value for the
link layer channel index n.
Channel n is bad = 0.
Channel n is unknown = 1.
The most significant bits are reserved and shall be set to 0.
At least one channel shall be marked as unknown.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_host_channel_classification(uint8_t LE_Channel_Map[5]);
/**
  * @brief The LE_Read_Channel_Map command returns the current Channel_Map for
the specified Connection_Handle. The returned value indicates the state of the
Channel_Map specified by the last transmitted or received Channel_Map (in a
CONNECT_REQ or LL_CHANNEL_MAP_REQ message) for the specified
Connection_Handle, regardless of whether the Master has received an
acknowledgement.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.20)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param[out] LE_Channel_Map This parameter contains 37 1-bit fields.
The nth such field (in the range 0 to 36) contains the value for the
link layer channel index n.
Channel n is unused = 0.
Channel n is used = 1.
The most significant bits are reserved and shall be set to 0.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_channel_map(uint16_t Connection_Handle,
                                   uint8_t LE_Channel_Map[5]);
/**
  * @brief This command requests a list of the used LE features from the remote device.
This command shall return a list of the used LE features. For details see [Vol 6]
Part B, Section 4.6.
This command may be issued on both the master and slave.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.21)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_remote_used_features(uint16_t Connection_Handle);
/**
  * @brief The LE_Encrypt command is used to request the Controller to encrypt the
Plaintext_Data in the command using the Key given in the command and
returns the Encrypted_Data to the Host. The AES-128 bit block cypher is
defined in NIST Publication FIPS-197 (http://csrc.nist.gov/publications/fips/
fips197/fips-197.pdf).
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.22)
  * @param Key 128 bit key for the encryption of the data given in the command.
  * @param Plaintext_Data 128 bit data block that is requested to be encrypted.
  * @param[out] Encrypted_Data 128 bit encrypted data block.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_encrypt(uint8_t Key[16],
                          uint8_t Plaintext_Data[16],
                          uint8_t Encrypted_Data[16]);
/**
  * @brief The LE_Rand command is used to request the Controller to generate 8 octets
of random data to be sent to the Host. The Random_Number shall be generated
according to [Vol 2] Part H, Section 2 if the LE Feature (LL Encryption) is
supported.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.23)
  * @param[out] Random_Number Random Number
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_rand(uint8_t Random_Number[8]);
/**
  * @brief The LE_Start_Encryption command is used to authenticate the given encryption
key associated with the remote device specified by the connection handle,
and once authenticated will encrypt the connection. The parameters are as
defined in [Vol 3] Part H, Section 2.4.4.
If the connection is already encrypted then the Controller shall pause connection
encryption before attempting to authenticate the given encryption key, and
then re-encrypt the connection. While encryption is paused no user data shall
be transmitted.
On an authentication failure, the connection shall be automatically disconnected
by the Link Layer. If this command succeeds, then the connection shall
be encrypted.
This command shall only be used when the local device's role is Master.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.24)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Random_Number 64 bit random number.
  * @param Encrypted_Diversifier 16 bit encrypted diversifier.
  * @param Long_Term_Key 128 bit long term key.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_start_encryption(uint16_t Connection_Handle,
                                   uint8_t Random_Number[8],
                                   uint16_t Encrypted_Diversifier,
                                   uint8_t Long_Term_Key[16]);
/**
  * @brief The LE_Long_Term_Key_Request_Reply command is used to reply to an LE
Long Term Key Request event from the Controller, and specifies the
Long_Term_Key parameter that shall be used for this Connection_Handle. The
Long_Term_Key is used as defined in [Vol 6] Part B, Section 5.1.3.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.25)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Long_Term_Key 128 bit long term key.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_long_term_key_request_reply(uint16_t Connection_Handle,
                                              uint8_t Long_Term_Key[16]);
/**
  * @brief The LE_Long_Term_Key_Request_Negative_Reply command is used to reply
to an LE Long Term Key Request event from the Controller if the Host cannot
provide a Long Term Key for this Connection_Handle.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.26)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_long_term_key_requested_negative_reply(uint16_t Connection_Handle);
/**
  * @brief The LE_Read_Supported_States command reads the states and state combinations
that the link layer supports. See [Vol 6] Part B, Section 1.1.1.
LE_States is an 8-octet bit field. If a bit is set to 1 then this state or state combination
is supported by the Controller. Multiple bits in LE_States may be set to 1
to indicate support for multiple state and state combinations.
All the Advertising type with the Initiate State combinations shall be set only if
the corresponding Advertising types and Master Role combination are set.
All the Scanning types and the Initiate State combinations shall be set only if
the corresponding Scanning types and Master Role combination are set.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.27)
  * @param[out] LE_States 0x0000000000000000
Reserved for future use
(No state combinations supported).
0x0000000000000001 Non-connectable Advertising State supported.
0x0000000000000002 Scannable Advertising State supported.
0x0000000000000004 Connectable Advertising State supported.
0x0000000000000008 Directed Advertising State supported.
0x0000000000000010 Passive Scanning State supported.
0x0000000000000020 Active Scanning State supported.
0x0000000000000040
Initiating State supported.
Connection State in the Master Role supported is also supported.
0x0000000000000080 Connection State in the Slave Role supported.
0x0000000000000100
Non-connectable Advertising State and Passive Scanning State combination
supported.
0x0000000000000200
Scannable Advertising State and Passive Scanning State combination supported.
0x0000000000000400
Connectable Advertising State and Passive Scanning State combination
supported.
0x0000000000000800
Directed Advertising State and Passive Scanning State combination supported.
0x0000000000001000
Non-connectable Advertising State and Active Scanning State combination
supported.
0x0000000000002000
Scannable Advertising State and Active Scanning State combination supported.
0x0000000000004000
Connectable Advertising State and Active Scanning State combination supported.
0x0000000000008000
Directed Advertising State and Active Scanning State combination supported.
0x0000000000010000
Non-connectable Advertising State and Initiating State combination supported.
0x0000000000020000 Scannable Advertising State and Initiating State combination supported
0x0000000000040000 Non-connectable Advertising State and Master Role combination supported.
0x0000000000080000 Scannable Advertising State and Master Role combination supported.
0x0000000000100000 Non-connectable Advertising State and Slave Role combination supported.
0x0000000000200000 Scannable Advertising State and Slave Role combination supported.
0x0000000000400000 Passive Scanning State and Initiating State combination supported.
When the LE_Read_Supported_States command has completed, a Command
Complete event will be generated.
0x0000000000800000 Active Scanning State and Initiating State combination supported.
0x0000000001000000 Passive Scanning State and Master Role combination supported.
0x0000000002000000 Active Scanning State and Master Role combination supported.
0x0000000004000000 Passive Scanning state and Slave Role combination supported.
0x0000000008000000 Active Scanning state and Slave Role combination supported.
0x0000000010000000
Initiating State and Master Role combination supported.
Master Role and Master Role combination is also supported.
0xFFFFFFFFE0000000 Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_supported_states(uint8_t LE_States[8]);
/**
 * @}
 */
/**
 *@defgroup HCI_TESTING_API HCI TESTING API
 *@brief HCI TESTING API layer.
 *@{
 */
/**
  * @brief This command is used to start a test where the DUT receives test reference
packets at a fixed interval. The tester generates the test reference packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.28)
  * @param RX_Frequency N = (F - 2402) / 2
Range: 0x00 - 0x27. Frequency Range : 2402 MHz to 2480 MHz
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_receiver_test(uint8_t RX_Frequency);
/**
  * @brief This command is used to start a test where the DUT generates test reference
packets at a fixed interval. The Controller shall transmit at maximum power.
An LE Controller supporting the LE_Transmitter_Test command shall support
Packet_Payload values 0x00, 0x01 and 0x02. An LE Controller may support
other values of Packet_Payload.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.29)
  * @param TX_Frequency N = (F - 2402) / 2
Range: 0x00 - 0x27. Frequency Range : 2402 MHz to 2480 MHz
  * @param Length_Of_Test_Data 0x00-0x25 Length in bytes of payload data in each packet
0x26-0xFF Reserved for future use
  * @param Packet_Payload 0x00 Pseudo-Random bit sequence 9
0x01 Pattern of alternating bits '11110000'
0x02 Pattern of alternating bits '10101010'
0x03 Pseudo-Random bit sequence 15
0x04 Pattern of All '1' bits
0x05 Pattern of All '0' bits
0x06 Pattern of alternating bits '00001111'
0x07 Pattern of alternating bits '0101'
0x08-0xFF Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_transmitter_test(uint8_t TX_Frequency,
                                   uint8_t Length_Of_Test_Data,
                                   uint8_t Packet_Payload);
/**
  * @brief This command is used to stop any test which is in progress. The Number_
Of_Packets for a transmitter test shall be reported as 0x0000. The Number_
Of_Packets is an unsigned number and contains the number of received
packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.30)
  * @param[out] Number_Of_Packets Number of packets received
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_test_end(uint16_t *Number_Of_Packets);
/**
 * @}
 */
/**
 *@defgroup HAL_API HAL API
 *@brief HAL API layer.
 *@{
 */
/**
  * @brief This command writes a value to a low level configure data structure. It is useful to setup
directly some low level parameters for the system in the runtime.
  * @param Offset Offset of the element in the configuration data structure
which has to be written. The valid offsets are:
0x00 = CONFIG_DATA_PUBADDR_OFFSET,
0x06 = CONFIG_DATA_DIV_OFFSET,
0x08 = CONFIG_DATA_ER_OFFSET,
0x18 = CONFIG_DATA_IR_OFFSET,
0x2C = LL_WITHOUT_HOST,
0x2D = ROLE
  * @param Length Length of data to be written
  * @param Value Data to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_write_config_data(uint8_t Offset,
                                     uint8_t Length,
                                     uint8_t Value[]);
/**
  * @brief This command requests the value in the low level configure data structure.
The number of read bytes changes for different Offset. 
  * @param Offset Offset of the element in the configuration data structure
which has to be written. The valid offsets are:
0x00 = CONFIG_DATA_PUBADDR_OFFSET,
0x06 = CONFIG_DATA_DIV_OFFSET,
0x08 = CONFIG_DATA_ER_OFFSET,
0x18 = CONFIG_DATA_IR_OFFSET,
0x2C = LL_WITHOUT_HOST,
0x2D = ROLE
0x80 = RANDOM_ADDRESS
  * @param[out] Data_Length Length of Data in octets
  * @param[out] Data Data field associated with Offset parameter
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_read_config_data(uint8_t Offset,
                                    uint8_t *Data_Length,
                                    uint8_t Data[]);
/**
  * @brief This command sets the TX power level of the BlueNRG-MS. By controlling the
EN_HIGH_POWER and the PA_LEVEL, the combination of the 2 determines the output
power level (dBm). 
When the system starts up or reboots, the default TX power level will be used, which is the
maximum value of 8 dBm. Once this command is given, the output power will be changed
instantly, regardless if there is Bluetooth communication going on or not. For example, for
debugging purpose, the BlueNRG-MS can be set to advertise all the time. And use this
command to observe the signal strength changing.
The system will keep the last received TX power level from the command, i.e. the 2nd
command overwrites the previous TX power level. The new TX power level remains until
another Set TX Power command, or the system reboots.
  * @param En_High_Power Can be only 0 or 1. Set high power bit on or off.
  * @param PA_Level PA Level.
If En_High_Power=0 
0 = -18 dBm,
1 = -15 dBm,
2 = -12 dBm,
3 = -9 dBm,
4 = -6 dBm,
5 = -2 dBm,
6 =  0 dBm,
7 =  5 dBm.
If En_High_Power=1 
0 = -14 dBm,
1 = -11 dBm,
2 = -8 dBm,
3 = -5 dBm,
4 = -2 dBm,
5 =  2 dBm,
6 =  4 dBm,
7 =  8 dBm
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_set_tx_power_level(uint8_t En_High_Power,
                                      uint8_t PA_Level);
/**
  * @brief Put the device in standby mode.
Normally the BlueNRG will automatically enter sleep mode to save power. This command puts the 
device into the Standby mode instead of the sleep mode. The difference is that, in sleep mode, 
the device can still wake up itself with the internal timer. But in standby mode, this timer is 
disabled. So the only possibility to wake up the device is by external signals, e.g. a HCI command 
sent via SPI bus. 
Based on the measurement, the current consumption under sleep mode is ~2 uA. And this
value is ~1.5 uA in standby mode.
The command is only accepted when there is no other Bluetooth activity. 
Otherwise an error code ERR_COMMAND_DISALLOWED will be returned.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_device_standby(void);
/**
  * @brief This command returns the number of packets sent in Direct Test Mode.
When the Direct TX test is started, a 32-bit counter is used to count how many packets have been transmitted. 
This command can be used to check how many packets have been sent during the Direct TX test.
The counter starts from 0 and counts upwards. The counter can wrap and start from 0 again. 
The counter is not cleared until the next Direct TX test starts. 
  * @param[out] Number_Of_Packets Number of packets sent during the last Direct TX test.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_le_tx_test_packet_number(uint32_t *Number_Of_Packets);
/**
  * @brief This command starts a carrier frequency, i.e. a tone, on a specific channel. The frequency
sine wave at the specific channel may be used for debugging purpose only. The channel ID
is a parameter from 0x00 to 0x27 for the 40 BLE channels, e.g. 0x00 for 2.402 GHz, 0x01
for 2.404 GHz etc.
This command should not be used when normal Bluetooth activities are ongoing.
The tone should be stopped by @ref aci_hal_tone_stop command.
  * @param RF_Channel BLE Channel ID, from 0x00 to 0x27 meaning (2.402 + 2*0xXX) GHz
Device will continuously emit 0s, that means that the tone
will be at the channel center frequency less the maximum
frequency deviation (250kHz).
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_tone_start(uint8_t RF_Channel);
/**
  * @brief This command is used to stop the previously started @ref aci_hal_tone_start command.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_hal_tone_stop(void);
/**
 * @}
 */
/**
 *@defgroup GAP_API GAP API
 *@brief GAP API layer.
 *@{
 */
/**
  * @brief Put the device in non-discoverable mode. This command will disable the LL advertising and
put the device in standby state.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_non_discoverable(void);
/**
  * @brief Put the device in limited discoverable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.2.3). The device will be discoverable for maximum period of TGAP
(lim_adv_timeout) = 180 seconds (from errata). The advertising can be disabled at any time
by issuing Aci_Gap_Set_Non_Discoverable command.
The Adv_Interval_Min and Adv_Interval_Max parameters are optional. If both are set to 0,
the GAP will use default values for adv intervals for limited discoverable mode (250 ms
and 500 ms respectively).
To allow a fast connection, the host can set Local_Name, Service_Uuid_List,
Slave_Conn_Interval_Min and Slave_Conn_Interval_Max. If provided, these data will be 
inserted into the advertising packet payload as AD data. These parameters are optional
in this command. These values can be set in advertised data using GAP_Update_Adv_Data
command separately.
The total size of data in advertising packet cannot exceed 31 bytes.
With this command, the BLE Stack will also add automatically the following
standard AD types:
- AD Flags
- Power Level
When advertising timeout happens (i.e. limited discovery period has elapsed), controller generates
@ref aci_gap_limited_discoverable_event event. 
  * @param Advertising_Type 0x00 Connectable undirected advertising (ADV_IND) (default)
0x02 Scannable undirected advertising (ADV_SCAN_IND)
0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
0x04 - 0xFF Reserved for future use
  * @param Advertising_Interval_Min Minimum advertising interval for non-directed advertising.
Range: 0x0020 to 0x4000
Default: N = 0x0800 (1.28 second)
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval for non-directed advertising.
Range: 0x0020 to 0x4000
Default: N = 0x0800 (1.28 seconds)
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Advertising_Filter_Policy 0x00 Allow Scan Request from Any, Allow Connect Request from Any (default).
0x01 Allow Scan Request from White List Only, Allow Connect Request from Any.
0x02 Allow Scan Request from Any, Allow Connect Request from White List Only.
0x03 Allow Scan Request from White List Only, Allow Connect Request from
    White List Only.
0x04 - 0xFF Reserved for future use.
  * @param Local_Name_Length Length of the Local name string in octets.
If length is set to 0x00, Local_Name parameter should not be used.
  * @param Local_Name Local name of the device.
This is an ASCII string without NULL character.
  * @param Service_Uuid_length Length of the Service Uuid List in octets.
If there is no service to be advertised, set this field to 0x00.
  * @param Service_Uuid_List This is the list of the UUIDs AD Types as defined in Volume 3,
Section 11.1.1 of GAP Specification.
  * @param Slave_Conn_Interval_Min Slave connection internal minimum value. 
Connection interval is defined in the following manner:
connIntervalmin = Slave_Conn_Interval_Min * 1.25ms 
Slave_Conn_Interval_Min range: 0x0006 to 0x0C80 
Value of 0xFFFF indicates no specific minimum.
  * @param Slave_Conn_Interval_Max Slave connection internal maximum value.
ConnIntervalmax = Slave_Conn_Interval_Max * 1.25ms
Slave_Conn_Interval_Max range: 0x0006 to 0x0C80
Slave_ Conn_Interval_Max shall be equal to or greater than the Slave_Conn_Interval_Min.
Value of 0xFFFF indicates no specific maximum.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_limited_discoverable(uint8_t Advertising_Type,
                                            uint16_t Advertising_Interval_Min,
                                            uint16_t Advertising_Interval_Max,
                                            uint8_t Own_Address_Type,
                                            uint8_t Advertising_Filter_Policy,
                                            uint8_t Local_Name_Length,
                                            uint8_t Local_Name[],
                                            uint8_t Service_Uuid_length,
                                            uint8_t Service_Uuid_List[],
                                            uint16_t Slave_Conn_Interval_Min,
                                            uint16_t Slave_Conn_Interval_Max);
/**
  * @brief Put the device in general discoverable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.2.4). The device will be discoverable until the host issues 
the @ref aci_gap_set_non_discoverable command. The Adv_Interval_Min and Adv_Interval_Max
parameters are optional. If both are set to 0, the GAP uses the default values for adv
intervals for general discoverable mode.
When using connectable undirected advertising events:
- Adv_Interval_Min = 30 ms 
- Adv_Interval_Max = 60 ms
When using non-connectable advertising events or scannable undirected advertising events:
- Adv_Interval_Min = 100 ms 
- Adv_Interval_Max = 150 ms 
Host can set the Local Name, a Service UUID list and the Slave Connection Interval Range.
If provided, these data will be inserted into the advertising packet payload as AD data.
These parameters are optional in this command. These values can be also set using
aci_gap_update_adv_data() separately.
The total size of data in advertising packet cannot exceed 31 bytes.
With this command, the BLE Stack will also add automatically the following standard
AD types:
- AD Flags
- TX Power Level
  * @param Advertising_Type 0x00 Connectable undirected advertising (ADV_IND) (default)
0x02 Scannable undirected advertising (ADV_SCAN_IND)
0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
0x04 - 0xFF Reserved for future use
  * @param Advertising_Interval_Min Minimum advertising interval for non-directed advertising.
Range: 0x0020 to 0x4000
Default: N = 0x0800 (1.28 second)
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval for non-directed advertising.
Range: 0x0020 to 0x4000
Default: N = 0x0800 (1.28 seconds)
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Advertising_Filter_Policy 0x00 Allow Scan Request from Any, Allow Connect Request from Any (default).
0x01 Allow Scan Request from White List Only, Allow Connect Request from Any.
0x02 Allow Scan Request from Any, Allow Connect Request from White List Only.
0x03 Allow Scan Request from White List Only, Allow Connect Request from
    White List Only.
0x04 - 0xFF Reserved for future use.
  * @param Local_Name_Length Length of the Local name string in octets.
If length is set to 0x00, Local_Name parameter should not be used.
  * @param Local_Name Local name of the device.
This is an ASCII string without NULL character.
  * @param Service_Uuid_length Length of the Service Uuid List in octets.
If there is no service to be advertised, set this field to 0x00.
  * @param Service_Uuid_List This is the list of the UUIDs AD Types as defined in Volume 3,
Section 11.1.1 of GAP Specification.
  * @param Slave_Conn_Interval_Min Slave connection internal minimum value. 
Connection interval is defined in the following manner:
connIntervalmin = Slave_Conn_Interval_Min * 1.25ms 
Slave_Conn_Interval_Min range: 0x0006 to 0x0C80 
Value of 0xFFFF indicates no specific minimum.
  * @param Slave_Conn_Interval_Max Slave connection internal maximum value.
ConnIntervalmax = Slave_Conn_Interval_Max * 1.25ms
Slave_Conn_Interval_Max range: 0x0006 to 0x0C80
Slave_ Conn_Interval_Max shall be equal to or greater than the Slave_Conn_Interval_Min.
Value of 0xFFFF indicates no specific maximum.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_discoverable(uint8_t Advertising_Type,
                                    uint16_t Advertising_Interval_Min,
                                    uint16_t Advertising_Interval_Max,
                                    uint8_t Own_Address_Type,
                                    uint8_t Advertising_Filter_Policy,
                                    uint8_t Local_Name_Length,
                                    uint8_t Local_Name[],
                                    uint8_t Service_Uuid_length,
                                    uint8_t Service_Uuid_List[],
                                    uint16_t Slave_Conn_Interval_Min,
                                    uint16_t Slave_Conn_Interval_Max);
/**
  * @brief Set the device in direct connectable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.3.3). Device uses direct connectable mode to advertise using 
cycle advertisement events or Low Duty cycle advertisement events and the address as
either High Duty what is specified in the Own Address Type parameter. The Advertising 
the command specifies the type of the advertising used. If the privacy is enabled, the
Type parameter in reconnection address is used for advertising, otherwise the address 
of the type specified in OwnAddrType is used.
The device will be in directed connectable mode only for 1.28 seconds. If no connection 
is established within this duration, the device enters non discoverable mode and 
advertising will have to be again enabled explicitly.
The controller generates a @ref hci_le_connection_complete_event event with the status set to
HCI_DIRECTED_ADV_TIMEOUT if the connection was not established and 0x00 if the 
connection was successfully established.
  * @param Own_Address_Type 0x00: Public device address (default)
0x01: Random device address
  * @param Directed_Advertising_Type Type of directed advertising.
0x01: High Duty Cycle Directed Advertising,
0x04: Low Duty Cycle Directed Advertising
  * @param Direct_Address_Type 0x00: Public device address (default)
0x01: Random device address
  * @param Direct_Address Initiator Bluetooth address
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_direct_connectable(uint8_t Own_Address_Type,
                                          uint8_t Directed_Advertising_Type,
                                          uint8_t Direct_Address_Type,
                                          uint8_t Direct_Address[6]);
/**
  * @brief Set the IO capabilities of the device. This command has to be given only when the device is
not in a connected state.

  * @param IO_Capability IO capability of the device:
0x00: 'IO_CAP_DISPLAY_ONLY',
0x01: 'IO_CAP_DISPLAY_YES_NO',
0x02: 'KEYBOARD_ONLY',
0x03: 'IO_CAP_NO_INPUT_NO_OUTPUT',
0x04: 'IO_CAP_KEYBOARD_DISPLAY
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_io_capability(uint8_t IO_Capability);
/**
  * @brief Set the authentication requirements for the device. If the OOB_Enable is set to 0, the
following 16 octets of OOB_Data will be ignored on reception. This command has to be
given only when the device is not in a connected state.
  * @param MITM_Mode 0 = MITM protection not required,
1 = MITM protection required
  * @param OOB_Enable 0 = OOB data is not available,
1 = OOB data is available and specified in OOB_Data
  * @param OOB_Data Out-Of-Band data
  * @param Min_Encryption_Key_Size Minimum size of the encryption key to be used during the pairing process
  * @param Max_Encryption_Key_Size Maximum size of the encryption key to be used during the pairing process
  * @param Use_Fixed_Pin If set to 0x00, then during the pairing process
the application will not be requested for a pin (Fixed_Pin will be used).
If set to 0x01, then during pairing process if a
passkey is required the application will be
notified
  * @param Fixed_Pin Fixed pin to be used during pairing if MIMT protection is enabled.
Any random value between 0 to 999999
  * @param Bonding_Mode Only if bonding is enabled (0x01), the bonding
information is stored in flash
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_authentication_requirement(uint8_t MITM_Mode,
                                                  uint8_t OOB_Enable,
                                                  uint8_t OOB_Data[16],
                                                  uint8_t Min_Encryption_Key_Size,
                                                  uint8_t Max_Encryption_Key_Size,
                                                  uint8_t Use_Fixed_Pin,
                                                  uint32_t Fixed_Pin,
                                                  uint8_t Bonding_Mode);
/**
  * @brief Set the authorization requirements of the device. This command has to be given only when
the device is not in a connected state.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Authorization_Enable 0x00: Authorization not required (default)
0x01: Authorization required. This enables the authorization in the device and when a remote device tries to connect to GATT server,
ACI_Gap_Authorization_Request event will be sent to the Host in this case.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_authorization_requirement(uint16_t Connection_Handle,
                                                 uint8_t Authorization_Enable);
/**
  * @brief This command should be send by the host in response to @ref aci_gap_pass_key_req_event
event. The command parameter contains the pass key which will be used during the pairing
process.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Pass_Key Pass key that will be used during the pairing process. 
Must be a number between 0 and 999999.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_pass_key_resp(uint16_t Connection_Handle,
                                 uint32_t Pass_Key);
/**
  * @brief Authorize a device to access attributes. This command should be send by the host in
response to @ref aci_gap_authorization_req_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Authorize authorization response:
0x01 : Authorize (accept connection)
0x02 : Reject (reject connection)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_authorization_resp(uint16_t Connection_Handle,
                                      uint8_t Authorize);
/**
  * @brief Initialize the GAP layer. Register the GAP service with the GATT.
All the standard GAP characteristics will also be added:
- Device Name
- Appearance
- Peripheral Preferred Connection Parameters (peripheral role only)
  * @param Role Bitmap of allowed roles:
0x01 : Peripheral
0x02 : Broadcaster
0x04 : Central
0x08 : Observer
  * @param privacy_enabled 0x00: Privacy is not enabled.
0x01: Privacy is enabled.
  * @param device_name_char_len Length of the device name characteristic
  * @param[out] Service_Handle Handle of the GAP service
  * @param[out] Dev_Name_Char_Handle Device Name Characteristic handle
  * @param[out] Appearance_Char_Handle Appearance Characteristic handle
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_init(uint8_t Role,
                        uint8_t privacy_enabled,
                        uint8_t device_name_char_len,
                        uint16_t *Service_Handle,
                        uint16_t *Dev_Name_Char_Handle,
                        uint16_t *Appearance_Char_Handle);
/**
  * @brief Put the device into non connectable mode. This mode does not support connection. The
privacy setting done in the @ref aci_gap_init command plays a role in deciding the valid 
parameters for this command.
  * @param Advertising_Event_Type 0x02 = Scannable undirected advertising (ADV_SCAN_IND)
0x03 = Non connectable undirected advertising (ADV_NONCONN_IND)
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_non_connectable(uint8_t Advertising_Event_Type,
                                       uint8_t Own_Address_Type);
/**
  * @brief Put the device into undirected connectable mode.
If privacy is enabled in the device, a resolvable private address is generated and used as the 
advertiser's address. If not, the address of the type specified in own_addr_type is used for
advertising.
  * @param Adv_Filter_Policy 0x00 Allow Scan Request from Any, Allow Connect Request from Any.
0x03 Allow Scan Request from White List Only, Allow Connect Request from
    White List Only.
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_undirected_connectable(uint8_t Adv_Filter_Policy,
                                              uint8_t Own_Address_Type);
/**
  * @brief Send a slave security request to the master.
This command has to be issued to notify the master of the security requirements of the slave.
The master may encrypt the link, initiate the pairing procedure, or reject the request.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Bonding 0x00 = No bonding,
0x01 = Bonding required
  * @param MITM_Protection 0 = MITM protection not required,
1 = MITM protection required
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_slave_security_req(uint16_t Connection_Handle,
                                      uint8_t Bonding,
                                      uint8_t MITM_Protection);
/**
  * @brief This command can be used to update the advertising data for a particular AD type. If the AD
type specified does not exist, then it is added to the advertising data. If the overall
advertising data length is more than 31 octets after the update, then the command is
rejected and the old data is retained.
  * @param AdvDataLen Length of AdvData in octets
  * @param AdvData Advertising data used by the device while advertising.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_update_adv_data(uint8_t AdvDataLen,
                                   uint8_t AdvData[]);
/**
  * @brief This command can be used to delete the specified AD type from the advertisement data if
present.
  * @param ADType One of the AD types like in Bluetooth specification (see volume 3, Part C, 11.1)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_delete_ad_type(uint8_t ADType);
/**
  * @brief This command can be used to get the current security settings of the device.
  * @param[out] MITM_Mode 0 = MITM protection not required,
1 = MITM protection required
  * @param[out] Bonding_Mode Only if bonding is enabled (0x01), the bonding
information is stored in flash
  * @param[out] OOB_Enable 0 = OOB data is not available,
1 = OOB data is available and specified in OOB_Data
  * @param[out] Passkey_required 0x00 = Passkey not required,
0x01 = Fixed pin is present which is being used,
0x02 = Passkey required for pairing. An event will be generated when required.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_get_security_level(uint8_t *MITM_Mode,
                                      uint8_t *Bonding_Mode,
                                      uint8_t *OOB_Enable,
                                      uint8_t *Passkey_required);
/**
  * @brief It allows masking events from the GAP. The default configuration is all the events masked.
  * @param GAP_Evt_Mask 0x0000 No events specified,
0x0001 ACI_GAP_LIMITED_DISCOVERABLE_EVENT,
0x0002 ACI_GAP_PAIRING_COMPLETE_EVENT,
0x0004 ACI_GAP_PASS_KEY_REQ_EVENT,
0x0008 ACI_GAP_AUTHORIZATION_REQ_EVENT,
0x0010 ACI_GAP_SLAVE_SECURITY_INITIATED_EVENT,
0x0020 ACI_GAP_BOND_LOST_EVENT,
0x0080 ACI_GAP_PROC_COMPLETE_EVENT,
0x0100 ACI_L2CAP_CONNECTION_UPDATE_REQ_EVENT,
0x0200 ACI_L2CAP_CONNECTION_UPDATE_RESP_EVENT,
0x0400 ACI_L2CAP_PROC_TIMEOUT_EVENT,
0x0800 ACI_GAP_ADDR_NOT_RESOLVED_EVENT,
0xFFFF Default
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_event_mask(uint16_t GAP_Evt_Mask);
/**
  * @brief Add addresses of bonded devices into the controller's whitelist.
The command will return an error if there are no devices in the database or if it was  
unable to add the device into the whitelist.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_configure_whitelist(void);
/**
  * @brief Command the controller to terminate the connection.
A @ref hci_disconnection_complete_event event will be generated when the link is disconnected.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Reason Authentication Failure error code (0x05), Other End Terminated Connection error codes (0x13-0x15),
Unsupported Remote Feature error code(0x1A) and Pairing with Unit Key Not Supported error code (0x29)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_terminate(uint16_t Connection_Handle,
                             uint8_t Reason);
/**
  * @brief Clear the security database. All the devices in the security database will be removed.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_clear_security_db(void);
/**
  * @brief Allows the security manager to complete the pairing procedure and re-bond with the master.
This command should be given by the application when it receives the
ACI_GAP_BOND_LOST_EVENT if it wants the re-bonding to happen successfully. If this
command is not given on receiving the event, the bonding procedure will timeout.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_allow_rebond(uint16_t Connection_Handle);
/**
  * @brief Start the limited discovery procedure. The controller is commanded to start active scanning.
When this procedure is started, only the devices in limited discoverable mode are returned
to the upper layers.
The procedure is terminated when either the upper layers issue a command to terminate 
the procedure by issuing the command @ref aci_gap_terminate_gap_proc with the procedure 
code set to 0x01 or a timeout happens. When the procedure is terminated due to any of the 
above  reasons, @ref aci_gap_proc_complete_event event is returned with the procedure code
set to 0x01.
The device found when the procedure is ongoing is returned to the upper layers through the
event @ref hci_le_advertising_report_event.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_limited_discovery_proc(uint16_t LE_Scan_Interval,
                                                uint16_t LE_Scan_Window,
                                                uint8_t Own_Address_Type,
                                                uint8_t Filter_Duplicates);
/**
  * @brief Start the general discovery procedure. The controller is commanded to start active
scanning. The procedure is terminated when  either the upper layers issue a command
to terminate the procedure by issuing the command @ref aci_gap_terminate_gap_proc
with the procedure code set to 0x02 or a timeout happens. When the procedure is
terminated due to any of the above reasons, @ref aci_gap_proc_complete_event event
is returned with the procedure code set to 0x02. The device found when the procedure
is ongoing is returned to @ref hci_le_advertising_report_event.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_general_discovery_proc(uint16_t LE_Scan_Interval,
                                                uint16_t LE_Scan_Window,
                                                uint8_t Own_Address_Type,
                                                uint8_t Filter_Duplicates);
/**
  * @brief Start the name discovery procedure. A LE_Create_Connection call will be made to the
controller by GAP with the initiator filter policy set to "ignore whitelist and process
connectable advertising packets only for the specified device". Once a connection is
established, GATT procedure is started to read the device name characteristic. When the
read is completed (successfully or unsuccessfully), a @ref aci_gap_proc_complete_event
event is given to the upper layer. The event also contains the name of the device if the
device name was read successfully.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Peer_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Peer_Address Public Device Address or Random Device Address of the device
to be connected
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_name_discovery_proc(uint16_t LE_Scan_Interval,
                                             uint16_t LE_Scan_Window,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Own_Address_Type,
                                             uint16_t Conn_Interval_Min,
                                             uint16_t Conn_Interval_Max,
                                             uint16_t Conn_Latency,
                                             uint16_t Supervision_Timeout,
                                             uint16_t Minimum_CE_Length,
                                             uint16_t Maximum_CE_Length);
/**
  * @brief Start the auto connection establishment procedure. The devices specified are added to the
white list of the controller and a LE_Create_Connection call will be made to the controller by
GAP with the initiator filter policy set to "use whitelist to determine which advertiser to
connect to". When a command is issued to terminate the procedure by upper layer, a
LE_Create_Connection_Cancel call will be made to the controller by GAP.
The procedure is terminated when either a connection is successfully established with one of
the specified devices in the white list or the procedure is explicitly terminated by issuing
the command @ref aci_gap_terminate_gap_proc with the procedure code set to 0x08. A
@ref aci_gap_proc_complete_event event is returned with the procedure code set to 0x08.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_auto_connection_establish_proc(uint16_t LE_Scan_Interval,
                                                        uint16_t LE_Scan_Window,
                                                        uint8_t Own_Address_Type,
                                                        uint16_t Conn_Interval_Min,
                                                        uint16_t Conn_Interval_Max,
                                                        uint16_t Conn_Latency,
                                                        uint16_t Supervision_Timeout,
                                                        uint16_t Minimum_CE_Length,
                                                        uint16_t Maximum_CE_Length,
                                                        uint8_t Num_of_Whitelist_Entries,
                                                        Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Start a general connection establishment procedure. The host enables scanning in the
controller with the scanner filter policy set to "accept all advertising packets" and from the
scanning results, all the devices are sent to the upper layer using the event
LE_Advertising_Report. The upper layer then has to select one of the devices to which it
wants to connect by issuing the command @ref aci_gap_create_connection. If privacy is
enabled, then either a private resolvable address or a non resolvable address, based on the
address type specified in the command is set as the scanner address but the gap create
connection always uses a private resolvable address if the general connection
establishment procedure is active.
The procedure is terminated when a connection is established or the upper layer terminates
the procedure by issuing the command @ref aci_gap_terminate_gap_proc with the procedure
code set to 0x10. On completion of the procedure a @ref aci_gap_proc_complete_event event
is generated with the procedure code set to 0x10.
  * @param LE_Scan_Type 0x00 Passive Scanning. No SCAN_REQ packets shall be sent.(default)
0x01 Active scanning. SCAN_REQ packets may be sent.
0x02 - 0xFF Reserved for future use
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_general_connection_establish_proc(uint8_t LE_Scan_Type,
                                                           uint16_t LE_Scan_Interval,
                                                           uint16_t LE_Scan_Window,
                                                           uint8_t Own_Address_Type,
                                                           uint8_t Filter_Duplicates);
/**
  * @brief Start a selective connection establishment procedure. The GAP adds the specified device
addresses into white list and enables scanning in the controller with the scanner filter policy
set to "accept packets only from devices in whitelist". All the devices found are sent to the
upper layer by the event EVT_LE_ADVERTISING_REPORT. The upper layer then has to select one of
the devices to which it wants to connect by issuing the command @ref aci_gap_create_connection.
On completion of the procedure a @ref aci_gap_proc_complete_event event is generated with
the procedure code set to 0x20. The procedure is terminated when a connection is established
or the upper layer terminates the procedure by issuing the command
@ref aci_gap_terminate_gap_proc with the procedure code set to 0x20.
  * @param LE_Scan_Type 0x00 Passive Scanning. No SCAN_REQ packets shall be sent.(default)
0x01 Active scanning. SCAN_REQ packets may be sent.
0x02 - 0xFF Reserved for future use
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_selective_connection_establish_proc(uint8_t LE_Scan_Type,
                                                             uint16_t LE_Scan_Interval,
                                                             uint16_t LE_Scan_Window,
                                                             uint8_t Own_Address_Type,
                                                             uint8_t Filter_Duplicates,
                                                             uint8_t Num_of_Whitelist_Entries,
                                                             Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Start the direct connection establishment procedure. A LE_Create_Connection call will be
made to the controller by GAP with the initiator filter policy set to "ignore whitelist and
process connectable advertising packets only for the specified device". The procedure can
be terminated explicitly by the upper layer by issuing the command
@ref aci_gap_terminate_gap_proc. When a command is issued to terminate the
procedure by upper layer, a @ref hci_le_create_connection_cancel call will be made to the
controller by GAP.
On termination of the procedure, a @ref hci_le_connection_complete_event event is returned. The  
procedure can be explicitly terminated by the upper layer by issuing the command
@ref aci_gap_terminate_gap_proc with the procedure_code set to 0x40.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Peer_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Peer_Address Public Device Address or Random Device Address of the device
to be connected
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F4
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_create_connection(uint16_t LE_Scan_Interval,
                                     uint16_t LE_Scan_Window,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6],
                                     uint8_t Own_Address_Type,
                                     uint16_t Conn_Interval_Min,
                                     uint16_t Conn_Interval_Max,
                                     uint16_t Conn_Latency,
                                     uint16_t Supervision_Timeout,
                                     uint16_t Minimum_CE_Length,
                                     uint16_t Maximum_CE_Length);
/**
  * @brief Terminate the specified GATT procedure. An @ref aci_gap_proc_complete_event event is
returned with the procedure code set to the corresponding procedure.
  * @param Procedure_Code 0x00 No events specified,
0x01 LIMITED_DISCOVERY_PROC,
0x02 GENERAL_DISCOVERY_PROC,
0x04 NAME_DISCOVERY_PROC,
0x08 AUTO_CONNECTION_ESTABLISHMENT_PROC,
0x10 GENERAL_CONNECTION_ESTABLISHMENT_PROC,
0x20 SELECTIVE_CONNECTION_ESTABLISHMENT_PROC,
0x40 DIRECT_CONNECTION_ESTABLISHMENT_PROC
0x80 OBSERVATION_PROC
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_terminate_gap_proc(uint8_t Procedure_Code);
/**
  * @brief Start the connection update procedure. A @ref hci_le_connection_update call is be made to 
thecontroller by GAP.
On completion of the procedure, an @ref hci_le_connection_update_complete_event event is returned to
the upper layer.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_connection_update(uint16_t Connection_Handle,
                                           uint16_t Conn_Interval_Min,
                                           uint16_t Conn_Interval_Max,
                                           uint16_t Conn_Latency,
                                           uint16_t Supervision_Timeout,
                                           uint16_t Minimum_CE_Length,
                                           uint16_t Maximum_CE_Length);
/**
  * @brief Send the SM pairing request to start a pairing process. The authentication requirements and
IO capabilities should be set before issuing this command using the
@ref aci_gap_set_io_capability and @ref aci_gap_set_authentication_requirement commands.
A @ref aci_gap_pairing_complete_event event is returned after the pairing process is completed.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Force_Rebond 0 : Pairing request is sent only if the device has not previously bonded
1 : Pairing request will be sent even if the device was previously bonded
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_send_pairing_req(uint16_t Connection_Handle,
                                    uint8_t Force_Rebond);
/**
  * @brief This command tries to resolve the address provided with the IRKs present in its database. If
the address is resolved successfully with any one of the IRKs present in the database, it
returns success and also the corresponding public/static random address stored with the
IRK in the database.
  * @param Address Address to be resolved
  * @param[out] Actual_Address The public or static random address of the peer device, distributed during pairing phase.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_resolve_private_addr(uint8_t Address[6],
                                        uint8_t Actual_Address[6]);
/**
  * @brief This command puts the device into broadcast mode. A privacy enabled device uses either a
resolvable private address or a non-resolvable private address as specified in the
Own_Addr_Type parameter of the command.
  * @param Advertising_Interval_Min Minimum advertising interval for non-directed advertising.
Range: 0x0020 to 0x4000
Default: N = 0x0800 (1.28 second)
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval for non-directed advertising.
Range: 0x0020 to 0x4000
Default: N = 0x0800 (1.28 seconds)
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Type 0x02 Scannable undirected advertising (ADV_SCAN_IND)
0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @param Adv_Data_Length Length of the advertising data in the advertising packet.
  * @param Adv_Data Advertising data used by the device while advertising.
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_broadcast_mode(uint16_t Advertising_Interval_Min,
                                      uint16_t Advertising_Interval_Max,
                                      uint8_t Advertising_Type,
                                      uint8_t Own_Address_Type,
                                      uint8_t Adv_Data_Length,
                                      uint8_t Adv_Data[],
                                      uint8_t Num_of_Whitelist_Entries,
                                      Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Starts an Observation procedure, when the device is in Observer Role. The host enables
scanning in the controller. The advertising reports are sent to the upper layer using standard
LE Advertising Report Event. (See Bluetooth Core v4.1, Vol. 2, part E, Ch. 7.7.65.2, LE
Advertising Report Event.)
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param LE_Scan_Type 0x00 Passive Scanning. No SCAN_REQ packets shall be sent.(default)
0x01 Active scanning. SCAN_REQ packets may be sent.
0x02 - 0xFF Reserved for future use
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_observation_proc(uint16_t LE_Scan_Interval,
                                          uint16_t LE_Scan_Window,
                                          uint8_t LE_Scan_Type,
                                          uint8_t Own_Address_Type,
                                          uint8_t Filter_Duplicates);
/**
  * @brief This command gets the list of the devices which are bonded. It returns the
number of addresses and the corresponding address types and values.
  * @param[out] Num_of_Addresses The number of bonded devices
  * @param[out] Bonded_Device_Entry See @ref Bonded_Device_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_get_bonded_devices(uint8_t *Num_of_Addresses,
                                      Bonded_Device_Entry_t Bonded_Device_Entry[]);
/**
  * @brief The command finds whether the device, whose address is specified in the command, is
bonded. If the device is using a resolvable private address and it has been bonded, then the
command will return BLE_STATUS_SUCCESS.
  * @param Peer_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Peer_Address Address used by the peer device while advertising
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_is_device_bonded(uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6]);
/**
 * @}
 */
/**
 *@defgroup GATT_API GATT API
 *@brief GATT API layer.
 *@{
 */
/**
  * @brief Initialize the GATT layer for server and client roles. 
It adds also the GATT service with Service Changed Characteristic. 
Until this command is issued the GATT channel will not process any commands even if the 
connection is opened. This command has to be given before using any of the GAP features. 
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_init(void);
/**
  * @brief Add a service to GATT Server. When a service is created in the server, the host needs to
reserve the handle ranges for this service using Max_Attribute_Records parameter. This
parameter specifies the maximum number of attribute records that can be added to this
service (including the service attribute, include attribute, characteristic attribute,
characteristic value attribute and characteristic descriptor attribute). Handle of the created
service is returned in command complete event. Service declaration is taken from the service pool. 
The attributes for characteristics and descriptors are allocated from the attribute pool.
  * @param Service_UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param Service_UUID See @ref Service_UUID_t
  * @param Service_Type 0x01 = Primary Service,
0x02 = Secondary Service
  * @param Max_Attribute_Records Maximum number of attribute records that can be added to this service
  * @param[out] Service_Handle Handle of the Service.
When this service is added to the server, a handle is allocated by the server to this service. 
Server also allocates a range of handles for this service from serviceHandle to <serviceHandle + max_attr_records>
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_service(uint8_t Service_UUID_Type,
                                Service_UUID_t *Service_UUID,
                                uint8_t Service_Type,
                                uint8_t Max_Attribute_Records,
                                uint16_t *Service_Handle);
/**
  * @brief Include a service given by Include_Start_Handle and Include_End_Handle to another 
service given by Service_Handle. Attribute server creates an INCLUDE definition 
attribute and return the handle of this attribute in Included_handle.
  * @param Service_Handle Handle of the Service to which another service has to be included.
  * @param Include_Start_Handle Start Handle of the Service which has to be included in service
  * @param Include_End_Handle End Handle of the Service which has to be included in service
  * @param Include_UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param Include_UUID See @ref Include_UUID_t
  * @param[out] Include_Handle Handle of the include declaration
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_include_service(uint16_t Service_Handle,
                                    uint16_t Include_Start_Handle,
                                    uint16_t Include_End_Handle,
                                    uint8_t Include_UUID_Type,
                                    Include_UUID_t *Include_UUID,
                                    uint16_t *Include_Handle);
/**
  * @brief Add a characteristic to a service.
  * @param Service_Handle Handle of the Service to which the characteristic will be added
  * @param Char_UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param Char_UUID See @ref Char_UUID_t
  * @param Char_Value_Length Maximum length of the characteristic value.
  * @param Char_Properties Characteristic Properties like defined in Volume 3, section 3.3.1.1 of Bluetooth Specification 4.0.
0x01: Broadcast,
0x02: Read,
0x04: Write w/o Resp.,
0x08: Write,
0x10: Notify,
0x20: Indicate,
0x40: Auth Signed Writes,
0x80: Extended Prop.
  * @param Security_Permissions 0x00: None,
0x01: AUTHEN_READ (Need authentication to read),
0x02: AUTHOR_READ (Need authorization to read),
0x04: ENCRY_READ (link should be encrypted to read),
0x08: AUTHEN_WRITE (need authentication to write),
0x10: AUTHOR_WRITE (need authorization to write),
0x20: ENCRY_WRITE (link should be encrypted to write)
  * @param GATT_Evt_Mask 0x01 = ATTR_WRITE,
0x02 = INTIMATE_WHEN_WRITE_N_WAIT,
0x04 = INTIMATE_WHEN_READ_N_WAIT
  * @param Enc_Key_Size Minimum encryption key size required to read the characteristic
range : 0x07 to 0x10
  * @param Is_Variable 0x00: The attribute has a fixed length value field
0x01: The attribute has a variable length value field
  * @param[out] Char_Handle Handle of the Characteristic that has been added. 
It is the handle of the characteristic declaration. 
The attribute that holds the characteristic value is allocated at the next handle, 
followed by the Client Characteristic Configuration descriptor if the characteristic 
has CHAR_PROP_NOTIFY or CHAR_PROP_INDICATE properties.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_char(uint16_t Service_Handle,
                             uint8_t Char_UUID_Type,
                             Char_UUID_t *Char_UUID,
                             uint8_t Char_Value_Length,
                             uint8_t Char_Properties,
                             uint8_t Security_Permissions,
                             uint8_t GATT_Evt_Mask,
                             uint8_t Enc_Key_Size,
                             uint8_t Is_Variable,
                             uint16_t *Char_Handle);
/**
  * @brief Add a characteristic descriptor to a service.
  * @param Service_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic to which description has to be added
  * @param Char_Desc_Uuid_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param Char_Desc_Uuid See @ref Char_Desc_Uuid_t
  * @param Char_Desc_Value_Max_Len The maximum length of the descriptor value
  * @param Char_Desc_Value_Length Current Length of the characteristic descriptor value
  * @param Char_Desc_Value Value of the characteristic description
  * @param Security_Permissions 0x00: None,
0x01: AUTHEN_READ (Need authentication to read),
0x02: AUTHOR_READ (Need authorization to read),
0x04: ENCRY_READ (link should be encrypted to read),
0x08: AUTHEN_WRITE (need authentication to write),
0x10: AUTHOR_WRITE (need authorization to write),
0x20: ENCRY_WRITE (link should be encrypted to write)
  * @param Access_Permissions 0x00: None,
0x01: READ,
0x02: WRITE,
0x04: WRITE_WO_RESP,
0x08: SIGNED_WRITE
  * @param GATT_Evt_Mask 0x01 = ATTR_WRITE,
0x02 = INTIMATE_WHEN_WRITE_N_WAIT,
0x04 = INTIMATE_WHEN_READ_N_WAIT
  * @param Enc_Key_Size Minimum encryption key size required to read the characteristic
range : 0x07 to 0x10
  * @param Is_Variable 0x00: The attribute has a fixed length value field
0x01: The attribute has a variable length value field
  * @param[out] Char_Desc_Handle Handle of the characteristic descriptor
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_char_desc(uint16_t Service_Handle,
                                  uint16_t Char_Handle,
                                  uint8_t Char_Desc_Uuid_Type,
                                  Char_Desc_Uuid_t *Char_Desc_Uuid,
                                  uint8_t Char_Desc_Value_Max_Len,
                                  uint8_t Char_Desc_Value_Length,
                                  uint8_t Char_Desc_Value[],
                                  uint8_t Security_Permissions,
                                  uint8_t Access_Permissions,
                                  uint8_t GATT_Evt_Mask,
                                  uint8_t Enc_Key_Size,
                                  uint8_t Is_Variable,
                                  uint16_t *Char_Desc_Handle);
/**
  * @brief Update a characteristic value in a service. 
If notifications (or indications) are enabled on that characteristic, 
a notification (or indication) will be sent to the client after sending 
this command to the BlueNRG. The command is queued into the BlueNRG command queue. 
If the buffer is full, because previous commands could not be still processed,
the function will return BLE_STATUS_INSUFFICIENT_RESOURCES. This will happen 
if notifications (or indications) are enabled and the application calls 
@ref aci_gatt_update_char_value at an higher rate than what is allowed by the link. 
Throughput on BLE link depends on connection interval and connection length 
parameters (decided by the master, see aci_l2cap_connection_parameter_update_request() 
for more info on how to suggest new connection parameters from a slave). If the 
application does not want to lose notifications because BlueNRG buffer becomes full, 
it has to retry again till the function returns BLE_STATUS_SUCCESS or any other error code.
  * @param Service_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic
  * @param Val_Offset The offset from which the attribute value has to be updated. 
If this is set to 0 and the attribute value is of variable length, then the length of the attribute will be set to the Char_Value_Length. 
If the Val_Offset is set to a value greater than 0, then the length of the attribute will be set to the maximum length as 
specified for the attribute while adding the characteristic.
  * @param Char_Value_Length Length of the characteristic value in octets
  * @param Char_Value Characteristic value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_update_char_value(uint16_t Service_Handle,
                                      uint16_t Char_Handle,
                                      uint8_t Val_Offset,
                                      uint8_t Char_Value_Length,
                                      uint8_t Char_Value[]);
/**
  * @brief Delete the specified characteristic from the service.
  * @param Serv_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic which has to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_char(uint16_t Serv_Handle,
                             uint16_t Char_Handle);
/**
  * @brief Delete the specified service from the GATT server database.
  * @param Serv_Handle Handle of the service to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_service(uint16_t Serv_Handle);
/**
  * @brief Delete the Include definition from the service.
  * @param Serv_Handle Handle of the service to which the include service belongs
  * @param Include_Handle Handle of the included service which has to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_include_service(uint16_t Serv_Handle,
                                        uint16_t Include_Handle);
/**
  * @brief Mask events from the GATT. The default configuration is all the events masked.
  * @param GATT_Evt_Mask 0x00000001: ACI_GATT_ATTRIBUTE_MODIFIED_EVENT
0x00000002: ACI_GATT_PROC_TIMEOUT_EVENT
0x00000004: ACI_ATT_EXCHANGE_MTU_RESP_EVENT
0x00000008: ACI_ATT_FIND_INFO_RESP_EVENT
0x00000010: ACI_ATT_FIND_BY_TYPE_VALUE_RESP_EVENT
0x00000020: ACI_ATT_READ_BY_TYPE_RESP_EVENT
0x00000040: ACI_ATT_READ_RESP_EVENT
0x00000080: ACI_ATT_READ_BLOB_RESP_EVENT
0x00000100: ACI_ATT_READ_MULTIPLE_RESP_EVENT
0x00000200: ACI_ATT_READ_BY_GROUP_TYPE_RESP_EVENT
0x00000800: ACI_ATT_PREPARE_WRITE_RESP_EVENT
0x00001000: ACI_ATT_EXEC_WRITE_RESP_EVENT
0x00002000: ACI_GATT_INDICATION_EVENT
0x00004000: ACI_GATT_NOTIFICATION_EVENT
0x00008000: ACI_GATT_ERROR_RESP_EVENT
0x00010000: ACI_GATT_PROC_COMPLETE_EVENT
0x00020000: ACI_GATT_DISC_READ_CHAR_BY_UUID_RESP_EVENT
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_event_mask(uint32_t GATT_Evt_Mask);
/**
  * @brief Perform an ATT MTU exchange procedure.
When the ATT MTU exchange procedure is completed, a @ref aci_att_exchange_mtu_resp_event
event is generated. A @ref aci_gatt_proc_complete_event event is also generated
to indicate the end of the procedure.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_exchange_config(uint16_t Connection_Handle);
/**
  * @brief Send a Find Information Request.
This command is used to obtain the mapping of attribute handles with their associated
types. The responses of the procedure are given through the 
@ref aci_att_find_info_resp_event event. The end of the procedure is indicated by
a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_find_info_req(uint16_t Connection_Handle,
                                 uint16_t Start_Handle,
                                 uint16_t End_Handle);
/**
  * @brief Send a Find By Type Value Request
The Find By Type Value Request is used to obtain the handles of attributes that
have a given 16-bit UUID attribute type and a given attribute value.
The responses of the procedure are given through the @ref aci_att_find_by_type_value_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID 2 octet UUID to find (little-endian)
  * @param Attribute_Val_Length Length of attribute value (maximum value is ATT_MTU - 7).
  * @param Attribute_Val Attribute value to find
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_find_by_type_value_req(uint16_t Connection_Handle,
                                          uint16_t Start_Handle,
                                          uint16_t End_Handle,
                                          uint16_t UUID,
                                          uint8_t Attribute_Val_Length,
                                          uint8_t Attribute_Val[]);
/**
  * @brief Send a Read By Type Request.
The Read By Type Request is used to obtain the values of attributes where the attribute
type is known but the handle is not known.
The responses of the procedure are given through the @ref aci_att_read_by_type_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_read_by_type_req(uint16_t Connection_Handle,
                                    uint16_t Start_Handle,
                                    uint16_t End_Handle,
                                    uint8_t UUID_Type,
                                    UUID_t *UUID);
/**
  * @brief Send a Read By Group Type Request. 
The Read By Group Type Request is used to obtain the values of grouping attributes where
the attribute type is known but the handle is not known. Grouping attributes are defined 
at GATT layer. The grouping attribute types are: "Primary Service", "Secondary Service" 
and "Characteristic". 
The responses of the procedure are given through the @ref aci_att_read_by_group_type_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_read_by_group_type_req(uint16_t Connection_Handle,
                                          uint16_t Start_Handle,
                                          uint16_t End_Handle,
                                          uint8_t UUID_Type,
                                          UUID_t *UUID);
/**
  * @brief Send a Prepare Write Request.
The Prepare Write Request is used to request the server to prepare to write the value of an attribute. 
The responses of the procedure are given through the @ref aci_att_prepare_write_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event. 
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset The offset of the first octet to be written
  * @param Attribute_Val_Length Length of attribute value (maximum value is ATT_MTU - 5).
  * @param Attribute_Val The value of the attribute to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_prepare_write_req(uint16_t Connection_Handle,
                                     uint16_t Attr_Handle,
                                     uint16_t Val_Offset,
                                     uint8_t Attribute_Val_Length,
                                     uint8_t Attribute_Val[]);
/**
  * @brief Send an Execute Write Request.
The Execute Write Request is used to request the server to write or cancel the write 
of all the prepared values currently held in the prepare queue from this client. 
The result of the procedure is given through the @ref aci_att_exec_write_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event. 
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Execute 0x00 = Cancel all prepared writes 
0x01 = Immediately write all pending prepared values
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_execute_write_req(uint16_t Connection_Handle,
                                     uint8_t Execute);
/**
  * @brief Start the GATT client procedure to discover all primary services on the server.
The responses of the procedure are given through the @ref aci_att_read_by_group_type_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_primary_services(uint16_t Connection_Handle);
/**
  * @brief Start the procedure to discover the primary services of the specified UUID on the server.
The responses of the procedure are given through the @ref aci_att_find_by_type_value_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_primary_service_by_uuid(uint16_t Connection_Handle,
                                                 uint8_t UUID_Type,
                                                 UUID_t *UUID);
/**
  * @brief Start the procedure to find all included services.
The responses of the procedure are given through the @ref aci_att_read_by_type_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_find_included_services(uint16_t Connection_Handle,
                                           uint16_t Start_Handle,
                                           uint16_t End_Handle);
/**
  * @brief Start the procedure to discover all the characteristics of a given service.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_read_by_type_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_char_of_service(uint16_t Connection_Handle,
                                             uint16_t Start_Handle,
                                             uint16_t End_Handle);
/**
  * @brief Start the procedure to discover all the characteristics specified by a UUID.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_gatt_disc_read_char_by_uuid_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_char_by_uuid(uint16_t Connection_Handle,
                                      uint16_t Start_Handle,
                                      uint16_t End_Handle,
                                      uint8_t UUID_Type,
                                      UUID_t *UUID);
/**
  * @brief Start the procedure to discover all characteristic descriptors on the server.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_find_info_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Char_Handle Starting handle of the characteristic
  * @param End_Handle End handle of the characteristic
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_char_desc(uint16_t Connection_Handle,
                                       uint16_t Char_Handle,
                                       uint16_t End_Handle);
/**
  * @brief Start the procedure to read the attribute value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packet is given through @ref aci_att_read_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the characteristic to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_char_value(uint16_t Connection_Handle,
                                    uint16_t Attr_Handle);
/**
  * @brief Start the procedure to read all the characteristics specified by the UUID.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_gatt_disc_read_char_by_uuid_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle Starting handle of the range to be searched
  * @param End_Handle End handle of the range to be searched
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_using_char_uuid(uint16_t Connection_Handle,
                                         uint16_t Start_Handle,
                                         uint16_t End_Handle,
                                         uint8_t UUID_Type,
                                         UUID_t *UUID);
/**
  * @brief Start the procedure to read a long characteristic value.
the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through @ref aci_att_read_blob_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the characteristic to be read
  * @param Val_Offset Offset from which the value needs to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_long_char_value(uint16_t Connection_Handle,
                                         uint16_t Attr_Handle,
                                         uint16_t Val_Offset);
/**
  * @brief Start a procedure to read multiple characteristic values from a server.
This sub-procedure is used to read multiple Characteristic Values from a server when the
client knows the Characteristic Value Handles.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_read_multiple_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Number_of_Handles The number of handles for which the value has to be read
  * @param Handle_Entry See @ref Handle_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_multiple_char_value(uint16_t Connection_Handle,
                                             uint8_t Number_of_Handles,
                                             Handle_Entry_t Handle_Entry[]);
/**
  * @brief Start the procedure to write a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the characteristic to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_value(uint16_t Connection_Handle,
                                     uint16_t Attr_Handle,
                                     uint8_t Attribute_Val_Length,
                                     uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_long_char_value(uint16_t Connection_Handle,
                                          uint16_t Attr_Handle,
                                          uint16_t Val_Offset,
                                          uint8_t Attribute_Val_Length,
                                          uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a characteristic reliably.
When the procedure is completed, a  @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_reliable(uint16_t Connection_Handle,
                                        uint16_t Attr_Handle,
                                        uint16_t Val_Offset,
                                        uint8_t Attribute_Val_Length,
                                        uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a long characteristic descriptor.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_long_char_desc(uint16_t Connection_Handle,
                                         uint16_t Attr_Handle,
                                         uint16_t Val_Offset,
                                         uint8_t Attribute_Val_Length,
                                         uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to read a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is
generated. Before procedure completion the response packets are given through
@ref aci_att_read_blob_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the characteristic descriptor
  * @param Val_Offset Offset from which the value needs to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_long_char_desc(uint16_t Connection_Handle,
                                        uint16_t Attr_Handle,
                                        uint16_t Val_Offset);
/**
  * @brief Start the procedure to write a characteristic descriptor.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_desc(uint16_t Connection_Handle,
                                    uint16_t Attr_Handle,
                                    uint8_t Attribute_Val_Length,
                                    uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to read the descriptor specified.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packet is given through @ref aci_att_read_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the descriptor to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_char_desc(uint16_t Connection_Handle,
                                   uint16_t Attr_Handle);
/**
  * @brief Start the procedure to write a characteristic value without waiting for any response from the
server. No events are generated after this command is executed.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written (maximum value is ATT_MTU - 3)
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_without_resp(uint16_t Connection_Handle,
                                       uint16_t Attr_Handle,
                                       uint8_t Attribute_Val_Length,
                                       uint8_t Attribute_Val[]);
/**
  * @brief Start a signed write without response from the server.
The procedure is used to write a characteristic value with an authentication signature without waiting
for any response from the server. It cannot be used when the link is encrypted.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written (up to ATT_MTU - 13)
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_signed_write_without_resp(uint16_t Connection_Handle,
                                              uint16_t Attr_Handle,
                                              uint8_t Attribute_Val_Length,
                                              uint8_t Attribute_Val[]);
/**
  * @brief Allow application to confirm indication. This command has to be sent when the application
receives the event @ref aci_gatt_indication_event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_confirm_indication(uint16_t Connection_Handle);
/**
  * @brief Allow or reject a write request from a client.
This command has to be sent by the application when it receives the
@ref aci_gatt_write_permit_req_event. If the write can be allowed, then the status and error
code has to be set to 0. If the write cannot be allowed, then the status has to be set to 1 and
the error code has to be set to the error code that has to be passed to the client.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute that was passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @param Write_status 0x00 = The value can be written to the attribute specified by attr_handle,
0x01 = The value cannot be written to the attribute specified by the attr_handle
  * @param Error_Code The error code that has to be passed to the client in case the write has to be rejected
  * @param Attribute_Val_Length Length of the value to be written as passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @param Attribute_Val Value as passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_resp(uint16_t Connection_Handle,
                               uint16_t Attr_Handle,
                               uint8_t Write_status,
                               uint8_t Error_Code,
                               uint8_t Attribute_Val_Length,
                               uint8_t Attribute_Val[]);
/**
  * @brief Allow the GATT server to send a response to a read request from a client.
The application has to send this command when it receives the
@ref aci_gatt_read_permit_req_event or @ref aci_gatt_read_multi_permit_req_event. This
command indicates to the stack that the response can be sent to the client. So if the
application wishes to update any of the attributes before they are read by the client, it has to
update the characteristic values using the @ref aci_gatt_update_char_value and then give
this command. The application should perform the required operations within 30 seconds.
Otherwise the GATT procedure will be timeout.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_allow_read(uint16_t Connection_Handle);
/**
  * @brief This command sets the security permission for the attribute handle specified. Currently the
setting of security permission is allowed only for client configuration descriptor.
  * @param Serv_Handle Handle of the service which contains the attribute whose security permission has to be modified
  * @param Attr_Handle Handle of the attribute whose security permission has to be modified
  * @param Security_Permissions 0x00: None,
0x01: AUTHEN_READ (Need authentication to read),
0x02: AUTHOR_READ (Need authorization to read),
0x04: ENCRY_READ (link should be encrypted to read),
0x08: AUTHEN_WRITE (need authentication to write),
0x10: AUTHOR_WRITE (need authorization to write),
0x20: ENCRY_WRITE (link should be encrypted to write)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_security_permission(uint16_t Serv_Handle,
                                            uint16_t Attr_Handle,
                                            uint8_t Security_Permissions);
/**
  * @brief This command sets the value of the descriptor specified by charDescHandle.
  * @param Serv_Handle Handle of the service which contains the characteristic descriptor
  * @param Char_Handle Handle of the characteristic which contains the descriptor
  * @param Char_Desc_Handle Handle of the descriptor whose value has to be set
  * @param Val_Offset Offset from which the descriptor value has to be updated
  * @param Char_Desc_Value_Length Length of the descriptor value
  * @param Char_Desc_Value Descriptor value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_desc_value(uint16_t Serv_Handle,
                                   uint16_t Char_Handle,
                                   uint16_t Char_Desc_Handle,
                                   uint16_t Val_Offset,
                                   uint8_t Char_Desc_Value_Length,
                                   uint8_t Char_Desc_Value[]);
/**
  * @brief Reads the value of the attribute handle specified from the local GATT database.
  * @param Attr_Handle Handle of the attribute to read
  * @param[out] Value_Length Length of the value
  * @param[out] Value 0-N bytes Value read. The length is as specified in the Value_Length field
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_handle_value(uint16_t Attr_Handle,
                                      uint16_t *Value_Length,
                                      uint8_t Value[]);
/**
  * @brief Reads the value of the attribute handle specified from the local GATT database, starting
from a given offset. If the length to be returned is greater than 128, then only 128
bytes are returned. The application should send this command with incremented offsets
until it gets an error with the offset it specified or the number of byes of attribute
value returned is less than 128.
  * @param Attr_Handle Handle of the attribute to read
  * @param Offset Offset from which the value needs to be read
  * @param[out] Value_Length Length of the value
  * @param[out] Value 0-N bytes Value read. The length is as specified in the Value_Length field
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_handle_value_offset(uint16_t Attr_Handle,
                                             uint8_t Offset,
                                             uint16_t *Value_Length,
                                             uint8_t Value[]);
/**
 * @}
 */
/**
 *@defgroup L2CAP_API L2CAP API
 *@brief L2CAP API layer.
 *@{
 */
/**
  * @brief Send an L2CAP connection parameter update request from the slave to the master.
An @ref aci_l2cap_connection_update_resp_event event will be raised when the master will respond to the 
request (accepts or rejects).
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Slave_latency Defines the slave latency parameter (as number of LL connection events).
  * @param Timeout_Multiplier Defines connection timeout parameter in the following manner: Timeout Multiplier * 10ms.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_l2cap_connection_parameter_update_req(uint16_t Connection_Handle,
                                                     uint16_t Conn_Interval_Min,
                                                     uint16_t Conn_Interval_Max,
                                                     uint16_t Slave_latency,
                                                     uint16_t Timeout_Multiplier);
/**
  * @brief Accept or reject a connection update. This command should be sent in response
to a @ref aci_l2cap_connection_update_req_event event from the controller. The accept parameter has to be
set if the connection parameters given in the event are acceptable.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Slave_latency Defines the slave latency parameter (as number of LL connection events).
  * @param Timeout_Multiplier Defines connection timeout parameter in the following manner: Timeout Multiplier * 10ms.
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Identifier Identifier received in ACI_L2CAP_Connection_Update_Req event.
  * @param Accept 0x00: The connection update parameters are not acceptable.
0x01: The connection update parameters are acceptable.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_l2cap_connection_parameter_update_resp(uint16_t Connection_Handle,
                                                      uint16_t Conn_Interval_Min,
                                                      uint16_t Conn_Interval_Max,
                                                      uint16_t Slave_latency,
                                                      uint16_t Timeout_Multiplier,
                                                      uint16_t Minimum_CE_Length,
                                                      uint16_t Maximum_CE_Length,
                                                      uint8_t Identifier,
                                                      uint8_t Accept);
/**
 * @}
 */
#endif /* __BLUENRG1_API_H__*/
