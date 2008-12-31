#ifndef _CREATEMENU_H_
#define _CREATEMENU_H_

class CrtMenu
{
public:
 
  int CreateMenu(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
  int CreateMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer);
  int CreateMenu(const ML_MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer);
  int CreateMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, WSHDR *hdr_t, int start_item, int n_items, void *user_pointer);
  int CreateMenu(const MENU_DESC *menu, const HEADER_DESC *hdr, int start_item, int n_items, void *user_pointer, int flag_30or2);

};

#endif



