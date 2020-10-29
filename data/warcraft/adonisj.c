// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m大肥肥[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "大肥肥[2;37;0m
它是阿多十的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "adonisj");
        set("owner_name", "阿多十");
        set_temp("owner", "adonisj");
        set_temp("owner_name", "阿多十");
        ::setup();
}
