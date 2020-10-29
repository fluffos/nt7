inherit ROOM;

void create()
{
        set("short", "杂货铺");
        set("long", @LONG
这是一家小小的杂货铺，平时就卖些日常用品，只见货柜上放着
各式各样的货物，老板正忙着招呼客人，进门处放着一个招牌(zhaop
ai)，上面写着些许小字。
LONG );
        set("item_desc", ([
                "zhaopai": "请用 \"list\" 列出货物表，\"buy\" 向老板购物。\n",
        ]));
        set("exits", ([
                "south"    : __DIR__"hengyang2",
        ]));
        set("objects", ([
                __DIR__"npc/qiang": 1,
        ]));

	set("coor/x", -6880);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}