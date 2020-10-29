// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m十小月份[2;37;0m[2;37;0m", ({"octa"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是十月份的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "oct");
        set("owner_name", "十月份");
        set_temp("owner", "oct");
        set_temp("owner_name", "十月份");
        ::setup();
}
