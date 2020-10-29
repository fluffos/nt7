//Room: bingying1.c

inherit ROOM;

void create ()
{
        set ("short", "兵营");
        set("long", @LONG
这里是一座临街而建的兵营，距离长安的北城门只有几步之遥。
兵营门口旌旗飘扬，偶尔可以看见兵士进出换岗，并且不动声色地巡
视着四周。兵营里面到处都有官兵来来回回地走动，有一名武将正在
指挥士兵列队操练。
LONG );
         set("exits", ([ /* sizeof() == 1 */
                 "northwest" : "/d/changan/beian-daokou",
         ]));
         set("objects", ([ /* sizeof() == 5 */
                 "/d/changan/npc/fujiang" : 1,
                 "/d/changan/npc/guanbing" : 4,
         ]));

         set("outdoors", "changan");
        set("coor/x", -10710);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
         replace_program(ROOM);
}