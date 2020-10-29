// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m阿莱克斯塔萨[2;37;0m[2;37;0m", ({"alksts"}));        
        set("gender", "女性");                
        set("long", "红龙女王阿莱克斯塔萨[2;37;0m
它是江月的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jiangyue");
        set("owner_name", "江月");
        set_temp("owner", "jiangyue");
        set_temp("owner_name", "江月");
        ::setup();
}
