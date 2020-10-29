// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m活期宝[2;37;0m[2;37;0m", ({"silverer"}));        
        set("gender", "男性");                
        set("long", "活期活期，死不可期！[2;37;0m
它是淘宝仲二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "taobaoe");
        set("owner_name", "淘宝仲二");
        set_temp("owner", "taobaoe");
        set_temp("owner_name", "淘宝仲二");
        ::setup();
}
