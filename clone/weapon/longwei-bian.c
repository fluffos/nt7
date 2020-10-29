#include <ansi.h>
#include <weapon.h>
inherit WHIP;

void create()
{
        set_name(HIY "龙尾长鞭", ({ "longwei bian", "bian","longwei" }));
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "根");
                set("long", HIY "这是一根做工奇特的长鞭，据说是用龙尾所铸，威力不菲。\n" NOR);
                set("wield_msg", "$N「唰」的一声从腰后抽出一根$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n别回腰后。\n");
                set("value", 100000);
        }
        init_whip(300);
        setup();
}

int query_autoload()
{
        return 1;
}
