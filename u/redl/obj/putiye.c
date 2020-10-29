// This program is a part of NITAN MudLIB 
// redl 2013/1/1 
#include <armor.h>
#include <ansi.h>

inherit EARRING;

#define OWNER_ID "juice,guoxiang,kelly,unable,ruby,"    //指定玩家的装备
#define TIME_INTERVAL 10
#define BONUS_DELAY 720         //每小时结5颗ptz，一天120，给盲人添点儿绿意


int is_redl_room(object room)
{
        if (base_name(room) == "/u/redl/workroom") return 1;
        return 0;
}

void jieguozi()//准许让他把这宝物借予普通玩家赏玩，让他觉得自己有存在感
{
        object own = environment(this_object());
        int i = query("guozi_step");
        
        if (objectp(own) && !is_redl_room(own)) {
                
                if (playerp(own)) {
                        i -= TIME_INTERVAL;
                        if (i<1) {
                                message_vision(NOR + YEL + "只见" + query("name") + NOR + YEL + "上，花瓣零落，露出一枚晶莹透绿的果实。\n$N伸手轻轻摘下果实，得到了一颗" + HIG + "菩提子" + NOR + YEL + "！\n" + NOR, own);
                                new("/clone/gift/puti-zi")->move(own);
                        }
                        else if (i==30) tell_object(own, NOR + YEL + "你看见" + query("name") + NOR + YEL + "上，菩提花开始渐渐凋谢……\n" + NOR);
                        else if (i==120) tell_object(own, NOR + YEL + "你看见" + query("name") + NOR + YEL + "上，花苞慢慢长大，变成了艳丽的红花。\n" + NOR);
                        else if (i==360) tell_object(own, NOR + YEL + "你看见" + query("name") + NOR + YEL + "上，嫩黄色的花骨朵长出来了。\n" + NOR);
                        else if (i==640) tell_object(own, NOR + YEL + "你看见" + query("name") + NOR + YEL + "上，悄悄钻出了一点嫩黄色。\n" + NOR);
                        if (i<1) set("guozi_step", BONUS_DELAY);
                                else set("guozi_step", i);
                }

                if (strsrch(OWNER_ID, query("id", own)+",")<0) {
                        addn("chk_own", TIME_INTERVAL);
                        if (query("chk_own") > 180 * TIME_INTERVAL) {//借出，或者丢失超过半小时
//                              message_vision(NOR + query("name") + NOR + CYN + "轻轻一颤，化为一道青烟消失了！\n" + NOR, own);
//                              own = find_player();
//                              if (playerp(own)) {
//                                      tell_object(own, NOR + CYN + "只见一缕青烟往你迎面扑来，原来是" + query("name") + NOR + CYN + "飞到怀里来了！\n" + NOR);
//                                      this_object()->move(own);
//                              } else {
                                        destruct(this_object());
//                                      return;
//                              }
                        }
                } else set("chk_own", 0);
        
        }
        
        call_out("jieguozi", TIME_INTERVAL);
}

void create()
{
        set_name(HIG "菩提叶·三仙" NOR, ({ "puti ye", "puti", "ye" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", HIG "这是一枚曾经生长在佛祖证道的菩提树上的树叶，象征着如海的智慧和胸怀广阔。\n" NOR);
                set("value", 50000000);
                set("material", "gold");
                set("armor_prop/str", 300);
                set("armor_prop/int", 300);
                set("armor_prop/con", 300);
                set("armor_prop/dex", 300);
                set("armor_prop/armor", 50000);
                set("armor_prop/armor1", 50000);
                set("armor_prop/damage", 25000);
                set("armor_prop/damage1", 25000);
                set("armor_prop/unarmed_damage", 25000);
                set("armor_prop/attack", 2000);
                set("armor_prop/defense", 2000);
                                set("armor_prop/research_times", 3000);
                set("armor_prop/research_effect", 800);
                set("armor_prop/practice_times", 3000);
                set("armor_prop/practice_effect", 800);
                set("armor_prop/learn_times", 3000);
                set("armor_prop/learn_effect", 800);
                set("armor_prop/derive_times", 1500);
                set("armor_prop/derive_effect", 800);
                set("armor_prop/full_self", 20);
                set("armor_prop/reduce_poison", 40);
                //set("armor_prop/add_locked", 10);
                //set("armor_prop/avoid_locked", 20);
                set("armor_prop/fatal_blow", 20);
                set("armor_prop/add_skill", 380);
                set("armor_prop/avoid_die", 35);
                set("armor_prop/avoid_blind", 90);
                set("armor_prop/ap_power", 100);
                set("armor_prop/dp_power", 150);
                set("armor_prop/da_power", 50);
                set("armor_prop/avoid_busy", 30);
                set("armor_prop/reduce_busy", 30);
                set("guozi_step", BONUS_DELAY);
        }
        setup();
        call_out("jieguozi", TIME_INTERVAL);
}        

int query_autoload()
{
        return 1;
}


int wear()
{
        object me = this_player();
        if (strsrch(OWNER_ID, query("id", me)+",")<0) {
                tell_object(me, NOR + "特殊物品，你戴不上这枚叶子...\n" + NOR);//不许普通玩家非法穿戴变态属性的物品
                return -1;
        }
        if (::wear()) {
                message_vision(YEL + "$N轻轻捻起一枚" + NOR + query("name") + NOR + YEL + "插在头发上。\n" + NOR, me);
                return 1;
        }
}


// 
// //get()
//      mapping ob; 
//      object *obs;
//      obs = all_inventory(); 
//      if (sizeof(obs) > 0) 
//      { 
//              if (arrayp(query_temp("objects"))) 
//                      obs -= query_temp("objects"); 
//              //obs = filter_array(obs, (: ! living($1) && clonep($1) && ! $1->is_character() :)); 
//              obs = filter_array(obs, (: ! $1->is_user() :)); //要驱逐宠物的帮助，只能留下玩家自己
//              if (sizeof(obs) > 0) 
//              { 
//                      obs = obs[0..<1]; 
//                      foreach (ob in obs) destruct(ob); 
//              } 
//      } 
        


