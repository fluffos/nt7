//Room: shoushi-dain.c

inherit ROOM;

void create()
{
        set("short", "首饰店");
        set("long", @LONG
一间首饰店。首饰店内放着一个长条桌子，桌子上摆有几只檀香
木盒，盒子是全开着的，里面各种金银首饰样样俱全，看得人眼花缭
乱，首饰店的老板正在查点货物。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "south" : "/d/changan/qixiang5",
        ]));
        set("objects", ([
                "/d/changan/npc/chen-laoban" : 1,
        ]) );

        set("coor/x", -10700);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}