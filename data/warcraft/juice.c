// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狮王[2;37;0m[2;37;0m", ({"lion"}));        
        set("gender", "女性");                
        set("long", "万寿之王?[2;37;0m
它是心宝贝的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "juice");
        set("owner_name", "心宝贝");
        set_temp("owner", "juice");
        set_temp("owner_name", "心宝贝");
        ::setup();
}
