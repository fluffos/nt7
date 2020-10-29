#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "皇宫大殿");
        set("long", @LONG
这里便是紫禁城的正门的大殿，寻常百姓是到不了这里来的，如
果你以不正当的途径到了这里，还是赶快离开为好。
LONG );
        set("exits", ([
                "north" : "/d/beijing/hgmen_n",
                "south" : "/d/beijing/hgmen_s",
                "west" : "/d/beijing/hg_w",
        ]));
        set("objects", ([
                "/d/beijing/npc/yuqian1" : 2,
        ]));
        set("outdoors", "beijing");
        set("coor/x", -190);
        set("coor/y", 4100);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
