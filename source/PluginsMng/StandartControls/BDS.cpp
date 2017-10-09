
#include "stdafx.h"
#include "BDS.h"

void AddListItem(CListCtrl *m_List, int icon, LPARAM data, int num, ...)
{
	LV_ITEM item;
    item.iItem = m_List->GetItemCount();
    item.iImage = icon;
	item.lParam = data;
   
    item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;

	va_list params;
	va_start(params, num);
	char * temp = va_arg(params,char *);

	item.iSubItem = 0;
    item.pszText = temp;
    m_List->InsertItem(&item);

	for(int i = 1;i<num;i++)
	{
		temp = va_arg(params,char *);
		item.mask = LVIF_TEXT;
		item.iSubItem = i;
		item.pszText = temp;
		m_List->SetItem(&item);
	}
} 