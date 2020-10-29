// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m狂[1;33m飙[1;31m网[1;34m速[2;37;0m[2;37;0m", ({"ldds"}));        
        set("gender", "男性");                
        set("long", "快快快。[2;37;0m
它是六灯大师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "liudeng");
        set("owner_name", "六灯大师");
        set_temp("owner", "liudeng");
        set_temp("owner_name", "六灯大师");
        ::setup();
}
