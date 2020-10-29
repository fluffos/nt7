// mafang.c

inherit ROOM;

string look_daocao();

void create()
{
	set("short", "马房");
	set("long", @LONG
这是杨铁心家的后院的马房，马槽前面有个很大的水缸。
马槽左边堆满了很多稻草，平时堆的很整齐，今天不知道怎
么了，稻草(Daocao)堆的乱七八糟的。
LONG
	);

	set("exits", ([
		"south" : __DIR__"houyuan.c",
	]));
        set("objects",([
              // __DIR__"npc/wanyan": 1,
               	
        ]));
            
        set("item_desc",([
		"daocao" : (: look_daocao :),
	]));
        set_temp("available",1);
	setup();
}

void init()
{
	add_action("do_move", "move");
}

int do_move(string arg)
{
//	string dir;
	object me,ob;

	if( !arg || arg=="" || !query_temp("available") ) return 0;

	if( arg=="daocao" && query_temp("available")) {
		write("你试著把稻草慢慢移开，突然发现下面埋着个身受重伤的男人 !\n\n");
	        delete_temp("available");
	}


	me = new(__DIR__"npc/wanyan",1);
	me->move(__DIR__"mafang");

	ob = this_player();	

	me->unconcious();

	remove_call_out("fainting");
	call_out("fainting", 100, me, ob);

	return 1;
}

void fainting(object me, object ob)
{
        message_vision("完颜洪烈缓缓苏醒了过来，说道: 救、、我、、\n",ob);
        me->revive();
	
	return;
}

string look_daocao()
{
	return "这是一大堆稻草，堆在墙脚边，不知是派什麽用场。\n";
}

