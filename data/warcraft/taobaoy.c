// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m余额宝[2;37;0m[2;37;0m", ({"goldyi"}));        
        set("gender", "男性");                
        set("long", "余额余额，多乎哉，不多矣！[2;37;0m
它是淘宝太一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "taobaoy");
        set("owner_name", "淘宝太一");
        set_temp("owner", "taobaoy");
        set_temp("owner_name", "淘宝太一");
        ::setup();
}
