//Room: kezhan.c

inherit ROOM;

void create ()
{
        set ("short", "悦宾客栈");
        set("long", @LONG
这家客栈长安城里最大的，最昂贵的客栈，也是花钱的客栈。你
若住在这客栈里，只要你有足够的钱，根本用不着走出客栈的门，就
可以获得一切最好的享受。在这里，只要你开口，就有人会将长安城
里最好的菜，最出名的歌妓，最美的女人送到你屋里来。墙上挂着一
个牌子。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "north" : "/d/changan/qixiang1",
                "up": "/d/changan/kzsleep",
        ]));
        set("objects", ([ /* sizeof() == 1 */
                "/d/changan/npc/xiaoer" : 1,
        ]));
        set("no_fight", 1);
        set("resource", ([ /* sizeof() == 1 */
        "water" : 1,
        ]));

        set("coor/x", -10750);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail("店小二满脸堆笑地挡住了你：对不起，上面是客人的卧房，不是本店的客人，不能上去。\n");
        return ::valid_leave(me, dir);
}