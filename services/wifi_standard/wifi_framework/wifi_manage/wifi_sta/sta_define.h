/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
#ifndef OHOS_STA_DEFINE_H
#define OHOS_STA_DEFINE_H

#include <functional>
#include <string>

namespace OHOS {
namespace Wifi {
#define WIFI_SVR_CMD_STA_ENABLE_WIFI 0x2001
#define WIFI_SVR_CMD_STA_DISABLE_WIFI 0x2002
#define WIFI_SVR_CMD_STA_START_SUPPLICANT 0x2003
#define WIFI_SVR_CMD_STA_OPERATIONAL_MODE 0x2004
#define WIFI_SVR_CMD_STA_STOP_SUPPLICANT 0x2005
#define WIFI_SVR_CMD_STA_CONNECT_NETWORK 0x2006
#define WIFI_SVR_CMD_STA_CONNECT_SAVED_NETWORK 0x2007
#define WIFI_SVR_CMD_STA_REMOVE_DEVICE_CONFIG 0x2008
#define WIFI_SVR_CMD_STA_RECONNECT_NETWORK 0x2009
#define WIFI_SVR_CMD_STA_REMOVE_All_DEVICE_CONFIG 0x2010
#define WIFI_SVR_CMD_STA_REASSOCIATE_NETWORK 0x200A
#define WIFI_SVR_CMD_STA_DISCONNECT 0x200B
#define WIFI_SVR_CMD_STA_STARTWPS 0x200C
#define WIFI_SVR_CMD_STA_CANCELWPS 0x200D
#define WIFI_SVR_COM_STA_START_ROAM 0x200E

#define WIFI_SVR_CMD_STA_ERROR 0x3001
#define WIFI_SVR_CMD_STA_SUP_CONNECTION_EVENT 0x3002
#define WIFI_SVR_CMD_STA_SUP_DISCONNECTION_EVENT 0x3003
#define WIFI_SVR_CMD_STA_NETWORK_CONNECTION_EVENT 0x3004
#define WIFI_SVR_CMD_STA_NETWORK_DISCONNECTION_EVENT 0x3005
#define WIFI_SVR_CMD_STA_WPS_START_EVENT 0x3006
#define WIFI_SVR_CMD_STA_WPS_CANCEL_EVENT 0x3007
#define WIFI_SVR_CMD_STA_WPS_FAILED_EVENT 0x3008
#define WIFI_SVR_CMD_STA_WPS_OVERLAP_EVENT 0x3009
#define WIFI_SVR_CMD_STA_WPS_TIMEOUT_EVNET 0x300A
#define WIFI_SVR_CMD_STA_WPS_WEP_PROHIBITED 0x300B
#define WIFI_SVR_CMD_STA_WPS_TKIP_ONLY_PROHIBITED 0x300C
#define WIFI_SVR_CMD_STA_WPS_AUTH_FAILURE 0x300D
#define WIFI_SVR_CMD_STA_WPS_OVERLAP_ERROR 0x300E
#define WIFI_SVR_CMD_STA_SUP_REQUEST_IDENTITY 0x300F
#define WIFI_SVR_CMD_STA_SUP_REQUEST_SIM_AUTH 0x3010
#define WIFI_SVR_CMD_STA_AUTHENTICATION_FAILURE_EVENT 0x3011
#define WIFI_SVR_CMD_STA_REASON_TKIP_ONLY_PROHIBITED 0x3012
#define WIFI_SVR_CMD_STA_REASON_WEP_PROHIBITED 0x3013
#define WIFI_SVR_CMD_STA_CONFIG_AUTH_FAILURE 0x3014
#define WIFI_SVR_CMD_STA_CONFIG_MULTIPLE_PBC_DETECTED 0x3015
#define WIFI_SVR_CMD_STA_WPA_STATE_CHANGE_EVENT 0x3016
#define WIFI_SVR_CMD_STA_WPA_PASSWD_WRONG_EVENT 0x3017
#define BSSID_LEN 17
#define KEY_LEN 128
#define SSID_LEN 30
#define VALUE_LIMIT_MIN_RSSI (-100)
#define VALUE_LIMIT_MAX_RSSI (-55)
#define WPA_BLOCK_LIST_CLEAR_EVENT 0x4001
#define NETWORK_SELECTED_BY_THE_USER 1
#define NETWORK_SELECTED_FOR_CONNECTION_MANAGEMENT 0
typedef enum EnumStaIpType {
    IPTYPE_IPV4,
    IPTYPE_IPV6,
    IPTYPE_MIX,
    IPTYPE_BUTT,
} StaIpType;

typedef enum EnumStaNetState {
    NETWORK_STATE_UNKNOW,
    NETWORK_STATE_WORKING,
    NETWORK_STATE_NOWORKING,
    NETWORK_STATE_BUTT,
} StaNetState;

typedef std::function<void(StaNetState netState)> NetStateHandler;
}  // namespace Wifi
}  // namespace OHOS
#endif /* OHOS_STA_DEFINE_H */
