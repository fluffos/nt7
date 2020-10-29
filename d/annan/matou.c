#include <ansi.h>
inherit ROOM;

void create ()
{
  set ("short","海防码头");
  set ("long", @LONG
这里是安南的码头。北方最大港口，第二大城，军事要地。位于红河
三角洲东北部，东临北部湾。靠在岸边的船密密麻麻，有鱼家用的小鱼船、
运货用的商船、还有普通人用不起的官船，船上船下人们忙落异常。旁
边好象有搭客的商船。有船(chuan) 可以去中国海南。
LONG);

  set("exits", ([ 
  "west":__DIR__"gj3",        
  "south":__DIR__"guandao4",
  "north":__DIR__"shulin3",        
       ]));
        set("item_desc", ([
                "chuan" : "一条大海船。出远海没这样的船可不行。\n",
        ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
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
    message_vision("船夫升起帆，船就向东北方航行。\n", ob);
    ob ->move("/d/quanzhou/dahai") ;
    tell_object(ob, BLU "你在海上航行了很久很久.......\n" NOR ) ;
    call_out("tpenghu", 10 , ob );
    return 1 ;
}
void tpenghu(object ob )
{
    tell_object(ob , "大船终于抵达了中国海南。你走下船来。\n" ) ;
    ob->move ("/d/hainan/haibian") ;
}
