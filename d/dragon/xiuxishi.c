inherit ROOM; 
#include <ansi.h> 
void create ()
{
  set ("short", "休息室");
  set ("long", HIG @LONG
这里看上去象是一间休息室，屋子中央摆着几张桌子，上面有
一些小菜，屋角有一个柜子(closet)，从里面传出扑鼻的香气，令
人垂涎。靠窗有取暖装置，屋里温暖如春。
LONG);

  set("item_desc", ([
     "closet" : "一个竹制的柜子，里面放着烟(cigarette)，酒(wine)和糖果(sugar)，可以拿(take)出来吃哦。\n",
   ]));
  set("exits", ([
        "north"    : __DIR__"spirit5",
        "east"    : __DIR__"spirit4",
        "west"    : __DIR__"liechang",
      ])); 
  set("objects", ([ 
      ]));
        set("no_fight", 1);
        set("sleep_room",1);

  set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_take", "take");
}

int do_take(string arg)
{
        object me=this_player();
        object ob;
        if(!arg) return notify_fail("你要拿什么？\n"); 
        if(arg=="wine"){
       ob = new ("/quest/tulong/obj/wine");   
       ob->move(me); 
  message_vision ("$N从柜子拿出$n。\n",me,ob);   
        return 1;
        }
        if(arg=="sugar"){
       ob = new ("/quest/tulong/obj/sugar");   
       ob->move(me); 
  message_vision ("$N从柜子拿出$n。\n",me,ob);   
        return 1;
        }
        if(arg=="cigarette"){
       ob = new ("/quest/tulong/obj/cigarette");   
       ob->move(me); 
  message_vision ("$N从柜子拿出$n。\n",me,ob);   
        return 1;
        }
        else
        write("那里面没有这样东西！\n");
        return 1;  
}
int valid_leave()
{
        if((present("wine", this_player())))
            return notify_fail("请不要带走这里的东西。\n"); 
        if((present("sugar", this_player())))
            return notify_fail("请不要带走这里的东西。\n"); 
        if((present("cigarette", this_player())))
            return notify_fail("请不要带走这里的东西。\n"); 
        if((present("budai", this_player())))
            return notify_fail("请放下布袋，这里的东西不能带出去，谢谢。\n");

    return ::valid_leave();
}
