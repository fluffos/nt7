// Room /d/heimuya/midao01.c
// By haiyan

#include <room.h>
inherit ROOM;

void create()
{
     set("short", "秘道");
        set("long", @LONG
这是日月神教极其秘密的通道。日月神教武功多为诡秘异功，为
免外人打扰，故教中弟子多在此地练功。
LONG );
     set("exits", ([
         "out"    : __DIR__"house1",
         "east"   : __DIR__"midao02",
     ]));
     set("no_clean_up", 0);
     setup();
     replace_program(ROOM);
}
