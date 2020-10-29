inherit ROOM;

void create()
{
        set("short", "大厅");
        set("long", @LONG
这是白驼山庄的大厅，内部摆设极尽豪华，当中一张黑色檀木条
案，上面陈放着精美的花瓶和一些珍贵的瓷器，四壁挂满名家的字画，
非常之醒目。
LONG );
        set("valid_startroom", 1);
        set("exits", ([
                "north" : __DIR__"liangong",
                "southdown" : __DIR__"yuanzi",
        ]));
 
        set("objects",([
                CLASS_D("ouyang") + "/ouyangfeng" : 1,
                __DIR__"npc/yahuan" : 2,
        ]));

        set("coor/x", -49970);
        set("coor/y", 20020);
        set("coor/z", 30);
        setup();

        "/clone/board/baituo_b"->foo();
        replace_program(ROOM);
}