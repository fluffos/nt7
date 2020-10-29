#include <room.h>
#include <ansi.h>

//inherit CREATE_CHAT_ROOM;
inherit ROOM;

void create()
{
	set("short", "客店");
        set("long", @LONG
这是一家价钱低廉的客栈，生意却是非常兴隆。外地游客多选择
在这里落脚，你可以在这里打听到各地的风土人情。店小二里里外外
忙得团团转，接待着南腔北调的客人。客店的主人从不露面，他究竟
是谁，有各种各样的猜测。客店的西墙上挂着一个牌子(paizi)。
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
        set("no_sleep_room",1);
	set("item_desc", ([
		"paizi" : WHT "\n\n        ※※※※※※※※※※※※※※※※※\n"
                              "        ※                              ※\n"
                              "        ※    " NOR + HIW "楼上雅房，每夜十两白银。" NOR + WHT "  ※\n"
                              "        ※                              ※\n"
                              "        ※※※※※※※※※※※※※※※※※\n\n\n" NOR,
	]));
	set("objects", ([
                __DIR__"npc/fuxinglaoren" : 1,
                __DIR__"npc/xiaoer" : 1,
                __DIR__"npc/qi"     : 1,
	]));
	set("exits", ([
                "east" : __DIR__"majiu",
		"west" : __DIR__"beidajie1",
		"up"   : __DIR__"kedian2",
                //"south": __DIR__"kedian4",
                "north": __DIR__"stock",
	]));


	set("coor/x", 10);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
        "/adm/npc/youxun"->come_here();
}

void init()
{
        //add_all_action();
}

int valid_leave(object me, string dir)
{

	if( !query_temp("rent_paid", me) && dir == "up" )
	        return notify_fail(CYN "店小二一下挡在楼梯前，白眼一翻：怎麽着，想白住啊？\n" NOR);

	if( query_temp("rent_paid", me) && dir == "west" )
	        return notify_fail(CYN "店小二跑到门边拦住：客官已经付了银子，怎麽不住店就走了呢！\n" NOR);

	return ::valid_leave(me, dir);
}
