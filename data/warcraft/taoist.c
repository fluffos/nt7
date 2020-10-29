// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("流云[2;37;0m[2;37;0m", ({"tofly"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是谢道一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "taoist");
        set("owner_name", "谢道一");
        set_temp("owner", "taoist");
        set_temp("owner_name", "谢道一");
        ::setup();
}
