// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猫[2;37;0m[2;37;0m", ({"xiaom"}));        
        set("gender", "男性");                
        set("long", "小猫[2;37;0m
它是和尚的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "koasi");
        set("owner_name", "和尚");
        set_temp("owner", "koasi");
        set_temp("owner_name", "和尚");
        ::setup();
}
