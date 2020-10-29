// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
#include <ansi.h>

void create()        
{
        set("short", "港口");
        set("long", @LONG
这里是一个港口，这里非常热闹，停泊着各种船只，有货船，商船
等等。很多旅客从这里进出港口，有从中原来的，也有从其他地方来的。
许多小贩在这里叫卖。有舟船可以通往日本(chuan) 十分方便。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"dadi6",
//   "east":"/d/job/killhaidao/gangkou",
                //"south":__DIR__"gangkou",
        ]));
        set("item_desc", ([
                "chuan" : "一条大海船。出远海没这样的船可不行。\n",
        ]));
          set("no_duhe",1);
       setup();
        
}
void init()
{
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
    message_vision("船夫升起帆，船就向东南方航行。\n", ob);
    ob ->move("/d/quanzhou/dahai") ;
    tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
    call_out("tpenghu", 10 , ob );
    return 1 ;
}
void tpenghu(object ob )
{
    tell_object(ob , "大船终于抵达了倭岛。你走下船来。\n" ) ;
    ob->move ("/d/japan/haigang") ;
}

