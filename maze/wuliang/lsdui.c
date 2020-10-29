// Room: lsdui.c
// By River 98/12
inherit ROOM;
void create()
{
        set("short", "乱石堆");
        set("long", @LONG
你片刻间转过山坳，只见一大堆乱石之中团团坐着二十余人。人丛中一个
瘦小的老者坐在一块高岩之上，高出旁人。
LONG
        );
        set("exits", ([ 
            "southwest" : __DIR__"xiaolu2",
        ]));
        set("objects", ([
                __DIR__"npc/sikong_xuan" : 1, 
        ]));
        set("outdoors", "大理");

        setup();
}
