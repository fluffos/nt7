// zhenwu-jian.c 真武剑
// Created by Lonely for only one object in mud
#include <ansi.h>
#include <weapon.h>
inherit SWORD;
inherit F_UNIQUE;
void create()
{
        set_name(HIW"真武剑"NOR, ({"zhenwu jian", "sword", "jian"}));
        set_weight(15000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "把");
                set("long", "一把毫不起眼的古剑,剑身不规则的花纹上似乎还带有些铁锈,剑锋上居然还有几个缺口。\n");
                set("value", 100000);
                set("material", "blacksteel");
                set("weapon_prop/dodge", -2);
                set("weapon_prop/parry", 3);
                set("unique", 1);
                set("rigidity", 300);
                set("replica_ob","/d/city/npc/obj/changjian");
                set("no_put",1);
                set("no_steal",1);    
                set("wield_neili", 300);
                set("wield_maxneili", 700);
                set("wield_str", 22);        
                set("enchase/flute", 5);        
                set("wield_msg",HIW"$N[噌]的一声抽出一把真武剑,空气中顿时充满了无边的杀气。\n"NOR);
                set("unwield_msg",HIW"$N把手中的宝剑插入剑鞘。四周的杀气也跟着消失了。\n"NOR);
        }
        init_sword(400,2);
        setup();
}       
