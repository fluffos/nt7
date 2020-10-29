// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h> 
inherit ITEM; 

void create() 
{ 
              set_name(HIC"鹊桥"NOR, ({"bridge oflove", "bridge"}) ); 
              set_weight(1); 
              if( clonep() ) 
                      set_default_object(__FILE__); 
              else { 
                      set("long", "这是Redl给爱妻Gigi的专用通道，闲人莫能enter bridge！\n");  
                      set("unit", "道"); 
                      set("value", 10000);
                      set("no_get",1); 
              } 
              setup(); 
} 
       
void init() 
{ 
              add_action("do_enter","enter"); 
} 
       
int do_enter(string arg)  
{ 
                object me = this_player();
                string id = query("id", me);

                        if (! arg || (arg != "bridge" && arg != "bridge oflove" && arg != "鹊桥"))
                                return 0;
                
                        if(me->is_busy()) return 1;
                        
                if (id != "gigi" && id != "redl") {
                        tell_object(me, NOR "你感觉鹊桥神秘莫测，犹豫中竟不敢往前踏足半步！\n" NOR);
                                me->start_busy(1);
                        return 1;
                }
                
                message_vision(NOR"$N轻轻移步踏上" + HIC"鹊桥"NOR + "。\n" + "一道" + HIW + BRED"七" + BGRN"彩" + BYEL"斑" + BBLU"斓" + BRED"的" + BMAG"霓" + BCYN"虹" + NOR"平地升起，\n托在$N的足下往九天之外飞去...\n", me);
                me->move("/u/redl/workroom");
                message_vision(NOR "$N轻轻移步走下" + HIC"鹊桥" + NOR + "。\n", me);
                tell_object(me, NOR "(要收起来输入：y)\n" NOR);
                        input_to("get_bridge", me);
            return 1; 
} 
protected void get_bridge(string fun, object me)
{
            switch (fun)
        {
        case "y":
        case "Y":
                        tell_object(me, HIC"鹊桥"NOR + "化作一点星芒闪电扑入你怀中。\n" NOR);
                        this_object()->move(me, 1);
                return;
        default:
                return;
        }
}

