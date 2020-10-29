#include <room.h>
inherit ROOM;

void create()
{
      set("short", "西间操练房");
        set("long", @LONG
这里摆满了大刀长剑、沙袋绑腿等，是武当弟子日常练功的地方。
LONG );

      set("exits", ([
                    "east"   : __DIR__"caolianfang",
      ]));
      set("for_family", "武当派");
        set("coor/x", -400);
        set("coor/y", -300);
        set("coor/z", 100);
        setup();
      replace_program(ROOM);
}