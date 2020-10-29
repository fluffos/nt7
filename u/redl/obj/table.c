// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <ansi.h> 
inherit ITEM; 

void create() 
{ 
              set_name(NOR"石桌"NOR, ({"table"}) ); 
              set_weight(1); 
              if( clonep() ) 
                      set_default_object(__FILE__); 
              else { 
                      set("long", "  这是一张厚重的石桌，桌上摆放着一只酒壶(pot)\n还有几包烟(cigarette)，似乎可以拿(take)走。\n");  
                      set("unit", "张"); 
                      set("value", 10000);
                      set("no_get",1); 
                      set("base_weight", 1999999999);
                      set("weight", 1999999999);
              } 
              setup(); 
} 
       
void init() 
{ 
              add_action("do_take","take"); 
} 

int can_take(object me)
{
        if (query("id", me) != "redl" && query("couple/couple_id", me) != "redl" && wiz_level(me) < wiz_level("(admin)")) return 0;
        return 1;
}

int clean_up() { return 1;} 
       
int do_take(string arg)  
{ 
                        object ob;
                object me = this_player();
                string id = query("id", me);

                        if (! arg || (arg != "cigarette" && arg != "pot"))
                                return 0;
                
                        if(me->is_busy()) {
                                write(NOR "你还是忙完再说吧！\n" NOR);
                                return 1;
                        }
                        

              if (!query_temp("can_enterredlroom", me) && query("id", me) != "redl" && query("couple/couple_id", me) != "redl") return notify_fail("傀儡将军对着你嘿嘿嘿奸笑了几声。\n"); 

                        if (!can_take(me)) me->start_busy(3+random(3));
                        
                        if (arg == "cigarette") {
                                if (query("take/cig/"+id)) if ( time() - query("take/cig/"+id) < 7200 ){
                                                if (!can_take(me)) {
                                                        write(NOR "你烟瘾太大，还是克制一下吧，多喝点茶！\n" NOR);
                                                        return 1;
                                                }
                                                write(NOR "虽然你有特权拿烟(玩家2小时一包)，但烟瘾不要大了！\n" NOR);
                                        }
                                set("take/cig/"+id, time());
                                ob = new(__DIR__"cigarette");
                        message_vision(YEL + "$N伸手从石桌上拿起一包"+query("name", ob)+"烟。\n" + NOR, me);
                        ob->move(me);
                        return 1;                               
                                
                        } else if (arg == "pot") {
                        if (!can_take(me)) {
                                message_vision(YEL "$N伸手想从石桌上拿走酒壶，却摸了一个空...\n" NOR, me);
                                return 1;
                        }
                
                ob = find_object(__DIR__"pot");
                if (! ob) ob = load_object(__DIR__"pot");
                if (objectp(environment(ob))) if (playerp(environment(ob))) message_vision(YEL "突闻化乐天外半声清鸣，$N身上的酒壶滴溜溜一转，旋即一闪化作星芒循声而去......\n" NOR, environment(ob));
                                ob->move(me);
                        message_vision(YEL "$N伸手从石桌上取走一个酒壶揣到腰里。\n" NOR, me);
                        return 1;
                }
                
                return 1;
} 


// 
// void reborn_pot()
// {
//              object ob;
//              ob = find_object(__DIR__"pot");
//              if (ob) {
//                      if (objectp(environment(ob))) if (playerp(environment(ob))) message_vision(YEL "突闻化乐天外半声清鸣，$N身上的酒壶滴溜溜一转，旋即一闪化作星芒循声而去......\n" NOR, environment(ob));
//                      destruct(ob);
//              }
//              set("amount", 1);
//         return;
// }

void ding_zx(object ob)
{
        if (!objectp(ob)) return;
        if(ob->is_busy()) {
                ob->set_short_desc("被斩仙飞刀定住了。");
                call_out("ding_zx", 1, ob);
        } else  {
                ob->set_short_desc(0);
        }
        return;
}






