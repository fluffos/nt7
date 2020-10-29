// Room /d/heimuya/midao7.c
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
         "northwest" : __DIR__"midao6",
         "out"       : "/d/city/yaopu",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
