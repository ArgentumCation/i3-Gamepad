#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <cstdio>
extern "C" {
#include <xdo.h>
}
#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

#define JS_BUTTON_PRESSED       0x01
#define JS_BUTTON_RELEASED      0x00

#define JS_AXIS_LEFT_X          0
#define JS_AXIS_LEFT_Y          1
#define JS_AXIS_DPAD_X          6
#define JS_AXIS_DPAD_Y          7

#define JS_BUTTON_A             0
#define JS_BUTTON_B             1
#define JS_BUTTON_X             2
#define JS_BUTTON_Y             3
#define JS_BUTTON_BACK          6
#define JS_BUTTON_START         7
#define JS_BUTTON_LSTICK        9
#define JS_BUTTON_RSTICK        10
#define JS_BUTTON_HOME          8
#define JS_BUTTON_LB            4
#define JS_BUTTON_RB            5
struct js_event {
    	uint32_t time;     /* event timestamp in milliseconds */
		int16_t value;    /* value */
		uint8_t type;      /* event type */
		uint8_t number;    /* axis/button number */
};


int main(){
    int fd = open("/dev/input/js3", O_RDONLY);
    struct js_event gamepad_event;
    xdo_t *x = xdo_new(NULL);
  
    while(true){
        read(fd, &gamepad_event, sizeof(gamepad_event));
//        std::cout << gamepad_event.type <<  std::endl;
        if(gamepad_event.type == JS_EVENT_BUTTON && gamepad_event.value == JS_BUTTON_PRESSED){
            switch(gamepad_event.number){
                case JS_BUTTON_X:
                    xdo_click_window(x,CURRENTWINDOW,1);
                    std::cout<< "X";
                    break;
                case JS_BUTTON_B:
                    //Xdo send escape key?
                    xdo_send_keysequence_window(x, CURRENTWINDOW, "Escape",20);
                    std::cout<< "B";
                    break;
                case JS_BUTTON_A:
                    xdo_send_keysequence_window(x, CURRENTWINDOW, "Return",20);
                    std::cout<< "A";
                    break;
                case JS_BUTTON_Y:
                    std::cout << "Y";
                    break;
                case JS_BUTTON_HOME:
                    std::cout << "Home";
                    xdo_send_keysequence_window(x, CURRENTWINDOW, "Super+space",20);
                    //system("exec rofi -combi-modi \"drun#run\" -show combi -show-icons");
                    break;
                case JS_BUTTON_RB:
                    system("exec i3-msg workspace next");
                    break;
                case JS_BUTTON_LB:
                    system("exec i3-msg workspace prev");
                    break;



            }
            std::cout << std::endl;
            std::cout << "Button Pressed: " << (int)gamepad_event.number << std::endl;
        }
        else if (gamepad_event.type == JS_EVENT_AXIS){
            auto val = gamepad_event.value * 0.001;
            if(val == 0){
                continue;
            }
            switch(gamepad_event.number){
                case JS_AXIS_LEFT_X:
                    xdo_move_mouse_relative(x,val,0);
                     break; 
                case JS_AXIS_LEFT_Y:
                    xdo_move_mouse_relative(x,0,val);
                    break;
                case JS_AXIS_DPAD_X:
                    xdo_send_keysequence_window(x,CURRENTWINDOW, (val < 0) ? "Left" : "Right",20);
                    break;
                case JS_AXIS_DPAD_Y:
                    xdo_send_keysequence_window(x,CURRENTWINDOW, (val < 0) ? "Up"  : "Down", 20);
                    break;
 
            }
            std::cout << (int)gamepad_event.number <<": " << gamepad_event.value << std::endl;
        }
    }
    xdo_free(x);
    return 0;
}
