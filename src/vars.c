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
