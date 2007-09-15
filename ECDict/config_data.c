#include "..\inc\cfg_items.h"
#include "define.h"


#ifdef ENGLISH_CONFIG   //english config without level menu

__root const CFG_HDR cfghdr0={CFG_CBOX, "Show free memory:", 0, 2};
__root const unsigned int cfg_showfreeram = 0;
__root const CFG_CBOX_ITEM cfgcbox1_1[2]={"No","Yes"};

//========================= level begin ======================//
//__root const CFG_HDR cfghdr_L1_BEGIN={CFG_LEVEL,"界面布局：", 1, 0};


__root const CFG_HDR cfghdr10={CFG_COORDINATES,"Up-left coords of input window:",0,0};
__root const unsigned int cfg_inputword_x = 4;
__root const unsigned int cfg_inputword_y = 3;

__root const CFG_HDR cfghdr11={CFG_COORDINATES,"Down-right coords of input win:",0,0};
__root const unsigned int cfg_inputword_x2 = 131;
__root const unsigned int cfg_inputword_y2 = 175;

__root const CFG_HDR cfghdr12={CFG_COORDINATES,"Up-left coords of word list:",0,0};
__root const unsigned int cfg_list_x_start = 2;
__root const unsigned int cfg_list_y_start = 20;

__root const CFG_HDR cfghdr13={CFG_UINT, "Number of words in list(>=3)", 0, 10};
__root const unsigned int cfg_item_n = 6;

__root const CFG_HDR cfghdr14={CFG_UINT, "Word list entry margin:", 0, 10};
__root const unsigned int cfg_padding = 2;

__root const CFG_HDR cfghdr15={CFG_UINT, "Word list entry spacing:", 0, 10};
__root const unsigned int cfg_spacing = 1;

//__root const CFG_HDR cfghdr_L1_END={CFG_LEVEL,"",0,0};
//========================= level end ========================//


//========================= level begin ======================//
//__root const CFG_HDR cfghdr_L2_BEGIN={CFG_LEVEL,"字体及配色：",1,0};

__root const CFG_HDR cfghdr20={CFG_UINT, "Normal font:", 0, 32};
__root const unsigned int cfg_dim_fontsize = 2;

__root const CFG_HDR cfghdr21={CFG_UINT, "Normal font color:", 0, 23};
__root const unsigned int cfg_dim_color = 0;

__root const CFG_HDR cfghdr22={CFG_UINT, "Highlight font:", 0, 32};
__root const unsigned int cfg_highlight_fontsize = 3;

__root const CFG_HDR cfghdr23={CFG_UINT, "Hightlight font color:", 0, 23};
__root const unsigned int cfg_highlight_color = 1;

__root const CFG_HDR cfghdr24={CFG_UINT, "Hightlight bg color:", 0, 23};
__root const unsigned int cfg_highlight_bgcolor = 0;

__root const CFG_HDR cfghdr25={CFG_UINT, "Hightlight frame color:", 0, 23};
__root const unsigned int cfg_bordercolor = 22;

__root const CFG_HDR cfghdr26={CFG_UINT, "Scrollbar color:", 0, 23};
__root const unsigned int cfg_scrollbar_color = 9;

__root const CFG_HDR cfghdr27={CFG_UINT, "Scrollbar slider color:", 0, 23};
__root const unsigned int cfg_scrollbar_blkcolor = 0;

__root const CFG_HDR cfghdr28={CFG_UINT, "Separator line color:", 0, 23};
__root const unsigned int cfg_separator_color = 22;

//__root const CFG_HDR cfghdr_L2_END={CFG_LEVEL,"",0,0};
//========================= level end ========================//
//extern const int cfg_dim_bgcolor = 23;


//========================= level begin ======================//
//__root const CFG_HDR cfghdr_L3_BEGIN={CFG_LEVEL,"浮动解释设置：",1,0};

__root const CFG_HDR cfghdr30={CFG_CBOX, "Show floating window:", 0, 2};
__root const unsigned int cfg_floatwin = 1;
__root const CFG_CBOX_ITEM cfgcbox30[2]={"No","Yes"};


__root const CFG_HDR cfghdr31={CFG_UINT, "Floating win delay(0.1 sec):", 0, 100};
__root const unsigned int cfg_fw_delay = 5;

__root const CFG_HDR cfghdr32={CFG_CBOX, "Show phonetic:", 0, 2};
__root const unsigned int cfg_fw_phonetic = 0;
__root const CFG_CBOX_ITEM cfgcbox31[2]={"No","Yes"};

__root const CFG_HDR cfghdr33={CFG_UINT, "Floating window height:", 0, 320};
__root const unsigned int cfg_fw_height = 51;

__root const CFG_HDR cfghdr34={CFG_UINT, "Floating window width:", 0 ,240};
__root const unsigned int cfg_fw_width = 90;


__root const CFG_HDR cfghdr35={CFG_UINT, "Floating win font:", 0, 32};
__root const unsigned int cfg_fw_fontsize = 8;

__root const CFG_HDR cfghdr36={CFG_UINT, "Floating win font color:", 0, 23};
__root const unsigned int cfg_fw_fontcolor = 1;

__root const CFG_HDR cfghdr37={CFG_UINT, "Floating win bg color:", 0, 23};
__root const unsigned int cfg_fw_bgcolor = 10;

__root const CFG_HDR cfghdr38={CFG_UINT, "Floating win frame color:", 0, 23};
__root const unsigned int cfg_fw_bordercolor = 20;

//__root const CFG_HDR cfghdr_L3_END={CFG_LEVEL,"",0,0};

#else  //Chinese config with level menu

__root const CFG_HDR cfghdr0={CFG_CBOX, "显示剩余内存", 0, 2};
__root const unsigned int cfg_showfreeram = 0;
__root const CFG_CBOX_ITEM cfgcbox1_1[2]={"否","是"};

//========================= level begin ======================//
__root const CFG_HDR cfghdr_L1_BEGIN={CFG_LEVEL,"界面布局：", 1, 0};


__root const CFG_HDR cfghdr10={CFG_COORDINATES,"单词输入框左上角坐标：",0,0};
__root const unsigned int cfg_inputword_x = 4;
__root const unsigned int cfg_inputword_y = 3;

__root const CFG_HDR cfghdr11={CFG_COORDINATES,"单词输入框右下角坐标：",0,0};
__root const unsigned int cfg_inputword_x2 = 131;
__root const unsigned int cfg_inputword_y2 = 175;

__root const CFG_HDR cfghdr12={CFG_COORDINATES,"列表左上角坐标：",0,0};
__root const unsigned int cfg_list_x_start = 2;
__root const unsigned int cfg_list_y_start = 20;

__root const CFG_HDR cfghdr13={CFG_UINT, "列表单词数（≥3）：", 0, 10};
__root const unsigned int cfg_item_n = 6;

__root const CFG_HDR cfghdr14={CFG_UINT, "列表条目边距：", 0, 10};
__root const unsigned int cfg_padding = 2;

__root const CFG_HDR cfghdr15={CFG_UINT, "列表条目间距：", 0, 10};
__root const unsigned int cfg_spacing = 1;

__root const CFG_HDR cfghdr_L1_END={CFG_LEVEL,"",0,0};
//========================= level end ========================//


//========================= level begin ======================//
__root const CFG_HDR cfghdr_L2_BEGIN={CFG_LEVEL,"字体及配色：",1,0};

__root const CFG_HDR cfghdr20={CFG_UINT, "普通条目字体：", 0, 32};
__root const unsigned int cfg_dim_fontsize = 2;

__root const CFG_HDR cfghdr21={CFG_UINT, "普通条目文字颜色：", 0, 23};
__root const unsigned int cfg_dim_color = 0;

__root const CFG_HDR cfghdr22={CFG_UINT, "高亮条目字体：", 0, 32};
__root const unsigned int cfg_highlight_fontsize = 3;

__root const CFG_HDR cfghdr23={CFG_UINT, "高亮条目文字颜色：", 0, 23};
__root const unsigned int cfg_highlight_color = 1;

__root const CFG_HDR cfghdr24={CFG_UINT, "高亮条目背景颜色：", 0, 23};
__root const unsigned int cfg_highlight_bgcolor = 0;

__root const CFG_HDR cfghdr25={CFG_UINT, "高亮条目边框颜色：", 0, 23};
__root const unsigned int cfg_bordercolor = 22;

__root const CFG_HDR cfghdr26={CFG_UINT, "滚动条颜色：", 0, 23};
__root const unsigned int cfg_scrollbar_color = 9;

__root const CFG_HDR cfghdr27={CFG_UINT, "滚动条滑块颜色：", 0, 23};
__root const unsigned int cfg_scrollbar_blkcolor = 0;

__root const CFG_HDR cfghdr28={CFG_UINT, "分隔线颜色：", 0, 23};
__root const unsigned int cfg_separator_color = 22;

__root const CFG_HDR cfghdr_L2_END={CFG_LEVEL,"",0,0};
//========================= level end ========================//
//extern const int cfg_dim_bgcolor = 23;


//========================= level begin ======================//
__root const CFG_HDR cfghdr_L3_BEGIN={CFG_LEVEL,"浮动解释设置：",1,0};

__root const CFG_HDR cfghdr30={CFG_CBOX, "默认显示浮动解释：", 0, 2};
__root const unsigned int cfg_floatwin = 1;
__root const CFG_CBOX_ITEM cfgcbox30[2]={"否","是"};


__root const CFG_HDR cfghdr31={CFG_UINT, "延时（单位为1/10秒）：", 0, 100};
__root const unsigned int cfg_fw_delay = 5;

__root const CFG_HDR cfghdr32={CFG_CBOX, "默认显示音标：", 0, 2};
__root const unsigned int cfg_fw_phonetic = 0;
__root const CFG_CBOX_ITEM cfgcbox31[2]={"否","是"};

__root const CFG_HDR cfghdr33={CFG_UINT, "浮动解释框高度：", 0, 320};
__root const unsigned int cfg_fw_height = 51;

__root const CFG_HDR cfghdr34={CFG_UINT, "浮动解释框宽度：", 0 ,240};
__root const unsigned int cfg_fw_width = 90;


__root const CFG_HDR cfghdr35={CFG_UINT, "字体：", 0, 32};
__root const unsigned int cfg_fw_fontsize = 8;

__root const CFG_HDR cfghdr36={CFG_UINT, "文字颜色：", 0, 23};
__root const unsigned int cfg_fw_fontcolor = 1;

__root const CFG_HDR cfghdr37={CFG_UINT, "背景颜色：", 0, 23};
__root const unsigned int cfg_fw_bgcolor = 10;

__root const CFG_HDR cfghdr38={CFG_UINT, "边框颜色：", 0, 23};
__root const unsigned int cfg_fw_bordercolor = 20;

__root const CFG_HDR cfghdr_L3_END={CFG_LEVEL,"",0,0};
//========================= level end ========================//
    
    #if 0       //not used yet..
    __root const CFG_HDR cfghdr_L4_BEGIN={CFG_LEVEL,"文件路径配置：",1,0};
    
    __root const CFG_HDR cfghdr40={CFG_STR_UTF8, "索引文件(.mod.idx)：", 3, 79};
    __root const char modidx_dir[80]="0:\\ZBin\\dict\\stardict1.3.mod.idx";
    
    __root const CFG_HDR cfghdr41={CFG_STR_UTF8, "字典文件(.dict)：", 3, 79};
    __root const char dict_dir[80]="0:\\ZBin\\dict\\stardict1.3.dict";
    
    __root const CFG_HDR cfghdr_L4_END={CFG_LEVEL,"",0,0};
    #endif
    
#endif


