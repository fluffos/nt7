// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m极度[5m[1;35m诱[1;31m惑[2;37;0m[2;37;0m[2;37;0m", ({"lovely"}));        
        set("gender", "女性");                
        set("long", "极度诱惑[2;37;0m
它是火辣小妞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "evillass");
        set("owner_name", "火辣小妞");
        set_temp("owner", "evillass");
        set_temp("owner_name", "火辣小妞");
        ::setup();
}
