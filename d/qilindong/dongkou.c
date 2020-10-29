//room: dongkou.c

#include <ansi.h> 
inherit ROOM;

#define REBORND   "/adm/daemons/rebornd"

void create()
{
     set("short","绝壁");
     set("long",@LONG
山道到此突然消失，在你面前是一条绝壁，往下看去云雾缭绕，你根
本无法看清谷底。绝壁边有个山洞（hole)，旁边有一块石碑(bei)。
LONG
     );
     set("exits", ([ 
                    "up" : "/d/city3/road2", 
             ])); 
     set("outdoors", "chengdu");     
     set("item_desc",([
         "bei" : "『麒麟窟』内有怪兽，无事切勿入内！\n" ,
         "hole" : "这是麒麟窟，你不想活了的话可以进去。(enter dong)\n" ,
     ]));
     setup();
}

void init()
{
     string id;
     object ob;
     object me = this_player();

     add_action("do_enter", "enter");

     if ( me->is_character() && ! userp(me) )
     {
        me->move("/d/city3/road2");
        return;
     }
     if ( ! me->query("reborn_start"))
     {
        tell_object(me, 
           BLINK HIR"麒麟窟哪里是随便能进的，莫非你活得不耐烦了!\n\n"NOR);

        message_vision(HIY"一股巨大的力量将$N推出了麒麟洞口。\n\n"NOR, me);
        me->move("/d/city3/road2");
        return;
     }
  
     id = REBORND->query("qilindong");
     
     if ( stringp(id) && id != me->query("id") )
        ob = find_player(id);

     if (objectp(ob) && 
         base_name(environment(ob))[0..20] == "/d/zhuanshi/qilindong")
     {     
         tell_object(me, 
            HIY"现在有人正在洞里，你迟点再来吧。\n\n"NOR);        
          message_vision(HIY"一股巨大的力量将$N推出了麒麟洞口。\n\n"NOR, me);
          me->move("/d/city3/shudao14");         
         return;
     }         
     REBORND->set("qilindong", me->query("id"));
     
}

int do_enter(string arg)
{
    object me, ob;    

    me = this_player();
 
    if( !arg || arg != "hole" )
       return notify_fail("你要进哪里去?\n"); 

    foreach (ob in deep_inventory(me)) 
    if (ob->is_character()) 
        return notify_fail("进麒麟窟，生死由天，就不要带其他人或动物进去了！\n"); 

    message_vision("$N一弯腰往洞里走了进去。\n\n",me);
    
    me->move(__DIR__"dong1");

    message("vision", me->name() + "从洞里走了进来。\n",
            environment(me), ({me}) );

    return 1;   
}   
