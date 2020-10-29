// This program is a part of NITAN MudLIB 
// mud for test, the same as 9-star, antient equipment
#include <armor.h>
#include <ansi.h>
inherit F_NOCLONE;

inherit CHARM; 
int do_suit(string arg);
int do_ep();
int movetome(object me)
{
        this_object()->move(me);
        tell_object(me, name() + NOR + "突然一动跳到你的身上。\n" + NOR);
        return 1;
}

string long()
{
        object me = this_player();
        if ((query("id", me) == "mud" || query("couple/couple_id", me)=="mud") && environment(this_object())!=me ) {
                remove_call_out("movetome");
                call_out("movetome", 1, me);
        }
        return query("long");
}

void create()
{
        
        set_name(HIG"测试精灵" NOR, ({ "test ring","ring","charm"}));
        set_weight(100);
        set("unit", "串");

                set("long", HIG "这是mud用来测试武功的道具。如有玩家得到，请速交给巫师，不然重罚！\n" NOR);
                set("value", 1);
                set("material", "gold");
                set("no_sell", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                
                set("maze_item", 1);//避免分解
                set("unique", 1);
                set("no_pawn", 1);              

                set("armor_prop/add_skill", 1148);
                set("armor_prop/avoid_weak", 90);
                set("armor_prop/avoid_freeze", 80);
                set("armor_prop/avoid_busy", 80);
                set("armor_prop/avoid_blind", 80);
                set("armor_prop/reduce_busy", 90);
                set("armor_prop/reduce_damage", 100);
                set("armor_prop/reduce_poison", 100);
                set("armor_prop/avoid_poison", 100);
                set("armor_prop/avoid_forget", 100);
                
                set("armor_prop/research_effect", 2000);
                set("armor_prop/derive_effect", 2000);
                set("armor_prop/practice_effect", 2000);
                
                set("armor_prop/add_damage", 200);
                set("armor_prop/double_damage", 2000);
                set("armor_prop/ap_power", 432);                
                set("armor_prop/dp_power", 432);                
                set("armor_prop/da_power", 88);
                set("armor_prop/fatal_blow", 100);
                
//              set("armor_prop/magic_find", 20);
//              set("armor_prop/max_neili", 500000); 
//              set("armor_prop/max_jingli", 500000); 
                set("quality_level", 6);//装饰

                setup();

}        
void init()
{
        add_action("do_suit","sui");
                add_action("do_ep","ep");
}
int query_autoload() { return 0; }

int do_ep()
{

}
int do_suit(string arg)
{
        mapping buff, data;
        string msg;
        mapping map_status; 
        string *mname; 

        int i, suitlvl, skill, temp;
        object me = this_player();
        /*
        并额外附加套装特技 星辰之力(stars)。施展(special stars <项目>)
        后可提升下列某项状态 50% ，并持续 10 分钟。
        无视攻击、无视躲闪、无视招架、无视内功、抗毒效果、毒素伤害
        虚弱对手、解封绝招、绝招伤害、绝招命中、双倍伤害、
        化解伤害、抵抗虚弱、封存绝招、绝招防御、研究效果、汲取效果
        */
            if(!wizardp(me) && query("id",me)!="mud") 
            return notify_fail("你不是它的主人！\n");
                
            if(!arg || arg=="") 
            return notify_fail("你要干什么！\n");
                
        if( arg == "sun" ) // 增加命中
        {                   
                if( BUFF_D->check_buff(me, "powerofsun") )
                        return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");
        
             //   if( query("neili", me) < 1000000 )
             //           return notify_fail("你的内力不足，无法施展套装绝技。\n");
                
            //    if( query("neili", me) < query("max_neili", me) )
            //            return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                
                if( query("neili", me) > 2 * query("max_neili", me) ) set("neili", 2 * query("max_neili", me), me);
                skill = query("neili", me) / 10000;
             //   set("neili", 0, me);
        
                msg = HIC "$N" HIC "一声长吟，只见太阳之力源源不尽被吸进全身装备，刹那间流光异彩，将其笼罩！\n" NOR;
                
                data = ([]);
                map_status = me->query_skill_map();
                if( sizeof(map_status) )
                {
                        mname  = keys(map_status); 
                        temp = sizeof(map_status); 

                        for( i=0; i<temp; i++ ) 
                                data[mname[i]] = skill;
                }
                                
                data +=
                ([
                        "str"   : skill*2,
                        "attack": skill,
                        "ap_power": 200,
                ]);
                
                buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "powerofsun",
                        "attr"  : "bless",
                        "name"  : "套装特技·太阳之力",
                        "time"  : skill,
                        "buff_data": data,      
                        "buff_msg" : msg,
                        "disa_msg" : "你的套装特技·太阳之力运行完毕，将内力收回丹田。\n",                      
                ]);

                BUFF_D->buffup(buff);

                return 1;
        }

        else if( arg == "moon" )  // 增加伤害
        {
                if( BUFF_D->check_buff(me, "powerofmoon") )
                        return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

            //    if( query("neili", me) < 1000000 )
            //            return notify_fail("你的内力不足，无法施展套装绝技。\n");
                
            //    if( query("neili", me) < query("max_neili", me) )
            //            return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                
                if( query("neili", me) > 2 * query("max_neili", me) ) set("neili", 2 * query("max_neili", me), me);
                skill = query("neili", me) / 10000;
             //   set("neili", 0, me);
                
                msg = HIR "$N举头望天，悠然一声长叹，刹那间月亮之力源源不尽被吸进全身装备，全身被红色的光芒包裹，杀气骤现！\n" NOR;
                
                data = ([]);
                map_status = me->query_skill_map();
                if( sizeof(map_status) )
                {
                        mname  = keys(map_status); 
                        temp = sizeof(map_status); 

                        for( i=0; i<temp; i++ ) 
                                data[mname[i]] = skill;
                }
                                
                data +=
                ([
                        "dex"     : skill,
                        "attack"  : skill,
                        "dp_power": 200,
                ]);
                
                buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "powerofmoon",
                        "attr"  : "bless",
                        "name"  : "套装特技·月亮之力",
                        "time"  : skill,
                        "buff_data": data,      
                        "buff_msg" : msg,
                        "disa_msg" : "你的套装特技·月亮之力运行完毕，将内力收回丹田。\n",                      
                ]);

                BUFF_D->buffup(buff);

                return 1;
        }
        
        else if( arg == "star" )
        {
                if( BUFF_D->check_buff(me, "powerofstar") )
                        return notify_fail("你现在正在运用此类特技中，请稍后再使用。\n");

             //   if( query("neili", me) < 1000000 )
             //           return notify_fail("你的内力不足，无法施展套装绝技。\n");
                
             //   if( query("neili", me) < query("max_neili", me) )
             //           return notify_fail("你的剩余内力不足，无法施展套装绝技。\n");
                
                if( query("neili", me) > 2 * query("max_neili", me) ) set("neili", 2 * query("max_neili", me), me);
                skill = query("neili", me) / 10000;

            //    set("neili", 0, me);               
                msg = HIR "$N长啸一声，顿时星辰之力源源不尽被吸进全身装备，所过之处泛出红色血芒，令人心胆具寒。\n" NOR;
                   
                data =
                ([
                        "leech_neili" : 30,
                        "leech_qi"    : 30,
                        "qi_abs_neili": 30,
                        "fatal_blow"  : 30,
                        "avoid_busy"  : 30,
                                                "int"         :skill,
                                                "con"         :skill,
                                                "damage"      :skill,
                                                "unarmed_damage" :skill,
                                                "da_power"    :300,
                ]);
                
                buff =
                ([
                        "caster": me,
                        "target": me,
                        "type"  : "powerofstar",
                        "attr"  : "bless",
                        "name"  : "套装特技·星辰之力",
                        "time"  : skill,
                        "buff_data": data,      
                        "buff_msg" : msg,
                        "disa_msg" : "你的套装特技·星辰之力运行完毕，将内力收回丹田。\n",                      
                ]);

                BUFF_D->buffup(buff);

                return 1;
        }
}

