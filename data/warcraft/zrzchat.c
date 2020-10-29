// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("女优[2;37;0m[2;37;0m", ({"avgirl"}));        
        set("gender", "女性");                
        set("long", "女优[2;37;0m
它是明粽的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zrzchat");
        set("owner_name", "明粽");
        set_temp("owner", "zrzchat");
        set_temp("owner_name", "明粽");
        ::setup();
}
