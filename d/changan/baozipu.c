//Room: baozipu.c

inherit ROOM;

void create ()
{
        set ("short", "包子铺");
        set("long", @LONG
铺子里的摆设并不是很讲究，横竖摆了几排圆木方桌，桌子四周
零乱的放了几把长条椅子。一个小伙计没精打采的靠在柜台边，看见
你进来，只是懒洋洋的向你打了个招呼。看起来这里的生意并不怎么
好。
LONG );
        //set("item_desc", ([" *** " : " *** ", ]));
        set("exits", 
        ([ //sizeof() == 1
                "north" : "/d/changan/yongtai-nankou",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/huoji" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10760);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}