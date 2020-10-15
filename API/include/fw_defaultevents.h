/* 
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#ifndef FW_DEFAULTEVENTS_H_
#define FW_DEFAULTEVENTS_H_


#define FW_EVENT_ADC 3001
#define FW_EVENT_DAC 3002
#define FW_EVENT_PWM 3003
#define FW_EVENT_WIFIAP 3004
#define FW_EVENT_WIFICON 3005
#define FW_EVENT_WIFIDIS 3006
#define FW_EVENT_MQTTSTART 3007
#define FW_EVENT_MQTTSUBS 3008
#define FW_EVENT_MQTTPUBL 3009
#define FW_EVENT_UARTWRITE 3010
#define FW_EVENT_UARTREAD 3011
#define FW_EVENT_I2CMASTERREAD 3012
#define FW_EVENT_I2CMASTERWRITE 3013
#define FW_EVENT_I2CSLAVEREAD 3014
#define FW_EVENT_I2CSLAVEWRITE 3015
#define FW_EVENT_SPITRANSMIT 3016

#ifdef __cplusplus
} // extern "C"
#endif

#endif // #ifndef FW_DEFAULTEVENTS_H_

