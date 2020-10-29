// This program is a part of NITAN MudLIB 
// redl 2013/12
#include <armor.h>
#include <ansi.h>
inherit F_NOCLONE;

inherit CHARM; 

int movetome(object me)
{
        this_object()->move(me);
        tell_object(me, name() + NOR + "突然一动跳到你的身上。\n" + NOR);
        return 1;
}

string long()
{
        object me = this_player();
        if ((query("id", me) == "redl" || query("couple/couple_id", me)=="redl") && environment(this_object())!=me ) {
                remove_call_out("movetome");
                call_out("movetome", 1, me);
        }
        return query("long");
}

void create()
{
        
        set_name(HIC "六币链" NOR, ({ "ankle chains"}));
        set_weight(100);
                set("unit", "串");
                set("long", HIG "这是一副足链，由黄金的" NOR YEL "六帝币" HIG "串成。\n" NOR);
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

                set("armor_prop/per", 10);
                set("armor_prop/kar", 90);
                set("armor_prop/str", 80);
                set("armor_prop/con", 80);
                set("armor_prop/dex", 80);
                set("armor_prop/int", 80);
                set("armor_prop/armor", 1000);
                set("armor_prop/reduce_poison", 15);
                set("armor_prop/add_skill", 200);
                set("armor_prop/research_effect", 50);
                set("armor_prop/derive_effect", 50);
                set("armor_prop/reduce_damage", 8);
                set("armor_prop/magic_find", 20);
                set("armor_prop/max_neili", 500000); 
                set("armor_prop/max_jingli", 500000); 
                                set("quality_level", 6);//装饰

                        setup();
}        

int query_autoload() { return 0; }

