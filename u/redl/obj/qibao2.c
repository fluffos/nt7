// This program is a part of NITAN MudLIB 
// redl 2013/5
#include <armor.h>
#include <ansi.h>

inherit EARRING;

#define TIME_INTERVAL 10        //BONUS_DELAY必须是这里的整数倍，且大于640
#define BONUS_DELAY 4320        //一天20次
#define BONUS_EXP 2000000       //每次奖励exp


void jieguozi()
{
        object own = environment(this_object());

        int i = query("guozi_step");
                if ( objectp(own) && playerp(own) && (query("id", own) == query("me_id")) && query("equipped") == "worn" ) {
                        i -= TIME_INTERVAL;
                        if (i<1) {
                                tell_object(own, NOR + YEL + "只见" + HIG + "七宝妙树·耳环" + NOR + YEL + "上，花瓣零落，露出几枚晶莹透绿的果实。\n$N伸手轻轻摘下果实，得到了七种珍宝！\n" + NOR);
                                new("/clone/tessera/fdiamond")->move(own);
                                new("/clone/tessera/femerald")->move(own);
                                new("/clone/tessera/fsapphire")->move(own);
                                new("/clone/tessera/fruby")->move(own);
                                new("/clone/tessera/ftopaz")->move(own);
                for(int i2 = 10; i2 > 0; i2--) {
                        new("/clone/gift/xuanhuang")->move(own);
                }
                                new("/clone/medicine/yuqingwan")->move(own);
                                call_other(GIFT_D, "bonus", own, ([ "exp":BONUS_EXP, "pot":BONUS_EXP/4, "mar":BONUS_EXP/8, "prompt":"你在七宝妙树下参悟了大道法则之后"]));
                        }
                        else if (i==30) tell_object(own, NOR + YEL + "你看见" + HIG + "七宝妙树·耳环" + NOR + YEL + "上，菩提花开始渐渐凋谢……\n" + NOR);
                        else if (i==120) tell_object(own, NOR + YEL + "你看见" + HIG + "七宝妙树·耳环" + NOR + YEL + "上，花苞慢慢长大，变成了艳丽的红莲花。\n" + NOR);
                        else if (i==360) tell_object(own, NOR + YEL + "你看见" + HIG + "七宝妙树·耳环" + NOR + YEL + "上，嫩黄色的花骨朵长出来了。\n" + NOR);
                        else if (i==640) tell_object(own, NOR + YEL + "你看见" + HIG + "七宝妙树·耳环" + NOR + YEL + "上，悄悄钻出了一点嫩黄色。\n" + NOR);
                        if (i<1) set("guozi_step", BONUS_DELAY);
                                else set("guozi_step", i);
                }

        call_out("jieguozi", TIME_INTERVAL);

        if (  objectp(own) && query("me_id") ) 
                if (query("id", own) != query("me_id")) destruct(this_object());//非主人身上时
                else if (!query("env/invisible_item", own)) destruct(this_object());//主人没有设置隐藏时
}

void create()
{
        set_name(HIR "紫金花耳环" NOR, ({ "zijinhua erhuan3", "qibao miaoshu", "qibao", "erhuan" }));
        set_weight(100);
                set("unit", "枚");
                set("long", GRN "七宝妙树·耳环，这是用老祖证道的菩提树枝所制，象征着如海的智慧。\n" NOR);
                set("value", 500000000);
                set("material", "gold");
                set("armor_prop/str", 50);
                set("armor_prop/int", 100);
                set("armor_prop/con", 50);
                set("armor_prop/dex", 50);
                set("armor_prop/armor", 5000);
                //set("armor_prop/armor1", 10000);
                set("armor_prop/damage", 2500);
                //set("armor_prop/damage1", 5000);
                set("armor_prop/unarmed_damage", 2500);
                set("armor_prop/attack", 500);
                set("armor_prop/defense", 500);
                                set("armor_prop/research_times", 200);
                set("armor_prop/research_effect", 200);
                set("armor_prop/practice_times", 200);
                set("armor_prop/practice_effect", 200);
                set("armor_prop/learn_times", 200);
                set("armor_prop/learn_effect", 200);
                set("armor_prop/derive_times", 200);
                set("armor_prop/derive_effect", 200);
                set("armor_prop/full_self", 10);
                set("armor_prop/reduce_poison", 15);
                //set("armor_prop/add_locked", 10);
                //set("armor_prop/avoid_locked", 20);
                set("armor_prop/fatal_blow", 5);
                set("armor_prop/add_skill", 180);
                set("armor_prop/avoid_die", 25);
                set("armor_prop/avoid_blind", 90);
                set("armor_prop/ap_power", 25);
                set("armor_prop/dp_power", 30);
                set("armor_prop/da_power", 20);
                set("armor_prop/avoid_busy", 25);
                set("armor_prop/reduce_busy", 20);
                set("armor_prop/max_qi", 300000); 
                set("armor_prop/max_jing", 200000); 
                set("armor_prop/max_neili", 800000); 
                set("armor_prop/max_jingli", 600000); 
                set("no_uget", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                set("guozi_step", BONUS_DELAY);
        setup();
        call_out("jieguozi", TIME_INTERVAL);
}        

int wear()
{
        object me = this_player();
        if (query("id", me) != query("me_id")) {
                tell_object(me, NOR + "你不能佩戴这种特殊物品！\n" + NOR);//不许普通玩家非法穿戴变态属性的物品
                return -1;
        }
        if (::wear()) {
                //message_vision(YEL + "$N轻轻捻起一枚" + NOR + query("name") + NOR + YEL + "戴在耳垂上。\n" + NOR, me);
                return 1;
        }
}

// int valid_equip(object user)
// {
//      if (query("id", user) != query("me_id")) {
//              tell_object(user, NOR + "你不能佩戴这种特殊物品！\n" + NOR);//不许普通玩家非法穿戴变态属性的物品
//              return -1;
//      }
//      if (::valid_equip(user)) {
//              //message_vision(YEL + "$N轻轻捻起一枚" + NOR + query("name") + NOR + YEL + "戴在耳垂上。\n" + NOR, me);
//              return 1;
//      }
// }

int do_name(string arg)//授权
{
        object me;
        me = this_player();
        if (! wizardp(me)) return 0;
        if (! arg) return notify_fail("name id!\n");
        
                me = find_player(arg);
                if (!me || !objectp(me) || !playerp(me)) {
                        write("你目前没有发现这玩家在线。\n");
                        return 1;
                }        
        
                set("bindable", 3); 
                set("bind_owner",query("id",  me)); 
        set("me_id", arg);
                set("set_data", 1); 
                set("auto_load", 1); 
        set("env/invisible_item", 1, me);
        this_object()->move(me);
        tell_object(me, "你获得了特殊装备七宝妙树，look erhuan\n不要丢弃或者展示给他人，否则它会消失。\n");
        write("七宝妙树被设为" + arg + "专用的！\n");
        return 1;
}

void init()
{
        add_action("do_name", "name");
}



        
        
