// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m极度[5m[1;33m诱[1;36m惑[2;37;0m[2;37;0m[2;37;0m", ({"lovely"}));        
        set("gender", "女性");                
        set("long", "极度诱惑![2;37;0m
它是清纯小妞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evilvirgin");
        set("owner_name", "清纯小妞");
        set_temp("owner", "evilvirgin");
        set_temp("owner_name", "清纯小妞");
        ::setup();
}
