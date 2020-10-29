inherit ROOM;

void create()
{
        set("short", "炼丹房");
        set("long", @LONG
这里是药王谷的炼丹房，周围墙壁都是用石块砌成的，青砖铺地，
房间中央放着一尊青铜筑成的大丹炉。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "south" : __DIR__"yuemen",
        ]));
        set("objects", ([
                __DIR__"npc/obj/danlu1" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
