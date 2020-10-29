// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎大帝[2;37;0m[2;37;0m", ({"lord"}));        
        set("gender", "男性");                
        set("long", "白虎大帝[2;37;0m
它是将臣的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "vampire");
        set("owner_name", "将臣");
        set_temp("owner", "vampire");
        set_temp("owner_name", "将臣");
        ::setup();
}
