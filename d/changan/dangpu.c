//Room: dangpu.c

inherit ROOM;

void create ()
{
        set ("short", "萧记当铺");
        set("long", @LONG
这是长安城里最大的一家当铺了。素来以买卖公平著称。门口挂
了一块牌子 (paizi)。一个三尺高的柜台挡在你的面前，柜台后坐着
掌柜的冯老板，见你走了进来，一双精明的眼睛上上下下打量着你。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/changan/qixiang3",
        ]));
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        卖 
buy         买
pawn        当
expiate     赎
value       估价
",
        ]));

        set("objects", ([ /* sizeof() == 1 */
                "/d/changan/npc/wanxi" : 1,
        ]));

        set("no_fight", 1);
        set("coor/x", -10730);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}