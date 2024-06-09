#ifndef _MY_DIALOGS_H_INCLUDED
#define _MY_DIALOGS_H_INCLUDED

#include "main.h"
#include "callbacks.h"

typedef struct _MyDialogInfo
{
	GMainLoop *loop;
	int response;
	char* nombre;
	char* carrera;
	int grade;
} MyDialogInfo;

void input_dialog_show (GtkWindow*,  const char*, MyDialogInfo*);
void output_dialog_show (GtkWindow*, const char*, int, CellItem*);

#endif