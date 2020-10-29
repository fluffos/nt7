// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m青鸟[2;37;0m[2;37;0m", ({"bird"}));        
        set("gender", "男性");                
        set("long", "一直可爱的鸟。[2;37;0m
它是吕二娘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wen");
        set("owner_name", "吕二娘");
        set_temp("owner", "wen");
        set_temp("owner_name", "吕二娘");
        ::setup();
}
