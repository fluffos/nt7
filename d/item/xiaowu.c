// xiaoyuan.c

inherit ROOM;

#define GANJIANG        "/adm/npc/ganjiang"
#define MOYE            "/adm/npc/moye"

void create()
{
        object ob;

        set("short", "铸剑室");
        set("long", @LONG
你一走进这个屋子，就感觉到有一股热浪扑面而来。屋角有一个炉子，
里面燃着熊熊火光，似乎无数的金蛇在你面前晃动。屋角堆放着一堆堆黑
乎乎的东西，不知道是什么。
LONG );

        GANJIANG->come_here();
        MOYE->come_here();

        set("no_fight", 1);
        set("no_sleep_room", 1);

        set("exits", ([
                "out" : __DIR__"road5",
        ]));
        set("objects", ([
                __DIR__"obj/dzt" : 1,
        ]));
        set("coor/x", 900);
        set("coor/y", -1060);
        set("coor/z", 0);
        setup();
}

void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/ganjiang");
}


