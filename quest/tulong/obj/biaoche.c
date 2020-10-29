#include <ansi.h>
inherit ITEM;
void set_out(object me);

void create()
{
      set_name("锦绣马车",({"mache"}));
      set_weight(20000); 
      set("short","锦绣马车");
      set("id","mache");
set("long","这是巫师出游用的马车，镏金彩旆，\n");  
      set_max_encumbrance (1000000000);
      if (clonep()) {
           set_default_object(__FILE__);
                    }
      else {
      set("material", "wood");
      set("no_sell",1); 
      set("sleep_room",1);
      set("if_bed",1);
      set("no_get",1);
      set("unit", "辆"); 
      set("power",1000);
      set("value",100);
            }
      setup();
}

void init()
{
           add_action("do_jump","jump");    
           add_action("do_out","out");
           add_action("do_look","look"); 
           add_action("do_move","drive"); 

}

int do_jump(string str)
{
     object me = this_player();
     object who = this_object(); 

     if (!objectp(environment(who)) || environment(who)==me) {
            return 0;
              }
     if (!str||str!="biaoche") {
      return notify_fail("你想跳上什么？\n");
                           }
     message_vision("$N揭起帷帘，走了进去。帷帘随即又垂了下来。\n",me);
     remove_call_out("set_out");
     call_out("set_out",1,me);
     me->move(who);
     message_vision("帷帘掀起，$N走了进来。\n",me);
     return 1;
}

void set_out(object me)
{
     tell_room(environment(this_object()),"拉车的马一声长嘶，甩甩耳朵，准备出发了。\n");
     tell_object(me,"准备完毕，可以出发了！\n");
}

int do_out(string arg)
{
     object me = this_player();
     object who = this_object();

     if (environment(me)!=who) {
           return 0;
               }
     if (!environment(who)) {
           return 0;
               } 
     message_vision("$N掀起帷帘，跳下了车。\n",me);     me->move(environment(who));
     message_vision("马车的帷帘掀了起来，$N从车里跳到地上。\n",me);
     return 1;     
} 

int do_rob(string arg)
{
     object me = this_player();
     object who = this_object(); 
     object *humen;
     int i, end;
     if (environment(me)==who) {
           return 0;
               } 
        if( query_temp("get_mission", me) )
      return notify_fail("你是镖头耶！\n");

     if (!arg||arg!="biaoche") {
      return notify_fail("你想打劫什么？\n");
                           }

     message_vision("$N拦住镖车，高声叫道：“打劫，车上的人统统给我下来！”\n",me);
     set_temp("stopped", 1, who);
     if (arrayp(all_inventory(who)))  humen = all_inventory(who);
     end = sizeof(all_inventory(who));
     for (i=0; i<end; i++) {
         if (!interactive(humen[i])) continue;
         else {
             tell_object(humen[i],query("name", humen[i])+"，有人来打劫了，快下车帮忙吧！\n");
             humen[i]->move(environment(who));       
                 }  
    }
     tell_object(environment(who),"车上的人跳了下来，摆开架式迎战。\n"NOR,me);
        return 1;     
}

int do_look(string arg)
{
     object me = this_player();
     object who = this_object();
     object room,*sth,*outsth;
     string str,*str2;
     mapping str1;
     int i, exitcon,objcon,obcon;

     str = "";
     if (arg)  return 0;       
     if (environment(me)!=who)   return 0;
     if (!environment(who))      return 0;
     
     else { 
tell_object(me,"        ______________________\n");
tell_object(me,"       |  _______    _______  |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |_______|  |_______| |\n");
tell_object(me,"       |  _______    _______  |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |       |  |       | |\n");
tell_object(me,"       | |_______|  |_______| |\n");
tell_object(me,"       |                      |\n");
tell_object(me,"       |----------------------|\n");
tell_object(me,"       |______________________|\n");
           tell_object(me,query("long", environment(who)));
 
           room = environment(who);
           if( !query("exits", room)){
                    str += "\n    这里已经没有路了。\n";
                             }
           else {
           str1=query("exits", room);
           str2 = keys(str1);
           exitcon = sizeof(str2);
           if (exitcon==1) {
                   str += "\n    前面唯一的出口是："+HIG+str2[0]+"。\n"+NOR;
                           }
           else {
              str += "\n    前面的出口有：";
              for (i=0; i<exitcon; i++) {
                    if (i==exitcon-1) {
                       str += "和"+str2[i]+"。\n"+NOR;
                           }
                    else {
                       str += HIG+str2[i]+"、";
                         }
                     }
                 }
           objcon = sizeof(all_inventory(who));
           sth = all_inventory(who);
           str += WHT"    镖车里面有：\n"NOR;
           for (i=0; i<objcon; i++) {
                if (!objectp(sth[i])) {
                        continue;
                         }
                else str+=""+HIG+query("name", sth[i])+"\t"+HIG+"("+query("id", sth[i])+")"+"\n"NOR;
                   }
          str += HIW"    镖车外面有：\n"NOR;
          obcon = sizeof(all_inventory(environment(who)));
          outsth = all_inventory(environment(who));
          for (i=0; i<obcon; i++) {
                if (!objectp(outsth[i])) continue;
                if (query("id", outsth[i])=="biaoche") continue;
                else str += HIG+"    "+query("name", outsth[i])+"\t("+query("id", outsth[i])+")\n"+NOR;
                  }
           write(str);
           return 1;
               }
            }

}
  
int do_move(string arg)
{
     object me = this_player();
     object who = this_object();
     object end;
     mapping exi;
     string *key,*val;
     string filename;
     int i,count;
     
     if (environment(me)!=who) {
             return 0;
                } 
     if( !query_temp("get_mission", me)){
             return notify_fail("你不是镖头，不要乱搅和。\n");
                }
     if( query_temp("stopped", who)){
             return notify_fail("有人在劫镖呢，快护镖吧。\n");
                }
     if (!arg) {
             return notify_fail("你要去哪儿？\n");
               }
     if( !query("exits", environment(who))){
             return notify_fail("这里已经没有路了，你哪儿也去不了。\n");
               }
      exi=query("exits", environment(who));
     key = keys(exi);
     val = values(exi);
     count = sizeof(val);
     for (i=0; i<count; i++) {
          if (arg==key[i]) {
                filename = val[i] + ".c";
                if (file_size(filename)<=0) continue;
                end = load_object(filename);
                tell_room(environment(who),"拉车的马一声长嘶，放开四蹄，如离弦之箭般的向着"+query("short", end)+"奔去……\n\n"+NOR);
                tell_room(who,"马车轻微晃了一下，如离弦之箭般的向着"+query("short", end)+"奔去……\n\n");
                who->move(end);
                if (environment(who)!=end) return 0;
                tell_room(who,"很快，马车已到了目的地。("+query("short", end)+")\n"+NOR);
                            tell_room(environment(who),"只听马蹄声声，一辆镖车开了过来。\n"+NOR);
                return 1;
                   }
           else continue;
             }
           return notify_fail("你确定有这个地方吗？\n"); 
}
 
int do_open(string arg)
{
     object me = this_player();
     object who = this_object();  
     object silver, env;
     env=environment(who);

        if( query_temp("get_mission", me))return 0;
     if( !query_temp("stopped", who))return 0;

     if (!arg||arg!="biaoche") 
      return notify_fail("你想打开什么？\n"); 

       if (objectp(who=present("biaotou",environment())))
       return notify_fail("李镖头瞪了你一眼喝道：“"+RANK_D->query_self_rude(me)+"，你要干什么！”\n");
      silver=new(SILVER_OB);
      set("name", "镖银", silver);
      silver->set_weight(0); 
    message_vision("$N打开镖车，取出了"+query("name", silver)+"。\n",me);
      silver->set_amount(20000+random(20000));
      silver->move(me);  
    message("vision",HIM"\n【谣言】某人：听说"+HIM+query("name", me)+HIM"在"+HIM+query("short", env)+HIM"把镖银劫走啦！\n\n"NOR,users());

      return 1;
}