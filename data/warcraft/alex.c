// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m天[2;37;0m[1;35m涯[1;36m海[1;31m角[2;37;0m[2;37;0m", ({"sky"}));        
        set("gender", "男性");                
        set("long", "天涯海角~天涯海角[2;37;0m
它是路过而已的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "alex");
        set("owner_name", "路过而已");
        set_temp("owner", "alex");
        set_temp("owner_name", "路过而已");
        ::setup();
}
