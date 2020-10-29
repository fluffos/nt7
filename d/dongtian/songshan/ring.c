// This program is a part of NITAN MudLIB 
// redl 2013/10
// 一次心跳回复气运点，并有几率抗雷击
#include <armor.h>
#include <ansi.h>
inherit F_NOCLONE;

inherit HAIRPIN;

/*
TEMP DATA :
armor           : 
  "hands" : /data/item/ring/redl ("结婚戒指"),
  "cloth" : /clone/cloth/jinduan#22682389 ("锦缎"),
  "boots" : /clone/cloth/xianlv#22682390 ("仙履"),
  "earring" : /d/dongtian/emei/ring ("凝碧气运莲"),
    "hairpin" : /d/dongtian/moban/ring ("清白气运莲"),
]) 
#define MYHEART         "/inherit/armor/myheart"
#define MYHEART2        "/inherit/armor/myheart2"
#define MYMASK          "/inherit/armor/mymask"
#define EARRING         "/inherit/armor/earring"
#define HAIRPIN         "/inherit/armor/hairpin"
#define MEDAL           "/inherit/armor/medal"
#define MEDAL2          "/inherit/armor/medal2"
#define MEDAL3          "/inherit/armor/medal3"
#define RINGS           "/inherit/armor/rings"
#define CHARM           "/inherit/armor/charm"
*/

void create()
{
        
        set_name(HIY "气运莲" NOR, ({ "qiyun lian", "lian" }));
        set_weight(100);
                set("unit", "支");
                set("value", 1);
                set("material", "gold");
                set("no_uget", 1);
                set("no_drop", 1);
                set("no_give", 1);//坚决不能give，凸显洞主独有的好处
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                                
                                set("wear_msg", NOR CYN "$N" NOR CYN "轻轻拈起一朵$n" NOR CYN "簪在发间。\n"); 
                                set("remove_msg", NOR CYN "$N" NOR CYN "把$n" NOR CYN "从头发上摘了下来。\n"); 
                
                set("maze_item", 1);//避免分解
                set("unique", 1);
                set("no_pawn", 1);
                
                                set_heart_beat(1);
                        setup();
}        


void reborn()
{
        int lv = __DIR__"guangchang.c"->chk_zhenlv();
        string dtn, *dtns;
        
        set("qy", __DIR__"guangchang.c"->query_dt_qy());
        set("dtname", __DIR__"guangchang.c"->load_name());
        dtns = explode(query("dtname"),"");
        dtn = dtns[0]+dtns[1]+dtns[2]+dtns[3];
        set_name(HIC +  dtn + HIY + "气运莲" + NOR, ({ "qiyun lian", "lian" }));
        set("long", HIG "这是一支簪子，由洞天的气运(" + HIK + query("qy") + HIG + ")点结出来的宝贝。\n" NOR);
                                set("armor_prop/max_experience", 150000 + lv * 30000);
                //set("armor_prop/per", 10 + lv * 2);
                set("armor_prop/kar", 30 + lv * 12);
                set("armor_prop/str", 50 + lv * 10);
                set("armor_prop/con", 50 + lv * 10);
                set("armor_prop/dex", 50 + lv * 10);
                set("armor_prop/int", 50 + lv * 10);
                //set("armor_prop/armor", 800 + lv * 160);
                set("armor_prop/reduce_poison", 10);
                set("armor_prop/add_skill", 10 + lv * 10);
                set("armor_prop/research_effect", 25 + lv);
                set("armor_prop/derive_effect", 25 + lv);
                set("armor_prop/reduce_damage", 3 + lv);
                set("armor_prop/magic_find", 10 + lv * 2);
                //set("armor_prop/max_neili", 200000 + lv * 40000); 
                //set("armor_prop/max_jingli", 150000 + lv * 30000); 
        set("quality_level", lv + 1);//装饰，阵等级检查
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
        int dam, i, qy = copy(query("qy"));
        mapping my;
        string fmsg, msg = NOR + "你头发上戴着的" + query("name") + NOR + "撒落几瓣天花，";
        string *cmsg = ({});
        object *enemies, enemy;
        
        qy += 10000;
        
        my = me->query_entire_dbase();

        if ( ((my["jing"]<my["max_jing"]/5) || 
                (my["qi"]<my["max_qi"]/5)) &&
                me->is_fighting() && 
                query("full_time") < time() && 
                random(8)) {//十分钟内，在战斗中，87.5%几率触发一次长生诀
                        set("full_time", time() + 600);

                message_vision(NOR + YEL + "\n虚空中穿过来一只大如山岳的巨掌，按住$N" + NOR + YEL + "的天灵念道：\n  『" + 
                        NOR + CYN + "天上白玉京，十二楼五城，仙人抚汝顶，结发受长生..." + NOR + YEL + "』\n" + NOR, me);
                tell_object(me, HIG "受到洞天气运的加持，你的精气神瞬间全满，原地复活。\n" NOR);
                my["jing"]   = my["eff_jing"]   = my["max_jing"]; 
            my["jingli"] = my["eff_jingli"] = my["max_jingli"]; 
                my["qi"]     = my["eff_qi"]     = my["max_qi"]; 
                my["neili"]  = my["max_neili"];
                me->clear_condition();
                me->stop_busy();
                me->clear_weak();
                if( query_temp("block_msg/all", me) ) {
                        //tell_object(me, HIR "你终于抹掉了眼前的鲜血，能看见了。\n" NOR);
                        delete_temp("block_msg/all", me);
                }
                me->full_self();
                me->start_busy(2);
                message_vision(NOR + YEL + "巨掌缓缓放开$N" + NOR + YEL + "的头顶，对着在场众生轻轻一挥，然后缩回虚空就此不见踪影。\n\n" + NOR, me);
                enemies = me->query_enemy();
            if( enemies && sizeof(enemies) ) {
                foreach(enemy in enemies) {
                        if (enemy && objectp(enemy)) {
                                enemy->start_busy(2);
                                if (playerp(enemy)) {
                                        dam = query("max_qi", enemy) / 2 + qy * 100;
                                enemy->receive_damage("qi", dam, me);
                                enemy->receive_wound("qi", dam / 2, me);
                                } else {
                                        dam = query("max_qi", enemy) * 99 / 100 + qy * 20000;
                                enemy->receive_damage("qi", dam, me);
                                enemy->receive_wound("qi", dam / 2, me);
                                }
                                message_vision(NOR + HIY + "$N" + NOR + HIY + "犹如" + (random(2) ? "飓风":"狂风") + "中的落叶，" + 
                                        (random(2) ? "失魂落魄":"摇摇欲坠") + "地" + (random(2) ? "喷":"吐") + "出几口" + HIR + "鲜血" + HIY + "。  "+NOR+WHT+"( -"+(string)dam+" )\n" + NOR, enemy);
                                COMBAT_D->report_status(enemy);
                        }
                }
            }
            return;
                }

        if (!random(8)) return;//非战斗中的回复
        if (me->is_fighting()) return;
        if (query("recover_time") > time()) return;
        set("recover_time", time() + 21);
        if (qy > 10000000) qy = 10000000;
        
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
        
        if (sizeof(cmsg)) {
                //tell_object(me, sort_msg(msg + implode(cmsg, "、") + "。\n" + NOR, 56));
                tell_object(me, msg + implode(cmsg, "、") + "。\n" + NOR);
        }
}


void heart_beat()
{
        object where = environment();
        
        if (!where || !where->is_character()) return;
        if (!query("equipped")) return;
        addn_p(where);
}

int query_autoload() { return 0; }


