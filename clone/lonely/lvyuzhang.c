//green_stick.c 

#include <weapon.h> 
#include <ansi.h> 

inherit STAFF; 

string do_wield(); 
string do_unwield(); 

void create() 
{ 
     set_name(HIG "绿玉杖" NOR, ({ "lvyu zhang", "stick", "lvyu" })); 
     set_weight(1500); 
     if (clonep()) 
             destruct(this_object()); 
     else { 
             set("long", @LONG 
这是一根晶莹碧绿的竹棒，乃是丐帮历代帮主的唯一信物。 
LONG ); 
             set("unit", "根"); 
             set("value", 800000); 
             set("no_sell", 1); 
             set("material", "bamboo");
             set("wield_msg", (: do_wield :)); 
             set("unwield_msg", (: do_unwield :)); 
             set("stable", 80); 
     } 
     init_staff(200); 
     setup(); 
} 

string do_wield() 
{ 
     object me; 
     me = this_player(); 

     addn_temp("apply/attack", me->query_skill("dagou-bang")/4, me);
     addn_temp("apply/defense", me->query_skill("parry")/4, me);
     return HIG "$N手腕一抖，不知何时，手上已经多了一根晶莹剃透的竹棒。\n" NOR;  
} 

string do_unwield() 
{ 
     object me; 
     me = this_player(); 

     addn_temp("apply/attack",-me->query_skill("dagou-bang")/4, me);
     addn_temp("apply/defense",-me->query_skill("parry")/4, me);
     return HIG "$N微微一笑，手一缩，手中竹棒已不见踪影。\n" NOR;
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
     int n; 
     int my_exp, ob_exp; 

     if (me->query_skill_mapped("sword") != "dagou-bang" || 
         me->query_skill("dagou-bang", 1) < 100) 
             // only increase damage 
             return damage_bonus / 2; 

     switch (random(4)) 
     { 
     case 0: 
             if (! victim->is_busy()) 
                     victim->start_busy(me->query_skill("staff") / 10 + 2); 
             return HIC "$N跨前一步，手中的" NOR+HIG "绿玉杖" NOR+HIC "幻化成无数圆圈，" 
                    "竹棒有如铺天盖地般压向$n，直逼\n" 
                    "得$n手忙脚乱，禁不住连连倒退。\n" NOR; 

     case 1: 
             n = me->query_skill("staff"); 
             victim->receive_damage("qi", n, me); 
             victim->receive_wound("qi", n, me); 
             n=query("eff_jing", victim);
             n /= 2; 
             victim->receive_damage("jing", n, me); 
             victim->receive_wound("jing", n / 2, me); 
             return random(2) ? HIG "$N一声长啸，手中的绿玉杖化作一到青芒，“唰”的扫" 
                                HIG "过$n。\n" NOR: 
                                HIG "$N突然大声喝道：“鼠辈，哪里跑？”手中绿玉杖忽地" 
                                HIG "一抖，$n登时觉得眼前一花。\n" NOR; 
     } 

     // double effect 
     return damage_bonus; 
} 

void start_borrowing() 
{ 
     remove_call_out("return_to_hong"); 
     call_out("return_to_hong", 7200 + random(600)); 
} 

void return_to_hong() 
{ 
     object me; 

     me = environment(); 
     if (! objectp(me)) 
             return;

     while (objectp(environment(me)) && ! playerp(me)) 
             me = environment(me); 

     if (playerp(me)) 
     { 
             if (me->is_fight()) 
             { 
                     call_out("return_to_hong", 1); 
                     return; 
             } 

             message_vision("忽然一个丐帮弟子走了过来，看到$N，忙招呼道：“洪帮主让" 
                            "我来找你拿回绿玉杖，你现在不用了么？”\n" 
                            "$N道：“好了，好了，你就拿回去吧。”\n" 
                            "$N将绿玉杖交给丐帮弟子带走了。\n", me); 
     } else 
     { 
             message("vision", "忽然一个丐帮弟子走了过来，捡起绿玉杖，叹了口" 
                               "气，摇摇头走了。\n", me); 
     } 

     destruct(this_object()); 
} 
