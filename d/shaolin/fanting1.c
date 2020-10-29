// Room: /d/shaolin/fanting1.c
// Date: YZC 96/01/19

inherit ROOM;

string* names = ({
        __DIR__"obj/mizhi-tianou",
        __DIR__"obj/jiaxin-biji",
        __DIR__"obj/basi-shanyao",
        __DIR__"obj/furong-huagu",
        "/d/shaolin/obj/suji",
        "/d/shaolin/obj/suya",
});

void create()
{
        set("short", "斋厅");
        set("long", @LONG
这里便是少林全寺寺僧用斋的地方。斋厅极大，足可容纳上千人
同时进膳。从东到西一排排摆满了长长的餐桌和长凳，几位小和尚正
来回忙碌着布置素斋。桌上摆了几盆豆腐，花生，青菜以及素鸭等美
味素食。北面是个厨房。
LONG );
        set("exits", ([
                "south" : __DIR__"fanting",
                "north" : __DIR__"chufang",
        ]));
        set("objects",([
                __DIR__"obj/qingshui-hulu" : 1,
                names[random(sizeof(names))]: 1,
                names[random(sizeof(names))]: 1,                
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
