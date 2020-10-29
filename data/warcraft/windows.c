// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m导师[2;37;0m[2;37;0m", ({"dos"}));        
        set("gender", "男性");                
        set("long", "我的坐骑[2;37;0m
它是晕倒死的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "windows");
        set("owner_name", "晕倒死");
        set_temp("owner", "windows");
        set_temp("owner_name", "晕倒死");
        ::setup();
}
