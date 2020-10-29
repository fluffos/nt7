// This program is a part of NITAN MudLIB 
// redl 2013/1/1 
#include <ansi.h> 
inherit ITEM; 

void create() 
{ 
              set_name(NOR"随机播放器"NOR, ({"rplayer"}) ); 
              set_weight(1); 
              if( clonep() ) {
                      set_default_object(__FILE__); 
                              call_out("reborn", 1);
                      }
              else { 
                      set("long", "    这是一个随机播放文选的设备，使用指令是(rr)。\n");  
                      set("unit", "个"); 
                      set("value", 10000);
              } 
              setup(); 
} 


int query_autoload()
{
        return 1;
}
       
void init() 
{ 
        add_action("do_rr","rr"); 
} 

void rr2(object me)
{
                        if (!query_temp("rr")) return;
                message_vision(YEL "$N正在阅读文选。\n" NOR, me);
                switch (random(2)) //2010、2005、2008、2012、2011
                {
                        case 0:
                                me->command("wenxuan 2005 "+ to_string(1+random(44)));
                                break;
                        case 1:
                                me->command("wenxuan 2008 "+ to_string(1+random(21)));
                                break;
//                              case 2:
//                                      me->command("wenxuan 2010 "+ to_string(1+random(6)));
//                                      break;
//                              case 3:
//                                      me->command("wenxuan 2011 "+ to_string(1+random(2)));
//                                      break;
//                              case 4:
//                                      me->command("wenxuan 2012 "+ to_string(1+random(4)));
//                                      break;
                }
                call_out("rr2", 5, me);
}

void do_flood(object me)
{
        int i;
        //me->command("wenxuan 2011 1");
        for( i=12; i>0; i-- )
                me->command("hp");
                
        return;
}
       
int do_rr()  
{ 
                object me = this_player();
                if (query_temp("rr")) {
                        delete_temp("rr");
                        message_vision(YEL "$N已经阅读完毕。\n" NOR, me);
                }
                        else {
                                set_temp("rr", 1);
                                message_vision(YEL "$N正在阅读文选。\n" NOR, me);
                                do_flood(me);
                                call_out("rr2", 4, me);
                        }
                return 1;
} 



void reborn()
{
                object me;
                me = environment();
                if (!objectp(me) || !playerp(me)) {
                        call_out("reborn", 1);
                        return;
                }
                do_flood(me);
                return;
}




