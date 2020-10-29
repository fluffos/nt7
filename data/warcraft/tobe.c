// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小静[2;37;0m[2;37;0m", ({"ching"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是谢云的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tobe");
        set("owner_name", "谢云");
        set_temp("owner", "tobe");
        set_temp("owner_name", "谢云");
        ::setup();
}
