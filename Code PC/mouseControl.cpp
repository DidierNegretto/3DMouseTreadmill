//============================================================================
// Name        : mouseControl.cpp
// Author      : Didier
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "mouse/mavlink.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <ctime>

using namespace std;
char portname[22] = "/dev/cu.usbmodem14101";
mavlink_heartbeat_t heart;

int set_interface_attribs (int fd, int speed, int parity){
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
            cout<< "error %d from tcgetattr"<< errno;
            return -1;
    }

    cfsetospeed (&tty, speed);
    cfsetispeed (&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    // disable IGNBRK for mismatched speed tests; otherwise receive break
    // as \000 chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= parity;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
    {
            cout<<"error %d from tcsetattr"<<errno;
            return -1;
    }
    return 0;
}

void set_blocking (int fd, int should_block){
    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (fd, &tty) != 0)
    {
        cout<<"error %d from tggetattr"<<errno;
            return;
    }

    tty.c_cc[VMIN]  = should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    if (tcsetattr (fd, TCSANOW, &tty) != 0)
        cout<< "error %d setting term attributes" <<errno;
}

void comm_receive(int fd) {

    static mavlink_message_t msg;
    static mavlink_status_t r;
    static uint8_t byte;


    while(read(fd, &byte, 1) > 0 )
    {
        if (mavlink_parse_char(0,byte,&msg,&r)){
            // uint8_t mode = cout<<"Received message with ID" <<(int)msg.msgid<<", sequence:"<<(int)msg.seq<<endl;
            switch(msg.msgid){

                case MAVLINK_MSG_ID_HEARTBEAT:
                    mavlink_msg_heartbeat_decode(&msg, &heart);
                    //cout<<"Received heart beat. Mode"<<(int)heart.mode<<" time"<<(int)heart.time<<endl;
                    return;
                    break;
                default:
                    cout<<"ID NON VALID";
                    break;
            }
        }
    }
    return;
}

void comm_send(int fd, uint8_t mode){
    mavlink_message_t msg;
    uint8_t buf[100];

    mavlink_msg_heartbeat_pack(0,0, &msg, mode, 0);

    // Copy the message to the send buffer
    uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
    uint16_t written = write(fd, buf, len);
    if (len!=written)
        cout<<"len = "<<len<<" written = "<<written<<endl;

    return;
}
int main() {

    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);


    set_interface_attribs (fd, B230400, 0);  // set speed to 115,200 bps, 8n1 (no parity)
    set_blocking (fd, 0);                // set no blocking

	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	heart.mode = 2;
    uint8_t mode = 239;
    int count = 0;

    while(1){

       count = 0;
        while(heart.mode != mode){
            comm_send(fd, mode);
            comm_receive(fd);
            count++;
        }
        cout<< "Needed = "<<count<<" to transmit information"<<endl;
        mode+=23;


    }


    return 0;
}
