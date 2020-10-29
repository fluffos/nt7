#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(HIY "诛元仙丹" NOR, ({ "zhuyuan xiandan1",  }));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIY "传说此丹乃是天宫中的神品，凡人吃了可以平增膂力。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 100000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "str");
                set("gift_name", "先天膂力");
                set("gift_point", 79);
                set("gift_msg", HIY "突然间你只觉双臂几乎爆裂，充满了力量。\n" NOR);
        }
        setup();
}
