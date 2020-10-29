//Room: /d/dali/jinzhihe.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","金汁河畔");
        set("long", @LONG
这里位处金汁河畔，原本建有一座地藏寺，如今寺院早废。唯有
一座石刻经幢(jingzhuang)半埋土中。此幢为方锥状，七层石雕。高
约丈五尺，基座为八角形的磐石，边上刻有莲花；层与层之间有界石。
即是本层之盖檐，又是上层之基石。
LONG );
        set("item_desc", ([
           "jingzhuang" : "这是个稀世经幢，进去看看也不坏。\n",
        ]));
        set("objects", ([
           "/d/dali/npc/seng": 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "dalic");
        set("exits",([ /* sizeof() == 1 */
            "east"  : "/d/dali/yanchi1",
            "west"  : "/d/dali/xiaojing",
            "enter" : "/d/dali/jingzhuang1",
        ]));
	set("coor/x", -19090);
	set("coor/y", -6870);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}