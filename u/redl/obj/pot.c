// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
#include <weapon.h>
#include <ansi.h>
#include <armor.h> 
inherit HANDS;

#define SK_ID "taishang-wangqing"

int check_dest(string msg, object me)
{
        if (! msg || msg == "") msg = "有动作";
                if (query("amount") < 1) {
                        message_vision(YEL + "$N一扬酒壶欲"+ msg + "，酒壶却嗖地化作一点星芒破空往化乐天外而去......\n" + NOR, me);
                        destruct(this_object());
                        return 1;
                }
                return 0;
}

int chkw()
{
        if (query("equipped") == "worn") return 1;
        return 0;
}
       
void chkd()
{
        if (!query("no_get")) {
                if (query("amount") < 1) {
                        if (playerp(environment(this_object()))) message_vision(YEL + "$N怀里的酒壶一阵颤抖，嗖地化作一点星芒破空往化乐天外而去......\n" + NOR, environment(this_object()));
                                else message_vision(YEL + "酒壶一阵颤抖，嗖地化作一点星芒破空往化乐天外而去......\n" + NOR, this_object());
                        destruct(this_object());
                        return;
                }       
                
                        addn("amount", -1);
        }
        call_out("chkd", 8);
}

void init() 
{ 
        object me = this_player();
              add_action("do_drink","drink"); 
              add_action("do_ding","ding"); 
              add_action("do_zhan","zhan"); 
        if (wizardp(me) || query("id", me) == "redl" || query("couple/couple_id", me) == "redl") {
              add_action("do_setnoget","setnoget"); 
              add_action("do_setamount","setamount"); 
    }
} 

int do_setnoget()  
{
        if (!query("no_get")) set("no_get",1); 
                else delete("no_get"); 
        return 1;
}

int do_setamount(string arg)  
{
        if (! arg || arg == "") return notify_fail(NOR + "需要输入数值参数！\n" + NOR); 
        set("amount",to_int(arg)); 
        return 1;
}

int can_force(object me, object victim)
{
        object where = environment(victim);
        
        if (!where || !objectp(where)) {
                tell_object(me, NOR + "这个目标大概还没有出生！\n" + NOR); 
                return 0;
        }
        if ((!wizardp(me) && query("id", me) != "redl" && query("couple/couple_id", me) != "redl") && (
                        query("no_fight", where) || query("sleep_room", where) || (playerp(victim) && !sscanf(base_name(where), "/d/pk/%*s"))
                                )) {
                tell_object(me, NOR  + query("name") + "一阵躁动，但很快就平静了...\n" + NOR); 
                return 0;
        }
        return 1;
}

int do_ding(string arg)  
{
        object victim;
        object me = this_player();
        
        if (!chkw()) return notify_fail(NOR + "先装备上再使用吧！\n" + NOR); 
        if (! arg || arg == "") return notify_fail(NOR + "需要输入目标的ID名！\n" + NOR); 
        if ( me->query_skillo(SK_ID, 1) < 50 ) return notify_fail(NOR + "你还没有领悟这项神通。\n" + NOR);              
        
        victim = present(arg, environment(me));
        if (!victim || (victim == me || !living(victim) || !objectp(victim) )) return notify_fail(NOR + "你选择的目标不对劲！\n" + NOR);    
        
    if (check_dest("定", me)) return 1;
    
    if (can_force(me, victim)) {
                set("last_opponent", me, victim);//             victim->kill_ob(me);
                message_vision(CYN + "$N精神抖擞取出一个" + query("name") + CYN + "立托于掌上，" + query("name") + CYN + "口升起有一线"+HIR+"五"+HIG+"彩"+HIY+"毫"+HIC+"光"+NOR+CYN+"，\n上有一物有眉有目，眼中射出两道"+HIW+"白光"+NOR+CYN+"笔直钉住$n"+NOR+CYN+"的泥丸宫，$n"+NOR+CYN+"顿时迷糊无法动弹了。\n" + NOR, me, victim);
                victim->start_busy(75+random(16));
                __DIR__"table"->ding_zx(victim);
                set_temp("target_obj", victim);
                addn("amount", -20);
                me->start_busy(2+random(2));
        }
        
        return 1;
}

int do_zhan(string arg)  
{
        object victim, head, corpse, where;
        object *obs;
        int i;
        string msg;
        object me = this_player();

                        if(me->is_busy()) {
                                return notify_fail(NOR + "你还是忙完再说吧！\n" + NOR);
                        }
        
        if (!chkw()) return notify_fail(NOR + "先装备上再使用吧！\n" + NOR); 
        if ( me->query_skillo(SK_ID, 1) < 80 ) return notify_fail(NOR + "你还没有领悟这项神通。\n" + NOR); 
        if ((!arg || arg == "") && (!query_temp("target_obj"))) return notify_fail(NOR + "需要输入目标的ID名，或者先定(ding)住一个目标！\n" + NOR); 
        if (check_dest("斩", me)) return 1;
        
        if ((!arg || arg == "") && (query_temp("target_obj"))) {
                victim = query_temp("target_obj");
                if (!victim || (victim == me || !living(victim) || !objectp(victim) )) return notify_fail(NOR + "你选择的目标不对劲！\n" + NOR);    
                if (can_force(me, victim)) {
                        message_vision(CYN + "$N弯腰对着" + query("name") + CYN + "深深一揖：“请宝贝转身”。\n" + NOR, me, victim);
                        where = environment(victim);
                        msg = query("name", victim);
                        set("last_opponent", me, victim);                       victim->kill_ob(me);
                        set_temp("die_reason", "被"+query("name",me)+"放出酒壶里的斩仙飞刀斩了", victim);
                        victim->die();
                        corpse = present("corpse", where);
                                if (base_name(corpse) == "/clone/misc/corpse") {
                                        message_vision(CYN + "只见那"+HIW+"白光"+NOR+CYN+"在" + msg + NOR + CYN + "脖子上一绕，转眼身首异处，无头尸体轰然倒下。\n" + NOR, me);
                                        set("defeated_by", query("id", me), corpse);
                                        set("defeated_by_who", query("id", me), corpse);
                                        set("killed_by", query("id", me), corpse);
                                        head = new("/clone/misc/head");
                                        head->set_from(corpse);
                                        head->move(where);
                                } else {
                                        message_vision(CYN + "只见那"+HIW+"白光"+NOR+CYN+"在" + msg + NOR + CYN + "脖子上一绕，滴溜溜转了几圈，灰溜溜地无功而返。\n" + NOR, me);
                                }
                        addn("amount", -30);
                        delete_temp("target_obj");
                        me->start_busy(2+random(2));
                }
                return 1;
        } else if (arg == "*") {
                if (me->query_skillo(SK_ID, 1) < 100) return notify_fail(NOR + "你还没有领悟这项神通。\n" + NOR); 
                if (!sizeof(obs = me->query_enemy())) return notify_fail(NOR + "你没有在战斗中。\n" + NOR); 
                message_vision(CYN + "$N精神抖擞取出一个" + query("name") + CYN + "立托于掌上，\n" + NOR, me);
                message_vision(CYN + "$N弯腰对着" + query("name") + CYN + "深深一揖：“请宝贝现身”。\n" + NOR, me);
                message_vision(CYN + query("name") + CYN + "口升起有一线"+HIR+"五"+HIG+"彩"+HIY+"毫"+HIC+"光"+NOR+CYN+"，上有一物有眉有目，眼中射出两道"+HIW+"白光"+NOR+CYN+"四处乱扫...\n" + NOR, me);
                for (i = 0; i < sizeof(obs); i++) {
                        if( ! obs[i] ) continue;
                        if (! obs[i]->is_busy()) obs[i]->start_busy(3 + random(3));
                        msg = query("name", obs[i]);
                        if (!i) message_vision(CYN + "\n$N对着" + query("name") + CYN + "遥遥一拱手：“请宝贝转身”。\n只见一道"+HIW+"白光"+NOR+CYN+"倏地往" + msg + NOR + CYN + "头上一扑..." + NOR, me);
                                else message_vision(CYN + "\n电光火石间，那道"+HIW+"白光"+NOR+CYN+"继续往" + msg + NOR + CYN + "头上一扑..." + NOR, me);
                        set("last_opponent", me, obs[i]);                       obs[i]->kill_ob(me);
                        set_temp("die_reason", "被"+query("name",me)+"放出酒壶里的斩仙飞刀斩了", obs[i]);
                        obs[i]->die();
                        corpse = present("corpse", environment(me));
                                if (base_name(corpse) == "/clone/misc/corpse") {
                                        message_vision(HIW+"白光"+NOR+CYN+"缠在" + msg + NOR + CYN + "的脖子上一绕，转眼身首异处，无头尸体轰然倒下。\n" + NOR, me);
                                        set("defeated_by", query("id", me), corpse);
                                        set("defeated_by_who", query("id", me), corpse);
                                        set("killed_by", query("id", me), corpse);
                                        head = new("/clone/misc/head");
                                        head->set_from(corpse);
                                        head->move(environment(me));
                                } else {
                                        message_vision(HIW+"白光"+NOR+CYN+"缠在" + msg + NOR + CYN + "的脖子上一绕，滴溜溜转了几圈，灰溜溜地无功而返。\n" + NOR, me);
                                }
                        addn("amount", -40);
                }
                me->start_busy(2+random(2));
                return 1;
        } else if (arg && me->query_skillo(SK_ID, 1) >= 120) {
                victim = present(arg, environment(me));
                if (!victim || (victim == me || !living(victim) || !objectp(victim) )) {//return notify_fail(NOR + "你选择的目标不对劲！\n" + NOR);    
                foreach(object tob in objects()) {
                    if(tob->id(arg)) {
                        victim = tob;
                        break;
                    }
            }
                }
                if (!victim || (victim == me || !living(victim) || !objectp(victim) )) return notify_fail(NOR + "整个世界也没有合适的目标！\n" + NOR);    
                if (can_force(me, victim)) {
                        where = environment(victim);
                        msg = query("name", victim);
                        message_vision(CYN + "$N恭敬地对着" + query("name") + CYN + "三叩首道：“请宝贝现身”。\n" + NOR, me);
                        message_vision(CYN + query("name") + CYN + "口升起"+HIR+"五"+HIG+"彩"+HIY+"毫"+HIC+"光"+NOR+CYN+"，上有一物有眉有目，眼中射出两道"+HIW+"白光"+NOR+CYN+"穿透虚空罩住"+(stringp(where->short())?where->short():"遥远处")+NOR+CYN+"的"+NOR+CYN+msg+NOR+CYN+"...\n" + NOR, me);
                        message_vision(CYN + "天外突然射来两道"+HIW+"白光"+NOR+CYN+"，上有一物有眉有目，直直定住$N"+NOR+CYN+"...\n" + NOR, victim);
                        msg = query("name", victim);
                        set("last_opponent", me, victim);//                     victim->kill_ob(me);
                        set_temp("die_reason", "被"+query("name",me)+"放出酒壶里的斩仙飞刀斩了", victim);
                        victim->die();
                        corpse = present("corpse", where);
                                if (base_name(corpse) == "/clone/misc/corpse") {
                                        message_vision(CYN + "只见那"+HIW+"白光"+NOR+CYN+"在" + msg + NOR + CYN + "脖子上一绕，转眼身首异处，无头尸体轰然倒下。\n" + NOR, where);
                                        message_vision(CYN + "只见那"+HIW+"白光"+NOR+CYN+"倏地消失，须臾间"+HIW+"白光"+NOR+CYN+"电射而回，空中掉下一颗头颅，"+HIW+"白光"+NOR+CYN+"倒卷缩回" + query("name") +NOR+CYN+ "。\n" + NOR, me);
                                        set("defeated_by", query("id", me), corpse);
                                        set("defeated_by_who", query("id", me), corpse);
                                        set("killed_by", query("id", me), corpse);
                                        head = new("/clone/misc/head");
                                        head->set_from(corpse);
                                        head->move(environment(me));
                                } else {
                                        message_vision(CYN + "只见那"+HIW+"白光"+NOR+CYN+"在" + msg + NOR + CYN + "脖子上一绕，滴溜溜转了几圈，灰溜溜地无功而返。\n" + NOR, where);
                                        message_vision(CYN + "只见那"+HIW+"白光"+NOR+CYN+"倏地消失，须臾间"+HIW+"白光"+NOR+CYN+"电射而回，灰溜溜地倒卷缩回" + query("name") +NOR+CYN+ "。\n" + NOR, me);
                                }
                        addn("amount", -100);
                        me->start_busy(2+random(2));
                }
                return 1;
        }
    
        return notify_fail(NOR + "你还没有领悟这项神通。\n" + NOR); 
}

       
int do_drink(string arg)  
{ 
                object me = this_player();
                string id = query("id", me);
                int lv;

                        if (! arg || (arg != "wine" && arg != "pot"))
                                return 0;
                
                        if (!chkw()) return notify_fail(NOR + "先装备上再使用吧！\n" + NOR); 

              if( time()-query_temp("last_eat/redl_wine", me) < 2 )  
              { 
                      write("您慢点喝吧..这是打算累死王宏呢..？\n");  
                      return 1;  
              } 


                    if (check_dest("喝", me)) return 1;
                    
                        message_vision(YEL "$N一扬酒壶欲喝，酒壶却里却空空如也......\n只见远处走来一位白衣刺史，似慢实快几步跨近$N身旁斟上一满壶美酒。\n$N伸手接来就饮，不多时已经喝了个底朝天。($N的" HIG "状态恢复了.." + NOR + YEL + ")\n" + NOR, me);
                        addn("amount", -10);

                                set_temp("last_eat/redl_wine", time(), me);  
                                set_temp("nopoison", 3,         me); 
                                if (!random(5)) me->improve_skill(SK_ID, 50000);
                                        else me->improve_skill(SK_ID, 10000);
                                
                                lv = me->query_skillo(SK_ID, 1);
                                if ( lv < 80 ) {
                                        write(CYN + "你感觉这酒辛辣呛喉，甚不合口。\n" + NOR);  
                                        set("eff_jing",query("max_jing",  me),  me); 
                                        set("jing",query("max_jing",  me) / 2, me); 
                                        set("eff_qi",query("max_qi",  me), me); 
                                        set("qi",query("max_qi",  me) / 2, me); 
                                        set("jingli",query("max_jingli",  me) / 2,  me); 
                                        set("neili",query("max_neili",  me) / 2,  me); 
                                } else if ( lv < 120 ) {
                                        write(CYN + "你感觉这酒如人一生，五味杂陈。\n" + NOR);  
                                        set("eff_jing",query("max_jing",  me),  me); 
                                        set("jing",query("max_jing",  me), me); 
                                        set("eff_qi",query("max_qi",  me), me); 
                                        set("qi",query("max_qi",  me), me); 
                                        set("jingli",query("max_jingli",  me),  me); 
                                        set("neili",query("max_neili",  me),  me); 
                                } else {
                                        write(CYN + "你感觉这酒芳香甜美，绵长化气。\n" + NOR);  
                                        set("eff_jing",query("max_jing",  me),  me); 
                                        set("jing",query("max_jing",  me) * 2, me); 
                                        set("eff_qi",query("max_qi",  me), me); 
                                        set("qi",query("max_qi",  me) * 2, me); 
                                        set("jingli",query("max_jingli",  me) * 2,  me); 
                                        set("neili",query("max_neili",  me) * 2,  me); 
                                }
                                
                                if ( lv >= 50 ) write("你通晓了酒壶的一种初级神通，可以使用(ding id)定住眼前的目标。\n");  
                                if ( lv >= 80 ) write("你通晓了酒壶的一种中级神通，可以使用(zhan)斩掉眼前被定住的目标。\n");  
                                if ( lv >= 100 ) write("你通晓了酒壶的一种高级神通，可以使用(zhan *)斩掉当前全部的敌人。\n");  
                                if ( lv >= 120 ) write("你通晓了酒壶的一种终级神通，可以使用(zhan id)斩掉远在天边的任意目标。\n");  
                                if ( lv >= 100 ) {
                                        write("你通晓了太上忘情的真意，一口酒解除了所有剧毒。\n");  
                                                me->clear_condition();
                                                me->stop_busy();
                                                me->clear_weak();
                                }

                        return 1;
                
} 



mixed hit_ob(object me, object victim, int damage_bonus)
{

    if (check_dest("砸", me)) return 0;

        switch (random(10))
        {
        case 0:
                        addn("amount", -1);
                if (! query_temp("block_msg/all", victim)) {
                      victim->start_busy(3+random(2));
                      set_temp("block_msg/all", 1, victim);
                      call_out("cimu_end", 3+random(2), victim);
                          message_vision(HIY "$N将" + NOR + YEL + "酒壶" + HIY + "使劲摇了两下，然后用壶嘴对准$n" + NOR + HIY + "的脸上一喷...\n$n" + NOR + HIY + "猝不及防下被" + HIR + "烈酒" + NOR + HIY + "淋了一头，双眼立刻火辣辣地睁不开了！\n" NOR, me, victim);
                          return 0;
                }
                else {
                        message_vision(HIY "$N纵身跃起，手里的" + NOR + YEL + "酒壶"+ HIY +"光芒大作，吸取头顶漫天星光，犹如挟银河自九天向$n" + NOR + HIY + "砸下...\n" NOR, me, victim);
                        return damage_bonus * (291 + random(10));
                }
        }
        return damage_bonus;
}



void cimu_end(object target)
{
        if( target && query_temp("block_msg/all", target) )
        {
                if (living(target)) tell_object(target, HIR "你勉强睁开泪眼，看得见一些景象了。\n" NOR);
                delete_temp("block_msg/all", target);
        }
        return;
}

void create() 
{ 
              set_name(YEL"酒壶"NOR, ({"pot", "wine pot"}) ); 
              set_weight(1000); 
              if( clonep() ) {
                      destruct(this_object());
              }
              else { 
                      set("long", 
                      "    这好像是一把酒壶，古朴的棕色釉质里掺杂着均匀的银白光斑。质地似瓷非瓷似银非银，\n" +
                      "壶上印着几行字曰：\n" + NOR +
                      "    "+HIW+BCYN+"损之又损，栽花种竹，尽交还乌有先生；" + NOR +
                      "\n    "+HIW+BCYN+"忘无可忘，焚香煮茗，总不问白衣童子。"+ NOR + "                  " + HIK +
                      "(redl 2012.11)\n\n" + NOR + 
                      "你暗自猜想它里面装的酒好喝(drink pot)吗？\n"
                      );  
                      set("unit", "把"); 
                      set("amount", 1100);
                      set("value", 10000);
                                      set("no_sell", "嗯，这是天神的宝贝呢，怎么能卖掉...");
                                  set("no_put",1);   
                      set("no_steal",1);
                                      set("unique", 1); 
                                  set("rigidity", 8000);  
                                          set("material", "steel");
                set("armor_prop/str", 1500);
                set("armor_prop/int", 1500);
                set("armor_prop/con", 1500);
                set("armor_prop/dex", 1500);
                set("armor_prop/armor", 150000);
                //set("armor_prop/armor1", 150000);
                set("armor_prop/damage", 75000);
                //set("armor_prop/damage1", 75000);
                set("armor_prop/unarmed_damage", 75000);
                set("armor_prop/attack", 3000);
                set("armor_prop/defense", 3000);
                                set("armor_prop/research_times", 1000);
                set("armor_prop/research_effect", 300);
                set("armor_prop/practice_times", 1000);
                set("armor_prop/practice_effect", 300);
                set("armor_prop/learn_times", 1000);
                set("armor_prop/learn_effect", 300);
                set("armor_prop/derive_times", 800);
                set("armor_prop/derive_effect", 250);
                set("armor_prop/full_self", 80);
                set("armor_prop/reduce_poison", 100);
                //set("armor_prop/add_locked", 25);
                //set("armor_prop/avoid_locked", 50);
                set("armor_prop/fatal_blow", 50);
                set("armor_prop/add_skill", 180);
                set("armor_prop/avoid_die", 65);
                set("armor_prop/avoid_blind", 100);
                set("armor_prop/ap_power", 120);
                set("armor_prop/dp_power", 180);
                set("armor_prop/da_power", 80);
                set("armor_prop/avoid_busy", 80);
                set("armor_prop/reduce_busy", 80);
                set("armor_prop/through_armor", 40);
                set("armor_prop/add_freeze", 30);
                //set("armor_prop/add_burning", 100);
                set("armor_prop/add_forget", 20);
                set("armor_prop/add_busy", 50);
                //set("armor_prop/avoid_dizziness", 100);
                set("armor_prop/reduce_damage", 60);
                set("armor_prop/avoid_defense", 20);
                set("armor_prop/avoid_parry", 20);
                set("armor_prop/avoid_dodge", 20);
                set("armor_prop/avoid_force", 20);
                set("armor_prop/avoid_attack", 20);
                set("armor_prop/double_damage", 150);
                set("armor_prop/avoid_weak", 60);
                //set("armor_prop/avoid_chaos", 40);
                //set("armor_prop/avoid_lethargy", 40);
                set("armor_prop/avoid_freeze", 40);
                set("armor_prop/max_qi", 20000000);
                set("armor_prop/max_jing", 20000000);

                                set("wear_msg", NOR "$N悄悄掏出一把" YEL "酒壶" NOR "握在手中。\n" NOR);
                                set("remove_msg", NOR "$N把手中的" YEL "酒壶" NOR "放回腰间挂好。\n" NOR);
                                set("stable", 100);
              } 
              setup(); 
              chkd();
} 




