// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻[2;37;0m[2;37;0m", ({"qilinid"}));        
        set("gender", "女性");                
        set("long", "魔[2;37;0m
它是波恩弟弟的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "bedd");
        set("owner_name", "波恩弟弟");
        set_temp("owner", "bedd");
        set_temp("owner_name", "波恩弟弟");
        ::setup();
}
