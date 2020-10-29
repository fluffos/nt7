// 上古十大神器之 轩辕剑
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIY "轩辕剑" NOR, ({ "xuanyuan jian", "xuanyuan", "jian" }) );
        set_weight(200);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "把");
                set("long", HIY "此乃上古神器之首，拥有着无穷的力量，据说"
                                "拥有此剑者可驰骋人、魔、神三界，势不可挡。\n"
                                "上面刻满了各种奇怪的文字，像是佛教经文。\n" NOR);
                set("material", "tian jing");
                set("wield_msg", HIY "$N" HIY "一声轻呼，两条神龙自天而下，拥着一把周身泛着\n"
                                 "金光的神剑，刹那间此剑犹如一道流星划过，落入$N" HIY "手中。\n" NOR);                               
                set("unwield_msg", HIY "$N" HIY "心意一转，轩辕剑已归鞘。\n" NOR);
                set("stable", 100);

        }
        init_sword(1200);
        setup();
}