// cool 980725
// Modify By River 98/12
//COOL@SJ,9908
//tangfeng@SJ,2004

#include <ansi.h>
#include <room.h>
inherit ROOM;
#define QUESTDIR1 "quest/天龙八部/凌波微步篇/"
void create()
{
        set("short", "石屋里");
        set("long", @LONG
这里是石屋里了，里面黑漆漆的，什么也看不清楚，阳光都被门口的一块
大岩石挡住了，只能透过几缕石缝中透过来的阳光，你打量着这间屋子。
LONG
        );

        set("item_desc", ([
              "yan" : "一块大岩石，可以试着推开!。\n",
        ]));
        setup();
}

void init()
{   
       object ob,obj;
       ob=this_player();

       if (interactive(ob)
        && !present("qingnian nanzi", this_object())
        && !present("duan yu",this_object())
         && query_temp(QUESTDIR1+"kill_duan", ob )
         && query(QUESTDIR1+"pass_shanlu", ob )
         && !query(QUESTDIR1+"over", ob)){
		     obj=new(__DIR__"npc/dy");
         obj->move(this_object());
       }
       if (userp(ob)) {
	        remove_call_out("close");
          call_out("close", 2, this_object());
          }
	  add_action("do_tui", "tui");
    add_action("do_tui", "push");
}

int do_tui(string arg)
{
       int i;
        i=query("neili", this_player());
       if( !arg || arg!="yan" ) 
         return notify_fail("你要推什么？\n");
        message_vision(HIY"$N站在门后，把双掌放在岩上，深深的吸了一口气，双臂一发劲，大喝一声“开”。\n"NOR, this_player());
       if ( i >=800 ){
        message_vision(RED"$N只听一阵轰响，大石缓缓的移开了！\n"NOR, this_player());
        set("exits/out", __DIR__"muwu2");
        addn("neili", -800, this_player());
        remove_call_out("close");
        call_out("close", 5, this_object());
        }
       else {
        message_vision("$N却见大石纹丝不动，看来$N的内力还不够。\n", this_player());
        set("neili", 0, this_player());
        }
    return 1;
}

void close(object room)
{
      message("vision",YEL"大石缓缓移动，把石屋再次封住了。\n"NOR, room);
      delete("exits/out", room);
}