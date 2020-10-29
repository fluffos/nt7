// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("闲云野鹤[2;37;0m[2;37;0m", ({"zyfhe"}));        
        set("gender", "女性");                
        set("long", "雨花石的坐骑[2;37;0m
它是雨花石的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zyf");
        set("owner_name", "雨花石");
        set_temp("owner", "zyf");
        set_temp("owner_name", "雨花石");
        ::setup();
}
