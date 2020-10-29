#include <ansi.h>
#include <music.h>
#include <weapon.h> 

inherit XSWORD; 
inherit F_UNIQUE;

void create()
{
        set_name(HIG"玉箫"NOR,({ "yu xiao", "xiao" }) );
        set_weight(3000);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("value", 7000000);
                set("unique", 1);
                set("rigidity", 300);
                set("no_put", 1);
                set("no_steal", 1);
                set("replica_ob","/clone/weapon/zhuxiao");
                set("material", "steel");
                set("shape", "flute");
                set("long", 
                        "一柄翠玉制玉箫，通体晶莹碧绿，近吹口处几点朱斑，殷红如血，显然都是\n"
                        "数百年乃至上千年的古物。\n");
                set("wield_msg", 
                    HIG "$N从腰间抽出一支玉箫，吹出优雅的箫声。箫声入耳，众人激荡的心情便即平\n"
                        "复。$N随即和道：“苍生笑，不再寂聊，豪情仍在痴痴笑笑。”\n"NOR);
                set("unwield_msg", CYN "$N将$n插到领後。\n" NOR);
                set("unequip_msg", CYN "$N将$n插到领後。\n" NOR);
        }

        init_xsword(90); 
        setup();
}

void init()
{
        add_action("play_xiao", "play");
}