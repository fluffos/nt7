// This program is a part of NITAN MudLIB 
// redl 2013/10
#include <armor.h>
#include <ansi.h>

inherit CLOTH;

string long()
{
        return query("longx") + HIK + " ( " + (string)(query("n_flee")) + " )\n" + NOR;
}

void create()
{
        
        set_name(HIY "洞天甲" NOR, ({ "dongtian jia", "jia" }));
        set_weight(100);
                set("longx", NOR "这副铠甲由洞天的傀儡侍卫凝聚而成。" NOR);
                set("unit", "副");
                set("value", 500);
                set("material", "steel");
                set("no_uget", 1);
                set("no_drop", 1);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_get", 1);
                set("no_steal", 1);
                set("no_beg", 1);
                set("no_put", 1);
                set("no_store", 1);
                
                set("maze_item", 1);//避免分解
                set("unique", 1);
                set("no_pawn", 1);

                set_heart_beat(1);
                        setup();
}        

void fill()
{
        set("n_flee", 2700 + query("zhenlv") * 240 + random(30));
        delete("flag_use_summ");
}

void reborn(object own)
{
        int lv = __DIR__"guangchang.c"->chk_zhenlv();
        string dtn, *dtns;
        
        set("dtname", __DIR__"guangchang.c"->load_name());
        set("zhenlv", lv);
        dtns = explode(query("dtname"),"");
        dtn = dtns[0]+dtns[1]+dtns[2]+dtns[3];
        set("dtname2", dtn);
        set_name(HIC +  dtn + HIY + "洞天甲" + NOR, ({ "dongtian jia", "jia" }));
                                set("armor_prop/max_experience", 15000 + lv * 3000);
                //set("armor_prop/per", 10 + lv * 2);
                set("armor_prop/kar", 20 + lv * 12);
                set("armor_prop/str", 20 + lv * 8);
                set("armor_prop/con", 20 + lv * 8);
                set("armor_prop/dex", 20 + lv * 8);
                set("armor_prop/int", 20 + lv * 8);
                set("armor_prop/armor", 800 + lv * 160);
                set("armor_prop/reduce_poison", 15);
                //set("armor_prop/add_skill", 10 + lv * 10);
                set("armor_prop/research_effect", 15 + lv);
                set("armor_prop/derive_effect", 100 + lv * 50);
                set("armor_prop/reduce_damage", 5 + lv * 2);
                set("armor_prop/magic_find", 5 + lv * 2);
                set("armor_prop/max_neili", 200000 + lv * 40000); 
                set("armor_prop/max_jingli", 150000 + lv * 30000); 
        set("quality_level", lv + 1);//装饰
        set("dt_owner", own);
        fill();

        set("material", "tian jing");
        set("material_file", "/clone/goods/tianjing");

}

int query_autoload() { return 0; }

/*int unequip()
{
        int f;
        object own, me = this_object();
        f = ::unequip();
        if (f) {
                own = query("dt_owner");
                if (own && own==environment()) {
                        message_vision(NOR + CYN + "$N" + NOR + CYN + "身上的$n" + NOR + CYN + "化作一阵流光往" + query("dtname") + NOR + CYN + "飞走了。\n" + NOR, own, me);
                }
                delete("dt_owner");
        }
        return f;
}*/

void heart_beat()
{
        object *enemies, enemy, ob;
        object own, where = environment();
        object me = this_object();
        if (!where) return;
        own = query("dt_owner");
        if (!own || own!=where) {
                destruct(me);
                return;
        }
        //if( !query("equipped") ) return;
        if (query("n_flee") < 1) {
                message_vision(NOR + CYN + "$N" + NOR + CYN + "身上的$n" + NOR + CYN + "化作一阵流光往" + query("dtname") + NOR + CYN + "飞走了。\n" + NOR, own, me);
                destruct(me);
                return;
        }
        if (query("equipped") && own->is_fighting() && !query("summ_ob") && query("summ_time") < time()) {
        enemies = own->query_enemy();
        if( enemies && sizeof(enemies) ) {
                enemy = enemies[random(sizeof(enemies))];
                if (enemy && objectp(enemy) && enemy->is_character() && !query_temp("flag_hslj", enemy)) {
                        set("flag_use_summ", 1);
                message_vision(append_color(NOR + HIY + "\n$N" + NOR + HIY + "身上的" + name() + NOR + HIY + (random(2)? "七彩" : "光华") + 
                        (random(2)? "流转" : "熠熠") + "，" + (random(2)? "化作" : "凝成") + "个傀儡侍卫扑向$n" + NOR + HIY + "。\n\n" NOR, HIY),
                        own, enemy);
                                ob = new(__DIR__"npc/guarder3");
                                set("shadow_own", own, ob);
                                set("is_shadow", 1, ob);
                                set("guarder_level", query("level", own) * (query("zhenlv") * 3 + 5) / 10, ob);
                                set("nflee", time() + 30 , ob);
                                ob->do_copyskill();
                                ob->move(environment(own)); 
                                set("name", query("name", own) + "的" + query("name", ob), ob);
                                set("enemy_player", enemy, ob);
                                ob->stop_busy();
                        ob->command("exert powerup");
                        ob->stop_busy();
                        ob->command("exert shield");
                        ob->stop_busy();
                                ob->set_leader(enemy);
                                ob->kill_ob(enemy);
                                set("nickname", HIC + query("dtname") + NOR, ob);
                                set("armor_own", me, ob);
                                set("smash_ob", get_object(__DIR__"guangchang"), ob);
                                set("summ_ob", ob);
                                set("summ_time", time() + 120);
                        }
                }
        }
        if (query("flag_use_summ")) addn("n_flee", -1);
}


