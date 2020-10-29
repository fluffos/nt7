// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱[1;31m雀[1;31m[2;37;0m[2;37;0m", ({"que"}));        
        set("gender", "男性");                
        set("long", "火红火红的鸟[2;37;0m
它是胡一刃的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xjearl");
        set("owner_name", "胡一刃");
        set_temp("owner", "xjearl");
        set_temp("owner_name", "胡一刃");
        ::setup();
}
