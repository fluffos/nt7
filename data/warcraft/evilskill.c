// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;35m小妞[1;34m别[1;31m跑[2;37;0m[2;37;0m[2;37;0m", ({"evils"}));        
        set("gender", "男性");                
        set("long", "小妞尖叫是必须的！[2;37;0m
它是小妞看招的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evilskill");
        set("owner_name", "小妞看招");
        set_temp("owner", "evilskill");
        set_temp("owner_name", "小妞看招");
        ::setup();
}
