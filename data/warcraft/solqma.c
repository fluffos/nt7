// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("顶替[2;37;0m[2;37;0m", ({"gasdf"}));        
        set("gender", "男性");                
        set("long", "顶替[2;37;0m
它是完美名字的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "solqma");
        set("owner_name", "完美名字");
        set_temp("owner", "solqma");
        set_temp("owner_name", "完美名字");
        ::setup();
}
