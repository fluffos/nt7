
inherit ROOM;

void create()
{
	set("short", "物品房");
	set("long", @LONG
这里是天龙寺内的物品房，房间堆的满满的，你看了看，到处是
一排排的大木架，架上放着许多物品，却不粘灰尘，看样子随时都有
人来打扫。南面过去是慈悲院。
LONG);
	set("exits", ([ 
           "south" : __DIR__"cby",
        ]));
	set("coor/x",-340);
  set("coor/y",-270);
   set("coor/z",30);
   setup();
}
void init()
{
      // add_action("do_clean", ({"clean","打扫"}))
}

int do_clean(string arg)
{
     object me=this_player();

     if(arg != "木 架" ){
          message_vision("$N你认真的把物品房打扫了一遍。\n", me);
          return 1;
          }
     if(random(100) < 5){               
           message_vision("$N正认真的打扫着物品房中的木架上堆放的各式物品，
一本破旧的书突然从木架缝中掉了下来。\n", me);
           new("/clone/medicine/m-book4")->move(me);
           }
     else message_vision("$N你认真的把物品房打扫了一遍。\n", me);
     return 1;
}
