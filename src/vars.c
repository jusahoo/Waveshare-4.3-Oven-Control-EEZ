#include <vars.h>

int tempSet = 0;
int minTempSet = 0;
int maxTempSet = 0;
int stepTempSet = 0;
int initTimer = 0;
bool started = false;

 int32_t get_var_temp_set_point(){
    return tempSet;
 };
 void set_var_temp_set_point(int32_t value){
    tempSet = value;
 };

 //////////// Variables for temperature setpoint

int32_t get_var_min_temp_set_point(){
   return minTempSet;

};
 void set_var_min_temp_set_point(int32_t value){
   minTempSet = value;
 };
 int32_t get_var_max_temp_set_point(){
   return maxTempSet;
 };
 void set_var_max_temp_set_point(int32_t value){
   maxTempSet = value;
 };

 int32_t get_var_step_temp_set_point(){
   return stepTempSet;

 };
 void set_var_step_temp_set_point(int32_t value){
   stepTempSet = value;
 };

 ////////Timer variables

 int32_t get_var_timer_set_min(){
  return initTimer;
 };
 void set_var_timer_set_min(int32_t value){
  initTimer = value;
 };
 int32_t get_var_timer_remain_min(){

 };
 void set_var_timer_remain_min(int32_t value){
  
 };

  bool get_var_start_clicked(){
    return started;
  };

 void set_var_start_clicked(bool value){
  started = value;
 };

bool light_btn_clicked;

bool get_var_light_btn_clicked() {
    return light_btn_clicked;
}

void set_var_light_btn_clicked(bool value) {
    light_btn_clicked = value;
}

#include "vars.h"

bool light_state;

bool get_var_light_state() {
    return light_state;
}

void set_var_light_state(bool value) {
    light_state = value;
}

bool fan_btn_clicked;

bool get_var_fan_btn_clicked() {
    return fan_btn_clicked;
}

void set_var_fan_btn_clicked(bool value) {
    fan_btn_clicked = value;
}


bool fan_state;

bool get_var_fan_state() {
    return fan_state;
}

void set_var_fan_state(bool value) {
    fan_state = value;
}

bool door_motor_btn_clicked;

bool get_var_door_motor_btn_clicked() {
    return door_motor_btn_clicked;
}

void set_var_door_motor_btn_clicked(bool value) {
    door_motor_btn_clicked = value;
}

bool door_motor_state;

bool get_var_door_motor_state() {
    return door_motor_state;
}

void set_var_door_motor_state(bool value) {
    door_motor_state = value;
}

bool bot_res_btn_clicked;

bool get_var_bot_res_btn_clicked() {
    return bot_res_btn_clicked;
}

void set_var_bot_res_btn_clicked(bool value) {
    bot_res_btn_clicked = value;
}
bool bot_res_state;

bool get_var_bot_res_state() {
    return bot_res_state;
}

void set_var_bot_res_state(bool value) {
    bot_res_state = value;
}
bool top_res_btn_clicked;

bool get_var_top_res_btn_clicked() {
    return top_res_btn_clicked;
}

void set_var_top_res_btn_clicked(bool value) {
    top_res_btn_clicked = value;
}


bool top_res_state;

bool get_var_top_res_state() {
    return top_res_state;
}

void set_var_top_res_state(bool value) {
    top_res_state = value;
}

bool bake_btn_clicked;

bool get_var_bake_btn_clicked() {
    return bake_btn_clicked;
}

void set_var_bake_btn_clicked(bool value) {
    bake_btn_clicked = value;
}


int32_t heating_mode;

int32_t get_var_heating_mode() {
    return heating_mode;
}

void set_var_heating_mode(int32_t value) {
    heating_mode = value;
}
