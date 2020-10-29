//bridge.c

inherit ROOM;

void create()
{
        set("short", "小桥");
        set("long", @LONG
这是一座小竹桥，黑木崖顶上的冰雪融化形成一条清澈的小溪，
从桥下缓缓流过。不时有顽皮的小鱼跃出水面，在阳光下划出一条银
白色的弧线。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
            "northwest" : "/d/baituo/guangchang",
            "east" : "/d/baituo/xijie",
        ]));
        set("objects",([
                __DIR__"npc/cungu" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}