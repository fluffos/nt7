// Code of JHSH
// Room: /d/mingjiao/jinlianchang.c
// Zhangchi 3/00

inherit ROOM;

void create()
{
        set("short", "精练场");
        set("long", @LONG
地是青砖铺，壁为红墙砌。东边置有兵器架，十八般兵器，无一
不有。再朝西面看，左有梅花桩，右是铁沙场，齐备非常。场子南边
齐整地放着百来个大小不一的青石锁，不时有几个明教弟子过去提举
两下。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "north" : __DIR__"rjqlwch",
]));
        set("objects",([
                __DIR__"obj/huolu" : 1,
]));

        set("no_fight", 1);
        set("no_sleep", 1);
        set("no_steal", 1);
        set("no_clean_up", 0);
        set("cost", 1);

        setup();

}

int valid_leave(object me, string dir)
{
        if( dir == "north" && query_temp("refining", this_player()) )
               return notify_fail("你正在打铁，不能离开这里！\n");
        return ::valid_leave(this_player(), dir);
}