#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
        set_name(HIR "凤凰披风" NOR, ({ "fenghuang pifeng", "fenghuang", "pifeng" }));
        set_weight(1000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "件");
                set("long", HIR"\n一件用凤凰羽毛织成的披风，乃稀世珍。\n" NOR
                            HIC "有效招架修正：+ 20        有效轻功修正：+ 30\n" NOR
                            HIC "抗毒效果修正：+ 15%       防御效果等级：  70\n" NOR
                            HIC "抗毒回避修正：+ 15%\n" NOR);

                set("material", "phoenix");
                set("material_name", "朱雀羽毛、朱雀之角、朱雀筋、五彩玲珑珠");
                set("can_summon", 1);
                set("summon_id", "fenghuangjia");
                set("ctype", "披风");
                set("summon_wear_msg", HIR "刹那间，一股火焰从地心腾射而出，直冲天际，\n"
                                       "转眼间，火焰渐渐化作一只火凤凰，与$N" HIR "合为一体。\n" NOR);
                set("summon_remove_msg", HIR "只听得一声长嘶，一只巨大的火凤凰消失与天际。\n" NOR);

                set("value", 4500000);
                set("armor_prop/armor", 50);
                set("armor_prop/dodge", 30);
                set("armor_prop/parry", 20);
                set("armor_prop/reduce_poison", 15);
                set("armor_prop/avoid_poison", 15);
        }
        setup();
}

int query_autoload()
{
        return 1;
}