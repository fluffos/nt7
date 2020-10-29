// bankong.c
// 半空中

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "石壁半空");
	set("long", 
HIW"你轻身提气，在石壁半空小心翼翼的攀爬着。\n"NOR
);
	setup();
}
void init()
{ 
//    object me = this_player();
      add_action("do_action", "");                             
}
int do_action(string arg)
{
       string action = query_verb();

       switch (action) {
               case "look":
               case "exercise": 
               case "lian":
               case "tuna":       
               case "quit":
	       case "l" :
	       case "dazuo" : 
               case "practice":
               write(HIW"你轻身提气，在石壁半空小心翼翼的攀爬着。\n\n"NOR);
                       return 1;
       }
       return 0;
}