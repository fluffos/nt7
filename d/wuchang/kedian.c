//Edited by fandog, 02/15/2000
inherit ROOM;

void create()
{
        set("short", "晴川客栈");
        set("long", @LONG
这是一家价钱低廉的客栈，生意非常兴隆。外地游客多选择这里落
脚，你可以在这里打听到各地的风土人情。店小二里里外外忙得团团转，
接待着南腔北调的客人。墙上挂着一个牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
//        set("no_clean_up", 0);
        set("item_desc", ([
                "paizi" : "楼上雅房，每夜五十两白银。\n",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"majiu",
                "north" : __DIR__"hzjie4",
                "up"   : __DIR__"kedian2",
        ]));

	set("coor/x", -5100);
	set("coor/y", -1890);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{

        if( !query_temp("rent_paid", me) && dir == "up" )
        return notify_fail("店小二一下挡在楼梯前，白眼一翻：怎麽着，想白住啊！\n");

        if( query_temp("rent_paid", me) && dir == "north" )
        return notify_fail("店小二跑到门边拦住：客官已经付了银子，怎麽不住店就走了呢！
旁人还以为小店伺候不周呢！\n");

        return ::valid_leave(me, dir);
}