#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "天安门广场");
        set("long", @LONG
这里就是天安门广场，灰色的城墙给人以庄严肃穆之感，再往北
通过金水桥就是皇宫紫禁城了。远远望去，紫禁城的轮廓益发显得雄
伟高大，一条护城河绕城而过。一条笔直的青石大道横贯东西，东边
是东长安街广场，西边是西长安街广场。南边是宽阔繁华的长安街广
场，往南经过凡陛桥一直延伸至天坛和永定门。
LONG );
        set("exits", ([
                "south" : "/d/beijing/cagc_s",
                "north" : "/d/beijing/qiao",
               "west" : "/d/beijing/cagc_w",
              "east" : "/d/beijing/cagc_e",
        ]));
        set("objects", ([
                "/d/beijing/npc/maiyi2" : 1,
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/old2" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
}


void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/rideto");
}

