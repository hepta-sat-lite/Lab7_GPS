#include "mbed.h"
#include "HEPTA_CDH.h"
#include "HEPTA_EPS.h"
#include "HeptaCamera_GPS.h"

HEPTA_CDH cdh(PB_5, PB_4, PB_3, PA_8, "sd");
RawSerial pc(USBTX,USBRX,9600);
HEPTA_EPS eps(PA_0,PA_4);
HeptaCamera_GPS sensor(PA_9,PA_10);

int main()
{
    sensor.gps_setting();
    int quality=0,stnum=0,gps_check=0;
    char ns='A',ew='B',aunit='m';
    float time=0.0,latitude=0.0,longitude=0.0,hacu=0.0,altitude=0.0;
    for(int i=1; i<1000; i++) {
        sensor.gga_sensing(&time, &latitude, &ns, &longitude, &ew, &quality, &stnum, &hacu, &altitude, &aunit, &gps_check);
        if((gps_check==0)|(gps_check==1)) {
            pc.printf("GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f,%c\r\n",time,latitude,ns,longitude,ew,quality,stnum,hacu,altitude,aunit);
        }
    }
}