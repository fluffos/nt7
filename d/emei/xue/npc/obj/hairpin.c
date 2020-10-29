// This program is a part of NITAN MudLIB 
// redl 2014
// 回复，并抗九老
#include <armor.h>
#include <ansi.h>
inherit F_NOCLONE;

inherit HAIRPIN;
int query_autoload() { return 0; }

void create()
{
        
        set_name(HIR "波陀摩" HIY "神花" NOR, ({ "hua", "btm hua" }));
        set("long", HIG "这是一支花簪子，对九老洞里的邪物有特殊抵御，新手刷蝙蝠必备。\n" NOR);
        set_weight(100);
                set("unit", "朵");
                set("value", 100);
                set("material", "gold");
                
//                set("no_give", 1);
//                set("no_drop", 1);
//                set("no_get", 1);
//                set("no_uget", 1);
                set("no_steal", 1);
                set("no_sell", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                set("no_pawn", 1);
                //set("maze_item", 1);//不能give
                set("unique", 1);//已避免分解
                                set("quality_level", 6);
                                
                                set("wear_msg", NOR CYN "$N" NOR CYN "轻轻拈起一朵$n" NOR CYN "簪在发间。\n"); 
                                set("remove_msg", NOR CYN "$N" NOR CYN "把$n" NOR CYN "从头发上摘了下来。\n"); 
                
                set("armor_prop/per", 20);
                set("armor_prop/kar", 30);
                set("armor_prop/armor", 50000);
                set("armor_prop/reduce_poison", 100);
                set("armor_prop/add_skill", 280);
                set("armor_prop/research_effect", 150);
                set("armor_prop/derive_effect", 300);
                set("armor_prop/reduce_damage", 50);
                set("armor_prop/max_qi", 50000000); 
                set("armor_prop/max_jing", 25000000); 

                set("full_time", 3);
                                set_heart_beat(3);
                        setup();
}        


void reborn(object me)
{
        tell_object(me, NOR + "\n你身上的" + query("name") + NOR + "嗖地一声，往虚空中飞走了。\n\n" + NOR);
        this_object()->unequip();
        destruct(this_object());
}

int addn_c(int a, int b, int c)//max,current,add
{
        if (a > b) {
                if (b + c <= a) return c;
                return a - b;
        }
        return 0;
}

void addn_p(object me)
{
        int dam, i, qy = 10000 + copy(query("level", me) * 100000);
        mapping my;
        string fmsg, msg = NOR + "$N头发上戴着的" + query("name") + NOR + "散发着芬芳，";
        string *cmsg = ({});

        if (query("recover_time") > time()) return;
        if (playerp(me)) {
                set("recover_time", time() + 29);
        }
        else {
                set("recover_time", time() + 8);
                qy /= 2;
        }
        my = me->query_entire_dbase();
        if (qy > 100000000) qy = 100000000;
        
                if (i = addn_c(my["max_qi"], my["eff_qi"], qy)) {
                        my["eff_qi"] += i;
                        if (i = addn_c(my["eff_qi"], my["qi"], qy)) {
                                my["qi"] += i;
                        }
                        cmsg += ({"气回复(" + HIY + (string)qy + NOR + ")点" + NOR});
                }
                qy /= 2;
                if (i = addn_c(my["max_jing"], my["eff_jing"], qy)) {
                        my["eff_jing"] += i;
                        if (i = addn_c(my["eff_jing"], my["jing"], qy)) {
                                my["jing"] += i;
                        }
                        cmsg += ({"精回复(" + HIY + (string)qy + NOR + ")点" + NOR});
                }
                qy /= 2;
                if (i = addn_c(my["max_neili"], my["neili"], qy)) {
                        my["neili"] += i;
                        cmsg += ({"内力回复(" + HIY + (string)qy + NOR + ")点" + NOR});
                }
        
 if (me->is_fighting()) {
        me->clear_condition();
        me->stop_busy();
        me->clear_weak();
}

        if( query_temp("block_msg/all", me) ) {
                        delete_temp("block_msg/all", me);
                        tell_object(me, HIR "你终于抹掉了眼前的鲜血，能看见了。\n" NOR);
        }

        if (sizeof(cmsg)) {
                message_vision(msg + implode(cmsg, "、") + "。\n" + NOR, me);
        }
}


void heart_beat()
{
        object me = this_object();
        object where2, where = environment();
        
        if (!where || !where->is_character()) {
                destruct(me);
                return;
        }
        
        if (playerp(where)) {
                if (query("owner_ob") == where) {
                        if ( (time()>query("owner_time") && (query("level", where)>100)) ||//对于小于100级的新手，永久使用
                                        !(where2 = environment(where)) || 
                                        (strsrch(base_name(where2), "/d/emei/xue/") == -1)
                                ) reborn(where);
                } else {
                        set("owner_ob", where);
                        set("owner_time", time() + 5400);//1.5小时掌控时间内攻破血池
                }
        }
        
        if (!query("equipped")) return;
        addn_p(where);
}



