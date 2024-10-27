#include "lib.h"
#include <stdio.h>
#include <cmath>
#include <fstream>

int main() {
    printer("LED data\n");

    std::ofstream f;
    std::string file_name = "/Users/ludwin/Elektronik/RD128/RD128_electronics/RD128_display/helper/output.txt";
    f.open(file_name);

    double LED_circle = 58.5;
    double Via_circle = 55.9;

// LED_col0...LED_col7
// supply of LEDs, 8 circles

    double radial_distance, theta;
    double LED_x, LED_y, Via_x, Via_y, s_start_x, s_start_y, s_end_x, s_end_y;
    std::string text, line1, line2, line3, front, back;
    int LED_nr, rest, net;

    for (LED_nr =0; LED_nr < 128; LED_nr++) {
        radial_distance = 132.825 - LED_nr*2.1;
        theta = radial_distance/60;

        rest = LED_nr%8;
        if (LED_nr>63) rest = 7 - rest;

        if (rest==0) net=3;
        else net=rest+4;

        if (LED_nr<64) {
            front = "\"F.Cu\"";
            back = "\"B.Cu\"";
        }
        else {
            front = "\"B.Cu\"";
            back = "\"F.Cu\"";
        }

        LED_x = - LED_circle * sin(theta);
        LED_y = - LED_circle * cos(theta);
        Via_x = - (Via_circle - 0.6 * rest) * sin(theta);
        Via_y = - (Via_circle - 0.6 * rest) * cos(theta);


        s_start_x = Via_x;
        s_start_y = Via_y;

        text = "LED: " + std::to_string(LED_nr)+"    x via= "+ std::to_string(Via_x)+"   y via= "+std::to_string(Via_y)+"\n";
        line1 ="(segment (start "+std::to_string(LED_x)+" "+std::to_string(LED_y)+") (end "+std::to_string(Via_x)+" "+std::to_string(Via_y)+") (width 0.2) (layer "+front+") (net "+std::to_string(net)+") (tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
        line2 ="(via (at "+std::to_string(Via_x)+" "+std::to_string(Via_y)+") (size 0.5) (drill 0.3) (layers \"F.Cu\" \"B.Cu\") (net "+std::to_string(net)+")(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";

        printer (line1);
        printer (line2);
        f<<line1;
        f<<line2;

        int i_max=17;
        if ((LED_nr>55)&&(LED_nr<64)) {
            i_max=4*(8-rest)-1;
        }

        for (int i = 1; i<i_max; i++) {
            s_end_x = - (Via_circle - 0.6 * rest) * sin(theta-i*0.0175);
            s_end_y = - (Via_circle - 0.6 * rest) * cos(theta-i*0.0175);

            line3 = "(segment (start "+std::to_string(s_start_x)+" "+std::to_string(s_start_y)+") (end "+std::to_string(s_end_x)+" "+std::to_string(s_end_y)+") (width 0.2) (layer "+back+") (net "+std::to_string(net)+")(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
            printer (line3);
            f<<line3;
            s_start_x = s_end_x;
            s_start_y = s_end_y;
        }

        if (LED_nr<8) {
            s_start_x = Via_x;
            s_start_y = Via_y;
            for (int i = 1; i<32; i++) {
                s_end_x = - (Via_circle - 0.6 * rest) * sin(theta+i*0.0175);
                s_end_y = - (Via_circle - 0.6 * rest) * cos(theta+i*0.0175);

                line3 = "(segment (start "+std::to_string(s_start_x)+" "+std::to_string(s_start_y)+") (end "+std::to_string(s_end_x)+" "+std::to_string(s_end_y)+") (width 0.2) (layer "+back+") (net "+std::to_string(net)+")(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
                printer (line3);
                f<<line3;
                s_start_x = s_end_x;
                s_start_y = s_end_y;
            }
        }

    }

// Ground, +5V circle

    double theta1, C_ground_circle, C_5V_circle, C_group_circle;
    theta1 = 132.825/60;
    C_ground_circle = 50.8;
    C_5V_circle = 48;

    s_start_x = -C_ground_circle * sin(theta1);
    s_start_y = -C_ground_circle * cos(theta1);

    for (int i = 1; i<257; i++) {
        s_end_x = -C_ground_circle * sin(theta1-i*0.0175);
        s_end_y = -C_ground_circle * cos(theta1-i*0.0175);
            line3 = "(segment (start "+std::to_string(s_start_x)+" "+std::to_string(s_start_y)+") (end "+std::to_string(s_end_x)+" "+std::to_string(s_end_y)+") (width 0.6) (layer \"F.Cu\") (net 2)(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
            printer (line3);
            f<<line3;
            s_start_x = s_end_x;
            s_start_y = s_end_y;
    }


    s_start_x = -C_5V_circle * sin(theta1);
    s_start_y = -C_5V_circle * cos(theta1);

    for (int i = 1; i<257; i++) {
        s_end_x = -C_5V_circle * sin(theta1-i*0.0175);
        s_end_y = -C_5V_circle * cos(theta1-i*0.0175);
            line3 = "(segment (start "+std::to_string(s_start_x)+" "+std::to_string(s_start_y)+") (end "+std::to_string(s_end_x)+" "+std::to_string(s_end_y)+") (width 0.75) (layer \"B.Cu\") (net 1)(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
            printer (line3);
            f<<line3;
            s_start_x = s_end_x;
            s_start_y = s_end_y;
    }


//////////
// C_group circles (4x4 lines each)

    C_group_circle = 46.5;
    for (int line=0; line<4; line++){
        s_start_x = -(C_group_circle-line*0.6) * sin(theta1);
        s_start_y = -(C_group_circle-line*0.6) * cos(theta1);

        int i_max;
        i_max = 2 + line * 16;

        for (int i = 1; i<i_max; i++) {
            s_end_x = -(C_group_circle-line*0.6) * sin(theta1-i*0.0175);
            s_end_y = -(C_group_circle-line*0.6) * cos(theta1-i*0.0175);
                line3 = "(segment (start "+std::to_string(s_start_x)+" "+std::to_string(s_start_y)+") (end "+std::to_string(s_end_x)+" "+std::to_string(s_end_y)+") (width 0.2) (layer \"F.Cu\") (net "+std::to_string(line+27)+")(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
                printer (line3);
                f<<line3;
                s_start_x = s_end_x;
                s_start_y = s_end_y;
        }
    }

    for (int line=0; line<4; line++){
        s_start_x = -(C_group_circle-line*0.6) * sin(theta1);
        s_start_y = -(C_group_circle-line*0.6) * cos(theta1);

        int i_max;
        i_max = 66 + line * 16;

        for (int i = 1; i<i_max; i++) {
            s_end_x = -(C_group_circle-line*0.6) * sin(theta1-i*0.0175);
            s_end_y = -(C_group_circle-line*0.6) * cos(theta1-i*0.0175);
                line3 = "(segment (start "+std::to_string(s_start_x)+" "+std::to_string(s_start_y)+") (end "+std::to_string(s_end_x)+" "+std::to_string(s_end_y)+") (width 0.2) (layer \"B.Cu\") (net "+std::to_string(line+31)+")(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
                printer (line3);
                f<<line3;
                s_start_x = s_end_x;
                s_start_y = s_end_y;
        }
    }

    theta1 = -133.875/60;

    for (int line=0; line<4; line++){
        s_start_x = -(C_group_circle-line*0.6) * sin(theta1);
        s_start_y = -(C_group_circle-line*0.6) * cos(theta1);

        int i_max;
        i_max = 2 + line * 16;

        for (int i = 1; i<i_max; i++) {
            s_end_x = -(C_group_circle-line*0.6) * sin(theta1+i*0.0175);
            s_end_y = -(C_group_circle-line*0.6) * cos(theta1+i*0.0175);
                line3 = "(segment (start "+std::to_string(s_start_x)+" "+std::to_string(s_start_y)+") (end "+std::to_string(s_end_x)+" "+std::to_string(s_end_y)+") (width 0.2) (layer \"F.Cu\") (net "+std::to_string(line+43)+")(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
                printer (line3);
                f<<line3;
                s_start_x = s_end_x;
                s_start_y = s_end_y;
        }
    }

    for (int line=0; line<4; line++){
        s_start_x = -(C_group_circle-line*0.6) * sin(theta1);
        s_start_y = -(C_group_circle-line*0.6) * cos(theta1);

        int i_max;
        i_max = 66 + line * 16;

        for (int i = 1; i<i_max; i++) {
            s_end_x = -(C_group_circle-line*0.6) * sin(theta1+i*0.0175);
            s_end_y = -(C_group_circle-line*0.6) * cos(theta1+i*0.0175);
                line3 = "(segment (start "+std::to_string(s_start_x)+" "+std::to_string(s_start_y)+") (end "+std::to_string(s_end_x)+" "+std::to_string(s_end_y)+") (width 0.2) (layer \"B.Cu\") (net "+std::to_string(line+47)+")(tstamp c98c8beb-da98-4656-8da4-32e4cf1c68d6))\n";
                printer (line3);
                f<<line3;
                s_start_x = s_end_x;
                s_start_y = s_end_y;
        }
    }



    f.close();

    return 0;
}
