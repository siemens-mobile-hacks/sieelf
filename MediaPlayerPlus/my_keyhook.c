#include "..\inc\swilib.h"
#include "..\inc\mplayer.h" 

extern const unsigned int next_key;
extern const unsigned int pre_key;
extern const unsigned int play_pause_key;

extern int is_player_active;

unsigned int key_switch(unsigned int key)
{
	switch(key)
	{
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return '*';
		case 11: return '#';
		case 12: return LEFT_SOFT;
		case 13: return RIGHT_SOFT;
		case 14: return GREEN_BUTTON;
		case 15: return RED_BUTTON;
		case 16: return LEFT_BUTTON;
		case 17: return RIGHT_BUTTON;
		case 18: return UP_BUTTON;
		case 19: return DOWN_BUTTON;
		case 20: return ENTER_BUTTON;
#ifndef ELKA
		case 21: return INTERNET_BUTTON; //ÉÏÍø¼ü
#endif
		default: return 100;
	}
}
void long_press_switch(unsigned int key)
{
  /*switch(key)
  {
    case next_key:
    	MPlayer_Next();
      break;
    case pre_key:
    	MPlayer_Prev();
      break;
    case play_pause_key:
    	MPlayer_Toggle();
      break;
  }*/
  if(key==next_key)
  {
  	MPlayer_Next();
  	return;
  }
  if(key==pre_key)
  {
  	MPlayer_Prev();
  	return;
  }
  if(key==play_pause_key)
  {
  	MPlayer_Toggle();
  	return;
  }
}

int hot_key_mode=0;
int my_keyhook(int submsg, int msg)
{
	if(is_player_active)
	{
    int i;
    unsigned int hot_keys[3]={key_switch(next_key),key_switch(pre_key),key_switch(play_pause_key)};
    for(i=0;i<3;i++)
    {
      if(submsg==hot_keys[i])
      {
        switch(msg)
        {
          case KEY_DOWN:
            if(hot_key_mode==2)
            {
              GBS_SendMessage(MMI_CEPID,KEY_UP,hot_keys[i]);
              return KEYHOOK_NEXT;
            }
            hot_key_mode=0;
            return KEYHOOK_BREAK;
          case KEY_UP:
            if(hot_key_mode==0)
            {
              hot_key_mode=2;
              GBS_SendMessage(MMI_CEPID,KEY_DOWN,hot_keys[i]);
              return KEYHOOK_BREAK;
            }
            if (hot_key_mode==2)
            {
              hot_key_mode=0;
              return KEYHOOK_NEXT;
            }
            hot_key_mode=0;
            return KEYHOOK_BREAK;
          case LONG_PRESS:
            hot_key_mode=1;
            long_press_switch(hot_keys[i]);
            break;
        }
      }
    }
  }
  return KEYHOOK_NEXT;
}
