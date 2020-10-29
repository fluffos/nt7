// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血傻[2;37;0m[2;37;0m", ({"super"}));        
        set("gender", "男性");                
        set("long", "血[2;37;0m
它是无兽的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wjwjwj");
        set("owner_name", "无兽");
        set_temp("owner", "wjwjwj");
        set_temp("owner_name", "无兽");
        ::setup();
}
