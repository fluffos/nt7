// Room: /d/xiangyang/dangpu.c
// Date: Jan. 8 1999 by Lonely

inherit ROOM;

void create()
{
        set("short", "当铺");
        set("long", @LONG
这是家远近闻名的当铺，三开间的门面，一块写着『邱航当铺』
四个金字的黑匾，足足七尺高的紫檀木的柜台被磨得光可照人，你一
进去就有一种压抑和悲怅的感觉，柜台后的老板邱航头也不抬的只顾
拨拉着算盘，柜台上方挂着一块花木牌子(paizi) 。据街坊们说铁面
当铺给的价还不算最坏，并且从不问货的来处，除了活人什么都收，
所以生意很不错。
LONG );
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        卖 
buy         买
pawn        当
expiate     赎
value       估价
",
        ]));

        //set("no_fight", 1);
        set("no_beg", 1);
        set("exits", ([
                "north" : __DIR__"westjie1",
        ]));
        set("objects", ([
                __DIR__"npc/qiuhang" : 1,
        ]));
        set("coor/x", -7830);
	set("coor/y", -780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
