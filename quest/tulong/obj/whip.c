// Jay May 27, 96

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("绸带", ({ "whip" }));
        set_weight(300);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "条");
                set("long", "这是一条素色的绸带，是舞蹈时的道具。\n");
                set("value", 300);
                set("material", "cloth");
                set("wield_msg", "$N浅笑嫣然，右手轻扬，舞出一条$n。\n");
                set("unwield_msg", "$N将手中的$n绕在腰间。\n");
        }
        init_whip(40);
        setup();
}