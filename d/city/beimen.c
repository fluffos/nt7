// Room: /city/beimen.c
// YZC 1995/12/04

#include <room.h>

inherit ROOM;

string look_gaoshi();

void create()
{
        set("short", "北门");
        set("long", @LONG
这是北城门，因为曾经失火，到现在城墙还是黑乎乎的，因此白
纸黑字的官府告示(gaoshi)就显得特别现眼。北方是一片崇山峻岭，
一条黄土小径在山里蜿蜒而上。
LONG );
        set("item_desc", ([
                "gaoshi" : (:look_gaoshi:),
        ]));
        set("exits", ([
                "east"  : "/d/city/hong-damen",
                "south" : "/d/city/beidajie2",
                "north" : "/d/nanyang/yidao",
                "west"  : "/d/huanghe/caodi1",
        ]));
        set("objects", ([
                "/kungfu/class/yunlong/ma" : 1,
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
//      set("no_clean_up", 0);
        set("outdoors", "city");
	set("coor/x", 0);
	set("coor/y", 30);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n扬州知府\n程药发\n";
}