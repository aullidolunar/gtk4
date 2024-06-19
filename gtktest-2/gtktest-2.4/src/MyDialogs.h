#ifndef _MY_DIALOGS_H_INCLUDED
#define _MY_DIALOGS_H_INCLUDED

#include "main.h"
#include "callbacks.h"

typedef struct _MyDialogInfo
{
	GMainLoop *loop;
	int response;
	char* nombre;
	int carrera;
	int grade;
} MyDialogInfo;

typedef struct _MsgBoxInfo
{
	GMainLoop *loop;
	int response;
} MsgBoxInfo;

void input_dialog_show (GtkWindow*,  const char*, MyDialogInfo*, gboolean);
void output_dialog_show (GtkWindow*, const char*, int, int, CellItem*);
int MessageBox (GtkWindow* toplevel, const gchar*, const gchar*, const gchar*);

#endif