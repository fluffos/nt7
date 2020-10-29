// Room /d/heimuya/midao6.c
// By haiyan

#include <room.h>
inherit ROOM;

void create()
{
     set("short", "秘道");
        set("long", @LONG
这是日月神教极其秘密的通道。是黑木崖与中原教众取得联系的
捷径。
LONG );
     set("exits", ([
         "northdown" : __DIR__"midao5",
         "southeast" : __DIR__"midao7",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
