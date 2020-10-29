// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m仙女[2;37;0m[2;37;0m", ({"meiren"}));        
        set("gender", "女性");                
        set("long", "仙女下凡[2;37;0m
它是吸轱辘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lwubo");
        set("owner_name", "吸轱辘");
        set_temp("owner", "lwubo");
        set_temp("owner_name", "吸轱辘");
        ::setup();
}
