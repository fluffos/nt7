#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "极高明台");
        set("long", @LONG
这里是福严寺最高处。唐邺侯李泌手书「[1；37m极高明[2；37；0m」三个大字于此，
意即佛相极高(高无见顶相)，佛光极明(明不借他光)，佛是至高无上
的，故曰极高明台。
LONG );
        set("exits", ([ 
               "northdown"  : __DIR__"sansheng",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5580);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}