/*
    SieNatJabber Project
    ������� ������ � �������-������

    ������ API ������ �������������� �� ���� ��������� �������-�����
*/

#ifndef _CLIST_UTIL_H_
  #define _CLIST_UTIL_H_

#include "main.h"

#define CHAR_ON_LINE 20

#define CLIST_FONT FONT_SMALL     // ����� �������-�����

#define CLIST_Y1 5 + SCR_START               // ad: ������ ������ (26->5)

// ���������� ������ ���������
  void CList_RedrawCList();

// ����������� ��������� ��� ������
  void CList_ToggleVisibilityForGroup(int GID);
// �������� ��������� ��������� ������
  int CList_GetVisibilityForGroup(int GID);

// �������� ���������� �������� �� FullJID (JID ������ � ��������)
  CLIST* CList_FindContactByJID(char* jid);

// ������, ���� �� ��� ����� ������ � ��������, �� FullJID
  TRESOURCE* CList_IsResourceInList(char* jid);

// �������� � ����� �������. ���������� ��������� ���������� ��������.
  CLIST* CList_AddContact(char* jid,
                          char* name,
                          JABBER_SUBSCRIPTION subscription,
                          char wants_subscription,
                          char group
                          );

// �������� ��������� �������� (�������� �������� � ��)

  void CList_ChangeContactParams(CLIST* Cont_Ex,
                          char* name,
                          JABBER_SUBSCRIPTION subscription,
                          char wants_subscription,
                          char group);

// ����� ���� �������� � ����� � ���������
  void CList_MUC_SetRole(char* jid, CONF_DATA priv);

// �������� ��������� � ������ ��������� ��������
  void CList_AddMessage(char* jid, MESS_TYPE mtype, char* mtext);

// �������� ��������� ���������
  void CList_AddSystemMessage(char* jid, char status, char* status_msg);
// ��� ��, �� ��������� ANSI-������. ������� � ��������� ������� :)
  void CList_AddSystemMessageA(char* jid, char status, char* ansi_status_msg);

  TRESOURCE* CList_AddResourceWithPresence(char* jid, char status, char* status_msg);

// �������� �������, �� ������� ����� ������
  TRESOURCE* CList_GetActiveContact();

// ������ ���������� ��� ������� ��������� ��������. Useful ��� �����������.
  void CList_MakeAllResourcesOFFLINE(CLIST* ClEx);

// ���������� ������ ���������
  void CList_Destroy();

// �������� ����� ����������� ��������� �������
  void CList_ToggleOfflineDisplay();

// �������� ����� ������-�������
  unsigned int CList_GetNumberOfOnlineUsers();

// �������� ����� �������
  unsigned int CList_GetNumberOfUsers();

// �������� ����� �������, ��� ������� ���������
  unsigned int CList_GetNumberOfUsers_Visible();

// �������� ����� �������������
  unsigned int CList_GetUnreadMessages();

// ������� �� ��������� ������� � ������������� ����������
  void nextUnread();

// ������ ������ �� ������ ������(��� ���������� ���� ����������)
  void MoveCursorTo(TRESOURCE* NewResEx);

// ���������, �������� �� ������� ��������������� ������
  int CList_isGroup(CLIST *cont);

// �������� ���������� � ������� �� ����������� ����
  void CList_Display_Popup_Info(TRESOURCE* ResEx);

// ���������� ��������
  void CList_MoveCursorUp();
  void CList_MoveCursorDown();

  void CList_MoveCursorHome();
  void CList_MoveCursorEnd();

// ����� ������ ���������
  void KillMsgList(LOG_MESSAGE* messtop);

#endif
