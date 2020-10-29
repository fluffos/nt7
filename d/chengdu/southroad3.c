// Room: southroad3.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "南大街");
        set("long", @LONG
你走在南大街坚实的青石板地面上，各色人等往来其中，很是喧
闹。有时你可能会见到一些江湖装束的人物，他们口音各异，服饰也
五花八门，可是中气都很足，可不是好惹的。往东长长的大道就是南
大街。西南方是个很巍峨的建筑群，人进人出，十分热闹。西北通往
西大街。
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "northwest"  : __DIR__"westroad1",
            "southwest"  : __DIR__"wuhoucigate",
            "east"       : __DIR__"southroad2",
        ]));
        set("objects", ([
            "/d/taishan/npc/jian-ke": 2,
            "/d/taishan/npc/dao-ke" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15230);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}