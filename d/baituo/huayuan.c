inherit ROOM;

void create()
{
        set("short", "花园");
        set("long", @LONG
这是个美丽的大花园，园子里面种着鲜艳的红玫瑰。白衣少女常
来这里嬉戏。沿着弯弯曲曲的花径，可以通到山庄的许多地方。东边
是厨房。西边是白驼山少主欧阳克的内室，门虚掩着，也不知主人在
不在。
LONG );
        set("outdoors", "baituo");
        set("exits",([
                "west"  : __DIR__"neishi",
                "north" : __DIR__"zhuyuan",
                "east"  : __DIR__"chufang",
                "south" : __DIR__"menlang",
        ]));

        set("objects",([
                __DIR__"npc/whitelady" : 2,
        ]));

        set("coor/x", -49980);
        set("coor/y", 20050);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}