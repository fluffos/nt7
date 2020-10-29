#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "书房" );
        set("long", @LONG
这是一间整洁明亮的书房，四壁都是书架，上面摆满了各
种书籍，中间一张桌子，放着笔墨纸印。
LONG);
        set("exits", ([
                "east"   :__DIR__"xizoulang1"
                
        ]));
        set("objects",([
                __DIR__"npc/wusangui" : 1,
                __DIR__"obj/pingfeng" : 1,
        ]));
	set("coor/x", -16870);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}