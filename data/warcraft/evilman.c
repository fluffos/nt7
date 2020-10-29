// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("迅影[2;37;0m[2;37;0m", ({"gogoro"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是谢达的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "evilman");
        set("owner_name", "谢达");
        set_temp("owner", "evilman");
        set_temp("owner_name", "谢达");
        ::setup();
}
