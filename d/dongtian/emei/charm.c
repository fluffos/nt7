// This program is a part of NITAN MudLIB 
// redl 2013/10
#include <armor.h>
#include <ansi.h>

inherit CHARM;

string long()
{
        return query("longx") + HIK + " ( " + (string)(query("n_flee")) + " )\n" + NOR;
}

void create()
{
        
        set_name(HIY "气运符" NOR, ({ "qiyun fu", "fu" }));
        set_weight(100);
                set("unit", "枚");
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

                set_heart_beat(3);
                        setup();
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
        set_name(HIC +  dtn + HIY + "气运符" + NOR, ({ "qiyun fu", "fu" }));
        set("longx", HIG "这是一枚护身符，由洞天的气运结成的宝贝，退出游戏或洞天都会飞走。\n" NOR);
                                set("armor_prop/max_experience", 2000000 + lv * 200000);
                set("armor_prop/kar", 120 + lv * 16);
                set("armor_prop/research_effect", 50 + lv * 6);
                set("armor_prop/derive_effect", 50 + lv * 6);
        set("quality_level", lv + 1);//装饰
        set("dt_owner", own);
        set("n_flee", 3600 + lv * 720);
        set("material", "tian jing");
        set("material_file", "/clone/goods/tianjing");

}

int query_autoload() { return 0; }

void heart_beat()
{
        object own, where = environment();
        object me = this_object();
        if (!where) return;
        own = query("dt_owner");
        if (!own || own!=where) {
                destruct(me);
                return;
        }
        if ( query("n_flee") < 1 || 
        (strsrch(base_name(environment(own)), "/d/dongtian") == -1) ) {
                message_vision(NOR + CYN + "$N" + NOR + CYN + "身上的$n" + NOR + CYN + "化作一阵流光往" + query("dtname") + "大殿" + NOR + CYN + "飞走了。\n" + NOR, own, me);
                destruct(me);
                return;
        }
        addn("n_flee", -3);
}


