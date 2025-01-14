/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_WIFIMSG_H
#define OHOS_WIFIMSG_H

#include <algorithm>
#include <cstring>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "ip_tools.h"
#include "wifi_ap_msg.h"
#include "wifi_scan_msg.h"

namespace OHOS {
namespace Wifi {
#define WIFI_COUNTRY_CODE_LEN 2
#define WEPKEYS_SIZE 4
#define INVALID_NETWORK_ID (-1)
#define REOPEN_STA_INTERVAL 500
#define BAND_2_G 1
#define BAND_5_G 2
#define IPV4_ADDRESS_TYPE 0
#define IPV6_ADDRESS_TYPE 1

#define DEVICE_CONFIG_INDEX_SSID 0
#define DEVICE_CONFIG_INDEX_BSSID 1

enum class SupplicantState {
    DISCONNECTED = 0,
    INTERFACE_DISABLED = 1,
    INACTIVE = 2,
    SCANNING = 3,
    AUTHENTICATING = 4,
    ASSOCIATING = 5,
    ASSOCIATED = 6,
    FOUR_WAY_HANDSHAKE = 7,
    GROUP_HANDSHAKE = 8,
    COMPLETED = 9,
    UNKNOWN = 10,

    INVALID = 0xFF,
};

enum class DetailedState {
    AUTHENTICATING = 0,
    BLOCKED = 1,
    CAPTIVE_PORTAL_CHECK = 2,
    CONNECTED = 3,
    CONNECTING = 4,
    DISCONNECTED = 5,
    DISCONNECTING = 6,
    FAILED = 7,
    IDLE = 8,
    OBTAINING_IPADDR = 9,
    WORKING = 10,
    NOTWORKING = 11,
    SCANNING = 12,
    SUSPENDED = 13,
    VERIFYING_POOR_LINK = 14,

    INVALID = 0xFF,
};

enum class ConnState {
    IDLE,
    SCANNING,
    CONNECTING,
    AUTHENTICATING,
    OBTAINING_IPADDR,
    CONNECTED,
    SUSPENDED,
    DISCONNECTING,
    DISCONNECTED,
    FAILED
};

struct WifiLinkedInfo {
    int networkId;
    std::string ssid;
    std::string bssid;
    int rssi; /* signal level */
    int band; /* 2.4G / 5G */
    int frequency;
    int linkSpeed; /* units: Mbps */
    std::string macAddress;
    unsigned int ipAddress;
    ConnState connState;
    bool ifHiddenSSID;
    std::string rxLinkSpeed; /* Downstream network speed */
    std::string txLinkSpeed; /* Upstream network speed */
    int chload;
    int snr;                         /* Signal-to-Noise Ratio */
    SupplicantState supplicantState; /* wpa_supplicant state */
    DetailedState detailedState;     /* connection state */

    WifiLinkedInfo()
    {
        networkId = INVALID_NETWORK_ID;
        rssi = 0;
        band = 0;
        frequency = 0;
        linkSpeed = 0;
        ipAddress = 0;
        connState = ConnState::FAILED;
        ifHiddenSSID = false;
        chload = 0;
        snr = 0;
        supplicantState = SupplicantState::INVALID;
        detailedState = DetailedState::INVALID;
    }
};

/* use WPS type */
enum class SetupMethod {
    PBC = 0,
    DISPLAY = 1,
    KEYPAD = 2,
    LABEL = 3,
    INVALID = 4,
};

/* WPS config */
struct WpsConfig {
    SetupMethod setup; /* WPS type */
    std::string pin;   /* pin code */
    std::string bssid; /* KEYPAD mode pin code */

    WpsConfig()
    {
        setup = SetupMethod::INVALID;
    }
};

enum class WifiDeviceConfigStatus {
    INVALID = -1, /* invalid */
    CURRENT = 0,  /* using */
    DISABLED = 1, /* disabled */
    ENABLED = 2,  /* enable */

    UNKNOWN
};

enum class AssignIpMethod { DHCP, STATIC, UNASSIGNED };

class WifiIpAddress {
public:
    int family;                             /* ip type */
    unsigned int addressIpv4;               /* IPv4 */
    std::vector<unsigned char> addressIpv6; /* IPv6 */

    WifiIpAddress()
    {
        family = -1;
        addressIpv4 = 0;
    }

    ~WifiIpAddress()
    {}

    std::string GetIpv4Address()
    {
        return IpTools::ConvertIpv4Address(addressIpv4);
    }

    void SetIpv4Address(const std::string &address)
    {
        family = IPV4_ADDRESS_TYPE;
        addressIpv4 = IpTools::ConvertIpv4Address(address);
        return;
    }

    std::string GetIpv6Address()
    {
        return IpTools::ConvertIpv6Address(addressIpv6);
    }

    void SetIpv6Address(const std::string &address)
    {
        family = IPV6_ADDRESS_TYPE;
        IpTools::ConvertIpv6Address(address, addressIpv6);
        return;
    }
};

class WifiLinkAddress {
public:
    WifiIpAddress address; /* IP address */
    int prefixLength;
    int flags;
    int scope;

    WifiLinkAddress()
    {
        prefixLength = 0;
        flags = 0;
        scope = 0;
    }

    ~WifiLinkAddress()
    {}
};

class StaticIpAddress {
public:
    WifiLinkAddress ipAddress;
    WifiIpAddress gateway;
    WifiIpAddress dnsServer1; /* main DNS */
    WifiIpAddress dnsServer2; /* backup DNS */
    std::string domains;

    std::string GetIpv4Mask()
    {
        return IpTools::ConvertIpv4Mask(ipAddress.prefixLength);
    }

    std::string GetIpv6Mask()
    {
        return IpTools::ConvertIpv6Mask(ipAddress.prefixLength);
    }
};

class WifiIpConfig {
public:
    AssignIpMethod assignMethod;
    StaticIpAddress staticIpAddress;

    WifiIpConfig()
    {
        assignMethod = AssignIpMethod::DHCP;
    }
    ~WifiIpConfig()
    {}
};

class WifiEapConfig {
public:
    std::string eap;      /* EAP mode Encryption Mode: PEAP/TLS/TTLS/PWD/SIM/AKA/AKA */
    std::string identity; /* EAP mode identity */
    std::string password; /* EAP mode password */
};

enum class ConfigureProxyMethod { AUTOCONFIGUE, MANUALCONFIGUE, CLOSED };

class AutoProxyConfig {
public:
    std::string pacWebAddress;
};

class ManualProxyConfig {
public:
    std::string serverHostName;
    int serverPort;
    std::string exclusionObjectList;

    void GetExclusionObjectList(std::vector<std::string> &exclusionList)
    {
        IpTools::GetExclusionObjectList(exclusionObjectList, exclusionList);
        return;
    }

    ManualProxyConfig()
    {
        serverPort = 0;
    }
    ~ManualProxyConfig()
    {}
};

class WifiProxyConfig {
public:
    ConfigureProxyMethod configureMethod;
    AutoProxyConfig autoProxyConfig;
    ManualProxyConfig manualProxyConfig;

    WifiProxyConfig()
    {
        configureMethod = ConfigureProxyMethod::CLOSED;
    }
    ~WifiProxyConfig()
    {}
};

enum class WifiPrivacyConfig { RANDOMMAC, DEVICEMAC };

/* Network configuration information */
struct WifiDeviceConfig {
    int networkId;
    /* 0: CURRENT, using 1: DISABLED 2: ENABLED */
    int status;
    /* mac address */
    std::string bssid;
    /* network name */
    std::string ssid;
    int band;
    int channel;
    int frequency;
    /* Signal strength */
    int rssi;
    /**
     * signal level，
     * rssi<=-100    level : 0
     * (-100, -88]   level : 1
     * (-88, -77]    level : 2
     * (-66, -55]    level : 3
     * rssi>=-55     level : 4
     */
    int level;
    /* Is Passpoint network */
    bool isPasspoint;
    /* is ephemeral network */
    bool isEphemeral;
    /* WPA-PSK mode pre shared key */
    std::string preSharedKey;
    /* Encryption Mode */
    std::string keyMgmt;
    /* WEP mode key, max size: 4 */
    std::string wepKeys[WEPKEYS_SIZE];
    /* use WEP key index */
    int wepTxKeyIndex;
    /* network priority */
    int priority;
    /* is hidden network */
    bool hiddenSSID;
    /* Random mac address */
    std::string macAddress;
    WifiIpConfig wifiIpConfig;
    WifiEapConfig wifiEapConfig;
    WifiProxyConfig wifiProxyconfig;
    WifiPrivacyConfig wifiPrivacySetting;

    WifiDeviceConfig()
    {
        networkId = INVALID_NETWORK_ID;
        status = static_cast<int>(WifiDeviceConfigStatus::INVALID);
        band = 0;
        channel = 0;
        frequency = 0;
        level = 0;
        isPasspoint = false;
        isEphemeral = false;
        wepTxKeyIndex = 0;
        priority = 0;
        hiddenSSID = false;
        wifiPrivacySetting = WifiPrivacyConfig::RANDOMMAC;
        rssi = -100;
    }
};

enum class WifiState { DISABLING = 0, DISABLED = 1, ENABLING = 2, ENABLED = 3, UNKNOWN = 4 };

enum class ConnectionState {
    CONNECT_CONNECTING = 0,
    CONNECT_AP_CONNECTED = 1,
    CONNECT_CHECK_PORTAL = 2,
    CONNECT_NETWORK_ENABLED = 3,
    CONNECT_NETWORK_DISABLED = 4,
    DISCONNECT_DISCONNECTING = 5,
    DISCONNECT_DISCONNECT_FAILED = 6,
    DISCONNECT_DISCONNECTED = 7,
    CONNECT_PASSWORD_WRONG = 8,
    CONNECT_CONNECTING_TIMEOUT = 9,
    CONNECT_OBTAINING_IP = 10,
    CONNECT_OBTAINING_IP_FAILED = 11,
    CONNECT_ASSOCIATING = 12,
    CONNECT_ASSOCIATED = 13,

    UNKNOWN,
};

/* wps state */
enum class WpsStartState {
    START_PBC_SUCCEED = 0,
    START_PIN_SUCCEED = 1,
    START_PBC_FAILED = 2,
    PBC_STARTED_ALREADY = 3,
    START_PIN_FAILED = 4,
    PIN_STARTED_ALREADY = 5,
    STOP_PBC_SUCCEED = 6,
    STOP_PBC_FAILED = 7,
    STOP_PIN_SUCCEED = 8,
    STOP_PIN_FAILED = 9,
    START_PBC_FAILED_OVERLAP = 10,
    START_WPS_FAILED = 11,
    WPS_TIME_OUT = 12,
};

enum class StreamDirection {
    STREAM_DIRECTION_UP = 0,
    STREAM_DIRECTION_DOWN = 1,
    UNKNOWN,
};

/* DHCP info */
struct IpInfo {
    int ipAddress;     /* ip address */
    int gateway;       /* gate */
    int netmask;       /* mask */
    int primaryDns;          /* main dns */
    int secondDns;          /* backup dns */
    int serverIp; /* DHCP server's address */
    int leaseDuration;

    IpInfo()
    {
        ipAddress = 0;
        gateway = 0;
        netmask = 0;
        primaryDns = 0;
        secondDns = 0;
        serverIp = 0;
        leaseDuration = 0;
    }
};

struct WifiEvent {
    void (*OnWifiStateChanged)(int state);
    void (*OnWifiConnectionChanged)(int state, const WifiLinkedInfo &info);
    void (*OnWifiScanStateChanged)(int state);
    void (*OnWifiRssiChanged)(int rssi);
    void (*OnWifiWpsStateChanged)(int state, std::string pinCode);
    void (*OnHotspotStateChanged)(int state);
    void (*OnHotspotStaJoin)(const StationInfo &info);
    void (*OnHotspotStaLeave)(const StationInfo &info);
    void (*OnStreamChanged)(int direction);

    WifiEvent()
    {
        OnWifiStateChanged = nullptr;
        OnWifiConnectionChanged = nullptr;
        OnWifiScanStateChanged = nullptr;
        OnWifiRssiChanged = nullptr;
        OnWifiWpsStateChanged = nullptr;
        OnHotspotStateChanged = nullptr;
        OnHotspotStaJoin = nullptr;
        OnHotspotStaLeave = nullptr;
        OnStreamChanged = nullptr;
    }
};
}  // namespace Wifi
}  // namespace OHOS
#endif