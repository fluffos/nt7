#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "兵器库大门");
        set("long", @LONG
你正站在荆州兵器库的门口，可以看到两个穿着制服的官兵正在
此地巡逻，不时地传来呐喊声。老百姓是不允许在此观看的，你最好
赶快走开。
LONG );
        set("exits", ([
                "east" : __DIR__"nandajie2",
        ]));
        set("objects", ([
                "/d/city/npc/bing" : 2,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}