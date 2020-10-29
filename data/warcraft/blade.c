// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("狂风[2;37;0m[2;37;0m", ({"oko"}));        
        set("gender", "男性");                
        set("long", "厉害的[2;37;0m
它是小李飞刀的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "blade");
        set("owner_name", "小李飞刀");
        set_temp("owner", "blade");
        set_temp("owner_name", "小李飞刀");
        ::setup();
}
