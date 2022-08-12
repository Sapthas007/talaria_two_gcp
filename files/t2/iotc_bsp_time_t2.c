/* Copyright 2018-2020 Google LLC
 *
 * This is part of the Google Cloud IoT Device SDK for Embedded C.
 * It is licensed under the BSD 3-Clause license; you may not use this file
 * except in compliance with the License.
 *
 * You may obtain a copy of the License at:
 *  https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iotc_bsp_time.h>

#include <kernel/os.h>
#include <wifi/wcm.h>
#include <lwip/ip_addr.h>
#include <lwip/netif.h>
#include "wifi_utils.h"
#include "../../../../../../components/sntp/inc/sntp.h"


const char *server_addr;
const ip_addr_t *addr;
int  total_sec =0 ,status;
ip_addr_t server_ip;
time_t tim;

void iotc_bsp_time_init() { 
    sntp_stop();
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    server_addr = "216.239.35.0";/*time.google.org*/
    status = ipaddr_aton(server_addr, &server_ip);
    if(status != 1) {
         return false;
    }
    sntp_init();
    sntp_setserver(0, &server_ip);
    os_sleep_us(2000000, OS_TIMEOUT_NO_WAKEUP);
    int time_now,  times = 0 , time_ntp = 0;
    uint64_t now = os_systime64();
    do{
        time_now = sntp_time();

        if(0 != time_now)
        {
            break;
        }
    	os_sleep_us(2000000, OS_TIMEOUT_NO_WAKEUP);
    }
    while(times < 16);

    if(times >= 16)
        return 0;
    time_ntp = (time_now + 19800);
    tim = time_ntp;

    sntp_stop(); 
    struct timespec tp,tp1;
    tp.tv_sec = time_ntp;
    tp.tv_nsec = 0;
    clock_settime(CLOCK_REALTIME, &tp);
    clock_gettime(CLOCK_REALTIME, &tp1);
    os_printf("\r\n utc:%lld:%lld:%lld",tp.tv_sec, os_get_utcoffset(), os_systime64());

}

iotc_time_t iotc_bsp_time_getcurrenttime_seconds() { 

    struct timeval now;

    gettimeofday(&now, NULL);
    return (now.tv_sec - 19800);
 }

iotc_time_t iotc_bsp_time_getcurrenttime_milliseconds() {
    struct timeval now;
   
    gettimeofday(&now, NULL);
    return ((now.tv_sec -19800) *1000);
 }
