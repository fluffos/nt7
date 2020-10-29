// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m龙门掌教[2;37;0m[2;37;0m", ({"daoista"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是马淳一的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "daoist");
        set("owner_name", "马淳一");
        set_temp("owner", "daoist");
        set_temp("owner_name", "马淳一");
        ::setup();
}
