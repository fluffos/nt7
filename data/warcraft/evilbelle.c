// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m极度[5m[1;32m诱[1;33m惑[2;37;0m[2;37;0m[2;37;0m", ({"lovely"}));        
        set("gender", "女性");                
        set("long", "极度诱惑![2;37;0m
它是娇媚小妞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evilbelle");
        set("owner_name", "娇媚小妞");
        set_temp("owner", "evilbelle");
        set_temp("owner_name", "娇媚小妞");
        ::setup();
}
