// Room: /d/xiakedao/xkroad4.c
// Modified by Java on Feb.14.1998
inherit ROOM;

void create()
{
        set("short", "南海渔村");
        set("long", @LONG
这是南海沿岸的偏僻小村，稀稀落落的几户人家。空地上晾着几
顶渔网。南面就是波涛浩淼的南海了。向西走好象还有个渔港。东面
是小村的沙滩晒网场。
LONG );
        set("outdoors", "nanhai");
        set("exits", ([
                "north"   : __DIR__"xkroad3",
                "east"    : __DIR__"xkroad5",
                "west"    : __DIR__"haigang",
                "south"   : __DIR__"haibin",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("can_hunting", 1); 
        //set("resource/quarry", ([
        set("quarry", ([
                //"/clone/quarry/gui" :  50,
                "gui" :  40,
                "eyu" :  3,
                //"/clone/quarry/eyu" :  10,
                "haibei" :  5,
                //"/clone/quarry/haibei" :  10,
                "/clone/quarry/eyu" :  10,
                "/clone/quarry/haibei" :  10,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -1400);
        set("coor/y", -9000);
        set("coor/z", 0);
        setup();
}
