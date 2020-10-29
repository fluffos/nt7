// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m血莺[2;37;0m[2;37;0m", ({"bloodeve"}));        
        set("gender", "女性");                
        set("long", "血色老莺[2;37;0m
它是盘子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "disk");
        set("owner_name", "盘子");
        set_temp("owner", "disk");
        set_temp("owner_name", "盘子");
        ::setup();
}
