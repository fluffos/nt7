// Room: gudi.c
// bbb 1997/06/11
// Modify By River 98/12
inherit ROOM;

void create()
{
        set("short", "山谷底部");
	set("long", @LONG
只见左边山崖上一条大瀑布如玉龙悬空，滚滚而下，倾入一座清澈异常的
大湖之中，大瀑布不断倾入，湖水却不满溢，瀑布注入处湖水翻腾，只离得瀑
布十余丈，湖水便又一平如镜，四周围长满了杂草(cao)。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
	    "west" : __DIR__"donghubian",            
        ]));
	set("item_desc",([	   
	   "cao" : "一大片杂草胡乱地长着，钻进去不知道通向哪里。\n"
	]));
	set("no_clean_up", 0);
        set("outdoors", "大理");
	setup(); 
}

void init()
{
	add_action("do_zuan", "zuan");
        add_action("do_zuan", "enter");
}

int do_zuan(string arg)
{
	object me;
	me = this_player();
        if (!arg || arg !="cao") 
           return notify_fail("你乱钻什么啊？\n");       
	message_vision("$N一头钻进了杂草丛。\n" , me);
        me->move("/d/dali/shanlu3");
        write("你眼前一亮，终于钻出了杂草丛。\n");
	return 1;
}