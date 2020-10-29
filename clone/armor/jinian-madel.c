#include <armor.h>
#include <ansi.h>

inherit MEDAL;

void create()
{
        set_name(HIM "炎黄纪念勋章" NOR, ({ "jinian medal" }));
        set("long", HIM "这是一枚炎黄官方赠送的纪念勋章，赠予那些对炎黄发展做出贡献的玩家。\n" NOR);
        set_weight(500);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "枚");
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/damage", 100);
                set("armor_prop/con", 3);
                set("armor_prop/dex", 3);
                set("armor_prop/str", 3);
                set("armor_prop/int", 3);

        }
        setup();
}        

int query_autoload()
{
        return 1;
}