#include "..\inc\cfg_items.h"

__root const CFG_HDR cfghdr0={CFG_CBOX,"用户界面",0,2};
__root const int cfg_dir_dial=1;
__root const CFG_CBOX_ITEM cfgcbox0[2]={"号码列表","直接拨打"};

__root const CFG_HDR cfghdr1 = {CFG_CBOX,"直接拨打按键",0,2};
__root const int cfg_green=1;
__root const CFG_CBOX_ITEM cfgcbox1[2] = {"中键拨号绿键短信","绿键拨号中键短信"};

__root const CFG_HDR cfghdr58={CFG_STR_UTF8,"通讯录目录",3,127};
__root const char root_dir[128]="0:\\\x1F\xE7\xB3\xBB\xE7\xBB\x9F\\apo\\addr";

__root const CFG_HDR cfghdr2 = {CFG_CBOX,"缺省显示号码",0,5};
__root const int cfg_deft_item = 2;
__root const CFG_CBOX_ITEM cfgcbox2[5] = {"办公室","传真","手机","住宅","传真2"};

__root const CFG_HDR cfghdr3 = {CFG_UINT,"图标间距",0,6};
__root const int cfg_icon_gaps=0;

__root const CFG_HDR cfghdr4 = {CFG_UINT,"条目间距",0,6};
__root const int cfg_item_gaps=2;

__root const CFG_HDR cfghdr5 = {CFG_UINT,"条目边距",0,6};
__root const int cfg_gaps_to_side=1;

__root const CFG_HDR cfghdr63 = {CFG_CHECKBOX,"长条目滚动显示",0,1};
__root const int cfg_scroll_item=1;

__root const CFG_HDR cfghdr60 = {CFG_UINT,"条目滚动步长",0,30};
__root const int cfg_scroll_step=2;

__root const CFG_HDR cfghdr6 = {CFG_CBOX,"列表中姓名对齐方式",0,3};
__root const int cfg_name_align=0;
__root const CFG_CBOX_ITEM cfgcbox6[3] = {"左对齐","居中","右对齐"};

__root const CFG_HDR cfghdr7 = {CFG_CBOX,"选中姓名对齐方式",0,3};
__root const int cfg_hl_name_align=0;
__root const CFG_CBOX_ITEM cfgcbox7[3] = {"左对齐","居中","右对齐"};

__root const CFG_HDR cfghdr8 = {CFG_CBOX,"选中号码对齐方式",0,3};
__root const int cfg_hl_num_align=0;
__root const CFG_CBOX_ITEM cfgcbox8[3] = {"左对齐","居中","右对齐"};

__root const CFG_HDR cfghdr9 = {CFG_CBOX,"在拨打时禁用",0,2};
__root const int cfg_disable_when_calling=0;
__root const CFG_CBOX_ITEM cfgcbox9[2] = {"否","是"};

__root const CFG_HDR cfghdr10 = {CFG_CBOX,"仅输入一个号码时禁用",0,2};
__root const int cfg_disable_one_number=0;
__root const CFG_CBOX_ITEM cfgcbox10[2] = {"否","是"};

__root const CFG_HDR cfghdr11 = {CFG_CBOX,"拨号时允许IP功能",0,2};
__root const int cfg_input_ip = 1;
__root const CFG_CBOX_ITEM cfgcbox11[2] = {"否","是"};

__root const CFG_HDR cfghdr12 = {CFG_COORDINATES,"拨号号码输入位置",0,0};
__root const int cfg_start_X = 6;
__root const int cfg_start_Y = 18;

__root const CFG_HDR cfghdr13 = {CFG_CBOX,"边框类型",0,2};
__root const int cfg_frame_flag = 0;
__root const CFG_CBOX_ITEM cfgcbox13[2] = {"实线","虚线"};

__root const CFG_HDR cfghdr14 = {CFG_COLOR,"边框颜色",0,24};
__root const int cfg_frame_color=23;

__root const CFG_HDR cfghdr15 = {CFG_COORDINATES,"边框左上角位置",0,0};
__root const int cfg_dialog_x1 = 0;
__root const int cfg_dialog_y1 = 40;

__root const CFG_HDR cfghdr16 = {CFG_COORDINATES,"边框右下角位置",0,0};
__root const int cfg_dialog_x2 = 130;
__root const int cfg_dialog_y2 = 160;

__root const CFG_HDR cfghdr17 = {CFG_CBOX,"选择框类型",0,2};
__root const int cfg_hl_frame_flag = 0;
__root const CFG_CBOX_ITEM cfgcbox17[2] = {"实线","虚线"};

__root const CFG_HDR cfghdr18 = {CFG_COLOR,"选择框颜色",0,24};
__root const int cfg_hl_frame_color=23;

__root const CFG_HDR cfghdr19 = {CFG_COLOR,"字体颜色",0,24};
__root const int cfg_font_color=3;

__root const CFG_HDR cfghdr20 = {CFG_COLOR,"背景颜色",0,24};
__root const int cfg_back_color=23;

__root const CFG_HDR cfghdr21 = {CFG_COLOR,"选中字体颜色",0,24};
__root const int cfg_hl_font_color=2;

__root const CFG_HDR cfghdr22 = {CFG_COLOR,"选中项目背景颜色",0,24};
__root const int cfg_hl_back_color=7;

__root const CFG_HDR cfghdr76={CFG_COLOR,"Color Search mark",0,0};
__root const char COLOR_SEARCH_MARK[4]={0xFF,0x0,0x0,0x64};

__root const CFG_HDR cfghdr72={CFG_COLOR,"Color Not selected",0,0};
__root const char COLOR_NOTSELECTED[4]={0xFF,0xFF,0xFF,0x64};

__root const CFG_HDR cfghdr23 = {CFG_COLOR,"滚动条颜色",0,20};
__root const int cfg_colour_scroll_bar = 3;

__root const CFG_HDR cfghdr_m31={CFG_LEVEL,"图标编号",1,0};

__root const CFG_HDR cfghdr24 = {CFG_UINT,"电话簿图标编号",0,2000};
__root const int cfg_ab_icon = 717;

__root const CFG_HDR cfghdr25 = {CFG_UINT,"编辑短信图标编号",0,2000};
__root const int cfg_SMS_icon = 710;

__root const CFG_HDR cfghdr26 = {CFG_UINT,"电话图标编号",0,2000};
__root const int cfg_phone_icon = 793;

__root const CFG_HDR cfghdr27 = {CFG_UINT,"办公室电话图标编号",0,2000};
__root const int cfg_office_icon = 795;

__root const CFG_HDR cfghdr28 = {CFG_UINT,"移动电话图标编号",0,2000};
__root const int cfg_mobile_icon = 794;

__root const CFG_HDR cfghdr29 = {CFG_UINT,"传真图标编号",0,2000};
__root const int cfg_fax_icon = 791;

__root const CFG_HDR cfghdr30 = {CFG_UINT,"传真2图标编号",0,2000};
__root const int cfg_fax2_icon = 792;

__root const CFG_HDR cfghdr31 = {CFG_UINT,"左软键语言包",0,0x7FFF};
__root const int cfg_left_sk_lgp = 456;

__root const CFG_HDR cfghdr32 = {CFG_UINT,"右软键语言包",0,0x7FFF};
__root const int cfg_right_sk_lgp = 368;

__root const CFG_HDR cfghdr33 = {CFG_UINT,"号码选择语言包",0,0x2E00};
__root const int cfg_select_lgp = 2866;

__root const CFG_HDR cfghdr34 = {CFG_UINT,"一页显示条目数",0,8};
__root const int cfg_count_page = 5;

__root const CFG_HDR cfghdr35 = {CFG_UINT,"字体大小",0,9};
__root const int cfg_font_size = 7;

__root const CFG_HDR cfghdr36 = {CFG_UINT,"本地IP号码",0,0xFFFFFFFF};
__root const int cfg_ip_number = 12593;

__root const CFG_HDR cfghdr37 = {CFG_UINT,"漫游IP号码",0,0xFFFFFFFF};
__root const int cfg_ip_number2 = 17951;

__root const CFG_HDR cfghdr_m30={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr_m11={CFG_LEVEL,"区号秀",1,0};

__root const CFG_HDR cfghdr38 = {CFG_CBOX,"是否显示区号秀",0,2};
__root const int cfg_cs_enable=1;
__root const CFG_CBOX_ITEM cfgcbox38[2] = {"否","是"};

__root const CFG_HDR cfghdr39 = {CFG_CBOX,"列表中区号秀对齐方式",0,3};
__root const int cfg_ls_cs_align = 0;
__root const CFG_CBOX_ITEM cfgcbox39[3] = {"左对齐","居中","右对齐"};

__root const CFG_HDR cfghdr40 = {CFG_CBOX,"区号秀对齐方式",0,3};
__root const int cfg_cs_align = 2;
__root const CFG_CBOX_ITEM cfgcbox40[3] = {"左对齐","居中","右对齐"};

__root const CFG_HDR cfghdr41 = {CFG_UINT,"区号秀分隔符",0,0xFFFF};
__root const int cfg_cs_split = '*'; //0x2027;

__root const CFG_HDR cfghdr42 = {CFG_COORDINATES,"区号秀左上角位置",0,0};
__root const int cfg_cs_x1 = 0;
__root const int cfg_cs_y1 = 40;

__root const CFG_HDR cfghdr43 = {CFG_COORDINATES,"区号秀右下角位置",0,0};
__root const int cfg_cs_x2 = 128;
__root const int cfg_cs_y2 = 60;

__root const CFG_HDR cfghdr44 = {CFG_UINT,"区号秀字体",0,9};
__root const int cfg_cs_font_size=3;

__root const CFG_HDR cfghdr45 = {CFG_COLOR,"区号秀字体颜色",0,24};
__root const int cfg_cs_font_color=2;

__root const CFG_HDR cfghdr46 = {CFG_COLOR,"区号秀背景颜色",0,24};
__root const int cfg_cs_bkg_color=23;

__root const CFG_HDR cfghdr47 = {CFG_UINT,"区号秀数据地址",0,0xFFFFFFFF};
__root const int cfg_cs_adr=0xA0CC0000;

__root const CFG_HDR cfghdr_m10={CFG_LEVEL,"",0,0};


__root const CFG_HDR cfghdr_m21={CFG_LEVEL,"miniGPS",1,0};

__root const CFG_HDR cfghdr48= {CFG_CBOX,"是否显示miniGPS",0,2};
__root const int cfg_gps_enable=1;
__root const CFG_CBOX_ITEM cfgcbox48[2] = {"否","是"};

__root const CFG_HDR cfghdr49 = {CFG_CBOX,"miniGPS对齐方式",0,3};
__root const int cfg_gps_align = 0;
__root const CFG_CBOX_ITEM cfgcbox49[3] = {"左对齐","居中","右对齐"};

__root const CFG_HDR cfghdr50 = {CFG_COORDINATES,"miniGPS左上角位置",0,0};
__root const int cfg_gps_x1 = 0;
__root const int cfg_gps_y1 = 110;

__root const CFG_HDR cfghdr51 = {CFG_COORDINATES,"miniGPS右下角位置",0,0};
__root const int cfg_gps_x2 = 131;
__root const int cfg_gps_y2 = 160;

__root const CFG_HDR cfghdr52 = {CFG_UINT,"miniGPS字体",0,24};
__root const int cfg_gps_font_size=8;

__root const CFG_HDR cfghdr53 = {CFG_COLOR,"miniGPS字体颜色",0,24};
__root const int cfg_gps_font_color=3;

__root const CFG_HDR cfghdr54 = {CFG_COLOR,"miniGPS背景颜色",0,24};
__root const int cfg_gps_bkg_color=0;

__root const CFG_HDR cfghdr55 = {CFG_UINT,"本地基站起始标识",0,0xFFFFFFFF};
__root const int cfg_local_start_lac=20400;

__root const CFG_HDR cfghdr56 = {CFG_UINT,"本地基站结束标识",0,0xFFFFFFFF};
__root const int cfg_local_end_lac=20999;

__root const CFG_HDR cfghdr_m20={CFG_LEVEL,"",0,0};

