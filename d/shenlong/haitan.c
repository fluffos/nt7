#include <ansi.h>
inherit ROOM;

void home(object ob);

void create()
{
        set("short", "海滩");
        set("long", @LONG
这里就是神龙岛了。南边是一望无际的大海；往北则是片
灌木林。岛上的空气似乎又热又闷，咸湿的海风中带着一股腥
臭，又夹杂了一缕奇特的花香，让人闻起来十分怪异。海边泊
着一艘大船(chuan)。
LONG);

        set("item_desc", ([
                "chuan" : "这是灵蛇岛对外联系的大船。岛上的客人或弟子只要\n"
                          "上船(enter)就可以回中原。\n",
        ]));
        set("exits",([
                "north" :__DIR__"lin1",
                "south" :__DIR__"jiutou1.1", 
                "west"  :__DIR__"jiutou11/jiutou1.1", 
                "east"  :__DIR__"jiutou22/jiutou1.1", 
                "southeast"  :__DIR__"jiutou3/jiutou1.1", 
                "southwest"  :__DIR__"jiutou4/jiutou1.1", 
        ]));
        set("outdoors", "shenlong");
        set("valid_startroom", 1);
        set("no_clean_up", 1);
        /*
	set("objects", ([
		"/clone/dream_npc/shenlongdao/nianshou" : 1,
	]));
	*/
        setup();
}

void init()
{
        set("startroom", base_name(this_object()), this_player());
	add_action("do_enter", "enter");
}

int do_enter ( string arg )
{
        object ob ;
        string dir;
        if( !arg || arg !="chuan" ) 
        {
                tell_object(this_player() , "你要 enter 哪儿？\n" ) ;
                return 1 ;
        }
        ob = this_player () ;
        message_vision("船夫一见有人上船，忙叫了一声：开船喽！\n", ob);
        message_vision("船夫升起帆，船就向西方航行。\n", ob);
        ob->move(__DIR__"dahai") ;
        tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
        call_out("home", 10 , ob );
        return 1 ;
}
void home( object ob )
{
        if (! objectp(ob))
	        return;
        if (base_name(environment(ob)) != "/d/shenlong/dahai")
                return;
        tell_object(ob , "大船终于抵达了中原的一个繁华城市。你走下船来。\n" ) ;
        ob->move ("/d/beijing/haigang") ;
}


