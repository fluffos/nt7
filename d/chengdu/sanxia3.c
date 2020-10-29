#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "瞿塘峡");
        set("long", @LONG
这里是长江三峡中的瞿塘峡，河水由东流来，进入此峡谷，河道
变窄，水流变急，两岸的高山中间夹着一条河流，就好象一条丝带一
般，蜿蜒而行。
LONG );
        set("exits", ([
                "east" :  __DIR__"sanxia2",
                "west" : __DIR__"shudao11",
        ]));
        set("objects", ([
                "/d/beijing/npc/youke" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");

        set("coor/x", -15060);
	set("coor/y", -1830);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}