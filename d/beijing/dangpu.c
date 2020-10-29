inherit ROOM;

void create()
{
        set("short", "当铺");
        set("long", @LONG
这是一家坐落在京城王府井大街西边的当铺。这家当铺规模不大，
但是素来以买卖公平著称，京城的百姓遇手紧的情况时，都会把东西
拿到这里来典当。一个五尺高的木制柜台挡在你的面前，柜台上摆着
一个牌子 (paizi)，柜台后坐着当铺的老板，一双精明的眼睛上上下
下打量着你。
LONG );
        set("no_fight", 1);
        set("no_beg",1);
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        卖 
buy         买
pawn        当
expiate     赎
value       估价
",
        ]));

        set("objects", ([
                "/d/beijing/npc/dangpuzhang" : 1,
        ]));
        set("exits", ([
                "west" : "/d/beijing/wang_6",
        ]));

	set("coor/x", -2760);
	set("coor/y", 7700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}