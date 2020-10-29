// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("乌龟[2;37;0m[2;37;0m", ({"cnn"}));        
        set("gender", "男性");                
        set("long", "好老的乌龟啊.......[2;37;0m
它是少林的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "shaolinmi");
        set("owner_name", "少林");
        set_temp("owner", "shaolinmi");
        set_temp("owner_name", "少林");
        ::setup();
}
