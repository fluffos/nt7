// Room: /city/ximenroad.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
    	set("short", "西门大道");
        set("long", @LONG
这里是扬州西城门外大道。西通洛阳城，向东就是西门了。南边，
新开了个武道大会场，每到比武之期，人声鼎沸，你不禁想去见识一
下当今的成名人物。北边就是大名鼎鼎的侠义盟扬州分部了。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : "/d/city/ximen",
                "west"  : "/d/luoyang/road8",
		"south" : "/d/city/wudao4",
                "north" : "/d/city/xym_yzdamen",
	]));
        set("objects", ([
            "/d/village/npc/boy" : 3,
        ]));
	set("coor/x", -50);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	object obj;
	if( dir == "south")set_temp("view_leitai", 1, me);
        return ::valid_leave(me, dir);
}