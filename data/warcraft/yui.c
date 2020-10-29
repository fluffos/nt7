// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"l_south"}));        
        set("gender", "男性");                
        set("long", "魔幻兽魔幻兽 [2;37;0m
它是小唯的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "yui");
        set("owner_name", "小唯");
        set_temp("owner", "yui");
        set_temp("owner_name", "小唯");
        ::setup();
}
