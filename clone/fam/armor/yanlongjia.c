#include <ansi.h>
#include <armor.h>

inherit ARMOR;

// 组合物品，通过特殊故事杀死特殊npc后获得
// 龍须2个 + 龍鳞10个 + 龍角2个 + 龍筋1根 + 赤龍之瞳2个 = 炎龍聖甲

void create()
{
        set_name(HIY "炎龍聖甲" NOR, ({ "yanlong shengjia", "yanlong", "shengjia" }));
        set_weight(6000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "副");
                set("long", HIY "\n一副充满着神奇力量的聖甲，散发着奇异的光芒。\n" NOR
                            HIG "有效招架修正：+ 50        有效轻功修正：+ 30\n" NOR
                            HIG "抗毒效果修正：+ 25%       防御效果等级： 180\n" NOR
                            HIG "抗毒回避修正：+ 20%\n" NOR);
                set("value", 2000000);
                set("material", "dragon");

                set("material_name", "龍须、龍鳞、龍角、龍筋、赤龍之瞳");
                set("can_summon", 1);
                set("summon_id", "yanlongjia");
                set("ctype", "护甲");
                set("summon_wear_msg", HIY "刹那间，天空忽暗，风声大作，一条炎龍腾空而来，\n"
                                "渐渐地化为一阵青烟，与$N" HIY 
                                "合为一体。\n" NOR);
                set("summon_remove_msg", HIY "风雨渐息，一条炎龍疼空而起，消失在天际。\n" NOR);
                set("armor_prop/armor", 180);
                set("armor_prop/dodge", 30);
                set("armor_prop/parry", 50);
                set("armor_prop/reduce_poison", 25); // 提高30%抗毒效果
                set("armor_prop/avoid_poison", 20); // 提高20%回避效果
                set("avoid_msg", HIG "刹那间，" HIY "炎龍聖甲" HIG "散发出"
                                             "一道奇异的光芒，将毒质全部吸收。\n" NOR);
                set("reduce_msg", HIR "刹那间，" HIY "炎龍聖甲" HIR "散发出"
                                             "一道奇异的光芒，吸收了部分毒质。\n" NOR);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
