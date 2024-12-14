#include <actions.h>
#include <vars.h>
#include <ui.h>




  void action_action_increase_temp(lv_event_t * e){

    int min = get_var_min_temp_set_point();
    int max = get_var_max_temp_set_point();
    int step = get_var_step_temp_set_point();
    int set = get_var_temp_set_point();

    if(((set + step) <= max) && (set >= min)){
      set = set + step;
      set_var_temp_set_point(set);
    }
        //loadScreen(SCREEN_ID_PAGE2);
 };
 void action_action_decrease_temp(lv_event_t * e){
    int set = get_var_temp_set_point();
    int min = get_var_min_temp_set_point();
    int max = get_var_max_temp_set_point();
    int step = get_var_step_temp_set_point();
   

    if(((set - step) >= min) && (set <= max)){
      set = set - step;
      set_var_temp_set_point(set);
    }};

void action_timer_increase_act(lv_event_t * e){
  int set = get_var_timer_set_min();
  int step = 1;
  lv_event_code_t code = lv_event_get_code(e);
  
  if ( code == LV_EVENT_LONG_PRESSED_REPEAT){
    step = 10;
  } else {
    step =1;
  }
  set = set + step;
  if (set <= 900){
    set_var_timer_set_min(set);
  }
  //        loadScreen(SCREEN_ID_PAGE2);
};
void action_timer_decrease_act(lv_event_t * e){
  int set = get_var_timer_set_min();
    int step = 1;
  lv_event_code_t code = lv_event_get_code(e);
  
  if ( code == LV_EVENT_LONG_PRESSED_REPEAT){
    step = 10;
  } else {
    step =1;
  }
  set = set - step;

  if(set=0){
    set_var_timer_set_min(set)
;  }

};


 void action_start_clicked_act(lv_event_t * e){
    set_var_start_clicked(true);
 };


 void action_goto_main(lv_event_t * e){
  loadScreen(SCREEN_ID_MAIN);
 };

void action_goto_status_page_act(lv_event_t *e) {
    // TODO: Implement action goto_status_page_act here
    loadScreen(SCREEN_ID_STATUS_PAGE);
}
