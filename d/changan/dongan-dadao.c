//Room: dongan-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "东安大道");
        set("long", @LONG
长安城的主街东安大道颇为热闹，除了本城的居民外，还有不少
外来的旅客和商人。东安大道再向东就是长安城的连德道口、东城门，
往西是故皇宫的冯诩道。往北就是大名鼎鼎的侠义盟总部了。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "west" : "/d/changan/fengxu3",
                "east" : "/d/changan/dongan-daokou",
                "north" : "/d/changan/xym_zb",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10690);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}