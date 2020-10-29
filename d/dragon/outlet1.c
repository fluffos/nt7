inherit ROOM; 
#include <ansi.h> 
void init();
int do_move(string arg);
int do_enter(object me);

void create()
{ 
      set("short", "白砂台");
      set("long",
"[1;32m白砂台约有一丈见方，上面有细沙铺就，整个台面非常的平\n"
"整。台中央有一块大石头(stone)，堵住了泉眼。\n"
);
  set("exits",([
      "east" : __DIR__"spirit4",
  ]));
  set("item_desc", ([
      "stone" : "这块石头看起来不算太大，你应该可以搬动(move)它。\n",
  ]));
//  set("no_clean_up", 0);
  set("no_magic", 1);
        setup();
}

void init()
{
        add_action("do_move", "move");
        add_action("do_enter", "enter");
}

int do_move(string arg)
{      
        object room; 
        object me=this_player();
        if(!arg || arg!="stone")
          return notify_fail("你要移动什么？\n");
        if((int)me->query_str()>25)
                {
message_vision(HIC"$N用力推开大石头，泉水又开始流了出来！似乎可以潜下去(enter)。\n"NOR,this_player() ); 
message_vision(HIC"一只小精灵出现在$N面前，说：谢谢你解开第二个封印，请你继续前进吧。\n"NOR,this_player() ); 
                set_temp("m_success/初级", 1, this_player());
                set("move_stone",1);
        if(!( room = find_object(__DIR__"entrance")) )
                room = load_object(__DIR__"entrance");
        if(objectp(room)) 
            {
                set("exits/down", __DIR__"spirit3", room);
                message("vision","泉眼中又涌出了泉水。\n",room);
            }                }
        else
                message_vision("$N使出吃奶的力气也挪不动石头，只好悻悻地放弃了。\n", this_player());    
        return 1;       
}

int do_enter(object me)
{
        object room;
        object where;
        me=this_player();
        where=environment(me); 
       if( !query("move_stone", where) )
          return notify_fail("你要进哪去？\n");        if(!( room = find_object(__DIR__"spirit5")) )
          room = load_object(__DIR__"spirit5");
        message_vision("$N“咕咚”一声，跳进泉水中。\n",me); 
        set("move_stone",0);        me->move(room);
        return 1;
}

