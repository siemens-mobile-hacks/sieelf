/*
    SieNatJabber Project
    ������� ������ � vCard

    ������ � ���������� ����� vCard, ���������� �����
*/

#ifndef _VCARD_H_
  #define _VCARD_H_

#include "xml_parser.h"

// ���������� ���� vCard
void Process_vCard(char *from, XMLNode *vCard);

// �������� ����� �� ������
void vCard_Photo_Display(char *path);

#endif

