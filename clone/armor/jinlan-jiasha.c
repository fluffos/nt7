
#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(HIR "锦" HIC "镧" HIM "袈裟" NOR, ({ "jinlan jiasha", "jinlan", "jiasha" }) );
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "件");
                set("long", HIR "此乃传说中唐僧所穿戴的锦镧袈裟，只见金光闪耀，令人睁不开眼，犹如佛光普照般祥和。\n"
                            HIC "仔细看去，袈裟上隐约出现几个大字：" HIG "不坠地狱，不入轮回\n" NOR);
                set("value", 800000);
                set("armor_prop/armor", 800);
                set("armor_prop/str", 7);
                set("armor_prop/dex", 7);
                set("armor_prop/int", 7);                                
                set("armor_prop/con", 7);
                set("limit", ([
                        "exp"  :   100000000,
                        "scborn" : 1,
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}