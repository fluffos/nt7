// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("凤凰[2;37;0m[2;37;0m", ({"phoenix"}));        
        set("gender", "男性");                
        set("long", "凤凰[2;37;0m
它是潇潇子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "glfly");
        set("owner_name", "潇潇子");
        set_temp("owner", "glfly");
        set_temp("owner_name", "潇潇子");
        ::setup();
}
