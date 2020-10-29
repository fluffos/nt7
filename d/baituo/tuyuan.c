//room: tuyuan.c
inherit ROOM;

void create()
{
        set("short","兔苑");
        set("long", @LONG
这是个好玩的兔苑，几只大白兔静静地蹲在绿草地上吃草。西南
方是竹园。西面传来阵阵猛兽的嚎叫，东面有一个蛇园。
LONG );
        set("exits",([
                "east"      : __DIR__"sheyuan",
                "west"      : __DIR__"shoushe",
                "southwest" : __DIR__"zhuyuan",
        ]));
        set("outdoors", "baituo");
        set("objects",([
                __DIR__"npc/baitu" : 2,
        ]));
        set("coor/x", -49970);
        set("coor/y", 20070);
        set("coor/z", 30);
        setup();
}