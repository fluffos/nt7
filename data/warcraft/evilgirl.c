// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m极度[5m[1;35m诱[1;31m惑[2;37;0m[2;37;0m[2;37;0m", ({"lovely"}));        
        set("gender", "女性");                
        set("long", "极度诱惑[2;37;0m
它是销魂小妞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evilgirl");
        set("owner_name", "销魂小妞");
        set_temp("owner", "evilgirl");
        set_temp("owner_name", "销魂小妞");
        ::setup();
}
