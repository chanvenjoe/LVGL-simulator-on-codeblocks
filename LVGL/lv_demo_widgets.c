/**
 * @file lv_demo_widgets.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
//#include "../../lv_examples.h"
#include "lv_demo_widgets.h"
#include "Lcd.config"
#include "stdio.h"
#if 1

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void event_handler(lv_obj_t * obj, lv_event_t event);
static void slider_event_cb(lv_obj_t * slider, lv_event_t e);
#if LV_USE_THEME_MATERIAL
static void color_chg_event_cb(lv_obj_t * sw, lv_event_t e);
#endif
#if LV_DEMO_WIDGETS_SLIDESHOW
static void tab_content_anim_create(lv_obj_t * parent);
static void tab_changer_task_cb(lv_task_t * task);
#endif

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t * page;
static lv_obj_t * list;
static lv_style_t style_box;
static lv_style_t label_big_style;
static lv_style_t regular_60;
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_demo_widgets(void)
{

    LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_secondary(),
                LV_THEME_MATERIAL_FLAG_DARK,
                lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
    lv_style_init(&label_big_style);
    lv_style_set_text_opa(&label_big_style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_text_font(&label_big_style, LV_STATE_DEFAULT, &tym_bold_32);
    
    lv_style_init(&regular_60);
    lv_style_set_text_opa(&regular_60, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_text_font(&regular_60, LV_STATE_DEFAULT, &tym_regular_60);

    //SettingCreat();
    //MasterMenu5_create(lv_scr_act());
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

void MasterMenu1_create(lv_obj_t * parent)
{

    lv_obj_t * btn;
     btn =  lv_btn_create(parent,NULL);
    lv_obj_set_size(btn,320,40);
    lv_obj_set_pos(btn, 0, 0);

    lv_obj_t * title_label =  lv_label_create(btn,NULL);
    lv_label_set_text(title_label, TYM_SYMBOL_BACK_LEFT"  Master Menu");
    lv_label_set_align(title_label,LV_LABEL_ALIGN_LEFT);
    lv_btn_set_layout(btn,LV_LAYOUT_ROW_MID);

    list = lv_list_create(parent, NULL);
    lv_list_set_scroll_propagation(list, true);
    lv_obj_set_size(list, 320, 200);
    lv_obj_set_pos(list,0,40);

    const char * txts[] = {TYM_SYMBOL_ACTIVITY_ON, "Ducking", TYM_SYMBOL_ACTIVITY_ON, "Master EQ ",
            TYM_SYMBOL_ACTIVITY_ON, "uto Feedback", TYM_SYMBOL_ACTIVITY_ON, "Master FX  ",
            TYM_SYMBOL_ACTIVITY_ON, "Bluetooth",  TYM_SYMBOL_ACTIVITY_ON, "GPS", TYM_SYMBOL_ACTIVITY_ON, "USB",
            TYM_SYMBOL_ACTIVITY_ON, "Setting", TYM_SYMBOL_ACTIVITY_ON, "Pass Through", NULL};

    uint32_t i;
    for(i = 0; txts[i] != NULL; i+=2) {
        btn = lv_list_add_btn(list, txts[i], txts[i+1]);
        lv_obj_move_foreground(lv_list_get_btn_label(btn));
        lv_btn_set_checkable(btn, true);
        lv_obj_set_event_cb(btn, event_handler);
        lv_group_add_obj(grp, btn);
    }
}

void MasterMenu2_create(lv_obj_t * parent)
{
    lv_obj_t * btn;
     btn =  lv_btn_create(lv_scr_act(),NULL);
    lv_obj_set_size(btn,320,40);
    lv_obj_set_pos(btn, 0, 0);

    lv_obj_t * title_label1 =  lv_label_create(btn,NULL);
    lv_label_set_recolor(title_label1, true);
    lv_label_set_text(title_label1, "#0000ff "TYM_SYMBOL_BLUETOOTH_ON"#""#0000ff                 EQ#"" FX DK");
    lv_label_set_align(title_label1, LV_LABEL_ALIGN_CENTER);
    lv_label_set_align(title_label1,LV_LABEL_ALIGN_LEFT);
    lv_btn_set_layout(btn,LV_LAYOUT_ROW_MID);

    btn =  lv_btn_create(lv_scr_act(),NULL);
    lv_obj_set_size(btn,320,160);
    lv_obj_set_pos(btn, 0, 40);
    lv_obj_t * title_label2 =  lv_label_create(btn,NULL);
    lv_obj_add_style(title_label2, LV_LABEL_PART_MAIN, &label_big_style);
    lv_label_set_text(title_label2, "PRX ONE \n\n");
    lv_obj_align(title_label2, title_label1, LV_ALIGN_CENTER, 0, 0);

    lv_obj_t * title_label3 =  lv_label_create(btn,NULL);
    lv_label_set_text(title_label3, "JBL PRX ONE");
    /* Shift the second label down and to the right by 2 pixel */
    lv_obj_align(title_label3, title_label2, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    btn =  lv_btn_create(lv_scr_act(),NULL);
    lv_obj_set_size(btn,320,40);
    lv_obj_set_pos(btn, 0, 200);
    lv_obj_t * lmeter;
    lmeter = lv_linearscale_create(btn, NULL);
    lv_linemeter_set_range(lmeter, 0, 30);                   /*Set the range*/
    lv_linemeter_set_value(lmeter, 20);                       /*Set the current value*/
    lv_linemeter_set_scale(lmeter, 0, 21);                  /*Set the angle and number of lines*/
    lv_obj_set_size(lmeter, 300, 20);
    lv_obj_align(lmeter, NULL, LV_ALIGN_CENTER, 0, 0);

}

void MasterMenu3_create(lv_obj_t * parent)
{

    lv_obj_t * btn;
     btn =  lv_btn_create(lv_scr_act(),NULL);
    lv_obj_set_size(btn,320,40);
    lv_obj_set_pos(btn, 0, 0);

    lv_obj_t * title_label =  lv_label_create(btn,NULL);
    lv_label_set_text(title_label, TYM_SYMBOL_ACTIVITY_ON"  Master Menu");
    lv_label_set_align(title_label,LV_LABEL_ALIGN_LEFT);
    lv_btn_set_layout(btn,LV_LAYOUT_ROW_MID);

    btn =  lv_btn_create(lv_scr_act(),NULL);
    lv_obj_set_size(btn,320,40);
    lv_obj_set_pos(btn, 0, 40);
    title_label =  lv_label_create(btn,NULL);
    lv_label_set_recolor(title_label, true);
    lv_label_set_text(title_label,"Rock""#0000ff "TYM_SYMBOL_TICK_MARK"#");
    lv_label_set_align(title_label,LV_LABEL_ALIGN_CENTER);
    lv_btn_set_layout(btn,LV_LAYOUT_COLUMN_MID);

    lv_obj_t * chart;
    chart = lv_chart_create(lv_scr_act(), NULL);
    lv_obj_set_size(chart, 320, 160);
    lv_obj_set_pos(chart,0,80);
    lv_obj_align(chart, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);   /*Show lines and points too*/

    lv_chart_series_t * ser1 = lv_chart_add_series(chart, LV_COLOR_YELLOW);

    /*Set the next points on 'ser1'*/
    lv_chart_set_next(chart, ser1, 10);
    lv_chart_set_next(chart, ser1, 10);
    lv_chart_set_next(chart, ser1, 10);
    lv_chart_set_next(chart, ser1, 10);
    lv_chart_set_next(chart, ser1, 10);
    lv_chart_set_next(chart, ser1, 10);
    lv_chart_set_next(chart, ser1, 10);
    lv_chart_set_next(chart, ser1, 30);
    lv_chart_set_next(chart, ser1, 70);
    lv_chart_set_next(chart, ser1, 90);

    lv_chart_refresh(chart); /*Required after direct set*/

}

void MasterMenu4_create(lv_obj_t * parent)
{

    static const char * btns[] ={"Continue", "Cancel", ""};

    lv_obj_t * mbox1 = lv_msgbox_create(lv_scr_act(), NULL);
    lv_msgbox_set_text(mbox1, "A message box with two buttons.");
    lv_msgbox_add_btns(mbox1, btns);
    lv_obj_set_width(mbox1, 200);
    lv_obj_set_event_cb(mbox1, event_handler);
    lv_obj_align(mbox1, NULL, LV_ALIGN_CENTER, 0, 0); /*Align to the corner*/
}

void MasterMenu5_create(lv_obj_t * parent,const uint8* eqidx, const uint8* chidx, void *vol,bool tag)
{
//    uint8 temp[9] =  {TYM_SYMBOL_VOLUME_ON"   "};
//    temp[6] = vol;
    //sprintf((char *)temp, "%d",vol);
    lv_obj_t * btn;
     btn =  lv_btn_create(parent,NULL);
    lv_obj_set_size(btn,320,40);
    lv_obj_set_pos(btn, 0, 0);

    lv_obj_t * title_label1 =  lv_label_create(btn,NULL);
    lv_label_set_recolor(title_label1, true);
    lv_label_set_text(title_label1, (char *)eqidx);
    lv_label_set_align(title_label1,LV_LABEL_ALIGN_LEFT);
    lv_btn_set_layout(btn,LV_LAYOUT_ROW_MID);

    btn =  lv_btn_create(parent,NULL);
    lv_obj_set_size(btn,320,160);
    lv_obj_set_pos(btn, 0, 40);

    lv_obj_t * title_label2 =  lv_label_create(btn,NULL);
    lv_label_set_text(title_label2, (char *)chidx);
    lv_btn_set_layout(btn, LV_LAYOUT_OFF);
    lv_obj_align(title_label2, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 20);

    lv_obj_t * title_label3 =  lv_label_create(btn,NULL);
    lv_obj_add_style(title_label3, LV_LABEL_PART_MAIN, &regular_60);
    if (tag == 0)
    {
        lv_label_set_text_fmt(title_label3,TYM_SYMBOL_VOLUME_ON"   %d",vol);
    }
    else{
        lv_label_set_text_fmt(title_label3,TYM_SYMBOL_VOLUME_ON"   %0.1f",*(float *)vol);
    }
    lv_obj_align(title_label3, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 80);

    lv_obj_t * title_label4 =  lv_label_create(btn,NULL);
    lv_label_set_text(title_label4, "dB");
    lv_obj_align(title_label4, title_label3, LV_ALIGN_OUT_RIGHT_BOTTOM, 0, -10);

    btn =  lv_btn_create(parent,NULL);
    lv_obj_set_size(btn,320,40);
    lv_obj_set_pos(btn, 0, 200);
    lv_obj_t * bar1 = lv_bar_create(btn, NULL);
    lv_obj_set_size(bar1, 300, 20);
    lv_obj_align(bar1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_bar_set_anim_time(bar1, 2000);
    lv_bar_set_value(bar1, 100, LV_ANIM_ON);
}

void focus_cb(lv_group_t * g,lv_obj_t * page,bool direction)
{
    //if(cont_Satellites == NULL) return;
    if(direction)
    {
        lv_list_down(list);
    }
    else
    {
        lv_list_up(list);    
    }
    lv_obj_t * obj = lv_group_get_focused(g);
    if(lv_obj_get_parent(obj) == lv_page_get_scrl(page))
    {
        lv_page_focus(list, obj, LV_ANIM_ON);
    }
}

static void slider_event_cb(lv_obj_t * slider, lv_event_t e)
{
    if(e == LV_EVENT_VALUE_CHANGED) {
        if(lv_slider_get_type(slider) == LV_SLIDER_TYPE_NORMAL) {
            static char buf[16];
            lv_snprintf(buf, sizeof(buf), "%d", lv_slider_get_value(slider));
            lv_obj_set_style_local_value_str(slider, LV_SLIDER_PART_KNOB, LV_STATE_DEFAULT, buf);
        } else {
            static char buf[32];
            lv_snprintf(buf, sizeof(buf), "%d-%d", lv_slider_get_left_value(slider), lv_slider_get_value(slider));
            lv_obj_set_style_local_value_str(slider, LV_SLIDER_PART_INDIC, LV_STATE_DEFAULT, buf);
        }

    }

}

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_VALUE_CHANGED) {
        //printf("Button: %s\n", lv_msgbox_get_active_btn_text(obj));
    }
}

#if LV_USE_THEME_MATERIAL
static void color_chg_event_cb(lv_obj_t * sw, lv_event_t e)
{
    if(LV_THEME_DEFAULT_INIT != lv_theme_material_init) return;
    if(e == LV_EVENT_VALUE_CHANGED) {
        uint32_t flag = LV_THEME_MATERIAL_FLAG_LIGHT;
        if(lv_switch_get_state(sw)) flag = LV_THEME_MATERIAL_FLAG_DARK;

        LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_secondary(),
                flag,
                lv_theme_get_font_small(), lv_theme_get_font_normal(), lv_theme_get_font_subtitle(), lv_theme_get_font_title());
    }
}
#endif

#if LV_DEMO_WIDGETS_SLIDESHOW

static void tab_content_anim_create(lv_obj_t * parent)
{
    lv_anim_t a;
    lv_obj_t * scrl = lv_page_get_scrl(parent);
    lv_coord_t y_start = lv_obj_get_style_pad_top(parent, LV_PAGE_PART_BG);
    lv_coord_t anim_h = lv_obj_get_height(scrl) - lv_obj_get_height_fit(parent);
    uint32_t anim_time = lv_anim_speed_to_time(LV_DPI, 0, anim_h);

    lv_anim_init(&a);
    lv_anim_set_var(&a, scrl);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
    lv_anim_set_values(&a, y_start, y_start - anim_h);
    lv_anim_set_time(&a, anim_time);
    lv_anim_set_playback_time(&a, anim_time);
    lv_anim_set_playback_delay(&a, 200);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&a, 200);
    lv_anim_start(&a);
}

static void tab_changer_task_cb(lv_task_t * task)
{
    uint16_t act = lv_tabview_get_tab_act(tv);
    act++;
    if(act >= 3) act = 0;

    lv_tabview_set_tab_act(tv, act, LV_ANIM_ON);

    switch(act) {
    case 0:
        tab_content_anim_create(t1);
        break;
    case 1:
        tab_content_anim_create(t2);
        break;
    case 2:
        tab_content_anim_create(t3);
        break;
    }
}
#endif

#endif
